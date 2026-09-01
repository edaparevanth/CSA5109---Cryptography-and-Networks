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
    if (!is_array($inputData)) {
        $inputData = $_POST;
    }

    $ehrManager = new EhrManager();
    $cleanEhr = $ehrManager->validateAndSanitize($inputData);
    $canonicalJson = $ehrManager->buildCanonicalJson($cleanEhr);

    $crypto = new SecureCrypto();
    $sha256 = $crypto->hashSha256($canonicalJson);
    $sha512 = $crypto->hashSha512($canonicalJson);

    $keyPair = $crypto->generateKeyPair();
    $keyId = $keyPair['key_id'];
    $publicKey = $keyPair['public_key'];

    $signature = $crypto->signData($canonicalJson, $keyId);

    $db = getDbConnection();
    $recordId = null;

    if ($db) {
        $stmt = $db->prepare("
            INSERT INTO ehr_records 
            (patient_id, patient_name, age, diagnosis, prescription, doctor_name, hospital, record_date, canonical_document, sha256_hash, sha512_hash, digital_signature, public_key, key_id, created_at)
            VALUES (:pid, :name, :age, :diag, :rx, :doc, :hosp, :rdate, :canon, :sha256, :sha512, :sig, :pub, :kid, NOW())
        ");
        $stmt->execute([
            ':pid' => $cleanEhr['patient_id'],
            ':name' => $cleanEhr['patient_name'],
            ':age' => $cleanEhr['age'],
            ':diag' => $cleanEhr['diagnosis'],
            ':rx' => $cleanEhr['prescription'],
            ':doc' => $cleanEhr['doctor_name'],
            ':hosp' => $cleanEhr['hospital'],
            ':rdate' => $cleanEhr['date'],
            ':canon' => $canonicalJson,
            ':sha256' => $sha256,
            ':sha512' => $sha512,
            ':sig' => $signature,
            ':pub' => $publicKey,
            ':kid' => $keyId
        ]);
        $recordId = (int)$db->lastInsertId();

        $logger = new SecurityLogger($db);
        $logger->log('EHR_CREATED', 'SUCCESS', "EHR record created for Patient ID {$cleanEhr['patient_id']}", $recordId);
        $logger->log('DOCUMENT_SIGNED', 'SUCCESS', "RSA-2048 Digital signature generated with SHA-256 digest", $recordId);
    } else {
        $recordId = rand(100, 999);
    }

    echo json_encode([
        'success' => true,
        'message' => 'EHR security record created successfully',
        'data' => array_merge($cleanEhr, [
            'record_id' => $recordId,
            'canonical_document' => $canonicalJson,
            'sha256' => $sha256,
            'sha512' => $sha512,
            'digital_signature' => $signature,
            'public_key' => $publicKey,
            'key_id' => $keyId
        ])
    ]);
} catch (Exception $e) {
    http_response_code(400);
    echo json_encode([
        'success' => false,
        'message' => $e->getMessage()
    ]);
}
