#ifndef BOOKING_H
#define BOOKING_H

class PassengerRole;
class SpecificFlight;

class Booking {
 public:
  Booking(int seatNumber) : seatNumber{seatNumber} {}
  void linkPassengerRole(PassengerRole* passenger) {
    this->passenger = passenger;
  }
  void linkSpecificFlight(SpecificFlight* specific_flight) {
    this->specific_flight = specific_flight;
  }

 private:
  int seatNumber;
  PassengerRole* passenger{nullptr};
  SpecificFlight* specific_flight{nullptr};
};

#endif /* BOOKING_H */
