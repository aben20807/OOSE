#include "movie_booking_transactor.h"

MovieBookingTransactor::MovieBookingTransactor(std::string name)
    : name_{name} {}

std::string MovieBookingTransactor::get_name() { return name_; }