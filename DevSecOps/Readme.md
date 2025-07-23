# Secure CI/CD Pipeline for OWASP Juice Shop using GitHub Actions

## Project Title
**Secure DevSecOps Pipeline Implementation**  
*Project for completion of CYxxxx - DevSecOps Course*

---

## Overview

This project demonstrates the implementation of a **secure CI/CD pipeline** using GitHub Actions for the open-source vulnerable web application **[OWASP Juice Shop](https://owasp.org/www-project-juice-shop/)**. The goal is to integrate security throughout the software development lifecycle by utilizing modern DevSecOps principles and tooling.

The pipeline includes multiple layers of security tools and scans to ensure:
- Static and dynamic code analysis
- Secret scanning
- Software composition analysis
- Container security
- Infrastructure-as-Code (IaC) security scanning
- Integration with SIEM and Vulnerability Management tools

---

## GitHub Flow Overview

GitHub Flow is a lightweight, branch-based workflow that supports collaboration and CI/CD automation. The pipeline is built around:

- Creating branches for new features or fixes
- Opening Pull Requests (PRs) for review and discussion
- Running automated CI/CD workflows on PRs
- Merging only after passing tests and security checks
- Deploying from the `main` branch after approval

---

## Objectives

- Integrate automated **SAST**, **DAST**, **SCA**, and **IaC scanning** in the CI/CD pipeline.
- Enforce secure coding standards using **GitHub Actions** workflows.
- Use container security tools to analyze Docker images before deployment.
- Centralize and monitor logs and alerts using **SIEM**.
- Leverage vulnerability management tools to maintain secure dependencies.

---

## Tools & Technologies Used

| Category                        | Tool(s)                        | Purpose                                               |
|--------------------------------|--------------------------------|-------------------------------------------------------|
| **Static Application Security Testing (SAST)** | Bandit                         | Python code vulnerability scanning                    |
| **Secrets Detection**          | TruffleHog                     | Detects secrets like API keys in code                 |
| **Software Composition Analysis (SCA)** | Snyk                          | Dependency and package vulnerability management       |
| **Containerization**           | Docker                         | Containerization of application and pipeline steps    |
| **Container Security**         | Clair, Trivy                   | Vulnerability scanning of Docker images               |
| **IaC Security Scanning**      | Checkov, Conftest              | Detects misconfigurations in Terraform, Kubernetes etc. |
| **Security Information and Event Management (SIEM)** | Datadog SIEM                   | Centralized log management and real-time alerting     |
| **Dynamic Application Security Testing (DAST)** | Gitbot, GraphQL-based tests    | Runtime vulnerability analysis and attack simulation  |

---

## CI/CD Pipeline Architecture

1. **GitHub Actions Workflow**
    - Triggered on pull requests and commits to main.
    - Each stage includes a specific category of security check.
  
2. **Stages in the Workflow**
    - **Lint & SAST** using Bandit
    - **Secrets Scanning** via TruffleHog
    - **Dependency Check** with Snyk
    - **Docker Build & Scan** using Trivy & Clair
    - **IaC Analysis** using Checkov and Conftest
    - **Deploy to Test Environment**
    - **DAST Scans** via Gitbot and GraphQL queries
    - **Logs & Alerts Forwarding** to Datadog SIEM

---

