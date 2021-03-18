// g++ --std=c++1z -O2 -Wall -o hw2 hw2.cc
// ./hw2
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

struct Date {
  uint16_t year;
  uint8_t month;
  uint8_t day;
};
std::ostream& operator<<(std::ostream& out, const Date date) {
  out << date.year << "/" << static_cast<int>(date.month) << "/"
      << static_cast<int>(date.day);
  return out;
}

template <typename T, typename... Args>
std::shared_ptr<T> make_aggregate_shared(Args&&... args) {
  return std::make_shared<T>(T{std::forward<Args>(args)...});
}
struct Booking {
  std::string buyer_name;
  std::string bus_name;
  int num_of_people;
  Date bus_departure_date;
};

class BookingTransactor {
 public:
  std::string get_name() const { return name_; }
  void AddBooking(const int booking_index,
                  const std::shared_ptr<Booking> booking) {
    bookings_.emplace(booking_index, std::move(booking));
  }
  void DeleteBookingByIndex(const int booking_index) {
    auto erase_count = bookings_.erase(booking_index);
    if (erase_count == 0) {
      std::cout << name_
                << " did have the booking with index: " << booking_index
                << ".\n";
    }
  }
  virtual void PrintBookings() const = 0;

 protected:
  explicit BookingTransactor(const std::string name) noexcept : name_{name} {}
  std::string name_;
  std::unordered_map<int, std::shared_ptr<Booking>> bookings_;
};

class Person : public BookingTransactor {
 public:
  explicit Person(const std::string name) noexcept : BookingTransactor{name} {}
  void PrintBookings() const override {
    if (bookings_.empty()) {
      std::cout << name_ << " does not book any booking for bus.\n";
      return;
    }
    std::cout << name_ << " has booked:";
    for ([[maybe_unused]] const auto& [_, booking_ptr] : bookings_) {
      std::cout << " (" << booking_ptr->bus_name << ", "
                << booking_ptr->bus_departure_date << ")";
    }
    std::cout << ".\n";
  }
};

class BusForBooking : public BookingTransactor {
 public:
  explicit BusForBooking(const std::string name, const Date date) noexcept
      : BookingTransactor{name}, departure_date_{date} {}
  Date get_departure_date() const { return departure_date_; }
  void PrintBookings() const override {
    if (bookings_.empty()) {
      std::cout << name_ << " does not have any passenger.\n";
      return;
    }
    std::cout << "The passengers of " << name_ << ":";
    for ([[maybe_unused]] const auto& [_, booking_ptr] : bookings_) {
      std::cout << " (" << booking_ptr->buyer_name << ", "
                << booking_ptr->num_of_people << ")";
    }
    std::cout << ".\n";
  }

 private:
  Date departure_date_;
};

class BookingMachine {
 public:
  static BookingMachine& GetBookingMachine() {
    static BookingMachine instance;
    return instance;
  }
  void MakeBooking(BookingTransactor* const buyer, BookingTransactor* const bus,
                   const int num_of_people) {
    auto booking = make_aggregate_shared<Booking>(
        buyer->get_name(), bus->get_name(), num_of_people,
        dynamic_cast<BusForBooking*>(bus)->get_departure_date());
    bus->AddBooking(booking_index_, booking);
    buyer->AddBooking(booking_index_, booking);
    booking_index_++;
  }

 private:
  BookingMachine() {}
  inline static int booking_index_{0};
};

int main() {
  /* New people */
  auto alice = std::make_unique<Person>("Alice");
  auto bob = std::make_unique<Person>("Bob");
  auto carol = std::make_unique<Person>("Carol");
  auto dave = std::make_unique<Person>("Dave");
  auto eve = std::make_unique<Person>("Eve");

  /* New buses */
  auto bus100 = std::make_unique<BusForBooking>("Bus100", Date{2021, 2, 25});
  auto bus101 = std::make_unique<BusForBooking>("Bus101", Date{2021, 2, 26});
  auto bus102 = std::make_unique<BusForBooking>("Bus102", Date{2021, 2, 27});
  auto bus103 = std::make_unique<BusForBooking>("Bus103", Date{2022, 2, 28});

  /* Book bus bookings */
  auto& tmachine = BookingMachine::GetBookingMachine();
  tmachine.MakeBooking(alice.get(), bus100.get(), 4);
  tmachine.MakeBooking(alice.get(), bus102.get(), 2);
  tmachine.MakeBooking(bob.get(), bus100.get(), 6);
  tmachine.MakeBooking(carol.get(), bus101.get(), 3);
  tmachine.MakeBooking(dave.get(), bus100.get(), 5);

  /* Validation */
  bus100->PrintBookings();
  alice->PrintBookings();
  bus101->PrintBookings();
  bob->PrintBookings();
  bus103->PrintBookings();
  eve->PrintBookings();
  return 0;
}
