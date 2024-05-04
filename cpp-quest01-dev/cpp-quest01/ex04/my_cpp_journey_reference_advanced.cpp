#include <iostream>

void my_final_function(int nbr, int* nbr2) {
  *nbr2 = 1337;
  std::cout << nbr;
  std::cout << std::endl;  
}

void my_middle_function(const int& nbr, int& nbr2) {
  my_final_function(nbr, &nbr2);
}

int main() {
  const int nbr = 40;
  int nbr2 = 0;
  
  my_middle_function(nbr, nbr2);
  std::cout << nbr;
  std::cout << std::endl;
  std::cout << nbr2;
  std::cout << std::endl;
  return 0;
}
