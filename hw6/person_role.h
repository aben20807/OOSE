#ifndef PERSON_ROLE_H
#define PERSON_ROLE_H

class Person;

class PersonRole {
 public:
  void linkPerson(Person* person) { this->person = person; }
  Person* getPerson() const { return person; }
  virtual ~PersonRole() = default;

 protected:
  Person* person{nullptr};
};

#endif /* PERSON_ROLE_H */
