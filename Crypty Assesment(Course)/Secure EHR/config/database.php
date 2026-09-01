<?php
/**
 * Database Configuration & Connection Helper
 * SecureEHR - EHR Cryptographic Integrity & Digital Signature System
 */

class Database {
    private string $host = 'localhost';
    private string $db_name = 'secure_ehr';
    private string $username = 'root';
    private string $password = '';
    private ?PDO $conn = null;

    public function getConnection(): ?PDO {
        $this->conn = null;
        try {
            $dsn = "mysql:host=" . $this->host . ";dbname=" . $this->db_name . ";charset=utf8mb4";
            $options = [
                PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION,
                PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
                PDO::ATTR_EMULATE_PREPARES => false,
            ];
            $this->conn = new PDO($dsn, $this->username, $this->password, $options);
        } catch (PDOException $e) {
            // Attempt auto-connection to server without DB selected to check server status
            // Connection errors will be handled gracefully in API responses
            error_log("Database connection error: " . $e->getMessage());
            $this->conn = null;
        }
        return $this->conn;
    }

    public function getHost(): string { return $this->host; }
    public function getDbName(): string { return $this->db_name; }
}

/**
 * Global helper function to get PDO database connection
 */
function getDbConnection(): ?PDO {
    static $database = null;
    if ($database === null) {
        $database = new Database();
    }
    return $database->getConnection();
}
