<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>SecureEHR — Cybersecurity Command Center & Cryptographic Security Lab</title>

    <!-- Google Fonts: Inter & JetBrains Mono -->
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700;800&family=JetBrains+Mono:wght@400;500;600;700&display=swap" rel="stylesheet">

    <!-- Bootstrap 5 CSS -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/css/bootstrap.min.css" rel="stylesheet">
    <!-- Bootstrap Icons -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap-icons@1.11.0/font/bootstrap-icons.css" rel="stylesheet">
    <!-- Lucide Icons -->
    <script src="https://unpkg.com/lucide@latest"></script>

    <!-- Custom Cybersecurity Styling -->
    <link href="assets/css/style.css" rel="stylesheet">
</head>
<body>

    <!-- Header Command Bar Navbar -->
    <nav class="navbar navbar-expand-xl navbar-cyber sticky-top">
        <div class="container-fluid px-4">
            <a class="navbar-brand d-flex align-items-center me-3" href="#">
                <i data-lucide="shield-check" class="text-info fs-2 me-2"></i>
                <div>
                    <div class="cyber-brand-text">Secure<span class="cyber-brand-accent">EHR</span></div>
                    <div class="cyber-brand-sub">CRYPTOGRAPHIC INTEGRITY & DIGITAL SIGNATURE LAB</div>
                </div>
            </a>
            
            <div class="d-flex align-items-center ms-auto ms-xl-0 me-3">
                <span class="badge cyber-badge rounded-pill px-3 py-2">
                    <span class="status-dot status-dot-green me-1"></span> LOCAL SECURITY LAB
                </span>
            </div>

            <button class="navbar-toggler border-secondary" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNav">
                <span class="navbar-toggler-icon"></span>
            </button>

            <div class="collapse navbar-collapse" id="navbarNav">
                <ul class="navbar-nav ms-auto font-mono">
                    <li class="nav-item"><a class="nav-link" href="#section-status">00 // DASHBOARD</a></li>
                    <li class="nav-item"><a class="nav-link" href="#section-ehr">01 // EHR DOCUMENT</a></li>
                    <li class="nav-item"><a class="nav-link" href="#section-hash">02 // CRYPTOGRAPHIC HASH</a></li>
                    <li class="nav-item"><a class="nav-link" href="#section-signature">03 // DIGITAL SIGNATURE</a></li>
                    <li class="nav-item"><a class="nav-link" href="#section-verification">04 // VERIFICATION</a></li>
                    <li class="nav-item"><a class="nav-link" href="#section-tampering">05 // TAMPERING SIMULATION</a></li>
                    <li class="nav-item"><a class="nav-link" href="#section-comparison">06 // ALGORITHM ANALYSIS</a></li>
                    <li class="nav-item"><a class="nav-link" href="#section-performance">07 // PERFORMANCE</a></li>
                    <li class="nav-item"><a class="nav-link" href="#section-audit">08 // AUDIT LOG</a></li>
                </ul>
            </div>
        </div>
    </nav>

    <div class="container-fluid px-4 mt-3">

        <!-- System Telemetry Command Bar -->
        <div class="telemetry-bar">
            <div class="telemetry-item">
                <span class="telemetry-label">SYSTEM STATUS</span>
                <span class="status-dot status-dot-green"></span>
                <span class="telemetry-val">ONLINE</span>
            </div>
            <div class="telemetry-item">
                <span class="telemetry-label">CRYPTO ENGINE</span>
                <span class="status-dot status-dot-cyan"></span>
                <span class="telemetry-val">OPENSSL / ACTIVE</span>
            </div>
            <div class="telemetry-item">
                <span class="telemetry-label">DATABASE</span>
                <span class="status-dot status-dot-green"></span>
                <span class="telemetry-val">MYSQL / CONNECTED</span>
            </div>
            <div class="telemetry-item">
                <span class="telemetry-label">SIGNATURE ENGINE</span>
                <span class="status-dot status-dot-cyan"></span>
                <span class="telemetry-val">RSA-2048 / READY</span>
            </div>
            <div class="telemetry-item">
                <span class="telemetry-label">THREAT MONITOR</span>
                <span class="status-dot status-dot-green"></span>
                <span class="telemetry-val">INTEGRITY ACTIVE</span>
            </div>
        </div>

        <!-- 00 // Top Security Status Cards -->
        <div class="row g-3 mb-4" id="section-status">
            <div class="col-6 col-lg-3">
                <div class="card status-card status-warning p-3" id="status-ehr">
                    <div class="text-uppercase font-mono text-muted fw-bold small">EHR SECURITY STATUS</div>
                    <div class="status-val mt-2">READY</div>
                    <div class="small font-mono text-secondary mt-1">Document Lifecycle State</div>
                </div>
            </div>
            <div class="col-6 col-lg-3">
                <div class="card status-card p-3" id="status-hash">
                    <div class="text-uppercase font-mono text-muted fw-bold small">HASH ALGORITHM</div>
                    <div class="status-val mt-2">SHA-256</div>
                    <div class="small font-mono text-secondary mt-1">256-bit Digest Engine</div>
                </div>
            </div>
            <div class="col-6 col-lg-3">
                <div class="card status-card p-3" id="status-signature">
                    <div class="text-uppercase font-mono text-muted fw-bold small">DIGITAL SIGNATURE</div>
                    <div class="status-val mt-2">NOT SIGNED</div>
                    <div class="small font-mono text-secondary mt-1">RSA-2048 Asymmetric Key</div>
                </div>
            </div>
            <div class="col-6 col-lg-3">
                <div class="card status-card p-3" id="status-integrity">
                    <div class="text-uppercase font-mono text-muted fw-bold small">DOCUMENT INTEGRITY</div>
                    <div class="status-val mt-2">NOT CHECKED</div>
                    <div class="small font-mono text-secondary mt-1">Tamper Detection Monitor</div>
                </div>
            </div>
        </div>

        <!-- Cryptographic Security Layers Info Panel -->
        <div class="card card-cyber mb-4">
            <div class="card-cyber-header">
                <div class="section-title">
                    <i data-lucide="layers" class="me-1"></i> 00 // CRYPTOGRAPHIC SECURITY LAYERS
                </div>
            </div>
            <div class="card-body bg-dark">
                <div class="row g-3">
                    <div class="col-md-4 border-end border-secondary">
                        <div class="security-layer-title">
                            <i data-lucide="hash"></i> 01. HASHING (INTEGRITY)
                        </div>
                        <p class="small text-secondary mb-0">
                            One-way cryptographic function (SHA-256 / SHA-512). Produces a fixed-length digest to detect any unauthorized data modification.
                        </p>
                    </div>
                    <div class="col-md-4 border-end border-secondary">
                        <div class="security-layer-title">
                            <i data-lucide="lock"></i> 02. ENCRYPTION (CONFIDENTIALITY)
                        </div>
                        <p class="small text-secondary mb-0">
                            Symmetric or asymmetric encryption safeguards payload privacy, ensuring unauthorized entities cannot read sensitive clinical records.
                        </p>
                    </div>
                    <div class="col-md-4">
                        <div class="security-layer-title">
                            <i data-lucide="key-round"></i> 03. DIGITAL SIGNATURE (AUTHENTICATION)
                        </div>
                        <p class="small text-secondary mb-0">
                            RSA-2048 private key signing of the hash digest. Provides origin authentication, tamper protection, and legal non-repudiation.
                        </p>
                    </div>
                </div>
            </div>
        </div>

        <!-- Section 1: EHR Document Creator Module -->
        <div class="card card-cyber mb-4" id="section-ehr">
            <div class="card-cyber-header">
                <div class="section-title">
                    <i data-lucide="file-text"></i> 01 // EHR DOCUMENT CREATOR
                </div>
                <span class="badge cyber-badge-warning rounded-pill px-3 py-1">
                    <i data-lucide="alert-triangle" class="me-1" style="width: 14px; height: 14px;"></i> CLASSIFICATION: DEMO DATA — NOT A REAL PATIENT RECORD
                </span>
            </div>
            <div class="card-body">
                <form id="ehr-form">
                    <div class="row g-3">
                        <div class="col-md-3">
                            <label for="patient_id" class="form-label-cyber">Patient ID</label>
                            <input type="text" class="form-control form-control-cyber font-mono" id="patient_id" required placeholder="e.g. P1001">
                        </div>
                        <div class="col-md-6">
                            <label for="patient_name" class="form-label-cyber">Patient Name</label>
                            <input type="text" class="form-control form-control-cyber" id="patient_name" required placeholder="Full Name">
                        </div>
                        <div class="col-md-3">
                            <label for="age" class="form-label-cyber">Age</label>
                            <input type="number" class="form-control form-control-cyber font-mono" id="age" required placeholder="Age">
                        </div>
                        <div class="col-md-6">
                            <label for="diagnosis" class="form-label-cyber">Diagnosis</label>
                            <input type="text" class="form-control form-control-cyber" id="diagnosis" required placeholder="Medical Diagnosis">
                        </div>
                        <div class="col-md-6">
                            <label for="prescription" class="form-label-cyber">Prescription</label>
                            <input type="text" class="form-control form-control-cyber" id="prescription" required placeholder="Prescribed Dosage">
                        </div>
                        <div class="col-md-4">
                            <label for="doctor_name" class="form-label-cyber">Attending Doctor</label>
                            <input type="text" class="form-control form-control-cyber" id="doctor_name" required placeholder="Doctor Name">
                        </div>
                        <div class="col-md-4">
                            <label for="hospital" class="form-label-cyber">Hospital / Facility</label>
                            <input type="text" class="form-control form-control-cyber" id="hospital" required placeholder="Hospital Name">
                        </div>
                        <div class="col-md-4">
                            <label for="date" class="form-label-cyber">Record Date</label>
                            <input type="text" class="form-control form-control-cyber font-mono" id="date" required placeholder="DD-MM-YYYY">
                        </div>
                    </div>
                </form>
                <div class="mt-4 d-flex flex-wrap gap-2">
                    <button type="button" class="btn btn-cyber-secondary" id="btn-load-demo">
                        <i data-lucide="rotate-ccw" style="width: 15px;"></i> LOAD DEMO EHR
                    </button>
                    <button type="button" class="btn btn-cyber-primary px-4" id="btn-generate">
                        <i data-lucide="shield-check" style="width: 16px;"></i> GENERATE SECURITY RECORD
                    </button>
                    <button type="button" class="btn btn-cyber-secondary ms-auto" id="btn-reset">
                        <i data-lucide="x-circle" style="width: 15px;"></i> RESET
                    </button>
                </div>
            </div>
        </div>

        <!-- Section 2: Cryptographic Hash Module -->
        <div class="card card-cyber mb-4" id="section-hash">
            <div class="card-cyber-header">
                <div class="section-title">
                    <i data-lucide="binary"></i> 02 // CRYPTOGRAPHIC HASH DIGESTS
                </div>
            </div>
            <div class="card-body">
                <!-- Visual Pipeline Diagram -->
                <div class="crypto-pipeline">
                    <span class="pipeline-node">EHR DOCUMENT PAYLOAD</span>
                    <span class="pipeline-arrow">➔</span>
                    <span class="pipeline-node active-cyan">SHA-256 ENGINE</span>
                    <span class="pipeline-arrow">➔</span>
                    <span class="pipeline-node active-cyan">64-HEX DIGEST</span>
                </div>

                <div class="row g-3">
                    <div class="col-md-6">
                        <div class="card card-cyber p-3 h-100">
                            <div class="d-flex justify-content-between align-items-center mb-2">
                                <span class="font-mono text-cyan fw-bold"><i data-lucide="hash" class="me-1" style="width: 16px;"></i> SHA-256 DIGEST</span>
                                <span class="badge cyber-badge">256 BITS / 64 HEX</span>
                            </div>
                            <div class="code-box mb-3" id="hash-256-display">
                                Click "GENERATE SECURITY RECORD" to compute SHA-256 digest...
                            </div>
                            <button class="btn btn-cyber-secondary btn-sm ms-auto" onclick="copyToClipboard('hash-256-display')">
                                <i data-lucide="copy" style="width: 14px;"></i> COPY SHA-256
                            </button>
                        </div>
                    </div>
                    <div class="col-md-6">
                        <div class="card card-cyber p-3 h-100">
                            <div class="d-flex justify-content-between align-items-center mb-2">
                                <span class="font-mono text-purple fw-bold" style="color: #C084FC;"><i data-lucide="hash" class="me-1" style="width: 16px;"></i> SHA-512 DIGEST</span>
                                <span class="badge cyber-badge" style="border-color: #C084FC; color: #C084FC;">512 BITS / 128 HEX</span>
                            </div>
                            <div class="code-box code-box-sha512 mb-3" id="hash-512-display">
                                Click "GENERATE SECURITY RECORD" to compute SHA-512 digest...
                            </div>
                            <button class="btn btn-cyber-secondary btn-sm ms-auto" onclick="copyToClipboard('hash-512-display')">
                                <i data-lucide="copy" style="width: 14px;"></i> COPY SHA-512
                            </button>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <!-- Section 3: Digital Signature Module -->
        <div class="card card-cyber mb-4" id="section-signature">
            <div class="card-cyber-header">
                <div class="section-title">
                    <i data-lucide="key"></i> 03 // DIGITAL SIGNATURE MODULE
                </div>
                <span class="badge cyber-badge-success rounded-pill px-3 py-1 font-mono">
                    <i data-lucide="cpu" class="me-1" style="width: 14px;"></i> RSA-2048 + SHA-256 SIGNING ENGINE
                </span>
            </div>
            <div class="card-body">
                <div class="row g-3">
                    <div class="col-md-8">
                        <label class="form-label-cyber">BASE64 ENCODED DIGITAL SIGNATURE (RSA PRIVATE KEY SIGNED):</label>
                        <div class="code-box code-box-sig mb-3" id="signature-display">
                            Click "GENERATE SECURITY RECORD" to generate RSA-2048 digital signature...
                        </div>
                        <button class="btn btn-cyber-success btn-sm ms-auto" onclick="copyToClipboard('signature-display')">
                            <i data-lucide="copy" style="width: 14px;"></i> COPY SIGNATURE
                        </button>
                    </div>
                    <div class="col-md-4">
                        <div class="card card-cyber p-3 h-100">
                            <div class="font-mono text-cyan fw-bold mb-2"><i data-lucide="shield-lock" class="me-1" style="width: 16px;"></i> KEY PAIR MANAGEMENT</div>
                            <div class="p-2 mb-3 bg-secondary rounded border border-secondary font-mono small">
                                <strong class="text-danger"><i data-lucide="lock" style="width: 14px;"></i> PRIVATE KEY:</strong> RESTRICTED<br>
                                <span class="text-secondary small">Stored inside protected <code>keys/</code> directory. Direct HTTP access blocked.</span>
                            </div>
                            <button class="btn btn-cyber-secondary btn-sm w-100 mb-2" type="button" data-bs-toggle="collapse" data-bs-target="#publicKeyCollapse">
                                <i data-lucide="eye" style="width: 14px;"></i> VIEW PUBLIC KEY
                            </button>
                            <div class="collapse" id="publicKeyCollapse">
                                <div class="code-box small mt-2" style="max-height: 120px; font-size: 0.75rem;" id="public-key-display">
                                    Public Key will appear here once generated...
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <!-- Section 4: Signature Verification Module -->
        <div class="card card-cyber mb-4" id="section-verification">
            <div class="card-cyber-header">
                <div class="section-title">
                    <i data-lucide="shield-alert"></i> 04 // SIGNATURE VERIFICATION
                </div>
                <button class="btn btn-cyber-success btn-sm" id="btn-verify-original" disabled>
                    <i data-lucide="shield-check" style="width: 15px;"></i> VERIFY ORIGINAL EHR
                </button>
            </div>
            <div class="card-body">
                <!-- Verification Pipeline Diagram -->
                <div class="crypto-pipeline mb-3">
                    <span class="pipeline-node">EHR DOCUMENT</span>
                    <span class="pipeline-arrow">➔</span>
                    <span class="pipeline-node">COMPUTE HASH</span>
                    <span class="pipeline-arrow">➔</span>
                    <span class="pipeline-node">SIGNATURE PAYLOAD</span>
                    <span class="pipeline-arrow">➔</span>
                    <span class="pipeline-node">PUBLIC KEY</span>
                    <span class="pipeline-arrow">➔</span>
                    <span class="pipeline-node active-cyan">VERIFICATION ENGINE</span>
                </div>

                <div id="verification-alert" class="d-none"></div>
            </div>
        </div>

        <!-- Section 5: Tampering Simulation Module -->
        <div class="card card-cyber mb-4" style="border-color: rgba(255, 59, 92, 0.4);" id="section-tampering">
            <div class="card-cyber-header" style="background-color: rgba(255, 59, 92, 0.1); border-bottom-color: rgba(255, 59, 92, 0.3);">
                <div class="section-title text-danger">
                    <i data-lucide="zap" class="text-danger"></i> 05 // TAMPERING SIMULATION MODULE
                </div>
                <button class="btn btn-cyber-danger btn-sm" id="btn-simulate-tamper" disabled>
                    <i data-lucide="zap" style="width: 15px;"></i> ⚡ SIMULATE UNAUTHORIZED MODIFICATION
                </button>
            </div>
            <div class="card-body">
                <div class="alert alert-dark border-secondary font-mono small mb-3">
                    <span class="text-danger fw-bold"><i data-lucide="alert-triangle" style="width: 14px;"></i> ETHICAL HACKING DEMONSTRATION:</span> 
                    Simulates an in-transit network attack where an unauthorized attacker modifies EHR document fields (e.g. altering medication dosage or diagnosis). 
                    The verification module will attempt validation against the <strong>ORIGINAL RSA digital signature</strong>.
                </div>

                <div id="tampering-panel" class="d-none">
                    <!-- Attack Flow Pipeline -->
                    <div class="crypto-pipeline mb-3 border-danger">
                        <span class="pipeline-node active-green">ORIGINAL SIGNED EHR</span>
                        <span class="pipeline-arrow text-danger">➔</span>
                        <span class="pipeline-node text-danger border-danger">UNAUTHORIZED ATTACK</span>
                        <span class="pipeline-arrow text-danger">➔</span>
                        <span class="pipeline-node text-danger border-danger">TAMPERED EHR</span>
                        <span class="pipeline-arrow text-danger">➔</span>
                        <span class="pipeline-node text-danger border-danger">VERIFICATION ✕ REJECTED</span>
                    </div>

                    <!-- Side-by-Side Comparison -->
                    <div class="row g-3 mb-3">
                        <div class="col-md-6">
                            <div class="card card-cyber h-100" style="border-color: var(--green);">
                                <div class="card-cyber-header bg-dark text-green font-mono fw-bold">
                                    <i data-lucide="file-check" class="me-1" style="width: 16px;"></i> ORIGINAL EHR DOCUMENT
                                </div>
                                <div class="card-body p-0" id="orig-comparison-box"></div>
                            </div>
                        </div>
                        <div class="col-md-6">
                            <div class="card card-cyber h-100" style="border-color: var(--red);">
                                <div class="card-cyber-header bg-dark text-danger font-mono fw-bold d-flex justify-content-between">
                                    <span><i data-lucide="file-x" class="me-1" style="width: 16px;"></i> MODIFIED (TAMPERED) EHR</span>
                                    <span class="badge cyber-badge-warning">ATTACK DETECTED</span>
                                </div>
                                <div class="card-body p-0" id="mod-comparison-box"></div>
                            </div>
                        </div>
                    </div>

                    <div class="row g-3 mb-3">
                        <div class="col-md-12" id="hash-comparison-box"></div>
                    </div>

                    <div class="d-flex flex-wrap gap-2">
                        <button class="btn btn-cyber-danger" id="btn-verify-modified">
                            <i data-lucide="shield-alert" style="width: 15px;"></i> VERIFY MODIFIED EHR (TEST FAILURE)
                        </button>
                        <button class="btn btn-cyber-success ms-auto" id="btn-restore-original">
                            <i data-lucide="rotate-ccw" style="width: 15px;"></i> RESTORE ORIGINAL EHR
                        </button>
                    </div>
                </div>
            </div>
        </div>

        <!-- Section 6: Hash Algorithm Security Comparison -->
        <div class="card card-cyber mb-4" id="section-comparison">
            <div class="card-cyber-header">
                <div class="section-title">
                    <i data-lucide="table"></i> 06 // HASH ALGORITHM SECURITY ANALYSIS
                </div>
            </div>
            <div class="card-body p-0">
                <div class="table-responsive">
                    <table class="table table-cyber table-hover mb-0">
                        <thead>
                            <tr>
                                <th>ALGORITHM</th>
                                <th>DIGEST SIZE</th>
                                <th>COLLISION RESISTANCE</th>
                                <th>SECURITY STATUS</th>
                                <th>RECOMMENDATION</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr>
                                <td><strong class="text-danger font-mono">MD5</strong></td>
                                <td class="font-mono">128 bits (32 hex)</td>
                                <td>Broken (Collisions reproducible in seconds)</td>
                                <td><span class="badge badge-cyber-weak">VULNERABLE / WEAK</span></td>
                                <td><span class="badge cyber-badge-warning">NOT RECOMMENDED</span></td>
                            </tr>
                            <tr>
                                <td><strong class="text-warning font-mono">SHA-1</strong></td>
                                <td class="font-mono">160 bits (40 hex)</td>
                                <td>Theoretical & Practical Collisions (SHAttered)</td>
                                <td><span class="badge badge-cyber-deprecated">DEPRECATED</span></td>
                                <td><span class="badge cyber-badge-warning">NOT RECOMMENDED</span></td>
                            </tr>
                            <tr>
                                <td><strong class="text-green font-mono">SHA-256</strong></td>
                                <td class="font-mono">256 bits (64 hex)</td>
                                <td>High Collision Resistance (2^128 ops)</td>
                                <td><span class="badge badge-cyber-strong">STRONG</span></td>
                                <td><span class="badge cyber-badge-success">RECOMMENDED</span></td>
                            </tr>
                            <tr>
                                <td><strong class="text-green font-mono">SHA-512</strong></td>
                                <td class="font-mono">512 bits (128 hex)</td>
                                <td>Ultra-High Collision Resistance (2^256 ops)</td>
                                <td><span class="badge badge-cyber-strong">STRONG / HIGH-SECURITY</span></td>
                                <td><span class="badge cyber-badge-success">RECOMMENDED</span></td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>

        <!-- Section 7: Performance Analysis -->
        <div class="card card-cyber mb-4" id="section-performance">
            <div class="card-cyber-header">
                <div class="section-title">
                    <i data-lucide="gauge"></i> 07 // PERFORMANCE & OVERHEAD BENCHMARK
                </div>
                <button class="btn btn-cyber-primary btn-sm" id="btn-run-benchmark">
                    <i data-lucide="play" style="width: 15px;"></i> RUN PERFORMANCE BENCHMARK
                </button>
            </div>
            <div class="card-body">
                <p class="text-secondary font-mono small mb-3">
                    Execution time metrics computed dynamically on local server via <code>microtime(true)</code>.
                </p>
                <div class="table-responsive">
                    <table class="table table-cyber table-bordered mb-0">
                        <thead>
                            <tr>
                                <th>CRYPTOGRAPHIC OPERATION</th>
                                <th>AVERAGE TIME PER OP</th>
                                <th>OVERHEAD VISUAL BENCHMARK</th>
                            </tr>
                        </thead>
                        <tbody id="benchmark-table-body">
                            <tr>
                                <td colspan="3" class="text-center text-secondary py-3 font-mono">
                                    Click "RUN PERFORMANCE BENCHMARK" to execute microsecond timing suite.
                                </td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>

        <!-- Section 8: Academic Security Evaluation & Recommendation -->
        <div class="card card-cyber mb-4" id="section-evaluation">
            <div class="card-cyber-header">
                <div class="section-title">
                    <i data-lucide="award"></i> 08 // ACADEMIC SECURITY EVALUATION
                </div>
            </div>
            <div class="card-body">
                <div class="table-responsive mb-4">
                    <table class="table table-cyber table-bordered align-middle">
                        <thead>
                            <tr>
                                <th>SECURITY CRITERION</th>
                                <th>HASHING (SHA-256)</th>
                                <th>DIGITAL SIGNATURE (RSA-2048)</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr>
                                <td><strong class="font-mono">Integrity</strong></td>
                                <td><i data-lucide="check-circle-2" class="text-green me-1" style="width: 16px;"></i> Yes (Detects alteration)</td>
                                <td><i data-lucide="check-circle-2" class="text-green me-1" style="width: 16px;"></i> Yes (Detects alteration)</td>
                            </tr>
                            <tr>
                                <td><strong class="font-mono">Authentication</strong></td>
                                <td><i data-lucide="x-circle" class="text-danger me-1" style="width: 16px;"></i> No (Anyone can calculate hash)</td>
                                <td><i data-lucide="check-circle-2" class="text-green me-1" style="width: 16px;"></i> Yes (Verifies signer's key)</td>
                            </tr>
                            <tr>
                                <td><strong class="font-mono">Non-repudiation</strong></td>
                                <td><i data-lucide="x-circle" class="text-danger me-1" style="width: 16px;"></i> No</td>
                                <td><i data-lucide="check-circle-2" class="text-green me-1" style="width: 16px;"></i> Yes (Private key tied to physician)</td>
                            </tr>
                            <tr>
                                <td><strong class="font-mono">Tamper Detection</strong></td>
                                <td><i data-lucide="check-circle-2" class="text-green me-1" style="width: 16px;"></i> Yes</td>
                                <td><i data-lucide="check-circle-2" class="text-green me-1" style="width: 16px;"></i> Yes</td>
                            </tr>
                            <tr>
                                <td><strong class="font-mono">Collision Resistance</strong></td>
                                <td>Algorithm Dependent (2^128 SHA-256)</td>
                                <td>Relies on underlying hash function</td>
                            </tr>
                            <tr>
                                <td><strong class="font-mono">Computational Overhead</strong></td>
                                <td>Extremely Low (&lt; 0.05ms)</td>
                                <td>Moderate (Sign ~7ms, Verify ~2.5ms)</td>
                            </tr>
                        </tbody>
                    </table>
                </div>

                <div class="card card-cyber p-4" style="background-color: var(--bg-secondary); border-color: var(--cyan);">
                    <h6 class="text-cyan font-mono fw-bold mb-3 d-flex align-items-center">
                        <i data-lucide="shield-check" class="me-2"></i> RECOMMENDED EHR SECURITY CONFIGURATION
                    </h6>
                    <div class="row font-mono mb-3">
                        <div class="col-md-5">
                            <strong>HASH ALGORITHM:</strong> <span class="badge cyber-badge-success">SHA-256</span>
                        </div>
                        <div class="col-md-7">
                            <strong>DIGITAL SIGNATURE:</strong> <span class="badge cyber-badge">RSA-2048 + RSA-PSS + SHA-256</span>
                        </div>
                    </div>
                    <hr class="border-secondary">
                    <p class="mb-0 small text-secondary">
                        <strong>SECURITY RATIONALE:</strong> SHA-256 provides robust, computationally efficient collision resistance for detecting document modifications. 
                        RSA 2048-bit digital signatures complete the security triad by providing origin authentication and legal non-repudiation, ensuring physicians cannot deny issuing signed prescription orders.
                    </p>
                </div>
            </div>
        </div>

        <!-- Section 9: Security Audit Activity Log -->
        <div class="card card-cyber mb-4" id="section-audit">
            <div class="card-cyber-header">
                <div class="section-title">
                    <i data-lucide="terminal"></i> 09 // SECURITY AUDIT ACTIVITY LOG
                </div>
                <span class="badge cyber-badge font-mono">LIVE SECURITY MONITOR</span>
            </div>
            <div class="card-body p-0">
                <div class="table-responsive" style="max-height: 320px; overflow-y: auto;">
                    <table class="table table-cyber mb-0">
                        <thead class="sticky-top">
                            <tr>
                                <th style="width: 140px;">TIMESTAMP</th>
                                <th style="width: 200px;">EVENT TYPE</th>
                                <th style="width: 120px;">STATUS</th>
                                <th>AUDIT DETAILS</th>
                            </tr>
                        </thead>
                        <tbody id="audit-logs-body" class="font-mono">
                            <tr>
                                <td colspan="4" class="text-center text-secondary py-3">Loading security audit records...</td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>

        <!-- Section 10: Cybersecurity Terminal Panel Widget -->
        <div class="terminal-console mb-4">
            <div class="terminal-console-header">
                <span><i data-lucide="terminal" style="width: 14px;" class="me-1"></i> SECURE-EHR LAB CONSOLE TERMINAL</span>
                <span>MODE: LOCAL DEMO</span>
            </div>
            <div class="terminal-console-body">
                <div><span class="terminal-prompt">&gt;</span> initializing cryptographic engine...</div>
                <div><span class="terminal-prompt">&gt;</span> SHA-256 digest module ............................... <span class="terminal-success">READY</span></div>
                <div><span class="terminal-prompt">&gt;</span> SHA-512 digest module ............................... <span class="terminal-success">READY</span></div>
                <div><span class="terminal-prompt">&gt;</span> RSA-2048 signature engine (OpenSSL) .................. <span class="terminal-success">READY</span></div>
                <div><span class="terminal-prompt">&gt;</span> signature verification engine ....................... <span class="terminal-success">READY</span></div>
                <div><span class="terminal-prompt">&gt;</span> MySQL database connection ............................ <span class="terminal-success">ACTIVE</span></div>
                <div><span class="terminal-prompt">&gt;</span> document integrity monitor .......................... <span class="terminal-success">ACTIVE</span></div>
                <div class="mt-2"><span class="terminal-prompt">&gt;</span> SYSTEM READY FOR OPERATION_<span class="terminal-cursor"></span></div>
            </div>
        </div>

        <!-- Footer -->
        <footer class="text-center py-4">
            <div class="font-mono text-cyan fw-bold mb-1">SECURE EHR SECURITY COMMAND CENTER</div>
            <div class="text-secondary small">Cryptographic Integrity & Asymmetric Digital Signature Verification System</div>
            <div class="text-secondary small mt-1">Academic Cybersecurity Lab | Powered by PHP 8.x, OpenSSL & MySQL</div>
        </footer>

    </div>

    <!-- Bootstrap 5 Bundle JS -->
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0/dist/js/bootstrap.bundle.min.js"></script>
    <!-- Application Logic JS -->
    <script src="assets/js/app.js"></script>
    <script>
        // Initialize Lucide Icons
        lucide.createIcons();
    </script>
</body>
</html>
