#include "bus_for_booking.h"

BusForBooking::BusForBooking(std::string name, Date departure_date)
    : BusBookingTransactor{name}, departure_date_{departure_date} {}

void BusForBooking::AddBooking(int index, std::shared_ptr<BusBooking> booking) {
  this->AddBookingTransaction(index, std::move(booking));
}

Date BusForBooking::get_departure_date() const { return departure_date_; }

void BusForBooking::PrintBookings() const {
  const auto& bookings_ = this->get_held_bookings();
  if (bookings_.empty()) {
    std::cout << name_ << " does not have any passenger.\n";
    return;
  }
  std::cout << "The passengers of " << name_ << ":";
  for ([[maybe_unused]] const auto& [_, booking_ptr] : bookings_) {
    std::cout << " (" << booking_ptr->get_buyer_name() << ", "
              << booking_ptr->get_num_of_people() << ")";
  }
  std::cout << ".\n";
}

void BusForBooking::BookingAdded(std::shared_ptr<BusBooking> b) {
  std::cout << "[BusForBooking INFO] booking added!:\n(" << *(b.get()) << ")\n";
}