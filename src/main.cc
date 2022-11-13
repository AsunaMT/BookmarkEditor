#include <filesystem>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "bmk_controller.h"
#include "bmk_sys/bmk_element.h"

int main() {
  // auto x = stringSplit(
  //     "[JFP](https://www.cambridge.org/core/journals/"
  //     "journal-of-functional-programming)",
  //     ']');
  // std::cout << x.front() << "  " << x.back() << std::endl;
  // x.front().erase(x.front().begin());
  // x.back().erase(x.back().begin());
  // x.back().pop_back();
  // std::cout << x.front() << "  " << x.back() << std::endl;
  // FileNode ls("./src");
  // ls.MakeFiletree();
  // std::cout << ShowTree(&ls).getTreeStr();
  BmkController con;
  con.Launch();
  return 0;
}