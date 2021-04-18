#include "passenger.h"

Passenger::Passenger(std::string name) : BusBookingTransactor{name} {}

void Passenger::AddBooking(int index, std::shared_ptr<BusBooking> booking) {
  this->AddBookingTransaction(index, std::move(booking));
}

void Passenger::PrintBookings() const {
  const auto& bookings_ = this->get_held_bookings();
  if (bookings_.empty()) {
    std::cout << name_ << " does not book any booking for bus.\n";
    return;
  }
  std::cout << name_ << " has booked:";
  for ([[maybe_unused]] const auto& [_, booking_ptr] : bookings_) {
    std::cout << " (" << booking_ptr->get_bus_name() << ", "
              << booking_ptr->get_bus_departure_date() << ")";
  }
  std::cout << ".\n";
}

void Passenger::BookingAdded(std::shared_ptr<BusBooking> b) {
  std::cout << "[Passenger     INFO] booking added!: (" << *(b.get()) << ")\n";
}