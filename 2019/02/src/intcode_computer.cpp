#include "intcode_computer.hpp"

void IntcodeComputer::runTheProgram() {
  int position = 0;
  while ( performInstruction( position ) ) {
    position += 4;
  }
}


bool IntcodeComputer::performInstruction( int position ) {
  int instruction = read( position );
  if ( instruction == 99 ) {
    return false;
  }
  int op1Position = read( position + 1 );
  int op2Position = read( position + 2 );
  int outputPosition = read( position + 3 );
  int op1 = read( op1Position );
  int op2 = read( op2Position );
  switch ( instruction ) {
    case 1: write( outputPosition, op1 + op2 ); break;
    case 2: write( outputPosition, op1 * op2 ); break;
    default: throw "error";
  }
  return true;
}
