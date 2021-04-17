#include "bus_booking_transactor.h"

BusBookingTransactor::BusBookingTransactor(
    std::string name, BusBookingTransactingBehaviorPtr booking_helper)
    : name_{name}, booking_helper_{std::move(booking_helper)} {}

std::string BusBookingTransactor::get_name() { return name_; }