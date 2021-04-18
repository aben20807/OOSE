#include "movie_showing.h"

MovieShowing::MovieShowing(std::string name, Date showing_date)
    : MovieBookingTransactor{name}, showing_date_{showing_date} {}

void MovieShowing::AddBooking(int index,
                              std::shared_ptr<MovieBooking> booking) {
  this->AddBookingTransaction(index, std::move(booking));
}

Date MovieShowing::get_showing_date() const { return showing_date_; }

/**
 * @brief Overridden function to print passenger info from movie's booking list.
 */
void MovieShowing::PrintBookings() const {
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

void MovieShowing::BookingAdded(std::shared_ptr<MovieBooking> b) {
  std::cout << "[MovieShowing INFO] booking added!: (" << *(b.get()) << ")\n";
}