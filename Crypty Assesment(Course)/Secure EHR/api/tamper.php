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
        throw new Exception("Invalid payload. 'document' object required.");
    }

    $recordId = isset($inputData['record_id']) ? (int)$inputData['record_id'] : null;
    $originalDoc = $inputData['document'];
    $modifiedDoc = $originalDoc;

    // Pick tamper modification strategy based on current prescription/diagnosis
    $tamperedField = 'prescription';
    $oldValue = $originalDoc['prescription'] ?? '';
    $newValue = 'Amlodipine 10mg';

    if (strpos($oldValue, '10mg') !== false) {
        $newValue = 'Amlodipine 20mg';
    } elseif ($oldValue === 'Amlodipine 10mg') {
        $tamperedField = 'diagnosis';
        $oldValue = $originalDoc['diagnosis'] ?? 'Hypertension';
        $newValue = 'Diabetes Type 2';
    }

    $modifiedDoc[$tamperedField] = $newValue;

    $ehrManager = new EhrManager();
    $origCanonical = $ehrManager->buildCanonicalJson($originalDoc);
    $modCanonical = $ehrManager->buildCanonicalJson($modifiedDoc);

    $crypto = new SecureCrypto();
    $origSha256 = $crypto->hashSha256($origCanonical);
    $modSha256 = $crypto->hashSha256($modCanonical);
    $modSha512 = $crypto->hashSha512($modCanonical);

    $db = getDbConnection();
    if ($db) {
        $logger = new SecurityLogger($db);
        $logger->log('TAMPERING_SIMULATED', 'WARNING', "Simulated unauthorized modification on field '{$tamperedField}': '{$oldValue}' → '{$newValue}'", $recordId);
    }

    echo json_encode([
        'success' => true,
        'message' => 'Unauthorized document modification simulated',
        'data' => [
            'record_id' => $recordId,
            'tampered_field' => $tamperedField,
            'old_value' => $oldValue,
            'new_value' => $newValue,
            'original_document' => $originalDoc,
            'modified_document' => $modifiedDoc,
            'original_canonical' => $origCanonical,
            'modified_canonical' => $modCanonical,
            'original_sha256' => $origSha256,
            'modified_sha256' => $modSha256,
            'modified_sha512' => $modSha512
        ]
    ]);
} catch (Exception $e) {
    http_response_code(400);
    echo json_encode([
        'success' => false,
        'message' => $e->getMessage()
    ]);
}
