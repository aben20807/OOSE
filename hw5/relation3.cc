#include <iostream>
#include <vector>

#include "board_of_directors.h"
#include "common.h"
#include "company.h"

int main() {
  auto apple = new Company("Apple", "0123456789");
  auto board_of_apple = new BoardOfDirectors();
  apple->set_board_of_directors(board_of_apple);

  std::cout << "The company of the board: ";
  std::cout << board_of_apple->get_company()->get_name() << "\n";
  std::cout << "The number of board members of Apple company: ";
  std::cout << apple->get_board_of_directors()->get_num_of_board() << "\n";

  /* Release allocated resources */
  delete apple;
  delete board_of_apple;
  return 0;
}