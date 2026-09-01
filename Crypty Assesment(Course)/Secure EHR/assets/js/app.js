/**
 * SecureEHR Frontend Application JavaScript
 * Electronic Health Record Cryptographic Integrity & Digital Signature System
 * Cybersecurity Command Center Edition
 */

document.addEventListener('DOMContentLoaded', () => {
    // Application State
    const state = {
        recordId: null,
        originalDocument: null,
        modifiedDocument: null,
        canonicalDocument: null,
        sha256: null,
        sha512: null,
        digitalSignature: null,
        publicKey: null,
        keyId: null,
        modifiedSha256: null,
        tamperedField: null
    };

    // DOM Element References
    const ehrForm = document.getElementById('ehr-form');
    const btnLoadDemo = document.getElementById('btn-load-demo');
    const btnGenerate = document.getElementById('btn-generate');
    const btnReset = document.getElementById('btn-reset');
    const btnVerifyOriginal = document.getElementById('btn-verify-original');
    const btnSimulateTamper = document.getElementById('btn-simulate-tamper');
    const btnVerifyModified = document.getElementById('btn-verify-modified');
    const btnRestoreOriginal = document.getElementById('btn-restore-original');
    const btnRunBenchmark = document.getElementById('btn-run-benchmark');

    // Status Cards
    const cardEhrStatus = document.getElementById('status-ehr');
    const cardHashAlg = document.getElementById('status-hash');
    const cardSignature = document.getElementById('status-signature');
    const cardIntegrity = document.getElementById('status-integrity');

    // Displays
    const hash256Box = document.getElementById('hash-256-display');
    const hash512Box = document.getElementById('hash-512-display');
    const signatureBox = document.getElementById('signature-display');
    const publicKeyBox = document.getElementById('public-key-display');
    const verificationAlert = document.getElementById('verification-alert');
    const tamperingPanel = document.getElementById('tampering-panel');
    const origComparisonBox = document.getElementById('orig-comparison-box');
    const modComparisonBox = document.getElementById('mod-comparison-box');
    const hashComparisonBox = document.getElementById('hash-comparison-box');
    const benchmarkTableBody = document.getElementById('benchmark-table-body');
    const auditLogsBody = document.getElementById('audit-logs-body');

    // Helper to refresh Lucide icons if available
    function refreshIcons() {
        if (window.lucide && typeof window.lucide.createIcons === 'function') {
            window.lucide.createIcons();
        }
    }

    // Initialize Default Demo Form Data
    const defaultDemoData = {
        patient_id: 'P1001',
        patient_name: 'Rahul Sharma',
        age: 42,
        diagnosis: 'Hypertension',
        prescription: 'Amlodipine 5mg',
        doctor_name: 'Dr. Kumar',
        hospital: 'ABC Medical Center',
        date: '31-08-2026'
    };

    // Helper: Fill Form
    function populateForm(data) {
        document.getElementById('patient_id').value = data.patient_id || '';
        document.getElementById('patient_name').value = data.patient_name || '';
        document.getElementById('age').value = data.age || '';
        document.getElementById('diagnosis').value = data.diagnosis || '';
        document.getElementById('prescription').value = data.prescription || '';
        document.getElementById('doctor_name').value = data.doctor_name || '';
        document.getElementById('hospital').value = data.hospital || '';
        document.getElementById('date').value = data.date || '';
    }

    // Helper: Read Form
    function getFormData() {
        return {
            patient_id: document.getElementById('patient_id').value.trim(),
            patient_name: document.getElementById('patient_name').value.trim(),
            age: parseInt(document.getElementById('age').value, 10) || 0,
            diagnosis: document.getElementById('diagnosis').value.trim(),
            prescription: document.getElementById('prescription').value.trim(),
            doctor_name: document.getElementById('doctor_name').value.trim(),
            hospital: document.getElementById('hospital').value.trim(),
            date: document.getElementById('date').value.trim()
        };
    }

    // Update Status Cards
    function setStatusCards(ehr, hash, sig, integrity) {
        // EHR Status
        const elEhr = cardEhrStatus.querySelector('.status-val');
        elEhr.textContent = ehr;
        cardEhrStatus.className = 'card status-card p-3 ';
        if (ehr === 'SECURE') cardEhrStatus.classList.add('status-secure');
        else if (ehr === 'TAMPERED') cardEhrStatus.classList.add('status-tampered');
        else cardEhrStatus.classList.add('status-warning');

        // Hash Status
        cardHashAlg.querySelector('.status-val').textContent = hash;

        // Signature Status
        const elSig = cardSignature.querySelector('.status-val');
        elSig.textContent = sig;
        cardSignature.className = 'card status-card p-3 ';
        if (sig === 'VERIFIED') cardSignature.classList.add('status-secure');
        else if (sig === 'INVALID') cardSignature.classList.add('status-tampered');

        // Integrity Status
        const elInt = cardIntegrity.querySelector('.status-val');
        elInt.textContent = integrity;
        cardIntegrity.className = 'card status-card p-3 ';
        if (integrity === 'INTACT') cardIntegrity.classList.add('status-secure');
        else if (integrity === 'COMPROMISED') cardIntegrity.classList.add('status-tampered');
    }

    // Load Demo EHR Button
    btnLoadDemo.addEventListener('click', () => {
        populateForm(defaultDemoData);
    });

    // Reset Button
    btnReset.addEventListener('click', () => {
        ehrForm.reset();
        state.recordId = null;
        state.originalDocument = null;
        state.modifiedDocument = null;
        state.digitalSignature = null;
        state.publicKey = null;

        setStatusCards('READY', 'SHA-256', 'NOT SIGNED', 'NOT CHECKED');
        hash256Box.textContent = 'Click "GENERATE SECURITY RECORD" to compute SHA-256 digest...';
        hash512Box.textContent = 'Click "GENERATE SECURITY RECORD" to compute SHA-512 digest...';
        signatureBox.textContent = 'Click "GENERATE SECURITY RECORD" to generate RSA-2048 digital signature...';
        publicKeyBox.textContent = 'Public Key will appear here once generated...';
        verificationAlert.className = 'd-none';
        tamperingPanel.classList.add('d-none');
        btnVerifyOriginal.disabled = true;
        btnSimulateTamper.disabled = true;
    });

    // 1. Generate Security Record
    btnGenerate.addEventListener('click', async () => {
        const formData = getFormData();
        if (!formData.patient_id || !formData.patient_name || !formData.diagnosis || !formData.prescription) {
            alert('Please fill out all required EHR fields or click "LOAD DEMO EHR".');
            return;
        }

        btnGenerate.disabled = true;
        btnGenerate.innerHTML = `<span class="spinner-border spinner-border-sm me-2"></span>GENERATING KEYPAIR & SIGNATURE...`;

        try {
            const response = await fetch('api/create_record.php', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(formData)
            });
            const res = await response.json();

            if (!res.success) {
                throw new Error(res.message);
            }

            const d = res.data;
            state.recordId = d.record_id;
            state.originalDocument = formData;
            state.canonicalDocument = d.canonical_document;
            state.sha256 = d.sha256;
            state.sha512 = d.sha512;
            state.digitalSignature = d.digital_signature;
            state.publicKey = d.public_key;
            state.keyId = d.key_id;

            // Render Output Displays
            hash256Box.textContent = d.sha256;
            hash512Box.textContent = d.sha512;
            signatureBox.textContent = d.digital_signature;
            publicKeyBox.textContent = d.public_key;

            // Update Status Cards
            setStatusCards('SECURE', 'SHA-256', 'VERIFIED', 'INTACT');

            // Enable Actions
            btnVerifyOriginal.disabled = false;
            btnSimulateTamper.disabled = false;

            // Auto-verify Original
            await verifyDocument(state.originalDocument, true);
            refreshAuditLogs();

        } catch (err) {
            alert('Failed to generate record: ' + err.message);
        } finally {
            btnGenerate.disabled = false;
            btnGenerate.innerHTML = `<i data-lucide="shield-check" style="width: 16px;"></i> GENERATE SECURITY RECORD`;
            refreshIcons();
        }
    });

    // Helper: Core Verification Call
    async function verifyDocument(docObj, isOriginal) {
        if (!state.digitalSignature || !state.publicKey) return;

        try {
            const response = await fetch('api/verify.php', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    record_id: state.recordId,
                    document: docObj,
                    original_sha256: state.sha256,
                    original_signature: state.digitalSignature,
                    public_key: state.publicKey
                })
            });
            const res = await response.json();
            if (!res.success) throw new Error(res.message);

            const v = res.data;
            verificationAlert.classList.remove('d-none');

            if (v.is_authentic) {
                verificationAlert.className = 'alert-cyber-success font-mono mb-3';
                verificationAlert.innerHTML = `
                    <div class="d-flex align-items-center mb-2">
                        <i data-lucide="shield-check" class="text-green fs-2 me-3"></i>
                        <div>
                            <h5 class="alert-heading mb-0 text-green font-mono fw-bold">✓ SIGNATURE VERIFIED SUCCESSFULLY</h5>
                            <div class="mt-2">
                                <span class="badge cyber-badge-success me-1">DOCUMENT: AUTHENTIC</span>
                                <span class="badge cyber-badge-success me-1">INTEGRITY: INTACT</span>
                                <span class="badge cyber-badge-success me-1">HASH: MATCH</span>
                                <span class="badge cyber-badge-success">SIGNATURE: VALID</span>
                            </div>
                        </div>
                    </div>
                    <hr class="border-secondary">
                    <p class="mb-0 text-secondary font-mono small">
                        <strong>Cryptographic Assurance:</strong> The RSA-2048 digital signature matches the SHA-256 digest of the EHR document payload. 
                        No unauthorized alterations have occurred since signing.
                    </p>
                `;
                setStatusCards('SECURE', 'SHA-256', 'VERIFIED', 'INTACT');
            } else {
                verificationAlert.className = 'alert-cyber-danger font-mono mb-3';
                verificationAlert.innerHTML = `
                    <div class="d-flex align-items-center mb-2">
                        <i data-lucide="shield-alert" class="text-danger fs-2 me-3"></i>
                        <div>
                            <h5 class="alert-heading mb-0 text-danger font-mono fw-bold">✕ SIGNATURE VERIFICATION FAILED</h5>
                            <div class="mt-2">
                                <span class="badge badge-cyber-weak me-1">DOCUMENT: TAMPERED</span>
                                <span class="badge badge-cyber-weak me-1">INTEGRITY: COMPROMISED</span>
                                <span class="badge badge-cyber-weak me-1">HASH: MISMATCH</span>
                                <span class="badge badge-cyber-weak">SIGNATURE: INVALID</span>
                            </div>
                        </div>
                    </div>
                    <hr class="border-secondary">
                    <div class="p-3 bg-dark rounded border border-danger text-danger font-mono">
                        <h6 class="fw-bold mb-1"><i data-lucide="alert-triangle" style="width: 15px;" class="me-1"></i> ⚠ SECURITY EVENT DETECTED — UNAUTHORIZED DOCUMENT MODIFICATION</h6>
                        <p class="mb-0 small text-secondary">
                            The document payload content does NOT match the payload that was originally signed by the physician's RSA private key.
                            The calculated current SHA-256 digest differs from the original signed digest.
                        </p>
                    </div>
                `;
                setStatusCards('TAMPERED', 'SHA-256', 'INVALID', 'COMPROMISED');
            }
            refreshIcons();
            refreshAuditLogs();
        } catch (err) {
            alert('Verification Error: ' + err.message);
        }
    }

    // 2. Verify Original Button
    btnVerifyOriginal.addEventListener('click', () => {
        if (state.originalDocument) {
            verifyDocument(state.originalDocument, true);
        }
    });

    // 3. Simulate Tampering Button
    btnSimulateTamper.addEventListener('click', async () => {
        if (!state.originalDocument) return;

        btnSimulateTamper.disabled = true;
        try {
            const response = await fetch('api/tamper.php', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    record_id: state.recordId,
                    document: state.originalDocument
                })
            });
            const res = await response.json();
            if (!res.success) throw new Error(res.message);

            const t = res.data;
            state.modifiedDocument = t.modified_document;
            state.modifiedSha256 = t.modified_sha256;
            state.tamperedField = t.tampered_field;

            // Render Comparison Panels
            renderDocumentComparison(t.original_document, t.modified_document, t.tampered_field);

            // Render Hash Mismatch Box
            hashComparisonBox.innerHTML = `
                <div class="p-3 bg-secondary text-primary rounded font-mono small border border-secondary">
                    <div class="text-green mb-2">
                        <strong>ORIGINAL SHA-256 DIGEST:</strong><br>
                        <span class="text-cyan">${t.original_sha256}</span>
                    </div>
                    <div class="text-danger mb-2">
                        <strong>MODIFIED SHA-256 DIGEST:</strong><br>
                        <span>${t.modified_sha256}</span>
                    </div>
                    <div class="border-top border-secondary pt-2 text-warning fw-bold d-flex justify-content-between align-items-center">
                        <span>HASH MATCH EVALUATION:</span>
                        <span class="badge badge-cyber-weak">FALSE (MISMATCH DETECTED)</span>
                    </div>
                </div>
            `;

            tamperingPanel.classList.remove('d-none');
            tamperingPanel.scrollIntoView({ behavior: 'smooth' });

            // Auto Verify Modified
            await verifyDocument(state.modifiedDocument, false);

        } catch (err) {
            alert('Tamper Simulation Failed: ' + err.message);
        } finally {
            btnSimulateTamper.disabled = false;
        }
    });

    // Render Side-by-Side Original vs Modified
    function renderDocumentComparison(orig, mod, tamperedField) {
        const buildListHtml = (doc, highlightField, isModified) => {
            return `
                <ul class="list-group list-group-flush font-mono small mb-0">
                    <li class="list-group-item d-flex justify-content-between"><span class="text-secondary">Patient ID:</span> <span class="fw-bold">${doc.patient_id}</span></li>
                    <li class="list-group-item d-flex justify-content-between"><span class="text-secondary">Patient Name:</span> <span>${doc.patient_name}</span></li>
                    <li class="list-group-item d-flex justify-content-between ${highlightField === 'age' ? (isModified ? 'field-tampered-highlight' : 'field-original-highlight') : ''}">
                        <span class="text-secondary">Age:</span> <span>${doc.age}</span>
                    </li>
                    <li class="list-group-item d-flex justify-content-between ${highlightField === 'diagnosis' ? (isModified ? 'field-tampered-highlight' : 'field-original-highlight') : ''}">
                        <span class="text-secondary">Diagnosis:</span> <span>${doc.diagnosis}</span>
                    </li>
                    <li class="list-group-item d-flex justify-content-between ${highlightField === 'prescription' ? (isModified ? 'field-tampered-highlight' : 'field-original-highlight') : ''}">
                        <span class="text-secondary">Prescription:</span> <span class="fw-bold">${doc.prescription}</span>
                    </li>
                    <li class="list-group-item d-flex justify-content-between"><span class="text-secondary">Doctor:</span> <span>${doc.doctor_name}</span></li>
                    <li class="list-group-item d-flex justify-content-between"><span class="text-secondary">Hospital:</span> <span>${doc.hospital}</span></li>
                    <li class="list-group-item d-flex justify-content-between"><span class="text-secondary">Date:</span> <span>${doc.date}</span></li>
                </ul>
            `;
        };

        origComparisonBox.innerHTML = buildListHtml(orig, tamperedField, false);
        modComparisonBox.innerHTML = buildListHtml(mod, tamperedField, true);
    }

    // 4. Verify Modified EHR Button
    btnVerifyModified.addEventListener('click', () => {
        if (state.modifiedDocument) {
            verifyDocument(state.modifiedDocument, false);
        }
    });

    // 5. Restore Original EHR Button
    btnRestoreOriginal.addEventListener('click', async () => {
        try {
            const response = await fetch('api/restore.php', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ record_id: state.recordId })
            });
            const res = await response.json();
            if (!res.success) throw new Error(res.message);

            const r = res.data;
            state.modifiedDocument = null;
            populateForm(r.document);

            tamperingPanel.classList.add('d-none');
            await verifyDocument(r.document, true);
            refreshAuditLogs();

        } catch (err) {
            alert('Restore Error: ' + err.message);
        }
    });

    // 6. Run Benchmark Button
    btnRunBenchmark.addEventListener('click', async () => {
        btnRunBenchmark.disabled = true;
        btnRunBenchmark.innerHTML = `<span class="spinner-border spinner-border-sm me-2"></span>BENCHMARKING CRYPTO OPERATIONS...`;

        try {
            const response = await fetch('api/performance.php');
            const res = await response.json();
            if (!res.success) throw new Error(res.message);

            const b = res.data;
            benchmarkTableBody.innerHTML = `
                <tr>
                    <td><strong class="text-danger font-mono">MD5</strong> (128-bit)</td>
                    <td class="font-mono">${b.md5_ms} ms</td>
                    <td><div class="progress"><div class="progress-bar bg-danger" style="width: 5%"></div></div></td>
                </tr>
                <tr>
                    <td><strong class="text-warning font-mono">SHA-1</strong> (160-bit)</td>
                    <td class="font-mono">${b.sha1_ms} ms</td>
                    <td><div class="progress"><div class="progress-bar bg-warning" style="width: 8%"></div></div></td>
                </tr>
                <tr>
                    <td><strong class="text-green font-mono">SHA-256</strong> (256-bit)</td>
                    <td class="font-mono text-green fw-bold">${b.sha256_ms} ms</td>
                    <td><div class="progress"><div class="progress-bar" style="background-color: var(--green); width: 12%"></div></div></td>
                </tr>
                <tr>
                    <td><strong class="text-green font-mono">SHA-512</strong> (512-bit)</td>
                    <td class="font-mono text-green fw-bold">${b.sha512_ms} ms</td>
                    <td><div class="progress"><div class="progress-bar" style="background-color: var(--green); width: 18%"></div></div></td>
                </tr>
                <tr>
                    <td><strong class="text-cyan font-mono">RSA-2048 Sign</strong> (SHA-256 digest)</td>
                    <td class="font-mono text-cyan fw-bold">${b.rsa_sign_ms} ms</td>
                    <td><div class="progress"><div class="progress-bar" style="background-color: var(--cyan); width: 75%"></div></div></td>
                </tr>
                <tr>
                    <td><strong class="text-primary font-mono" style="color: #60A5FA;">RSA-2048 Verify</strong> (Public Key)</td>
                    <td class="font-mono text-primary fw-bold" style="color: #60A5FA;">${b.rsa_verify_ms} ms</td>
                    <td><div class="progress"><div class="progress-bar bg-info" style="width: 40%"></div></div></td>
                </tr>
            `;
            refreshAuditLogs();

        } catch (err) {
            alert('Benchmark failed: ' + err.message);
        } finally {
            btnRunBenchmark.disabled = false;
            btnRunBenchmark.innerHTML = `<i data-lucide="play" style="width: 15px;"></i> RUN PERFORMANCE BENCHMARK`;
            refreshIcons();
        }
    });

    // 7. Audit Log Auto-Refresh
    async function refreshAuditLogs() {
        try {
            const response = await fetch('api/logs.php');
            const res = await response.json();
            if (!res.success) return;

            const logs = res.data;
            if (!logs || logs.length === 0) {
                auditLogsBody.innerHTML = `<tr><td colspan="4" class="text-center text-secondary py-3">No security activity logged yet.</td></tr>`;
                return;
            }

            auditLogsBody.innerHTML = logs.map(l => {
                let badgeClass = 'cyber-badge';
                if (l.event_status === 'SUCCESS') badgeClass = 'cyber-badge-success';
                else if (l.event_status === 'FAILED') badgeClass = 'badge-cyber-weak';
                else if (l.event_status === 'WARNING') badgeClass = 'cyber-badge-warning';
                else if (l.event_status === 'ALERT') badgeClass = 'badge-cyber-weak';

                return `
                    <tr>
                        <td class="font-mono text-secondary small">${l.log_time}</td>
                        <td><span class="badge cyber-badge">${l.event_type}</span></td>
                        <td><span class="badge ${badgeClass}">${l.event_status}</span></td>
                        <td class="small text-secondary">${l.message}</td>
                    </tr>
                `;
            }).join('');
        } catch (e) {
            console.error('Failed to load logs:', e);
        }
    }

    // Clipboard Helpers
    window.copyToClipboard = function(elementId) {
        const text = document.getElementById(elementId).textContent;
        navigator.clipboard.writeText(text).then(() => {
            alert('Copied to clipboard!');
        });
    };

    // Auto-load demo on initial view & set 5-second live polling interval
    populateForm(defaultDemoData);
    refreshAuditLogs();
    setInterval(refreshAuditLogs, 5000);
});
