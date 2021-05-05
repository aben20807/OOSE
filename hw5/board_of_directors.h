#ifndef BOARD_OF_DIRECTORS_H
#define BOARD_OF_DIRECTORS_H

#include <iostream>
#include <vector>
#include "common.h"
#include "person.h"

class Company;

class BoardOfDirectors {
 public:
  BoardOfDirectors() {}
  BoardOfDirectors(std::vector<const Person*>& p) {
    if (p.size() > 8 || p.size() < 3) {
      std::cerr << "[ERROR] The number of member should be in range 3 to 8.\n";
      return;
    }
    board_member_ = p;
  }
  void set_company(const Company* c) { company_ = c; }
  const Company* get_company() { return company_; }
  std::size_t get_num_of_board() const { return board_member_.size(); }

 private:
  std::vector<const Person*> board_member_{};
  const Company* company_{nullptr};
};

#endif /* BOARD_OF_DIRECTORS_H */
