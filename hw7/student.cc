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
