<?php
/**
 * EHR Record Validation & Canonicalization Helper
 * SecureEHR - EHR Cryptographic Integrity & Digital Signature System
 */

class EhrManager {
    /**
     * Validate raw input array for EHR creation
     * Returns array of sanitized data or throws Exception if invalid
     */
    public function validateAndSanitize(array $input): array {
        $fields = [
            'patient_id' => 'Patient ID',
            'patient_name' => 'Patient Name',
            'age' => 'Age',
            'diagnosis' => 'Diagnosis',
            'prescription' => 'Prescription',
            'doctor_name' => 'Doctor Name',
            'hospital' => 'Hospital',
            'date' => 'Date'
        ];

        $clean = [];
        foreach ($fields as $key => $label) {
            if (!isset($input[$key]) || trim((string)$input[$key]) === '') {
                throw new Exception("Validation Error: '{$label}' is required.");
            }
            $clean[$key] = trim((string)$input[$key]);
        }

        if (!is_numeric($clean['age']) || intval($clean['age']) <= 0) {
            throw new Exception("Validation Error: 'Age' must be a positive integer.");
        }
        $clean['age'] = intval($clean['age']);

        return $clean;
    }

    /**
     * Build canonical deterministic JSON representation of EHR.
     * Guaranteed field ordering and uniform formatting across sign/verify phases.
     */
    public function buildCanonicalJson(array $ehr): string {
        $canonical = [
            "patient_id"   => (string)($ehr['patient_id'] ?? ''),
            "patient_name" => (string)($ehr['patient_name'] ?? ''),
            "age"          => intval($ehr['age'] ?? 0),
            "diagnosis"    => (string)($ehr['diagnosis'] ?? ''),
            "prescription" => (string)($ehr['prescription'] ?? ''),
            "doctor_name"  => (string)($ehr['doctor_name'] ?? ''),
            "hospital"     => (string)($ehr['hospital'] ?? ''),
            "date"         => (string)($ehr['date'] ?? '')
        ];

        return json_encode($canonical, JSON_UNESCAPED_SLASHES | JSON_UNESCAPED_UNICODE);
    }
}
