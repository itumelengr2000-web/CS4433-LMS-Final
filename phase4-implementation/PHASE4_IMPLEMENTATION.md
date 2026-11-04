# Phase 4 — Implementation

Phase 4 is implemented as a C++17 console-based Learning Management System with SQLite persistence. The build uses CMake and Ninja, and the project includes GoogleTest tests and cppcheck static analysis.

## Implementation structure

The implementation remains at the repository root so that the documented CMake build continues to work:

- `src/` — application and service implementations.
- `include/` — public headers and service interfaces.
- `tests/` — GoogleTest unit and integration tests.
- `CMakeLists.txt` — C++17 build and test configuration.
- `schema.sql` — normalised SQLite schema, indexes and constraints.
- `BUILD_GUIDE.md` — complete build and dependency instructions.
- `END_TO_END_DEMO.md` — manual demonstration workflow.

## Implemented functionality

The application provides role-based workflows for Administrator, Lecturer, Head of Department and Student users. It supports account administration, department and course management, lecturer assignment, student enrolment, assignment creation and editing, individual and whole-class extensions, versioned submissions, late-penalty calculation, marking, feedback, moderation, release and persistent audit logging.

## Security and persistence

Passwords are stored as salted PBKDF2-HMAC-SHA256 derived values through OpenSSL; plaintext passwords are not stored. Console password entry disables terminal echo. SQLite operations use parameterised statements through the data-access layer. Mark and moderation changes are transactional and are recorded in the audit log with actor, timestamp, old value, new value and reason.

## Verification evidence

Phase 4 implementation is verified by the Phase 5 automated tests and acceptance workflows. The current regression suite contains 39 passing tests after the Phase 8 maintenance change. See `phase5-verification/`, `phase6-quality-assurance/` and `phase8-maintenance/` for the evidence packages.
