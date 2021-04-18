#include "bus_booking_transactor.h"

BusBookingTransactor::BusBookingTransactor(std::string name) : name_{name} {}

std::string BusBookingTransactor::get_name() { return name_; }