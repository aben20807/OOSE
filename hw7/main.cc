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
  std::cout << "SequentialSimulation:\n";
  SequentialSimulation();
  std::cout << "MultithreadingSimulation:\n";
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
