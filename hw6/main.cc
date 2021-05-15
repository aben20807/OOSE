#include "airline.h"
#include "person.h"
#include "person_role.h"
#include "specific_flight.h"

int main() {
  Airline* happy_air = new Airline("Happy Air");
  RegularFlight* flight1 = new RegularFlight(Time{8, 17}, 1, happy_air);

  Person* alice = new Person("Alice", "0123");
  Person* bob = new Person("Bob", "0124");
  Person* carol = new Person("Carol", "0125");
  Person* dave = new Person("Dave", "0126");
  Person* eve = new Person("Eve", "0127");
  Person* isaac = new Person("Isaac", "0128");
  Person* justin = new Person("Justin", "0129");

  for (auto& p : {alice, bob, carol, dave, eve, isaac, justin}) delete p;
  delete flight1;
  delete happy_air;
  return 0;
}
