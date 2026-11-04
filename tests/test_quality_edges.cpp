#include "lms/database.hpp"
#include "lms/moderation_service.hpp"
#include "lms/password_hasher.hpp"
#include "lms/user.hpp"

#include <gtest/gtest.h>

namespace {

TEST(QualityEdges, DatabaseReportsScriptErrorsAsExceptions) {
    lms::Database database(":memory:");
    EXPECT_THROW(database.execute_script("CREATE TABLE broken (id INTEGER;"), std::runtime_error);
}

// cppcheck-suppress syntaxError
TEST(QualityEdges, UserFactoryRejectsInvalidRoleAndNamesEveryRole) {
    EXPECT_EQ(lms::role_name(lms::Role::Student), "STUDENT");
    EXPECT_EQ(lms::role_name(lms::Role::Lecturer), "LECTURER");
    EXPECT_EQ(lms::role_name(lms::Role::HeadOfDepartment), "HOD");
    EXPECT_EQ(lms::role_name(lms::Role::SystemAdministrator), "ADMIN");
    EXPECT_THROW(lms::UserFactory::create(1, "bad", static_cast<lms::Role>(99)), std::invalid_argument);
}

TEST(QualityEdges, PasswordVerifierRejectsMalformedHashes) {
    EXPECT_FALSE(lms::PasswordHasher::verify("Password123", ""));
    EXPECT_FALSE(lms::PasswordHasher::verify("Password123", "pbkdf2-sha256$bad"));
    EXPECT_FALSE(lms::PasswordHasher::verify("Password123", "pbkdf2-sha256$210000$00$00"));
    EXPECT_THROW(lms::PasswordHasher::hash("short"), std::invalid_argument);
}

TEST(QualityEdges, ModerationQueriesReturnScopedSummaries) {
    lms::Database database(":memory:");
    database.execute_script(R"SQL(
        CREATE TABLE department (department_id INTEGER PRIMARY KEY, name TEXT);
        CREATE TABLE course (course_id INTEGER PRIMARY KEY, department_id INTEGER);
        CREATE TABLE assignment (assignment_id INTEGER PRIMARY KEY, course_id INTEGER);
        CREATE TABLE hod_department (hod_user_id INTEGER, department_id INTEGER, PRIMARY KEY(hod_user_id, department_id));
        CREATE TABLE enrolment (course_id INTEGER, student_id INTEGER, withdrawn_at TEXT);
        CREATE TABLE submission (submission_id INTEGER PRIMARY KEY, assignment_id INTEGER, student_id INTEGER);
        CREATE TABLE mark (mark_id INTEGER PRIMARY KEY, submission_id INTEGER, raw_mark REAL, final_mark REAL, feedback TEXT);
        CREATE TABLE assessment_batch (batch_id INTEGER PRIMARY KEY, assignment_id INTEGER UNIQUE, status TEXT, released_at TEXT);
        CREATE TABLE moderation_decision (decision_id INTEGER PRIMARY KEY, batch_id INTEGER, mark_id INTEGER, hod_user_id INTEGER, decision TEXT, reason TEXT, decided_at TEXT, UNIQUE(batch_id, mark_id));
        INSERT INTO department VALUES (1, 'Computing');
        INSERT INTO course VALUES (1, 1);
        INSERT INTO assignment VALUES (1, 1);
        INSERT INTO hod_department VALUES (7, 1);
        INSERT INTO enrolment VALUES (1, 9, NULL);
        INSERT INTO submission VALUES (1, 1, 9);
        INSERT INTO mark VALUES (1, 1, 80, 80, 'Good');
    )SQL");
    lms::ModerationService service(database);
    const auto before = service.batches_for_hod(7);
    EXPECT_TRUE(before.empty());
    const int batch = service.open_batch(7, 1);
    const auto batches = service.batches_for_hod(7);
    ASSERT_EQ(batches.size(), 1U);
    EXPECT_EQ(batches.front().batch_id, batch);
    const auto marks = service.marks_for_batch(7, batch);
    ASSERT_EQ(marks.size(), 1U);
    EXPECT_EQ(marks.front().decision, "PENDING");
}

} // namespace
