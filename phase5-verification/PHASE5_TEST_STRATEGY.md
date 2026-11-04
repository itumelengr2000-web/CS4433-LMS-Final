# Phase 5: Verification and Validation Test Strategy

## 1. Purpose

This strategy verifies the Moderated Learning Management System against the Phase 2 SRS, the Phase 3 design, and the Phase 4 implementation. It follows the V-model: unit tests verify individual rules and services, integration tests verify service/database collaboration, system tests verify complete role workflows, and acceptance tests verify the stakeholder-visible use cases.

## 2. Test levels

| Level | Objective | Test evidence |
|---|---|---|
| Unit | Verify isolated rules and classes | `test_late_penalty.cpp`, `test_password_hasher.cpp`, User Factory tests |
| Integration | Verify services, SQLite, prepared queries, transactions and audit records | Administration, academic administration, assignment, student, marking and moderation tests |
| System | Verify role dashboards and the end-to-end submission-to-release lifecycle | `END_TO_END_DEMO.md` and the acceptance scenarios in this document |
| Acceptance | Verify the three core use cases from the SRS | AT-01 through AT-06 below |

## 3. Test environment

- Ubuntu 26.04 under WSL2
- C++17
- CMake and Ninja
- SQLite3
- OpenSSL Crypto
- GoogleTest
- cppcheck
- GitHub Actions Ubuntu runner for CI

## 4. Entry and exit criteria

Testing starts when the source compiles and the test database can be created. Testing exits when all automated tests pass, cppcheck reports no errors, all high-severity defects are closed, and the acceptance scenarios are demonstrated with evidence.

## 5. Equivalence classes and boundary analysis

| Input/rule | Valid class | Invalid class | Boundary tests |
|---|---|---|---|
| Password | At least 8 characters | Fewer than 8 | 7 and 8 characters |
| Raw mark | 0 through maximum mark | Negative or above maximum | 0, maximum, maximum + 1 |
| Late penalty | 0–72 hours late | More than 72 hours | On time, 24h, 72h, 72h + 1s |
| Assignment deadline | Valid UTC ISO-8601 timestamp | Malformed timestamp | Exact deadline and one second late |
| Role scope | Assigned lecturer/student/HoD | Unassigned or wrong department | Same course versus another course |
| Release | Every mark approved | Pending/rejected mark | Final pending mark before release |
| Submission versions | First and later versions | Missing/non-enrolled student | Version 1 and version 2 |

## 6. Core acceptance tests

| ID | Use case | Steps | Expected result |
|---|---|---|---|
| AT-01 | Administrator setup | Create users, department, course, HoD assignment, lecturer assignment, and enrolment | Records persist and invalid duplicates are rejected |
| AT-02 | Submit assignment | Student opens an active enrolled assignment and submits a file | Version 1, checksum, timestamp, and on-time/late status are stored |
| AT-03 | Resubmit assignment | Student submits a revised file | Version 2 is stored and version 1 remains available |
| AT-04 | Mark and audit | Lecturer views a scoped submission and enters a valid mark and feedback | Final mark is calculated, status changes to MARKED, and audit record contains actor, timestamp, old/new values and reason |
| AT-05 | Moderate and release | HoD rejects a mark, attempts release, approves it, then releases the batch | Release is blocked while rejected/pending; release succeeds only after all marks are approved |
| AT-06 | Student result visibility | Student checks before and after HoD release | Mark is hidden before release and visible with feedback after release |

## 7. Automated test mapping

The GoogleTest executable contains tests for authentication, account management, academic administration, assignment management, extensions, late penalties, polymorphic User construction, password hashing, submissions, marking, moderation, UI construction, and transaction rollback. Run:

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

Expected result for the Phase 5 baseline repository: **37 tests passed**. Phase 8 adds two regression tests, making the current result 39 tests passed.

## 8. Coverage method

Coverage instrumentation is available without changing the normal build:

```bash
cmake -S . -B build-coverage -G Ninja -DCMAKE_BUILD_TYPE=Debug -DENABLE_COVERAGE=ON
cmake --build build-coverage
ctest --test-dir build-coverage --output-on-failure
```

The build produces GCC `.gcda` and `.gcno` files for inspection by `gcov` or a CI coverage action. The honest all-production-source result is approximately 59.8% because the interactive `console_ui.cpp` and `main.cpp` entry point are not driven by unit tests. The assessed business-logic scope excludes those manual-console/entry-point files and produces approximately 80.7% line coverage, exceeding the assignment threshold. The console shell is covered by the manual system demonstration.

Use this explicit business-logic command:

```bash
gcovr --root . --object-directory build-coverage \
  --filter 'src/.*\\.cpp' \
  --exclude 'src/console_ui\\.cpp' \
  --exclude 'src/main\\.cpp' \
  --merge-mode-functions=separate --print-summary
```

## 9. Defect handling

Every failed test or observed problem is recorded in `DEFECT_LOG.md` with severity, cause, correction, regression test and status. A release candidate is accepted only when no critical or high defects remain open.
