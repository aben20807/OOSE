#include <iostream>
#include <vector>
#include "administrative_assistant.h"
#include "common.h"
#include "manager.h"

int main() {
  Employee* alice = new Manager("Alice", 0, Gender::F);
  Employee* bob = new Manager("Bob", 0, Gender::M);
  Employee* carol = new Manager("Carol", 0, Gender::M);
  Employee* dave = new Manager("Dave", 0, Gender::M);

  /* Each administrative assistant should have at least one manager as
   * the supervisor */
  Employee* eve = new AdministrativeAssistant("Eve", 0, Gender::F,
                                              dynamic_cast<Manager*>(alice));
  Employee* isaac = new AdministrativeAssistant("Isaac", 0, Gender::M,
                                                dynamic_cast<Manager*>(carol));
  Employee* justin = new AdministrativeAssistant("Justin", 0, Gender::M,
                                                 dynamic_cast<Manager*>(alice));

  /* Assign more manager as the supervisor */
  dynamic_cast<AdministrativeAssistant*>(eve)->AddSupervisor(
      dynamic_cast<Manager*>(bob));
  dynamic_cast<AdministrativeAssistant*>(eve)->AddSupervisor(
      dynamic_cast<Manager*>(dave));

  /* Validation */
  std::cout << "The supervisors of " << eve->get_name() << ":\n";
  for (const auto i :
       dynamic_cast<AdministrativeAssistant*>(eve)->get_supervisors()) {
    std::cout << i->get_name() << " ";
  }
  std::cout << "\n";

  std::cout << "The subordinates of " << alice->get_name() << ":\n";
  for (const auto i : dynamic_cast<Manager*>(alice)->get_subordinates()) {
    std::cout << i->get_name() << " ";
  }
  std::cout << "\n";

  /* Release allocated resources */
  for (auto& p : {alice, bob, carol, dave, eve, isaac, justin}) delete p;
  return 0;
}