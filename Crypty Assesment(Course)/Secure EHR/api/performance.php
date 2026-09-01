<?php
header('Content-Type: application/json; charset=utf-8');

require_once __DIR__ . '/../config/database.php';
require_once __DIR__ . '/../includes/crypto.php';
require_once __DIR__ . '/../includes/ehr.php';
require_once __DIR__ . '/../includes/logger.php';

try {
    $rawInput = file_get_contents('php://input');
    $inputData = json_decode($rawInput, true);

    $sampleDoc = [
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
    $canonicalSample = $ehrManager->buildCanonicalJson($sampleDoc);

    $crypto = new SecureCrypto();
    $benchmarkResults = $crypto->runBenchmark($canonicalSample, 5000, 30);

    $db = getDbConnection();
    if ($db) {
        $logger = new SecurityLogger($db);
        $logger->log('BENCHMARK_EXECUTED', 'SUCCESS', "Cryptographic performance benchmark completed: SHA-256 avg={$benchmarkResults['sha256_ms']}ms, RSA Sign avg={$benchmarkResults['rsa_sign_ms']}ms");
    }

    echo json_encode([
        'success' => true,
        'message' => 'Cryptographic performance benchmark completed successfully',
        'data' => $benchmarkResults
    ]);
} catch (Exception $e) {
    http_response_code(500);
    echo json_encode([
        'success' => false,
        'message' => 'Benchmark execution error: ' . $e->getMessage()
    ]);
}
