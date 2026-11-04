# Phase 7 User Manual

## 1. Starting and stopping the LMS

From the project root, start the application with the database filename:

```bash
cd ~/projects/lms-phase4
./build/lms_app school-lms.db
```

At the login screen, enter the exact username and password. Password characters are hidden while typing.

To sign out, choose the `0. Sign out` option shown on the current dashboard. To stop the program completely, press `Ctrl+C` in the terminal after signing out or while the application is running.

## 2. Recommended first-time setup

The Administrator should perform setup in this order:

1. Create Lecturer, Student and HoD accounts.
2. Create a department.
3. Assign the HoD to the department.
4. Create a course linked to the department.
5. Assign the Lecturer to the course.
6. Enrol the Student in the course.
7. Sign out and test each role.

Record the displayed IDs because later operations use user, department, course, assignment, submission, batch and mark IDs.

## 3. Administrator dashboard

The Administrator dashboard provides:

```text
1. Create account
2. Edit account
3. Deactivate account
4. Create department
5. Create course
6. Assign lecturer
7. Enrol student
8. Withdraw student
9. Assign HoD to department
0. Sign out
```

### Create an account

Choose option `1`, enter a username, hidden password and role:

```text
1 = Student
2 = Lecturer
3 = HoD
4 = Administrator
```

Passwords must meet the validation rules. The system automatically creates the required student or lecturer profile.

### Create academic structure

Create the department first. Then create the course using the department ID. Assign the lecturer using the course ID and lecturer user ID. Enrol the student using the course ID and student user ID.

### HoD scope

A HoD must be assigned to the department containing the course. Without this link, the HoD cannot open or moderate an assignment from that department.

### Account deactivation

Deactivation prevents login while preserving linked academic records and audit history.

## 4. Lecturer dashboard

The Lecturer dashboard provides:

```text
1. Create assignment
2. Edit assignment
3. Activate/deactivate assignment
4. Grant an individual extension
5. View submissions
6. Enter marks and feedback
0. Sign out
```

### Create an assignment

Provide the course ID, title, instructions, UTC deadline, and maximum mark. The lecturer must be assigned to the course.

Example:

```text
Course ID: 1
Title: Final Project
Instructions: Submit the source code and report.
Effective due timestamp: 2026-11-07T23:59:59Z
Maximum mark: 100
```

### Edit or deactivate an assignment

Use the assignment ID. Editing and activation changes are restricted to the lecturer responsible for the assignment.

### Grant an extension

Enter the assignment ID, student user ID, new effective deadline and reason. Extensions are individual and do not alter the original deadline for other students.

### View and mark submissions

Choose `5` to view submissions in the lecturer's courses. Record the submission ID and version ID. Choose `6` and enter the raw mark and written feedback. The system validates the mark, applies the late penalty, stores the final mark, changes the submission status, and records an audit entry.

## 5. Student dashboard

The Student dashboard provides:

```text
1. View my courses and active assignments
2. Submit or resubmit an assignment
3. View my submission status
4. View released mark and feedback
0. Sign out
```

### View assignments

Choose option `1` to see active assignments for enrolled courses and their effective deadlines, including an individual extension where applicable.

### Submit or resubmit

Choose option `2`, enter the assignment ID and a valid path to the file:

```text
Assignment ID: 1
Path to file: /home/ubuntu/projects/sample-submission.txt
```

The system records a version number, receipt time, SHA-256 checksum and on-time/late status. A later submission is stored as a new version while the earlier version remains recorded.

### View status and released results

Choose option `3` to view submission versions and statuses. Choose option `4` to view a result. Marks remain hidden until the HoD releases the complete approved batch.

## 6. Head of Department dashboard

The HoD dashboard provides:

```text
1. Open or select assessment batch
2. View batch marks
3. Approve mark
4. Reject mark
5. Release approved batch
0. Sign out
```

### Open a batch

Choose option `1` and enter the assignment ID. The HoD must be assigned to the assignment's department.

### Review and decide

Choose option `2` to view marks. Choose option `3` to approve a mark with a reason or option `4` to reject it with a reason. Rejected or pending marks prevent release.

### Release results

Choose option `5` and enter the batch ID. Release succeeds only when every mark in the batch has been approved. After release, students can view their final mark and feedback.

## 7. Security and data rules

- Passwords are never displayed during entry.
- Passwords are stored as salted PBKDF2-HMAC-SHA256 hashes.
- Users can only access actions permitted by their role.
- Lecturers are restricted to assigned courses.
- HoDs are restricted to their departments.
- Students are restricted to enrolled courses and released results.
- Mark changes and moderation decisions are audited.
- Database files should be backed up and never committed to Git.

## 8. Common messages

| Message | Meaning | Action |
|---|---|---|
| `Invalid credentials` | Username/password combination failed | Check exact spelling, capitalisation and database filename |
| `No active assignments are available` | Student has no visible active assignment | Check enrolment and assignment activation |
| `Lecturer cannot access this course` | Lecturer is not assigned to the course | Ask Administrator to assign the lecturer |
| `HoD cannot access this assignment` | HoD is not linked to the assignment's department | Assign HoD to the correct department |
| `This mark has not been released yet` | Moderation is incomplete | HoD must approve all marks and release the batch |
| `Operation failed` | Input, validation or database operation failed | Read the displayed reason and correct the input |
