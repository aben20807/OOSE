#include <iostream>
#include <vector>

#include "common.h"
#include "company.h"
#include "employee.h"

int main() {
  /* New Company */
  auto apple = new Company("Apple", "0123456789");

  /* New employees */
  auto alice = new Employee("Alice", Gender::F, 0, Position::Chairman);
  auto bob = new Employee("Bob", Gender::M, 1, Position::SeniorEngineer);
  auto carol = new Employee("Carol", Gender::M, 2, Position::ProductManager);
  auto dave = new Employee("Dave", Gender::M, 3, Position::JuniorEngineer);
  auto eve = new Employee("Eve", Gender::F, 4, Position::JuniorEngineer);

  /* Add relation */
  apple->AddEmployee(alice);
  apple->AddEmployee(bob);
  apple->AddEmployee(carol);
  apple->AddEmployee(dave);
  apple->AddEmployee(eve);

  /* Validation */
  std::cout << "Number of employees in the company, " << apple->get_name()
            << ", is " << apple->get_num_of_employees() << ".\n";
  std::cout << alice->get_name() << " work for "
            << alice->get_workfor()->get_name() << ".\n";

  /* Filter function */
  std::cout << "Filter id where position is \"Junior Engineer\":\n";
  auto filter = apple->Filter(Position::JuniorEngineer);
  for (const auto e : filter) {
    std::cout << e->get_id() << " ";
  }
  std::cout << "\n";

  std::cout << "Filter name where gender is \"M\":\n";
  auto filter_gender = apple->Filter(Gender::M);
  for (const auto e : filter_gender) {
    std::cout << e->get_name() << " ";
  }
  std::cout << "\n";

  /* Release allocated resources */
  for (auto &p : {alice, bob, carol, dave, eve}) delete p;
  delete apple;
  return 0;
}
