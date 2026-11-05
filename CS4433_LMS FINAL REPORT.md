# Moderated Learning Management System

**CS4433 Software Engineering – Final Project Report**  
**Student:** Itumeleng Raphoto  
**Student number:** 202320764

## Abstract

This project developed a Moderated Learning Management System (LMS) to support the controlled submission, marking and release of coursework. The system provides separate access for students, lecturers, Heads of Department (HoDs) and administrators. Its central feature is a moderation workflow: lecturers record marks and feedback, HoDs review the assessment batch, and results are released only after the required approvals. The application was implemented as a C++17 console program with SQLite persistence. Password protection, submission versioning, late-submission handling and audit records were included. Verification evidence recorded 39 of 39 GoogleTest cases passing. Coverage was reported as 80.5% of lines, 94.6% of functions and 38.2% of branches.

## 1. Introduction

Learning management systems support the distribution and assessment of learning activities, but assessment results also require reliable oversight. Where marking and release are not controlled, errors may be published, changes may be difficult to trace, and students may receive inconsistent information. This project focuses on a moderated assessment process rather than attempting to reproduce every feature of a large commercial LMS.

The system allows students to submit and resubmit assignment files, lecturers to assess submissions and provide feedback, and HoDs to approve or reject marks before release. Administrators manage user accounts and system setup. The project artefacts are maintained in the public GitHub repository.

[Open the CS4433 LMS project repository](https://github.com/itumelengr2000-web/CS4433-LMS-Final)

## 2. Project management and lifecycle

The work was organised into eight linked phases: planning, requirements, design, implementation, verification, quality assurance, deployment and maintenance. Each phase produced artefacts used by later work. Project activities covered scope definition, stakeholder analysis, requirements specification, UML and database design, C++ implementation, automated testing, static analysis, release preparation and a maintenance change request.

## 3. Requirements engineering

The main stakeholders are students, lecturers, Heads of Department and system administrators. Their responsibilities are separated through role-based access so that users perform only the activities assigned to their role.

### 3.1 Functional requirements

- **FR1** – The system shall allow an administrator to create and manage user accounts and assign the appropriate role.
- **FR2** – The system shall allow students to view enrolled courses and active assignments, then submit or resubmit an assignment file.
- **FR3** – The system shall record submission versions, receipt information and whether a submission was on time.
- **FR4** – The system shall allow lecturers to review submissions and record marks with written feedback.
- **FR5** – The system shall allow an HoD to review, approve or reject marks and provide a reason for a rejection.
- **FR6** – The system shall prevent release of an assessment batch until the required marks have been approved.
- **FR7** – The system shall allow students to view marks and feedback after results have been released.
- **FR8** – The system shall record significant actions and changes in an audit log.

### 3.2 Non-functional requirements

- **Security:** passwords are protected using PBKDF2-based password derivation and access is separated by role.
- **Integrity:** submission versions, marks, moderation decisions and release status are stored persistently.
- **Traceability:** important changes record the actor, affected entity, action, values and reason where applicable.
- **Reliability:** validation and release checks prevent incomplete or unapproved results from being released.
- **Maintainability:** the implementation is separated into presentation, service, domain and persistence responsibilities.
- **Portability:** the application is built with C++17 and CMake and uses SQLite as its embedded database.

### 3.3 Use-case model and traceability

The use-case model identifies the four principal actors and the interactions required to submit work, mark submissions, moderate results, administer accounts and view released feedback. The requirements are reflected in the implementation and verification artefacts. A traceability record links requirements to design elements, source implementation and test cases. The repository includes a requirements traceability CSV.

[Open requirements-traceability.csv](https://github.com/itumelengr2000-web/CS4433-LMS-Final/blob/main/requirements-traceability.csv)

### 3.4 Scope

The delivered system is a console-based coursework assessment application. It concentrates on the assignment and marks lifecycle. It is not presented as a full web-based LMS with online teaching content, live classes or a graphical student portal. The console interface is a known usability limitation and a possible area for future development.

## 4. Software design

The design separates user interaction, application services, domain rules and data storage. This structure keeps role-specific workflows apart from the rules governing submissions, marking, moderation and release. The supplied Picture Guide was used as the reference for the diagrams.

### 4.1 Architecture and design

The layered component view groups the system into a presentation layer, application/service layer, domain layer and persistence/local-adapter layer. Services coordinate authentication, assignments, submissions, marking, moderation and administration. Domain objects represent the core academic entities and workflow rules. Repository interfaces and SQLite adapters handle persistent storage.

The class model and normalised entity-relationship diagram describe the principal records and relationships, including user accounts and role specialisations, departments, courses, enrolments, assignments, submissions, submission versions, marks, moderation, notifications, audit records and system settings. The behavioural diagrams show how a submission moves through submission, marking, moderation and release.

### 4.2 Design diagrams

| Figure 1. Phase 2 use-case diagram | Figure 2. Layered component architecture |
|:--:|:--:|
| ![Figure 1: Phase 2 use-case diagram](figures/figure-1.png) | ![Figure 2: Layered component architecture](figures/figure-2.jpeg) |
| **Figure 3. Core domain class diagram** | **Figure 4. Services, interfaces and patterns** |
| ![Figure 3: Core domain class diagram](figures/figure-3.jpeg) | ![Figure 4: Services, interfaces and patterns](figures/figure-4.jpeg) |
| **Figure 5. Submission lifecycle state machine** | **Figure 6. Assignment submission and moderation activity** |
| ![Figure 5: Submission lifecycle state machine](figures/figure-5.jpeg) | ![Figure 6: Assignment submission and moderation activity](figures/figure-6.jpeg) |
| **Figure 7. Submit-assignment sequence diagram** | **Figure 8. Normalised entity-relationship diagram** |
| ![Figure 7: Submit-assignment sequence diagram](figures/figure-7.jpeg) | ![Figure 8: Normalised entity-relationship diagram](figures/figure-8.jpeg) |

The eight diagram image files are included in the accompanying [`figures` folder](figures/). Keep that folder alongside this Markdown file in the repository so that the images render correctly on GitHub. The project's full design-phase artefacts are also available in the [Phase 3 design folder](https://github.com/itumelengr2000-web/CS4433-LMS-Final/tree/main/phase3-design).

## 5. Implementation, verification and quality assurance

### 5.1 Implementation

The application was implemented in C++17. CMake manages the build, SQLite provides embedded relational persistence, and OpenSSL is used for password-related cryptographic support. GoogleTest is used for automated tests. The codebase is organised into headers, source files and tests, with a build guide in the repository.

Implemented workflows include administrator account creation, student assignment viewing and submission, resubmission with a new version, lecturer marking and feedback, HoD moderation, approval-gated batch release, student viewing of released results and audit-log inspection. The database schema supports the records required by these workflows.

- [Source code](https://github.com/itumelengr2000-web/CS4433-LMS-Final/tree/main/src)
- [Header files](https://github.com/itumelengr2000-web/CS4433-LMS-Final/tree/main/include)
- [Build guide](https://github.com/itumelengr2000-web/CS4433-LMS-Final/blob/main/BUILD_GUIDE.md)

### 5.2 Security and persistence

Passwords are not stored as plain text; the implementation uses PBKDF2-based derivation. Role checks restrict access to administrative, lecturer, student and HoD functions. SQLite stores application records between runs. Audit entries capture who performed an action, the entity affected, the action and recorded change details. Submission versioning preserves a record of resubmitted work.

### 5.3 Verification and validation

Automated verification reported 39 tests passed and zero failed. The coverage report recorded 772 of 959 lines covered (80.5%), 70 of 74 functions covered (94.6%) and 867 of 2,272 branches covered (38.2%). These results indicate strong function coverage, while branch coverage leaves further paths for testing. Static analysis was also run using Cppcheck; this report does not claim that the scan produced zero warnings because the available evidence does not establish that conclusion.

End-to-end checks demonstrated the principal assessment workflow: create accounts, submit and resubmit work, mark submissions, reject and approve marks, block release when approvals are incomplete, release an approved batch, and view the released mark and feedback.

- [Verification evidence](https://github.com/itumelengr2000-web/CS4433-LMS-Final/tree/main/phase5-verification)
- [Quality-assurance artefacts](https://github.com/itumelengr2000-web/CS4433-LMS-Final/tree/main/phase6-quality-assurance)
- [Automated tests](https://github.com/itumelengr2000-web/CS4433-LMS-Final/tree/main/tests)

### 5.4 Configuration management

Git and GitHub were used to maintain the project repository and organise phase deliverables. CMake configuration and the build guide support repeatable compilation. The repository separates source code, tests, database schema, phase documentation and deployment materials. The requirements traceability file provides a link between requirements and implementation/testing evidence.

## 6. Deployment, maintenance and conclusion

### 6.1 Deployment

The application is built locally using the documented CMake workflow and its required C++17, SQLite, OpenSSL and GoogleTest dependencies. The deployment phase contains installation and user guidance, release notes and deployment-related artefacts. The project is delivered as a console application rather than a hosted web service.

[Open deployment documentation](https://github.com/itumelengr2000-web/CS4433-LMS-Final/tree/main/phase7-deployment)

### 6.2 Maintenance and change request

The maintenance phase records CR-01, described in the repository as a whole-class extension change, together with regression evidence. A change of this type must preserve the original submission and moderation rules while ensuring that any extension is applied consistently to the intended class or group. Regression testing is important because changes to deadlines can affect late-submission classification, receipt records and lecturer workflows.

[Open maintenance artefacts](https://github.com/itumelengr2000-web/CS4433-LMS-Final/tree/main/phase8-maintenance)

### 6.3 Professional, legal and ethical considerations

The system handles student accounts, assignment files, marks and feedback, which are sensitive academic records. Access should therefore be limited to authorised roles, passwords protected, and audit records retained responsibly. Marks should be released only through the defined approval process, supporting fairness and accountability. Users should be informed about how their information is used, and stored records should be protected against unauthorised access or disclosure. The implementation should be used in accordance with institutional policies on data protection, academic integrity, retention and acceptable use.

### 6.4 Limitations and future work

The current console interface is less accessible and intuitive than a graphical or web interface. The reported branch coverage is lower than line and function coverage, indicating a need for additional tests around conditional paths and exceptional cases. Future work could introduce a web interface, improve accessibility, expand role and permission tests, strengthen backup and recovery procedures, and extend audit-log review and reporting.

## 7. Conclusion

The project delivered a C++17 moderated LMS focused on assignment submission, marking, HoD approval and controlled result release. Its key contribution is the explicit moderation gate supported by persistent records, submission versioning and audit logging. The eight project phases provide a documented lifecycle from planning to maintenance, while automated and end-to-end tests provide evidence that the main workflows operate as intended.

## References

- SQLite (2026) *SQLite Documentation*. [https://www.sqlite.org/docs.html](https://www.sqlite.org/docs.html) (Accessed: 5 November 2026).
- OpenSSL Project (2026) *OpenSSL Documentation*. [https://docs.openssl.org/](https://docs.openssl.org/) (Accessed: 5 November 2026).
- GoogleTest (2026) *GoogleTest User’s Guide*. [https://google.github.io/googletest/](https://google.github.io/googletest/) (Accessed: 5 November 2026).
- Cppcheck (2026) *Cppcheck Manual*. [https://cppcheck.sourceforge.io/manual.html](https://cppcheck.sourceforge.io/manual.html) (Accessed: 5 November 2026).
- OWASP Foundation (2026) *Password Storage Cheat Sheet*. [https://cheatsheetseries.owasp.org/cheatsheets/Password_Storage_Cheat_Sheet.html](https://cheatsheetseries.owasp.org/cheatsheets/Password_Storage_Cheat_Sheet.html) (Accessed: 5 November 2026).
- Sommerville, I. (2016) *Software Engineering*. 10th edn. Harlow: Pearson.
- National University of Lesotho (2026) *CS4433 Software Engineering Project Assignment Guide*. Course material supplied for the project.
- CS4433 LMS Project Repository (2026) *Moderated Learning Management System: Phases 1–8, source code and project evidence*.

---

**National University of Lesotho**
