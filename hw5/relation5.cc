#include <vector>

#include "board_of_directors.h"
#include "common.h"
#include "person.h"

int main() {
  std::vector<const Person*> v1;
  v1.push_back(new Person("p0", Gender::F));
  v1.push_back(new Person("p1", Gender::F));
  v1.push_back(new Person("p2", Gender::M));
  v1.push_back(new Person("p3", Gender::M));
  v1.push_back(new Person("p4", Gender::F));

  auto board1 = new BoardOfDirectors(v1);
  std::cout << "The number of member: " << board1->get_num_of_board() << "\n";

  std::vector<const Person*> v2;
  v2.push_back(new Person("r0", Gender::F));
  v2.push_back(new Person("r1", Gender::F));

  auto board2 = new BoardOfDirectors(v2);
  std::cout << "The number of member: " << board2->get_num_of_board() << "\n";

  /* Release allocated resources */
  for (auto& p : v1) delete p;
  for (auto& p : v2) delete p;
  for (auto& p : {board1, board2}) delete p;
}