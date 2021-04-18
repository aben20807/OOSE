#include <iostream>
#include <memory>
#include "bus_booking_machine.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  /* New people */
  auto alice = std::make_unique<Passenger>("Alice");
  auto bob = std::make_unique<Passenger>("Bob");
  auto carol = std::make_unique<Passenger>("Carol");
  auto dave = std::make_unique<Passenger>("Dave");
  auto eve = std::make_unique<Passenger>("Eve");
  /* New buses */
  auto bus100 = std::make_unique<BusForBooking>("Bus100", Date{2021, 2, 25});
  auto bus101 = std::make_unique<BusForBooking>("Bus101", Date{2021, 2, 26});
  auto bus102 = std::make_unique<BusForBooking>("Bus102", Date{2021, 2, 27});
  auto bus103 = std::make_unique<BusForBooking>("Bus103", Date{2022, 2, 28});
  /* Book bus bookings */
  auto &bbmachine = BusBookingMachine::GetBusBookingMachine();
  bbmachine.MakeBooking(alice.get(), bus100.get(), 4);
  bbmachine.MakeBooking(alice.get(), bus102.get(), 2);
  bbmachine.MakeBooking(bob.get(), bus100.get(), 6);
  bbmachine.MakeBooking(carol.get(), bus101.get(), 3);
  bbmachine.MakeBooking(dave.get(), bus100.get(), 5);
  /* Validation */
  bus100->PrintBookings();
  alice->PrintBookings();
  bus101->PrintBookings();
  bob->PrintBookings();
  bus103->PrintBookings();
  eve->PrintBookings();
  return 0;
}