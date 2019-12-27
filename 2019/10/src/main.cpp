#include "asteroids_map.hpp"
#include <fstream>
#include <iostream>
#include <vector>

int main( int argc, char* argv[] ) {
  if ( argc != 2 ) {
    std::cout << "Call like this: 'main \"input.txt\"!\n";
    return 1;
  }

  std::ifstream inputStream;
  inputStream.open( argv[1] );
  if ( ! inputStream.is_open() ) {
    std::cout << "Couldn't open file " << argv[1] << "!\n";
    return 2;
  }

  AsteroidsMap asteroidsMap{ inputStream };
  auto location = asteroidsMap.countBestObservatoryLocation();
  std::cout << location.count() << '\n';
}
