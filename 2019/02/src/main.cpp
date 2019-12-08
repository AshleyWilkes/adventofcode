#include "intcode_computer.hpp"
#include <fstream>
#include <iostream>

//sets noun and verb to memory addresses 1 and 2 respectively, runs thus obtained program and
//returns whether the "output" (contents of memory address 0) of the program is equal to 
//expectedOutput
bool testSentence( const std::vector<int>& theProgram, int noun, int verb, long long expectedOutput ) {
  IntcodeComputer comp{ theProgram };
  comp.write( 1, noun );
  comp.write( 2, verb );
  comp.runTheProgram();
  return comp.read( 0 ) == expectedOutput;
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

  std::vector<int> theProgram;
  while ( inputStream.good() ) {
    std::string substr;
    getline( inputStream, substr, ',' );
    theProgram.push_back( std::stoi( substr ) );
  }

  long long expectedOutput = 19690720;

  for ( int noun = 0; noun < 100; ++noun ) {
    for ( int verb = 0; verb < 100; ++verb ) {
      if ( testSentence( theProgram, noun, verb, expectedOutput ) ) {
        std::cout << noun * 100 + verb << '\n';
      }
    }
  }
}
