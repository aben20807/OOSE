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
