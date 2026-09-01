<?php
header('Content-Type: application/json; charset=utf-8');

require_once __DIR__ . '/../config/database.php';
require_once __DIR__ . '/../includes/crypto.php';
require_once __DIR__ . '/../includes/ehr.php';
require_once __DIR__ . '/../includes/logger.php';

try {
    if ($_SERVER['REQUEST_METHOD'] !== 'POST') {
        throw new Exception("Invalid request method. POST required.");
    }

    $rawInput = file_get_contents('php://input');
    $inputData = json_decode($rawInput, true);

    if (!is_array($inputData) || !isset($inputData['document'])) {
        throw new Exception("Invalid verification payload. 'document' is required.");
    }

    $recordId = isset($inputData['record_id']) ? (int)$inputData['record_id'] : null;
    $document = $inputData['document'];

    $db = getDbConnection();
    $originalSha256 = $inputData['original_sha256'] ?? null;
    $originalSignature = $inputData['original_signature'] ?? null;
    $publicKey = $inputData['public_key'] ?? null;

    if ($db && $recordId) {
        $stmt = $db->prepare("SELECT * FROM ehr_records WHERE id = :id");
        $stmt->execute([':id' => $recordId]);
        $record = $stmt->fetch();
        if ($record) {
            $originalSha256 = $record['sha256_hash'];
            $originalSignature = $record['digital_signature'];
            $publicKey = $record['public_key'];
        }
    }

    if (!$originalSignature || !$publicKey) {
        throw new Exception("Missing cryptographic signature or public key for verification.");
    }

    $ehrManager = new EhrManager();
    $currentCanonicalJson = $ehrManager->buildCanonicalJson($document);

    $crypto = new SecureCrypto();
    $currentSha256 = $crypto->hashSha256($currentCanonicalJson);
    $currentSha512 = $crypto->hashSha512($currentCanonicalJson);

    $signatureValid = $crypto->verifySignature($currentCanonicalJson, $originalSignature, $publicKey);
    $hashMatches = ($originalSha256 !== null && hash_equals($originalSha256, $currentSha256));

    $isAuthentic = ($signatureValid && $hashMatches);

    if ($db) {
        $logger = new SecurityLogger($db);
        if ($isAuthentic) {
            $logger->log('SIGNATURE_VERIFIED', 'SUCCESS', "Original EHR signature verified successfully for Record #{$recordId}", $recordId);
        } else {
            $logger->log('SIGNATURE_FAILED', 'FAILED', "Signature verification failed! EHR document payload hash mismatch.", $recordId);
            $logger->log('TAMPERING_DETECTED', 'ALERT', "UNAUTHORIZED MODIFICATION DETECTED: Document content does not match original signature.", $recordId);
        }
    }

    echo json_encode([
        'success' => true,
        'data' => [
            'is_authentic' => $isAuthentic,
            'document_status' => $isAuthentic ? 'AUTHENTIC' : 'TAMPERED',
            'integrity_status' => $isAuthentic ? 'INTACT' : 'COMPROMISED',
            'hash_match' => $hashMatches,
            'signature_valid' => $signatureValid,
            'original_sha256' => $originalSha256,
            'current_sha256' => $currentSha256,
            'current_sha512' => $currentSha512,
            'current_canonical_document' => $currentCanonicalJson,
            'message' => $isAuthentic 
                ? 'Document is authentic. Signature and hash match perfectly.' 
                : 'Unauthorized modification detected! Document hash does not match original digital signature.'
        ]
    ]);
} catch (Exception $e) {
    http_response_code(400);
    echo json_encode([
        'success' => false,
        'message' => $e->getMessage()
    ]);
}
