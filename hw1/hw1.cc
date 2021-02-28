// g++ --std=c++1z -O2 -Wall -o hw1 hw1.cc
// ./hw1
#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Date {
  int year;
  int month;
  int day;
};
std::ostream& operator<<(std::ostream& out, const Date date) {
  out << date.year << "/" << date.month << "/" << date.day;
  return out;
}

template <typename T, typename... Args>
std::shared_ptr<T> make_aggregate_shared(Args&&... args) {
  return std::make_shared<T>(T{std::forward<Args>(args)...});
}
struct Ticket {
  std::string buyer_name;
  int num_of_people;
  std::string bus_name;
  Date bus_departure_date;
};

class TicketTransactor {
 public:
  std::string get_name() const { return name_; }

 protected:
  explicit TicketTransactor(const std::string name) noexcept : name_{name} {}
  void NewTransaction(const std::shared_ptr<Ticket> ticket) {
    tickets_.push_back(std::move(ticket));
  }
  std::string name_;
  std::vector<std::shared_ptr<Ticket>> tickets_;
};

class Person : public TicketTransactor {
 public:
  explicit Person(const std::string name) noexcept : TicketTransactor{name} {}
  void BuyTicket(const std::shared_ptr<Ticket> ticket) {
    NewTransaction(std::move(ticket));
  }
  void PrintBookedBuses() const {
    if (tickets_.empty()) {
      std::cout << name_ << " does not book any ticket for bus.\n";
      return;
    }
    std::cout << name_ << " has booked: ";
    for (const auto& t : tickets_) {
      std::cout << "(" << t->bus_name << ", " << t->bus_departure_date << ") ";
    }
    std::cout << std::endl;
  }
};

class Bus : public TicketTransactor {
 public:
  explicit Bus(const std::string name, const Date date) noexcept
      : TicketTransactor{name}, departure_date_{date} {}
  Date get_departure_date() const { return departure_date_; }
  void SellTicket(const std::shared_ptr<Ticket> ticket) {
    NewTransaction(std::move(ticket));
  }
  void PrintPassengers() const {
    if (tickets_.empty()) {
      std::cout << name_ << " does not have any passenger.\n";
      return;
    }
    std::cout << "The passengers of " << name_ << ": ";
    for (const auto& t : tickets_) {
      std::cout << "(" << t->buyer_name << ", " << t->num_of_people << ") ";
    }
    std::cout << std::endl;
  }

 private:
  Date departure_date_;
};

class TicketMachine {
 public:
  static TicketMachine& GetTicketMachine() noexcept {
    static TicketMachine instance;
    return instance;
  }
  TicketMachine(const TicketMachine&) = delete;
  void operator=(const TicketMachine&) = delete;
  void Book(Person* buyer, Bus* bus, const int num_of_people) const {
    auto ticket = make_aggregate_shared<Ticket>(buyer->get_name(),
                                                num_of_people, bus->get_name(),
                                                bus->get_departure_date());
    bus->SellTicket(ticket);
    buyer->BuyTicket(ticket);
  }

 private:
  TicketMachine() {}
};

int main() {
  /* People */
  auto alice = std::make_unique<Person>("Alice");
  auto bob = std::make_unique<Person>("Bob");
  auto carol = std::make_unique<Person>("Carol");
  auto dave = std::make_unique<Person>("Dave");
  auto eve = std::make_unique<Person>("Eve");

  /* Bus */
  auto bus100 = std::make_unique<Bus>("Bus100", Date{2021, 2, 25});
  auto bus101 = std::make_unique<Bus>("Bus101", Date{2021, 2, 26});
  auto bus102 = std::make_unique<Bus>("Bus102", Date{2021, 2, 27});
  auto bus103 = std::make_unique<Bus>("Bus103", Date{2022, 2, 28});

  /* Book tickets */
  auto& tmachine = TicketMachine::GetTicketMachine();
  tmachine.Book(alice.get(), bus100.get(), 4);
  tmachine.Book(alice.get(), bus102.get(), 2);
  tmachine.Book(bob.get(), bus100.get(), 6);
  tmachine.Book(carol.get(), bus101.get(), 3);
  tmachine.Book(dave.get(), bus100.get(), 5);

  /* Validation */
  bus100->PrintPassengers();
  alice->PrintBookedBuses();
  bus101->PrintPassengers();
  bob->PrintBookedBuses();
  bus103->PrintPassengers();
  eve->PrintBookedBuses();
  return 0;
}
