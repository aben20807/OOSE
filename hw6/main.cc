#include "airline.h"
#include "booking.h"
#include "employee_role.h"
#include "passenger_role.h"
#include "person.h"
#include "person_role.h"
#include "regular_flight.h"
#include "specific_flight.h"

int main() {
  Airline* happy_air = new Airline("Happy Air");
  RegularFlight* flight1 = new RegularFlight(Time{8, 17}, 1, happy_air);
  SpecificFlight* flight1_0516 = new SpecificFlight(Date{2021, 5, 16}, flight1);
  SpecificFlight* flight1_0517 = new SpecificFlight(Date{2021, 5, 17}, flight1);
  SpecificFlight* flight1_0518 = new SpecificFlight(Date{2021, 5, 18}, flight1);

  RegularFlight* flight2 = new RegularFlight(Time{18, 47}, 2, happy_air);
  SpecificFlight* flight2_0516 = new SpecificFlight(Date{2021, 5, 16}, flight2);

  Person* alice =
      new Person("Alice", "0123", happy_air, {new EmployeeRole("captain")});
  Person* bob =
      new Person("Bob", "0124", happy_air, {new EmployeeRole("crew")});
  Person* carol =
      new Person("Carol", "0125", happy_air,
                 {new EmployeeRole("crew", bob->get_employee_role(0))});
  Person* dave =
      new Person("Dave", "0126", happy_air,
                 {new EmployeeRole("crew", bob->get_employee_role(0)),
                  new PassengerRole()});

  Person* eve = new Person("Eve", "0127", {new PassengerRole()});
  Person* isaac = new Person("Isaac", "0128", {new PassengerRole()});
  Person* justin = new Person("Justin", "0129", {new PassengerRole()});

  std::cout << "Date for flight1:\n";
  for (const auto& f : flight1->getSpecificFlights()) {
    std::cout << f->getDate() << "\n";
  }
  std::cout << "\nDate for flight2:\n";
  for (const auto& f : flight2->getSpecificFlights()) {
    std::cout << f->getDate() << "\n";
  }
  std::cout << "\nTime for flights in Happy Air:\n";
  for (const auto& f : happy_air->getRegularFlights()) {
    std::cout << "No." << f->getFlightNumber() << ": " << f->getTime() << "\n";
  }
  std::cout << "\nEmployees in Happy Air:\n";
  for (const auto& p : happy_air->getPeople()) {
    std::cout << p->getName() << "\n";
  }
  std::cout << "\nThe employees whose supervisor is Bob:\n";
  for (const auto& s : bob->get_employee_role(0)->getSubordinates()) {
    std::cout << s->get_person()->getName() << "\n";
  }

  for (auto& p : {alice, bob, carol, dave, eve, isaac, justin}) delete p;
  for (auto& p : {flight1_0516, flight1_0517, flight1_0518, flight2_0516})
    delete p;
  for (auto& p : {flight1, flight2}) delete p;
  delete happy_air;
  return 0;
}
