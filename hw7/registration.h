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
