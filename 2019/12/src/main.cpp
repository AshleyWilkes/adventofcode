#include "n_body_engine.hpp"
#include <iostream>

int main() {
  std::vector<std::vector<int>> initialStatus {
      { -15, 1, 4 },
      { 1, -10, -8 },
      { -5, 4, 9 },
      { 4, 6, -2 } };
  NBodyEngine engine { initialStatus };
  engine.steps( 1000 );
  std::cout << engine.getTotalEnergy() << '\n';
}
