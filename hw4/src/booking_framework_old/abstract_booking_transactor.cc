#include "abstract_booking_transactor.h"

AbstractBookingTransactor::AbstractBookingTransactor(std::string name)
    : _name{name} {}

std::string AbstractBookingTransactor::get_name() { return _name; }

void AbstractBookingTransactor::AddBookingTransaction() {}
void AbstractBookingTransactor::RemoveBookingTransaction() {}
