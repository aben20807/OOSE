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

enum class Gender {
  M,
  F,
  O,  // other
};

enum class Field {
  Name,
  Id,
  Gender,
  Position,
};

#endif /* COMMON_H */