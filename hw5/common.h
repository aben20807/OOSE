#ifndef COMMON_H
#define COMMON_H

enum class Position {
  Chairman,
  Director,
  Manager,
  ProductManager,
  SeniorEngineer,
  JuniorEngineer,
  AdministrativeAssistant,
};

enum class Gender : unsigned char {
  M,  // male
  F,  // female
  O,  // other
};

#endif /* COMMON_H */