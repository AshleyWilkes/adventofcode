#include "wires.hpp"
#include <fstream>
#include <iostream>

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

  std::string wireStr1, wireStr2;
  getline( inputStream, wireStr1 );
  getline( inputStream, wireStr2 );

  auto wireInit1 = parseInitString( wireStr1 );
  auto wireInit2 = parseInitString( wireStr2 );
  Wire wire1{ wireInit1 };
  Wire wire2{ wireInit2 };
  auto intersection = countMinimalWiresIntersection( wire1, wire2 );
  std::cout << intersection.p_.first << ", " << intersection.p_.second << ", " << intersection.distance_ << "\n";
}
