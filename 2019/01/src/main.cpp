#include<fstream>
#include<iostream>

long long fuelForMassSinglePass( long long mass ) {
  return mass / 3 - 2;
}

long long fuelForMass( long long mass ) {
  long long result, partial = mass;
  while ( partial >= 3 ) {
    partial = fuelForMassSinglePass( partial );
    result += partial > 0 ? partial : 0;
  }
  return result;
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

  int mass;
  long long total;
  while ( inputStream >> mass ) {
    total += fuelForMass( mass );
  }

  std::cout << "Total mass: " << total << "\n";
}
