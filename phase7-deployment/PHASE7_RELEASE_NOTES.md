# LMS Release Notes — Version 1.0

## Release information

- **Product:** Moderated Learning Management System
- **Version:** 1.0
- **Platform:** C++17 console application on Ubuntu/Linux or Windows WSL2
- **Storage:** Local SQLite database
- **Date:** 7 November 2026

## Included functionality

- Role-based authentication for Administrator, Lecturer, Student and HoD.
- Salted PBKDF2-HMAC-SHA256 password hashing using OpenSSL.
- Hidden password entry in the console.
- Administrator management of accounts, departments, courses, assignments, lecturer assignments and student enrolments.
- Lecturer assignment creation, editing, activation, individual extensions, submission viewing, marking and feedback.
- Student assignment viewing, file submissions, resubmission versioning, checksums and submission status.
- HoD department-scoped moderation, approval/rejection and complete-batch release.
- Late penalty calculation and effective-deadline handling.
- Persistent mark and moderation audit records.
- SQLite persistence with foreign keys, normalised tables, indexes and parameterised queries.
- CMake/Ninja build and GoogleTest regression suite.

## Quality status

- Release build: PASS.
- Automated tests: 37/37 PASS.
- Production static analysis: PASS; 14 source files checked.
- Measured implementation line coverage: 80%.
- Critical or high-severity open defects: None.

## Installation

Follow `PHASE7_INSTALLATION_GUIDE.md`. The application must be started from the project root so it can locate `schema.sql`:

```bash
./build/lms_app school-lms.db
```

## Documentation included

- `PHASE7_DEPLOYMENT_DIAGRAM.mmd`
- `PHASE7_INSTALLATION_GUIDE.md`
- `PHASE7_USER_MANUAL.md`
- `PHASE7_RELEASE_NOTES.md`
- `BUILD_GUIDE.md`
- `END_TO_END_DEMO.md`

## Data and backup warning

SQLite database files may contain usernames, assessment records, marks and audit information. Back up the database while the application is stopped, protect the backup, and do not commit `.db` files to Git.

## Known limitations and out-of-scope items

The release is intentionally a local console application. It does not provide:

- Web or mobile interfaces
- Online payment
- Video conferencing
- Automated grading
- Plagiarism detection
- Multi-site synchronisation

## Upgrade and rollback

Version 1.0 is the initial deployment release. To preserve data before a future upgrade, stop the application and copy the SQLite database. If rollback is required, restore the backup under a new database filename and run the compatible release executable against it.
