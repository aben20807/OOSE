#ifndef PERSON_ROLE_H
#define PERSON_ROLE_H

class Person;

class PersonRole {
 public:
  void linkPerson(Person* person) { this->person = person; }
  Person* get_person() const { return person; }
  virtual ~PersonRole() = default;

 private:
  Person* person{nullptr};
};

#endif /* PERSON_ROLE_H */
