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
