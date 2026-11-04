# Phase 8 Maintenance — Change Request 1

## Change request

> A lecturer should be able to extend the deadline for a whole class, not only for an individual student, and students should see the updated deadline in the assignment list.

## Classification

This is a **perfective maintenance** change. It adds a new supported business capability after the version 1.0 release while preserving the existing individual-extension workflow.

## Impact analysis

| Area | Impact | Decision |
|---|---|---|
| Lecturer UI | New whole-class extension action is required. | Add option 5; shift submission and marking options to 6 and 7. |
| Student UI | Students must see the effective class deadline. | Display the effective deadline and label `[WHOLE-CLASS EXTENSION]`. |
| Assignment service | A new scoped service operation is required. | Add `grant_class_extension`. |
| Database | Individual extension rows cannot represent one deadline for an entire class without duplication. | Add normalised `class_extension` table with one row per assignment. |
| Submission deadline logic | Late calculation must use the class deadline when no individual deadline exists. | Use individual extension first, then class extension, then original deadline. |
| Existing individual extensions | Must continue to override the class deadline for the affected student. | Preserve the existing `extension` table and precedence rule. |
| Security/access control | Only the lecturer responsible for the assignment may change its class deadline. | Reuse lecturer-course and assignment scope checks. |
| Persistence and migration | Existing databases must continue to open. | `CREATE TABLE IF NOT EXISTS class_extension` is applied at startup by `schema.sql`. |

## Design change

Version 1.0 stored individual extensions in `extension`, keyed by `(assignment_id, student_id)`. Version 1.1 adds `class_extension`, keyed by `assignment_id`, with the original deadline, new deadline, reason, granting lecturer and UTC timestamp. This avoids duplicating a class-wide fact across every student row.

For a student, the effective deadline is resolved as:

```text
individual extension, if present
otherwise class-wide extension, if present
otherwise original assignment deadline
```

The class-wide deadline must be later than the original assignment deadline. Repeating the action updates the existing class-wide extension for that assignment rather than creating duplicate rows.

## Implementation summary

- Added `AssignmentService::grant_class_extension`.
- Added the `class_extension` SQLite table and assignment index.
- Added class-extension joins to student assignment and submission deadline queries.
- Added a visible whole-class extension label in the Student dashboard.
- Added a Lecturer dashboard action for class-wide extensions.
- Added regression tests for scope, deadline validation, upsert behavior, display and late calculation.

## Acceptance criteria

1. An assigned lecturer can extend an assignment deadline for the whole class.
2. An unassigned lecturer cannot make the change.
3. The new deadline must be later than the original deadline.
4. Repeating the operation updates the class-wide extension rather than creating duplicates.
5. Enrolled students see the updated effective deadline and extension label.
6. Submissions before the class-wide deadline are not classified as late.
7. An individual extension still takes precedence for the affected student.
8. All existing tests continue to pass.
