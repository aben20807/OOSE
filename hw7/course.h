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
