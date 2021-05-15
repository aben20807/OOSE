#ifndef PASSENGER_ROLE_H
#define PASSENGER_ROLE_H

#include <vector>

#include "booking.h"
#include "person_role.h"

class PassengerRole : public PersonRole {
 public:
  PassengerRole() {}
  void addBooking(Booking* booking) {
    bookings.emplace_back(booking);
    booking->linkPassengerRole(this);
  }

 private:
  std::vector<Booking*> bookings{};
  Person* person;
};

#endif /* PASSENGER_ROLE_H */
