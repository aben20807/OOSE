#include "passenger.h"

Passenger::Passenger(std::string name)
    : BusBookingTransactor{name, std::make_unique<BusBookingBuyingBehavior>()} {
}

void Passenger::AddBooking(int index, std::shared_ptr<BusBooking> booking) {
  booking_helper_->AddBookingTransaction(index, std::move(booking));
}

void Passenger::PrintBookings() const {
  auto& bookings_ = booking_helper_->get_held_bookings();
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