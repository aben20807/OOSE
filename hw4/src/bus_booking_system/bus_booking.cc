#include "bus_booking.h"

BusBooking::BusBooking(std::string buyer_name, std::string bus_name,
                       int num_of_people, Date bus_departure_date)
    : buyer_name_{buyer_name},
      bus_name_{bus_name},
      num_of_people_{num_of_people},
      bus_departure_date_{bus_departure_date} {}

std::string BusBooking::get_buyer_name() const { return buyer_name_; }
std::string BusBooking::get_bus_name() const { return bus_name_; }
int BusBooking::get_num_of_people() const { return num_of_people_; }
Date BusBooking::get_bus_departure_date() const { return bus_departure_date_; }