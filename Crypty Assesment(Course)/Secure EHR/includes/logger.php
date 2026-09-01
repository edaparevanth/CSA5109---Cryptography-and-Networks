<?php
/**
 * Security Audit Logger Module
 * SecureEHR - EHR Cryptographic Integrity & Digital Signature System
 */

class SecurityLogger {
    private ?PDO $db;

    public function __construct(?PDO $db = null) {
        $this->db = $db ?: getDbConnection();
    }

    /**
     * Log a security event to database
     */
    public function log(string $eventType, string $eventStatus, string $message, ?int $ehrId = null): bool {
        if (!$this->db) {
            return false;
        }

        try {
            $stmt = $this->db->prepare("
                INSERT INTO security_logs (ehr_id, event_type, event_status, message, created_at)
                VALUES (:ehr_id, :event_type, :event_status, :message, NOW())
            ");
            return $stmt->execute([
                ':ehr_id' => $ehrId,
                ':event_type' => $eventType,
                ':event_status' => strtoupper($eventStatus),
                ':message' => $message
            ]);
        } catch (PDOException $e) {
            error_log("Failed to insert security log: " . $e->getMessage());
            return false;
        }
    }

    /**
     * Retrieve recent logs (limit 20)
     */
    public function getRecentLogs(int $limit = 20): array {
        if (!$this->db) {
            return [];
        }

        try {
            $stmt = $this->db->prepare("
                SELECT l.id, l.ehr_id, l.event_type, l.event_status, l.message, 
                       DATE_FORMAT(l.created_at, '%H:%i:%s') as log_time,
                       e.patient_id
                FROM security_logs l
                LEFT JOIN ehr_records e ON l.ehr_id = e.id
                ORDER BY l.id DESC
                LIMIT :limit
            ");
            $stmt->bindValue(':limit', $limit, PDO::PARAM_INT);
            $stmt->execute();
            return $stmt->fetchAll(PDO::FETCH_ASSOC);
        } catch (PDOException $e) {
            error_log("Failed to fetch security logs: " . $e->getMessage());
            return [];
        }
    }
}
