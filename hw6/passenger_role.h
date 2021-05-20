#ifndef PASSENGER_ROLE_H
#define PASSENGER_ROLE_H

#include <vector>

#include "booking.h"
#include "person_role.h"
#include "specific_flight.h"

class PassengerRole : public PersonRole {
 public:
  PassengerRole() {}
  ~PassengerRole() {
    for (auto& b : bookings) {
      delete b;
    }
  }
  void addBooking(Booking* booking) {
    bookings.emplace_back(booking);
    booking->linkPassengerRole(this);
  }

  Booking* bookSpecificFlight(SpecificFlight* specific_flight, int seatNumber) {
    Booking* b = new Booking(seatNumber);
    this->addBooking(b);
    specific_flight->addBooking(b);
    return b;
  }
  void printBookings() {
    for (const auto& b : bookings) {
      std::cout << b->getSeatNumber() << " : "
                << b->getSpecificFlight()->getDate() << " : "
                << b->getSpecificFlight()->getRegularFlight()->getTime()
                << "\n";
    }
  }
  void cancelBooking(Booking* booking) {
    for (auto it = bookings.begin(); it != bookings.end(); ++it) {
      if (*it == booking) {
        (*it)->getSpecificFlight()->cancelBooking(*it);
        delete *it;
        bookings.erase(it);
        break;
      }
    }
  }

 private:
  std::vector<Booking*> bookings{};
};

#endif /* PASSENGER_ROLE_H */
