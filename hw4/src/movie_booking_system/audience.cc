#include "audience.h"

Audience::Audience(std::string name) : MovieBookingTransactor{name} {}

void Audience::AddBooking(int index, std::shared_ptr<MovieBooking> booking) {
  this->AddBookingTransaction(index, std::move(booking));
}

void Audience::PrintBookings() const {
  const auto& bookings_ = this->get_held_bookings();
  if (bookings_.empty()) {
    std::cout << name_ << " does not book any booking for movie.\n";
    return;
  }
  std::cout << name_ << " has booked:";
  for ([[maybe_unused]] const auto& [_, booking_ptr] : bookings_) {
    std::cout << " (" << booking_ptr->get_movie_name() << ", "
              << booking_ptr->get_movie_showing_date() << ")";
  }
  std::cout << ".\n";
}

void Audience::BookingAdded(std::shared_ptr<MovieBooking> b) {
  std::cout << "[Audience     INFO] booking added!:\n(" << *(b.get()) << ")\n";
}