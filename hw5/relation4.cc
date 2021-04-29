#include <iostream>

#include "employee.h"
#include "office.h"

int main() {
  /* New employees */
  auto alice = new Employee("Alice", Gender::F, 0, Position::Chairman);
  auto bob = new Employee("Bob", Gender::M, 1, Position::SeniorEngineer);
  auto carol = new Employee("Carol", Gender::M, 2, Position::ProductManager);
  auto dave = new Employee("Dave", Gender::M, 3, Position::JuniorEngineer);
  auto eve = new Employee("Eve", Gender::F, 4, Position::JuniorEngineer);

  auto office = new Office("room1");
  office->AddEmployee(bob);
  office->AddEmployee(carol);
  office->AddEmployee(dave);

  for (auto &e : {alice, bob, carol, dave, eve}) {
    if (e->get_office() != nullptr)
      std::cout << e->get_name() << " is in " << e->get_office()->get_name()
                << ".\n";
    else
      std::cout << e->get_name() << " not in any office.\n";
    delete e;
  }
  delete office;
  return 0;
}