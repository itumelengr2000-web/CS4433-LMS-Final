# Phase 5 Screenshot Placement Guide

Use this guide to insert the screenshots from the manual LMS demonstration into the Phase 5 evidence document. The screenshots should show the application result clearly without exposing real passwords, tokens, or unrelated personal information.

## Recommended document order

Place the screenshots after the relevant acceptance-test row in `PHASE5_TEST_RESULTS.md`, or place them in an appendix titled `Manual Acceptance Evidence` and use the captions below.

## Screenshot mapping

### Screenshot 1 — Build and automated tests

**Insert after:** `## Execution summary`

**Shows:** CMake build and the final CTest result.

**Caption:**

> Figure 1. C++17 build and automated verification completed successfully: 37 of 37 tests passed.

**Maps to:** General Phase 5 exit criteria and automated verification.

Suggested filename: `phase5-01-build-tests.png`.

### Screenshot 2 — Administrator setup

**Insert after:** the AT-01 row in `## Acceptance execution record`.

**Shows:** Administrator dashboard with accounts, department, course, lecturer assignment, HoD assignment, and student enrolment completed. If one screenshot cannot show all actions, use two screenshots and label them Figure 2a and Figure 2b.

**Caption:**

> Figure 2. Administrator completed the academic structure and role-account setup.

**Maps to:** AT-01 — Administrator setup.

Suggested filenames: `phase5-02-admin-setup.png` and `phase5-02b-admin-setup.png`.

### Screenshot 3 — Student submits assignment

**Insert after:** the AT-02 row.

**Shows:** Student dashboard displaying the active assignment and the successful submission message, preferably including `Submission version 1 saved as ON TIME` or the applicable late-status message.

**Caption:**

> Figure 3. Enrolled student submitted the active assignment and the system recorded the first version and submission status.

**Maps to:** AT-02 — Submit assignment.

Suggested filename: `phase5-03-student-submission.png`.

### Screenshot 4 — Student resubmits assignment

**Insert after:** the AT-03 row.

**Shows:** Successful resubmission and the version-2 result, or the submission-status screen showing both versions.

**Caption:**

> Figure 4. The student resubmitted the assignment; version 2 was stored while version 1 remained available.

**Maps to:** AT-03 — Resubmit assignment.

Suggested filename: `phase5-04-student-resubmission.png`.

### Screenshot 5 — Lecturer marks submission

**Insert after:** the AT-04 row.

**Shows:** Lecturer submission view, entered raw mark, feedback, and successful marking message. Do not show the lecturer password.

**Caption:**

> Figure 5. The assigned lecturer marked the scoped submission and recorded feedback.

**Maps to:** AT-04 — Mark and audit.

Suggested filename: `phase5-05-lecturer-marking.png`.

### Screenshot 6 — Audit log

**Insert immediately after Screenshot 5 or directly below the AT-04 evidence.**

**Shows:** SQLite query output containing `changed_by`, `entity_type`, `action`, `new_value`, `reason`, and `changed_at`.

Use this query after stopping the LMS:

```bash
sqlite3 fresh-demo.db -header -column "
SELECT changed_by, entity_type, entity_id, action,
       old_value, new_value, reason, changed_at
FROM audit_log
ORDER BY changed_at;
"
```

**Caption:**

> Figure 6. The mark change was persisted in the audit log with the actor, timestamp, old/new values, and reason.

**Maps to:** AT-04 — Mark and audit; SRS audit-log requirement.

Suggested filename: `phase5-06-audit-log.png`.

### Screenshot 7 — HoD moderation and release

**Insert after:** the AT-05 row.

**Shows:** HoD approval or rejection, release-blocking result when appropriate, and successful release after all marks are approved. If these are separate screens, use Figure 7a and Figure 7b.

**Caption:**

> Figure 7. The HoD moderated the assessment batch and released it only after the required marks were approved.

**Maps to:** AT-05 — Moderate and release.

Suggested filenames: `phase5-07-hod-moderation.png` and `phase5-07b-hod-release.png`.

### Screenshot 8 — Student views released result

**Insert after:** the AT-06 row.

**Shows:** Student result screen displaying the final mark and written feedback after release. If you captured the pre-release hidden-result message, include it as Figure 8a and the post-release result as Figure 8b.

**Caption:**

> Figure 8. The student could view the final mark and feedback after HoD release; the mark was hidden before release.

**Maps to:** AT-06 — Student result visibility.

Suggested filenames: `phase5-08a-before-release.png` and `phase5-08b-after-release.png`.

### Screenshot 9 — Coverage result

**Insert after:** `## Coverage evidence`.

**Shows:** Coverage tool output showing **80% line coverage**.

**Caption:**

> Figure 9. Automated coverage measurement achieved 80% line coverage, exceeding the required 70% threshold.

**Maps to:** Coverage evidence and the assignment quality requirement.

Suggested filename: `phase5-09-coverage-80-percent.png`.

## Completed acceptance table template

Replace the blank fields in `PHASE5_TEST_RESULTS.md` with the actual date/time and filenames from your screenshots:

| ID | Result | Screenshot evidence |
|---|---|---|
| AT-01 | PASS | Figure 2 / `phase5-02-admin-setup.png` |
| AT-02 | PASS | Figure 3 / `phase5-03-student-submission.png` |
| AT-03 | PASS | Figure 4 / `phase5-04-student-resubmission.png` |
| AT-04 | PASS | Figures 5–6 / lecturer marking and audit log |
| AT-05 | PASS | Figure 7 / HoD moderation and release |
| AT-06 | PASS | Figure 8 / student released result |

## Screenshot quality checklist

Before submitting, confirm that every screenshot:

- Shows the relevant username or role only when useful.
- Does not show a typed password or secret.
- Includes enough terminal/application context to identify the result.
- Is readable at normal zoom.
- Has a figure number and caption.
- Matches the acceptance-test row it supports.
- Is stored in an evidence folder or appended to the final report.
