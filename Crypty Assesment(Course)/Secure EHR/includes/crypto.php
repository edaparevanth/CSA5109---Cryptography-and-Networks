<?php
/**
 * Cryptographic Utility Module
 * Handles Hashing, RSA 2048 Key Management, RSA Digital Signatures, and Benchmarks
 * SecureEHR - EHR Cryptographic Integrity & Digital Signature System
 */

class SecureCrypto {
    private string $keyDir;
    private ?string $opensslCnf = null;

    public function __construct() {
        $this->keyDir = __DIR__ . '/../keys';
        if (!is_dir($this->keyDir)) {
            mkdir($this->keyDir, 0700, true);
        }

        // Auto-detect openssl.cnf location on Windows/XAMPP
        $candidatePaths = [
            'C:/xampp/php/extras/ssl/openssl.cnf',
            'C:/xampp/apache/bin/openssl.cnf',
            'C:/xampp/php/openssl.cnf',
            ini_get('openssl.cafile') ?: ''
        ];
        foreach ($candidatePaths as $path) {
            if ($path && file_exists($path)) {
                $this->opensslCnf = $path;
                putenv("OPENSSL_CONF=" . $path);
                break;
            }
        }
    }

    /**
     * Compute SHA-256 hash digest (64 hex characters)
     */
    public function hashSha256(string $data): string {
        return hash('sha256', $data);
    }

    /**
     * Compute SHA-512 hash digest (128 hex characters)
     */
    public function hashSha512(string $data): string {
        return hash('sha512', $data);
    }

    /**
     * Generate an RSA 2048-bit key pair.
     * The private key is saved on the server filesystem with restricted permissions.
     * Returns array ['key_id', 'public_key']
     */
    public function generateKeyPair(): array {
        $config = [
            "digest_alg" => "sha256",
            "private_key_bits" => 2048,
            "private_key_type" => OPENSSL_KEYTYPE_RSA,
        ];
        if ($this->opensslCnf) {
            $config["config"] = $this->opensslCnf;
        }

        $res = openssl_pkey_new($config);
        if (!$res) {
            throw new Exception("Failed to generate RSA key pair: " . openssl_error_string());
        }

        // Export Private Key
        $exported = openssl_pkey_export($res, $privateKeyPem, null, $config);
        if (!$exported) {
            throw new Exception("Failed to export RSA private key: " . openssl_error_string());
        }

        // Export Public Key
        $keyDetails = openssl_pkey_get_details($res);
        $publicKeyPem = $keyDetails['key'];

        // Generate unique key ID
        $keyId = bin2hex(random_bytes(16));
        $keyFile = $this->keyDir . '/key_' . $keyId . '.pem';

        // Write private key to restricted server location
        file_put_contents($keyFile, $privateKeyPem);
        @chmod($keyFile, 0600);

        return [
            'key_id' => $keyId,
            'public_key' => $publicKeyPem
        ];
    }

    /**
     * Retrieve private key for a key_id
     */
    private function getPrivateKey(string $keyId): ?OpenSSLAsymmetricKey {
        $keyFile = $this->keyDir . '/key_' . $keyId . '.pem';
        if (!file_exists($keyFile)) {
            return null;
        }
        $pem = file_get_contents($keyFile);
        $key = openssl_pkey_get_private($pem);
        return $key ?: null;
    }

    /**
     * Create Digital Signature using RSA-2048 + SHA-256
     * Signature is returned as Base64 string
     */
    public function signData(string $data, string $keyId): string {
        $privateKey = $this->getPrivateKey($keyId);
        if (!$privateKey) {
            throw new Exception("Private key for ID '{$keyId}' not found on server.");
        }

        $signature = '';
        $success = openssl_sign($data, $signature, $privateKey, OPENSSL_ALGO_SHA256);

        if (!$success) {
            throw new Exception("Failed to generate digital signature: " . openssl_error_string());
        }

        return base64_encode($signature);
    }

    /**
     * Verify Digital Signature against public key and data
     * Returns true if valid, false if tampered or invalid
     */
    public function verifySignature(string $data, string $base64Signature, string $publicKeyPem): bool {
        $signature = base64_decode($base64Signature);
        $publicKey = openssl_pkey_get_public($publicKeyPem);
        if (!$publicKey) {
            return false;
        }

        $result = openssl_verify($data, $signature, $publicKey, OPENSSL_ALGO_SHA256);
        return ($result === 1);
    }

    /**
     * Measure actual cryptographic performance execution time (in milliseconds)
     */
    public function runBenchmark(string $sampleData, int $hashIterations = 1000, int $rsaIterations = 10): array {
        // Benchmark MD5
        $t0 = microtime(true);
        for ($i = 0; $i < $hashIterations; $i++) {
            hash('md5', $sampleData);
        }
        $md5Time = ((microtime(true) - $t0) / $hashIterations) * 1000;

        // Benchmark SHA-1
        $t0 = microtime(true);
        for ($i = 0; $i < $hashIterations; $i++) {
            hash('sha1', $sampleData);
        }
        $sha1Time = ((microtime(true) - $t0) / $hashIterations) * 1000;

        // Benchmark SHA-256
        $t0 = microtime(true);
        for ($i = 0; $i < $hashIterations; $i++) {
            hash('sha256', $sampleData);
        }
        $sha256Time = ((microtime(true) - $t0) / $hashIterations) * 1000;

        // Benchmark SHA-512
        $t0 = microtime(true);
        for ($i = 0; $i < $hashIterations; $i++) {
            hash('sha512', $sampleData);
        }
        $sha512Time = ((microtime(true) - $t0) / $hashIterations) * 1000;

        // Benchmark RSA Key Gen + Sign + Verify
        $keyPair = $this->generateKeyPair();
        $keyId = $keyPair['key_id'];
        $pubKey = $keyPair['public_key'];
        $sig = $this->signData($sampleData, $keyId);

        // RSA Sign timing
        $t0 = microtime(true);
        for ($i = 0; $i < $rsaIterations; $i++) {
            $this->signData($sampleData, $keyId);
        }
        $rsaSignTime = ((microtime(true) - $t0) / $rsaIterations) * 1000;

        // RSA Verify timing
        $t0 = microtime(true);
        for ($i = 0; $i < $rsaIterations; $i++) {
            $this->verifySignature($sampleData, $sig, $pubKey);
        }
        $rsaVerifyTime = ((microtime(true) - $t0) / $rsaIterations) * 1000;

        // Cleanup temp key file
        $tempKeyFile = $this->keyDir . '/key_' . $keyId . '.pem';
        if (file_exists($tempKeyFile)) {
            @unlink($tempKeyFile);
        }

        return [
            'md5_ms' => round($md5Time, 5),
            'sha1_ms' => round($sha1Time, 5),
            'sha256_ms' => round($sha256Time, 5),
            'sha512_ms' => round($sha512Time, 5),
            'rsa_sign_ms' => round($rsaSignTime, 3),
            'rsa_verify_ms' => round($rsaVerifyTime, 3),
            'hash_iterations' => $hashIterations,
            'rsa_iterations' => $rsaIterations
        ];
    }
}
