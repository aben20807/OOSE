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
