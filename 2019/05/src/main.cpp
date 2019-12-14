#include "intcode_computer.hpp"
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

  std::vector<int> theProgram;
  while ( inputStream.good() ) {
    std::string substr;
    getline( inputStream, substr, ',' );
    theProgram.push_back( std::stoi( substr ) );
  }

  IntcodeComputer comp{ theProgram };
  comp.setInput( 5 );
  comp.runTheProgram();
}
