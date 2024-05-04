#include <iostream>

void my_initialize(int* nbr) {
  *nbr = 0;
}

int main() {
  int nbr = 40;
  
  std::cout << nbr;
  std::cout << std::endl;
  my_initialize(&nbr);
  std::cout << nbr;
  std::cout << std::endl;
  return 0;
}