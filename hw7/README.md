# Object-Oriented Software Engineering hw7

+ Author: 黃柏瑄 (P78081528)

## Environment

+ OS: Ubuntu18.04.5 (WSL2)
+ C++ compiler: g++ (Ubuntu 8.4.0-1ubuntu1~18.04) 8.4.0

## Source code

### File architecture
```txt
$  tree . -I 'bin|build|*.md|Makefile'
.
├── common.h
├── course.h
├── course_section.h
├── course_section.cc
├── registration.h
├── student.h
├── student.cc
├── main.cc
└── thread_pool.hpp
```

+ File `common.h`
  ```cpp
  #ifndef COMMON_H
#define COMMON_H
  
  enum class Result {
    doesNotHavePrereqs,
    hasPrereqs,
  
    hasPermission,
    noPermission,
  
    notFull,
    full,
  };
  
  #endif
  ```
  
+ File `course.h`
  ```cpp
  #ifndef COURSE_H
  #define COURSE_H
  
  #include <cstddef>
  #include <string>
  #include <vector>
  
  class Course {
   public:
    Course(std::string name, std::string serial_number, std::size_t max_num,
           std::vector<Course*> prerequisites)
        : name{name},
          serial_number{serial_number},
          max_num{max_num},
          prerequisites{prerequisites} {}
    Course(std::string name, std::string serial_number, int max_num)
        : Course(name, serial_number, max_num, {}) {}
    std::vector<Course*> get_prerequisites() const { return prerequisites; }
    std::string get_name() const { return name; }
    std::string get_serial_number() const { return serial_number; }
    std::size_t get_max_num() const { return max_num; }
  
   private:
    std::string name;
    std::string serial_number;
    std::size_t max_num;
    std::vector<Course*> prerequisites{};
  };
  
  #endif
  ```
  
+ File `course_section.h`
  ```cpp
  #ifndef COURSE_SECTION_H
  #define COURSE_SECTION_H
  
  #include <mutex>
  #include <vector>
  
  #include "common.h"
  #include "course.h"
  #include "registration.h"
  #include "student.h"
  #include "thread_pool.hpp"  // https://github.com/bshoshany/thread-pool
  
  class CourseSection {
   public:
    CourseSection(Course* const course) : course{course} {}
    ~CourseSection() { delete course; }
    Course* get_course() const { return course; }
    std::vector<Registration> get_registration_list() const {
      return registration_list;
    }
    int get_registration_num() const { return this->registration_list.size(); }
    void RequestToRegister(Student* student, bool verbose = true);
  
   private:
    Result CheckPrerequisites(const Student* const student, bool verbose) const;
    Result VerifyCourseNotFull(Student* const student);
    void CompleteRegistraion(const Student* const student, bool verbose) const;
  
    thread_pool pool{10};  // 使用 10 個執行緒處理註冊工作
    Course* course;
    mutable std::mutex registration_list_mutex;
    std::vector<Registration> registration_list{};
  };
  
  #endif
  ```
  
+ File `course_section.cc`
  ```cpp
  #include "course_section.h"
  
  void CourseSection::RequestToRegister(Student* student, bool verbose) {
    // 利用 thread pool 處理兩個工作: VerifyCourseNotFull 及 CheckPrerequisites
    // 此 thread pool 為現有開源標頭檔，來源:
    // https://github.com/bshoshany/thread-pool
    auto verify_course_not_full = pool.submit(
        [this, student] { return this->VerifyCourseNotFull(student); });
    auto check_prereqs = pool.submit([this, student, verbose] {
      return this->CheckPrerequisites(student, verbose);
    });
  
    // 等待並接收處理完的結果
    Result verify_course_not_full_value = verify_course_not_full.get();
    Result check_prereqs_value = check_prereqs.get();
  
    // 對結果進行處理
    if (verify_course_not_full_value == Result::notFull) {
      if (check_prereqs_value == Result::hasPrereqs ||
          check_prereqs_value ==
              Result::hasPermission) {  // 選課同學符合資格，所以選課成功
        this->CompleteRegistraion(student, verbose);
      } else {  // 當選課學生沒有選課資格時會在這邊進行移除
        const std::lock_guard<std::mutex> lock{this->registration_list_mutex};
        auto it = std::find_if(
            registration_list.begin(), registration_list.end(),
            [student](const auto& r) { return r.student == student; });
        if (it != registration_list.end()) {
          if (verbose) {
            std::cout << it->student->get_name()
                      << " does not meet the requirements.\n";
          }
          student->DeleteRegistration(it->course_section);
          registration_list.erase(it);
        }
      }
    } else {  // 課程人數已滿的情況
      if (verbose) {
        std::cout << student->get_name() << " failed to register because "
                  << this->course->get_name() << " is full.\n";
      }
    }
  }
  
  void CourseSection::CompleteRegistraion(const Student* const student,
                                          bool verbose) const {
    if (verbose) {
      std::cout << student->get_name() << " registration suceed for "
                << this->course->get_name() << ".\n";
    }
  }
  
  Result CourseSection::CheckPrerequisites(const Student* const student,
                                           bool verbose) const {
    std::vector<Course*> prerequisites = this->course->get_prerequisites();
    // 確認是否有修過前修課
    if (student->CheckPrerequisites(prerequisites) == Result::hasPrereqs) {
      if (verbose) {
        std::cout << student->get_name() << " has taken all prerequisites of "
                  << this->course->get_name() << ".\n";
      }
      return Result::hasPrereqs;
    }
    // 確認是否有修課授權
    if (student->CheckSpecialPermission({this->course}) ==
        Result::hasPermission) {
      if (verbose) {
        std::cout << student->get_name() << " has permission for "
                  << this->course->get_name() << ".\n";
      }
      return Result::hasPermission;
    }
    return Result::noPermission;
  }
  
  /**
     因為在選課同時去確認人數的話有可能遇到回報人數未滿，但是若同時有其他人在選，將導致數量錯誤。
     因此改為這樣的設計:
     確認完未滿後不論同學是否有資格選課，都會將其註冊先放進已註冊的名單中， 在使用
     lock_guard 保護下能夠保證人數再加入這個同學時仍不會超過限制人數。
     如果之後發現同學不符合資格，則會在後面再利用 lock_guard
     保證註冊名單刪除時不會有其他操作， 該刪除動作在 RequestToRegister 中完成。
     */
  Result CourseSection::VerifyCourseNotFull(Student* const student) {
    const std::lock_guard<std::mutex> lock{this->registration_list_mutex};
    if (this->registration_list.size() < this->course->get_max_num()) {
      auto r = Registration{this, student};
      registration_list.push_back(r);
      student->AddRegistration(r);
      return Result::notFull;
    }
    return Result::full;
  }
  ```
  
+ File `registration.h`
  ```cpp
  #ifndef REGISTRATION_H
  #define REGISTRATION_H
  
  class CourseSection;
  class Student;
  
  struct Registration {
    Registration(CourseSection* cs, Student* const s)
        : course_section{cs}, student{s} {}
    CourseSection* course_section;
    Student* student;
  };
  
  #endif
  ```
  
+ File `student.h`
  ```cpp
  #ifndef STUDENT_H
  #define STUDENT_H
  
  #include <algorithm>  // find_if
  #include <iostream>
  #include <string>
  #include <vector>
  
  #include "common.h"
  #include "course.h"
  #include "registration.h"
  
  class Student {
   public:
    Student(std::string name, std::vector<Course*> taken_courses,
            std::vector<Course*> permitted_courses)
        : name{name},
          taken_courses{taken_courses},
          permitted_courses{permitted_courses} {}
    Student(std::string name) : Student(name, {}, {}) {}
    Student() {}
    std::string get_name() const { return name; }
    void AddRegistration(const Registration r);
    void DeleteRegistration(const CourseSection* cs);
    Result CheckPrerequisites(std::vector<Course*> prerequisites) const;
    Result CheckSpecialPermission(std::vector<Course*> prerequisites) const;
    std::vector<Registration> get_registration_list() const {
      return registration_list;
    }
  
   private:
    std::string name;
    std::vector<Course*> taken_courses{};
    std::vector<Course*> permitted_courses{};
    std::vector<Registration> registration_list{};
  };
  
  #endif
  ```
  
+ File `student.cc`
  ```cpp
  #include "student.h"
  
  /**
    用於確認 courses 內的所有課程是否都可以在 search_set 中找到
    */
  static bool CheckMatch(std::vector<Course*> courses,
                         std::vector<Course*> search_set) {
    std::size_t match_cnt = 0;
    for (const auto c : courses) {
      for (const auto ss : search_set) {
        if (ss->get_serial_number() == c->get_serial_number()) {
          match_cnt++;
          break;
        }
      }
    }
    return match_cnt == courses.size();
  }
  
  Result Student::CheckPrerequisites(std::vector<Course*> prerequisites) const {
    if (CheckMatch(prerequisites, this->taken_courses)) {
      return Result::hasPrereqs;
    } else {
      return Result::doesNotHavePrereqs;
    }
  }
  
  Result Student::CheckSpecialPermission(std::vector<Course*> courses) const {
    if (CheckMatch(courses, this->permitted_courses)) {
      return Result::hasPermission;
    } else {
      return Result::noPermission;
    }
  }
  
  void Student::AddRegistration(const Registration r) {
    this->registration_list.push_back(r);
  }
  
  void Student::DeleteRegistration(const CourseSection* cs) {
    auto it =
        std::find_if(registration_list.begin(), registration_list.end(),
                     [cs](const auto& r) { return r.course_section == cs; });
    if (it != registration_list.end()) {
      registration_list.erase(it);
    }
  }
  ```
  
+ File `main.cc`
  ```cpp
  #include <map>
  #include <string>
  #include <vector>
  
  #include "course_section.h"
  
  std::map<std::string, CourseSection*> SetupCourses();
  void FreeCourses(std::map<std::string, CourseSection*>& courses);
  void SequentialSimulation();
  void MultithreadingSimulation();
  void RegisterHelper(CourseSection* cs, Student* s);
  void PrintInfo(const CourseSection* cs);
  void PrintInfo(const Student* s);
  
  int main() {
    SequentialSimulation();
    MultithreadingSimulation();
    return 0;
  }
  
  /**
    模擬學生在不同情況下是否可以選課
    */
  void SequentialSimulation() {
    auto courses = SetupCourses();
    // Alice 為一般學生
    Student* alice = new Student("Alice");
    courses["F7-004"]->RequestToRegister(alice);
    courses["F7-005"]->RequestToRegister(alice);
  
    // Bob 已經修過 F7-004
    Student* bob = new Student("Bob", {courses["F7-004"]->get_course()}, {});
    courses["F7-005"]->RequestToRegister(bob);
    courses["F7-007"]->RequestToRegister(bob);
  
    // Carol 擁有 F7-005, F7-007 的修課授權
    Student* carol = new Student(
        "Carol", {},
        {courses["F7-005"]->get_course(), courses["F7-007"]->get_course()});
    courses["F7-005"]->RequestToRegister(carol);
    courses["F7-007"]->RequestToRegister(carol);
    courses["F7-013"]->RequestToRegister(carol);
  
    // Dave 擁有 F7-005 的修課授權
    Student* dave = new Student("Dave", {}, {courses["F7-005"]->get_course()});
    courses["F7-005"]->RequestToRegister(dave);
  
    // Eve 為一般學生
    Student* eve = new Student("Eve");
    courses["F7-005"]->RequestToRegister(eve);
    courses["F7-012"]->RequestToRegister(eve);
  
    // Isaac 已經修過 F7-004, F7-010
    Student* isaac = new Student(
        "Isaac",
        {courses["F7-004"]->get_course(), courses["F7-010"]->get_course()}, {});
    courses["F7-005"]->RequestToRegister(isaac);
    courses["F7-011"]->RequestToRegister(isaac);
  
    // justin 已經修過 F7-004
    Student* justin =
        new Student("Justin", {courses["F7-004"]->get_course()}, {});
    courses["F7-005"]->RequestToRegister(justin);
  
    // 驗證每堂課的修課同學以及人數
    for (const auto& c : courses) {
      PrintInfo(c.second);
    }
  
    // 驗證每位同學修的課以及數量
    for (auto& s : {alice, bob, carol, dave, eve, isaac, justin}) {
      PrintInfo(s);
    }
  
    for (auto& p : {alice, bob, carol, dave, eve, isaac, justin}) delete p;
    FreeCourses(courses);
  }
  
  /**
    模擬多執行緒下搶同一堂課的結果
    */
  void MultithreadingSimulation() {
    auto courses = SetupCourses();
    std::vector<Student*> students(100);
    for (int i = 0; i < 100; i++) {
      students[i] = new Student("test" + std::to_string(i));
    }
  
    thread_pool tp{100};
    for (int i = 0; i < 100; i++) {
      tp.push_task(RegisterHelper, courses["F7-004"], students[i]);
    }
    tp.wait_for_tasks();
    PrintInfo(courses["F7-004"]);
    for (int i = 0; i < 100; i++) {
      delete students[i];
    }
    FreeCourses(courses);
  }
  
  void RegisterHelper(CourseSection* cs, Student* s) {
    cs->RequestToRegister(s, false);
  }
  
  /**
    初始化選課系統，設定不同課程的前修課以及人數
    */
  std::map<std::string, CourseSection*> SetupCourses() {
    std::map<std::string, CourseSection*> ret;
    Course* f7004 = new Course("PHYSICAL EDUCATION (1)", "F7-004", 20);
    Course* f7005 = new Course("PHYSICAL EDUCATION (2)", "F7-005", 4, {f7004});
    Course* f7006 = new Course("GENERAL PHYSICS (1)", "F7-006", 40);
    Course* f7007 = new Course("GENERAL PHYSICS (2)", "F7-007", 40, {f7006});
    Course* f7010 = new Course("PROGRAM DESIGN(1)", "F7-010", 5);
    Course* f7011 = new Course("PROGRAM DESIGN(2)", "F7-011", 50, {f7010});
    Course* f7012 = new Course("CALCULUS (1)", "F7-012", 6);
    Course* f7013 = new Course("CALCULUS (2)", "F7-013", 60, {f7012});
    ret.insert({f7004->get_serial_number(), new CourseSection(f7004)});
    ret.insert({f7005->get_serial_number(), new CourseSection(f7005)});
    ret.insert({f7006->get_serial_number(), new CourseSection(f7006)});
    ret.insert({f7007->get_serial_number(), new CourseSection(f7007)});
    ret.insert({f7010->get_serial_number(), new CourseSection(f7010)});
    ret.insert({f7011->get_serial_number(), new CourseSection(f7011)});
    ret.insert({f7012->get_serial_number(), new CourseSection(f7012)});
    ret.insert({f7013->get_serial_number(), new CourseSection(f7013)});
    return ret;
  }
  
  /**
    用於清除選課系統的資源
    */
  void FreeCourses(std::map<std::string, CourseSection*>& courses) {
    for (auto& c : courses) {
      delete c.second;
    }
  }
  
  void PrintInfo(const CourseSection* cs) {
    std::cout << "Course Name: " << cs->get_course()->get_name() << "\n"
              << "Course Serial Number: " << cs->get_course()->get_serial_number()
              << "\n"
              << "Registered Students:\n";
    auto rlist = cs->get_registration_list();
    for (const auto& r : rlist) {
      std::cout << "\t" << r.student->get_name() << "\n";
    }
    std::cout << "Total: " << rlist.size()
              << ", Max: " << cs->get_course()->get_max_num() << "\n\n";
  }
  
  void PrintInfo(const Student* s) {
    std::cout << "Student Name: " << s->get_name() << "\n"
              << "Registered Courses:\n";
    auto rlist = s->get_registration_list();
    for (const auto& r : rlist) {
      std::cout << "\t" << r.course_section->get_course()->get_name() << "\n";
    }
    std::cout << "Total: " << rlist.size() << "\n\n";
  }
  ```
  

## Executive results

```txt
$ ./bin/main
SequentialSimulation:
Alice has taken all prerequisites of PHYSICAL EDUCATION (1).
Alice registration suceed for PHYSICAL EDUCATION (1).
Alice does not meet the requirements.
Bob has taken all prerequisites of PHYSICAL EDUCATION (2).
Bob registration suceed for PHYSICAL EDUCATION (2).
Bob does not meet the requirements.
Carol has permission for PHYSICAL EDUCATION (2).
Carol registration suceed for PHYSICAL EDUCATION (2).
Carol has permission for GENERAL PHYSICS (2).
Carol registration suceed for GENERAL PHYSICS (2).
Carol does not meet the requirements.
Dave has permission for PHYSICAL EDUCATION (2).
Dave registration suceed for PHYSICAL EDUCATION (2).
Eve does not meet the requirements.
Eve has taken all prerequisites of CALCULUS (1).
Eve registration suceed for CALCULUS (1).
Isaac has taken all prerequisites of PHYSICAL EDUCATION (2).
Isaac registration suceed for PHYSICAL EDUCATION (2).
Isaac has taken all prerequisites of PROGRAM DESIGN(2).
Isaac registration suceed for PROGRAM DESIGN(2).
Justin has taken all prerequisites of PHYSICAL EDUCATION (2).
Justin failed to register because PHYSICAL EDUCATION (2) is full.
Course Name: PHYSICAL EDUCATION (1)
Course Serial Number: F7-004
Registered Students:
        Alice
Total: 1, Max: 20

Course Name: PHYSICAL EDUCATION (2)
Course Serial Number: F7-005
Registered Students:
        Bob
        Carol
        Dave
        Isaac
Total: 4, Max: 4

Course Name: GENERAL PHYSICS (1)
Course Serial Number: F7-006
Registered Students:
Total: 0, Max: 40

Course Name: GENERAL PHYSICS (2)
Course Serial Number: F7-007
Registered Students:
        Carol
Total: 1, Max: 40

Course Name: PROGRAM DESIGN(1)
Course Serial Number: F7-010
Registered Students:
Total: 0, Max: 5

Course Name: PROGRAM DESIGN(2)
Course Serial Number: F7-011
Registered Students:
        Isaac
Total: 1, Max: 50

Course Name: CALCULUS (1)
Course Serial Number: F7-012
Registered Students:
        Eve
Total: 1, Max: 6

Course Name: CALCULUS (2)
Course Serial Number: F7-013
Registered Students:
Total: 0, Max: 60

Student Name: Alice
Registered Courses:
        PHYSICAL EDUCATION (1)
Total: 1

Student Name: Bob
Registered Courses:
        PHYSICAL EDUCATION (2)
Total: 1

Student Name: Carol
Registered Courses:
        PHYSICAL EDUCATION (2)
        GENERAL PHYSICS (2)
Total: 2

Student Name: Dave
Registered Courses:
        PHYSICAL EDUCATION (2)
Total: 1

Student Name: Eve
Registered Courses:
        CALCULUS (1)
Total: 1

Student Name: Isaac
Registered Courses:
        PHYSICAL EDUCATION (2)
        PROGRAM DESIGN(2)
Total: 2

Student Name: Justin
Registered Courses:
Total: 0

MultithreadingSimulation:
Course Name: PHYSICAL EDUCATION (1)
Course Serial Number: F7-004
Registered Students:
        test0
        test1
        test2
        test11
        test12
        test4
        test14
        test15
        test18
        test3
        test28
        test6
        test30
        test29
        test5
        test7
        test31
        test16
        test24
        test17
Total: 20, Max: 20
```
