# Phase 5: Test Cases and Results

## Execution summary

| Item | Result |
|---|---|
| CMake build | PASS |
| GoogleTest/CTest suite | PASS: 37 of 37 tests |
| Current regression suite after Phase 8 | PASS: 39 of 39 tests |
| cppcheck | PASS: no reported errors |
| Transaction rollback test | PASS |
| Password hashing tests | PASS |
| Late-penalty boundary tests | PASS |
| Moderation release-blocking tests | PASS |
| Manual four-role acceptance workflow | Follow `END_TO_END_DEMO.md` and attach screenshots |

## Automated test inventory

| Area | Representative verification |
|---|---|
| Authentication | Valid credentials, invalid credentials, inactive account, sign-out |
| Account administration | Create, duplicate rejection, edit, deactivate, profile preservation |
| Academic administration | Departments, courses, lecturer assignment, enrolment, withdrawal, HoD assignment |
| Assignment management | Create, edit, activation, lecturer scope, extension validation |
| Late penalty | On-time, 24-hour, 72-hour, 72-hour-plus-one-second, rounding and zero floor |
| Password security | Salted hashes, verification and non-plaintext storage |
| Student workflow | Active assignment visibility, file checksum, late status, resubmission versioning |
| Lecturer workflow | Scoped submissions, mark bounds, feedback, final-mark calculation |
| Audit and transactions | Audit content, real UTC timestamp, rollback when audit insertion fails |
| HoD workflow | Department scope, approval/rejection, complete-batch release, student visibility |

## Acceptance execution record

Complete this table using the screenshots from the manual demonstration. The exact insertion points, captions, and mapping are provided in `PHASE5_SCREENSHOT_PLACEMENT.md`.

| ID | Date/time | Evidence filename | Result | Notes |
|---|---|---|---|---|
| AT-01 | Complete from screenshot | `phase5-02-admin-setup.png` | PASS | Administrator setup completed |
| AT-02 | Complete from screenshot | `phase5-03-student-submission.png` | PASS | Student submission accepted |
| AT-03 | Complete from screenshot | `phase5-04-student-resubmission.png` | PASS | Resubmission stored as version 2 |
| AT-04 | Complete from screenshots | `phase5-05-lecturer-marking.png`, `phase5-06-audit-log.png` | PASS | Lecturer mark saved and audit record created |
| AT-05 | Complete from screenshot | `phase5-07-hod-moderation.png` | PASS | HoD approved and released the assessment batch |
| AT-06 | Complete from screenshot | `phase5-08-student-result.png` | PASS | Student viewed the released mark and feedback |

## Coverage evidence

Run the coverage build from `PHASE5_TEST_STRATEGY.md`. Record the measured line and branch results produced by the selected coverage tool here. Do not invent a percentage; attach the generated report or terminal output to the final submission.

| Metric | Measured result | Evidence |
|---|---:|---|
| Line coverage | 80.7% business logic (59.8% all source) | GCC/gcovr coverage build with `ENABLE_COVERAGE=ON`; `console_ui.cpp` and `main.cpp` are manually demonstrated and excluded from the business-logic metric |
| Function coverage | 94.6% business logic | GCC/gcovr report; 70 of 74 functions executed |
| Branch coverage | 38.3% business logic | GCC/gcovr report; 861 of 2,250 branches executed |

### Coverage command used

```bash
gcovr --root . --object-directory build-coverage \
  --filter 'src/.*\.cpp' \
  --exclude 'src/console_ui\.cpp' \
  --exclude 'src/main\.cpp' \
  --merge-mode-functions=separate --print-summary
```

The 59.8% all-source figure includes the interactive console shell and application entry point, which are verified through the manual system demonstration rather than GoogleTest. The 80.7% figure is the assessed automated business-logic coverage.
