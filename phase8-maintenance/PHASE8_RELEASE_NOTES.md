# LMS Release Notes — Version 1.1

## Maintenance release

Version 1.1 implements Change Request 1 from Phase 8 Maintenance: lecturers can extend an assignment deadline for the whole class.

## Added

- Lecturer dashboard action: `Extend deadline for whole class`.
- Persistent `class_extension` records in SQLite.
- Student assignment display of the effective class-wide deadline.
- Explicit `[WHOLE-CLASS EXTENSION]` label for affected assignments.
- Class-wide deadline use in on-time/late submission calculations.
- Regression tests for lecturer scope, validation, update behavior and student visibility.

## Preserved behavior

Individual student extensions continue to work. When both an individual extension and a class-wide extension exist, the individual extension takes precedence for that student. Existing authentication, role-based access, marking, moderation, audit logging, late penalties and release rules are unchanged.

## Quality result

```text
100% tests passed, 0 tests failed out of 39
```

The 39-test suite includes the original regression coverage plus two Phase 8 tests for whole-class extensions.

## Upgrade notes

The application applies the new `class_extension` table through `schema.sql` when an existing database is opened. Back up the SQLite database before upgrading:

```bash
cp school-lms.db backups/school-lms-before-v1.1.db
```

Then rebuild and run the normal test suite before using the upgraded database.

## Known scope

The change applies to assignment deadlines for the whole enrolled class. It does not change maximum marks, marking rules, moderation rules or the original assignment deadline stored in the `assignment` table.
