#ifndef PERSON_H
#define PERSON_H

#include <string>

#include "common.h"

class Person {
 public:
  Person(std::string name, Gender gender) : name_{name}, gender_{gender} {}
  std::string get_name() const { return name_; }
  Gender get_gender() const { return gender_; }
  virtual ~Person() = default;

 protected:
  std::string name_;
  Gender gender_;
};

#endif /* PERSON_H */