# SecureEHR — EHR Cryptographic Integrity & Digital Signature System

**SecureEHR** is a web-based cybersecurity application demonstrating how cryptographic hash functions (SHA-256, SHA-512) and digital signatures (RSA 2048-bit + SHA-256) protect Electronic Health Record (EHR) documents from unauthorized modification and in-transit tampering.

This application is designed for academic cybersecurity demonstrations on a local **XAMPP** environment (Apache, PHP 8.x, MySQL).

---

## Key Features

- **EHR Document Lifecycle**: Create, canonicalize, hash, sign, verify, tamper, and restore EHR records.
- **Deterministic Canonicalization**: Strict JSON field ordering ensuring identical byte representation during signing and verification.
- **Dual Cryptographic Hashing**: Dynamic computation of SHA-256 (64 hex characters) and SHA-512 (128 hex characters) digests.
- **RSA Digital Signatures**: On-demand 2048-bit RSA key pair generation and digital signature generation using PHP OpenSSL.
- **Secure Server-Side Key Storage**: Private keys are saved strictly on the server in the `keys/` directory (protected from HTTP web access via `.htaccess`). Private keys are never stored in MySQL in plaintext nor exposed to the client interface.
- **In-Transit Tampering Simulation**: Live demonstration of modifying prescription or diagnosis fields without generating a new signature, proving how digital signatures fail verification when tampering occurs.
- **Restoration & Verification**: One-click restoration of the original document back to valid authentic status.
- **Hash Algorithm Comparison**: Comparative matrix analyzing MD5, SHA-1, SHA-256, and SHA-512 security, collision resistance, and status.
- **Real-Time Performance Analysis**: Microsecond runtime execution benchmark for MD5, SHA-1, SHA-256, SHA-512, RSA Signing, and RSA Verification.
- **Security Audit Activity Log**: Persistent event auditing stored in MySQL `security_logs` table.

---

## Tech Stack

- **Server Environment**: XAMPP (Apache + PHP 8.x + MySQL)
- **Backend Language**: PHP 8.x (using PDO & OpenSSL extension)
- **Frontend Interface**: HTML5, CSS3 (Vanilla + Custom Cybersecurity Theme), JavaScript (Vanilla JS `fetch()`), Bootstrap 5
- **Database**: MySQL (`secure_ehr` database)

---

## Directory Structure

```text
secure-ehr/
│
├── index.php                 # Single-page Cybersecurity Dashboard UI
│
├── config/
│   └── database.php          # PDO database connection helper
│
├── api/
│   ├── create_record.php     # Validates, canonicalizes, hashes, signs & stores EHR
│   ├── verify.php            # Verifies RSA digital signature & hash matching
│   ├── tamper.php            # Simulates unauthorized field modification
│   ├── restore.php           # Restores pristine original EHR record
│   ├── performance.php       # Measures live execution times of crypto operations
│   └── logs.php              # Retrieves audit activity logs
│
├── includes/
│   ├── crypto.php            # OpenSSL RSA signing/verification & hashing engine
│   ├── ehr.php               # Validation & canonical JSON builder
│   └── logger.php            # MySQL security activity audit logger
│
├── assets/
│   ├── css/
│   │   └── style.css         # Cybersecurity theme styling
│   └── js/
│       └── app.js            # Asynchronous frontend state & API handler
│
├── keys/
│   └── .htaccess             # Apache security rule denying HTTP access to private keys
│
├── database.sql              # Database creation & SQL schema import file
└── README.md                 # Complete project documentation
```

---

## Installation & Setup Guide (XAMPP)

### Step 1: XAMPP Setup
1. Launch the **XAMPP Control Panel**.
2. Start the **Apache** server (`Port 80`).
3. Start the **MySQL** server (`Port 3306`).

### Step 2: Copy Project Directory
Copy the `secure-ehr` folder into your local XAMPP web root:
```text
C:\xampp\htdocs\secure-ehr\
```

### Step 3: Import Database Schema
1. Open **phpMyAdmin** in your web browser:
   ```text
   http://localhost/phpmyadmin/
   ```
2. Click the **Import** tab at the top.
3. Choose the `database.sql` file from `C:\xampp\htdocs\secure-ehr\database.sql`.
4. Click **Go** to create the `secure_ehr` database and tables (`ehr_records` and `security_logs`).

*(Alternatively, run the SQL script via MySQL command line).*

### Step 4: Configure Database Connection (Optional)
If your XAMPP MySQL root password is non-empty, edit `config/database.php`:
```php
private string $host = 'localhost';
private string $db_name = 'secure_ehr';
private string $username = 'root';
private string $password = 'YOUR_PASSWORD';
```

### Step 5: Launch Application
Open your web browser and navigate to:
```text
http://localhost/secure-ehr/
```

---

## Step-by-Step Demonstration Walkthrough (2-Minute Test Flow)

1. **Open Dashboard**: Navigate to `http://localhost/secure-ehr/`. Note initial status: `EHR Status: READY`, `Signature: NOT SIGNED`.
2. **Load Demo Data**: Click **Load Demo EHR** (populates Patient ID `P1001`, Patient Name `Rahul Sharma`, Prescription `Amlodipine 5mg`).
3. **Generate Security Record**: Click **Generate Security Record**.
   - Generates SHA-256 (64 hex characters) & SHA-512 (128 hex characters).
   - Generates RSA-2048 asymmetric key pair.
   - Signs the canonical document using the private key.
   - Automatically verifies the original EHR, displaying:
     - `✓ SIGNATURE VERIFIED SUCCESSFULLY`
     - Status updates to `SECURE`, `VERIFIED`, and `INTACT`.
4. **Simulate Tampering Attack**: Click **Simulate Unauthorized Modification**.
   - Modifies `Amlodipine 5mg` to `Amlodipine 10mg` in the modified payload copy.
   - Displays side-by-side comparison highlighting the tampered prescription.
   - Shows SHA-256 hash mismatch (`FALSE`).
   - Automatically executes verification using the **ORIGINAL signature**, producing:
     - `✕ SIGNATURE VERIFICATION FAILED`
     - Status updates to `TAMPERED`, `INVALID`, and `COMPROMISED`.
5. **Restore Original EHR**: Click **Restore Original EHR**.
   - Resets state to the original database record.
   - Re-verifies signature, returning system to `SECURE` / `INTACT` status.
6. **Run Performance Analysis**: Scroll to **7. Performance & Overhead Analysis** and click **Run Performance Benchmark**.
   - Measures real runtime execution speeds in milliseconds for MD5, SHA-1, SHA-256, SHA-512, RSA Sign, and RSA Verify.
7. **View Security Activity Log**: Scroll to **9. System Audit Activity Log** to inspect recorded audit events (`EHR_CREATED`, `DOCUMENT_SIGNED`, `SIGNATURE_VERIFIED`, `TAMPERING_SIMULATED`, `TAMPERING_DETECTED`, `DOCUMENT_RESTORED`).

---

## Academic Security Evaluation Summary

| Security Criterion | Hash Functions (SHA-256) | Digital Signatures (RSA-2048) |
| :--- | :--- | :--- |
| **Integrity** | ✓ Detects document modifications | ✓ Detects document modifications |
| **Authentication** | ✕ No identity validation | ✓ Validates signer's private key |
| **Non-repudiation** | ✕ No proof of origin | ✓ Provides legal proof of authorship |
| **Tamper Detection** | ✓ Hash mismatch on change | ✓ Verification fails on change |
| **Overhead** | &lt; 0.05 ms (Ultra-fast) | ~7 ms Sign / ~2.5 ms Verify |

**Recommended Configuration**: `SHA-256` digest + `RSA-2048` signature with `RSA-PSS` padding.
