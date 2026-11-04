# Defect Log

| ID | Severity | Description | Cause | Correction | Regression evidence | Status |
|---|---|---|---|---|---|---|
| D-001 | High | Mark and audit records used a fixed historical timestamp instead of the actual change time | Temporary implementation value remained in marking service | Added current UTC timestamp generation using `std::chrono` and UTC conversion | Marking audit-timestamp assertion; full CTest suite | Closed |
| D-002 | Medium | Requirements matrix still reported completed UI workflows as pending | Matrix was not refreshed after dashboard integration | Rewrote statuses for authentication, administrator, lecturer, student and HoD workflows | Traceability review; end-to-end guide | Closed |
| D-003 | Medium | Transaction rollback was not directly demonstrated by an automated failure-injection test | Only successful transaction paths were initially tested | Added an audit-trigger failure test and verified mark/status rollback | `MarkingService.RollsBackMarkAndStatusWhenAuditWriteFails` | Closed |
| D-004 | Low | Repository could include generated build/database artifacts if users staged all files carelessly | Submission process needed explicit ignore rules and guidance | Added `.gitignore` and Git submission checklist | Clean repository check; ignored `build/` and `*.db` | Closed |
| D-005 | Low | Course records were created through the UI but had no menu listing action | Initial console scope prioritised creation and downstream workflows | Documented SQLite course-view query and retained service-level persistence path | Manual database inspection command | Accepted enhancement |

No critical or high-severity defects remain open for the Phase 4 release candidate.
