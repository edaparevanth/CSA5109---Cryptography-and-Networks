<?php
header('Content-Type: application/json; charset=utf-8');

require_once __DIR__ . '/../config/database.php';
require_once __DIR__ . '/../includes/logger.php';

try {
    $db = getDbConnection();
    $logger = new SecurityLogger($db);
    $logs = $logger->getRecentLogs(25);

    echo json_encode([
        'success' => true,
        'data' => $logs
    ]);
} catch (Exception $e) {
    http_response_code(500);
    echo json_encode([
        'success' => false,
        'message' => $e->getMessage()
    ]);
}
