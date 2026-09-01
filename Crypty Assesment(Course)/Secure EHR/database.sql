-- SecureEHR Database Schema
-- EHR Cryptographic Integrity & Digital Signature System

CREATE DATABASE IF NOT EXISTS `secure_ehr` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE `secure_ehr`;

-- --------------------------------------------------------
-- Table structure for `ehr_records`
-- --------------------------------------------------------

CREATE TABLE IF NOT EXISTS `ehr_records` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `patient_id` VARCHAR(50) NOT NULL,
  `patient_name` VARCHAR(100) NOT NULL,
  `age` INT NOT NULL,
  `diagnosis` VARCHAR(255) NOT NULL,
  `prescription` TEXT NOT NULL,
  `doctor_name` VARCHAR(100) NOT NULL,
  `hospital` VARCHAR(150) NOT NULL,
  `record_date` VARCHAR(50) NOT NULL,
  `canonical_document` LONGTEXT NOT NULL,
  `sha256_hash` VARCHAR(64) NOT NULL,
  `sha512_hash` VARCHAR(128) NOT NULL,
  `digital_signature` TEXT NOT NULL,
  `public_key` TEXT NOT NULL,
  `key_id` VARCHAR(64) NOT NULL,
  `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------
-- Table structure for `security_logs`
-- --------------------------------------------------------

CREATE TABLE IF NOT EXISTS `security_logs` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `ehr_id` INT NULL,
  `event_type` VARCHAR(50) NOT NULL,
  `event_status` VARCHAR(20) NOT NULL,
  `message` TEXT NOT NULL,
  `created_at` DATETIME DEFAULT CURRENT_TIMESTAMP,
  FOREIGN KEY (`ehr_id`) REFERENCES `ehr_records`(`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
