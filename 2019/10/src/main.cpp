#include "asteroids_map.hpp"
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

void printATan2( float x, float y ) {
  std::cout << "atan2(" << x << ", " << y << ") = " << atan2(x, y) << '\n';
}

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

  auto lOSvector = asteroidsMap.getSortedLinesOfSightFrom( location.point() );
  if ( lOSvector.size() < 200 ) {
    std::cout << "!!!! there are less then 200 linesOfSight, more work is needed\n";
  } else {
    Point the200thAsteroid = unnormalize( lOSvector.at( 199 ).nearest(), location.point() );
    std::cout << "The 200th asteroid is at [" << the200thAsteroid.first << ", " << the200thAsteroid.second << "]\n";
  }
}
