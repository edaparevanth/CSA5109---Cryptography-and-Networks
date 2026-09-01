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

    $recordId = isset($inputData['record_id']) ? (int)$inputData['record_id'] : null;

    $db = getDbConnection();
    $record = null;

    if ($db && $recordId) {
        $stmt = $db->prepare("SELECT * FROM ehr_records WHERE id = :id");
        $stmt->execute([':id' => $recordId]);
        $record = $stmt->fetch();
    }

    if ($record) {
        $doc = [
            'patient_id'   => $record['patient_id'],
            'patient_name' => $record['patient_name'],
            'age'          => (int)$record['age'],
            'diagnosis'    => $record['diagnosis'],
            'prescription' => $record['prescription'],
            'doctor_name'  => $record['doctor_name'],
            'hospital'     => $record['hospital'],
            'date'         => $record['record_date']
        ];
        $canonical = $record['canonical_document'];
        $sha256 = $record['sha256_hash'];
        $sha512 = $record['sha512_hash'];
        $sig = $record['digital_signature'];
        $pub = $record['public_key'];
        $keyId = $record['key_id'];
    } else {
        // Fallback default demo document if no DB record found
        $doc = [
            'patient_id'   => 'P1001',
            'patient_name' => 'Rahul Sharma',
            'age'          => 42,
            'diagnosis'    => 'Hypertension',
            'prescription' => 'Amlodipine 5mg',
            'doctor_name'  => 'Dr. Kumar',
            'hospital'     => 'ABC Medical Center',
            'date'         => '31-08-2026'
        ];
        $ehrManager = new EhrManager();
        $canonical = $ehrManager->buildCanonicalJson($doc);
        $crypto = new SecureCrypto();
        $sha256 = $crypto->hashSha256($canonical);
        $sha512 = $crypto->hashSha512($canonical);
        $sig = '';
        $pub = '';
        $keyId = '';
    }

    if ($db) {
        $logger = new SecurityLogger($db);
        $logger->log('DOCUMENT_RESTORED', 'SUCCESS', "Original document restored to pristine state.", $recordId);
    }

    echo json_encode([
        'success' => true,
        'message' => 'Original document restored successfully',
        'data' => [
            'record_id' => $recordId,
            'document' => $doc,
            'canonical_document' => $canonical,
            'sha256' => $sha256,
            'sha512' => $sha512,
            'digital_signature' => $sig,
            'public_key' => $pub,
            'key_id' => $keyId
        ]
    ]);
} catch (Exception $e) {
    http_response_code(400);
    echo json_encode([
        'success' => false,
        'message' => $e->getMessage()
    ]);
}
