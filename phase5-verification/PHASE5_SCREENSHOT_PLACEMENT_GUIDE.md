# Phase 5 Screenshot Placement Guide

This GitHub-readable document is the conversion of the updated `PHASE5_SCREENSHOT_PLACEMENT_GUIDE.docx` supplied with screenshots. The screenshots are stored in `evidence/`.

## Screenshot mapping

| Screenshot | Evidence shown | Acceptance mapping |
|---|---|---|
| [Screenshot 1](evidence/phase5-01.png) | CMake build and automated tests | Phase 5 exit criteria |
| [Screenshot 2](evidence/phase5-02.png) | Administrator accounts, department, course, assignments and enrolment | AT-01 — Administrator setup |
| [Screenshot 3](evidence/phase5-03.png) | Student active assignment and successful first submission | AT-02 — Submit assignment |
| [Screenshot 4](evidence/phase5-04.png) | Successful resubmission and version 2 | AT-03 — Resubmit assignment |
| [Screenshot 5](evidence/phase5-05.png) | Lecturer mark, feedback and success message | AT-04 — Mark and audit |
| [Screenshot 6](evidence/phase5-06.png) | SQLite audit output showing actor, action, values, reason and timestamp | AT-04 — Mark and audit |
| [Screenshot 7](evidence/phase5-07.png) | HoD moderation, release blocking and successful release | AT-05 — Moderate and release |
| [Screenshot 8](evidence/phase5-08.png) | Student final mark and feedback after release | AT-06 — Student result visibility |
| [Screenshot 9](evidence/phase5-09.png) | Coverage output | Coverage evidence |

## Captions

1. C++17 build and automated verification completed successfully.
2. Administrator completed academic structure and role-account setup.
3. Enrolled student submitted the active assignment and the system recorded the first version and status.
4. The student resubmitted; version 2 was stored while version 1 remained available.
5. The assigned Lecturer marked the scoped submission and recorded feedback.
6. The mark change was persisted with actor, timestamp, old/new values and reason.
7. The HoD moderated and released the batch only after required approvals.
8. The student viewed the final mark and written feedback after release.
9. Coverage evidence exceeded the 70% business-logic target; the final transparent metric is 80.7% business-logic line coverage and 59.8% all-source coverage.

## Acceptance execution record

| ID | Result | Screenshot evidence |
|---|---|---|
| AT-01 | PASS | Screenshot 2 — Administrator setup |
| AT-02 | PASS | Screenshot 3 — Student submission |
| AT-03 | PASS | Screenshot 4 — Student resubmission |
| AT-04 | PASS | Screenshots 5–6 — Marking and audit log |
| AT-05 | PASS | Screenshot 7 — HoD moderation and release |
| AT-06 | PASS | Screenshot 8 — Student released result |

The original updated Word evidence is [`PHASE5_SCREENSHOT_PLACEMENT_GUIDE.docx`](PHASE5_SCREENSHOT_PLACEMENT_GUIDE.docx). The test result record is [`PHASE5_TEST_RESULTS.md`](PHASE5_TEST_RESULTS.md).
