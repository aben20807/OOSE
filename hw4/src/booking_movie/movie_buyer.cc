#include <iostream>
#include <functional>
#include "../booking_framework/abstract_booking.h"

int main(int argc, char *argv[])
{
  [out = std::ref(std::cout << "Hello ")](){out.get() << "World\n";}();
  std::cout << AbstractBooking::adder(3,4);
  return 0;
}