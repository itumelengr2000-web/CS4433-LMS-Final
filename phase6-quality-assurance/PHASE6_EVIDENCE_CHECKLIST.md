# Phase 6 Evidence Checklist

Use this checklist to capture the evidence required for the Phase 6 submission. Run the commands from the project root in WSL2. Do not include a real password, secret, or personal token in a screenshot.

## A. Clean Release build and automated tests

```bash
cd ~/projects/lms-phase4
rm -rf build-release
cmake -S . -B build-release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build-release
ctest --test-dir build-release --output-on-failure
```

Capture the final terminal showing the successful build and:

```text
100% tests passed, 0 tests failed out of 39
```

Suggested filename: `phase6-01-release-build-and-tests.png`.

## B. Static analysis

```bash
cppcheck --enable=warning,style,performance,portability \
  --std=c++17 --suppress=missingIncludeSystem \
  -I include src
```

Capture the final output showing all 14 production source files checked and no reported findings.

Suggested filename: `phase6-02-cppcheck.png`.

## C. Coverage evidence

Run the coverage build and measure the tested business-logic scope. The interactive console shell and `main.cpp` entry point are covered by manual demonstration rather than GoogleTest:

```bash
gcovr --root . --object-directory build-coverage \
  --filter 'src/.*\.cpp' \
  --exclude 'src/console_ui\.cpp' \
  --exclude 'src/main\.cpp' \
  --merge-mode-functions=separate --print-summary
```

Expected business-logic result: approximately **80.7% line coverage**. The all-source result including the interactive shell is approximately 59.8% and should not be presented as the business-logic metric.

If a fresh terminal capture is required, run the coverage commands from `PHASE5_TEST_STRATEGY.md` and capture the summary.

Suggested filename: `phase6-03-coverage.png`.

## D. Audit-log evidence

Use the database that contains the demonstration data, currently `fresh-demo.db`:

```bash
sqlite3 fresh-demo.db -header -column "
SELECT changed_by, entity_type, entity_id, action,
       old_value, new_value, reason, changed_at
FROM audit_log
ORDER BY changed_at;
"
```

Capture a row showing the actor, mark change, new value, reason, and UTC timestamp.

Suggested filename: `phase6-04-audit-log.png`.

## E. Repository hygiene

```bash
git status --short
git log --oneline -4
git ls-files '*.db' '*.db-wal' '*.db-shm'
```

The status should be clean, and the final command should produce no output.

Suggested filename: `phase6-05-clean-repository.png`.

## F. Manual acceptance evidence

Attach screenshots from the end-to-end demonstration for:

1. Administrator dashboard and account/academic setup.
2. Student submission and resubmission.
3. Lecturer marking and feedback.
4. Audit-log query after marking.
5. HoD approval/rejection and release.
6. Student viewing the released mark.

Keep the screenshots readable and crop out unrelated personal information.

## Evidence summary

| Evidence | Result |
|---|---|
| Release build | PASS |
| Automated tests | 39/39 PASS |
| Production static analysis | PASS; 14 source files checked |
| Line coverage | 80.7% business logic (59.8% all source) |
| Audit logging | PASS; actor, time, old/new values and reason recorded |
| Open critical/high defects | None |
| Repository hygiene | Clean; generated databases ignored |
