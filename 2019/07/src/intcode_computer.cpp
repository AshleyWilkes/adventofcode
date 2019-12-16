#include "intcode_computer.hpp"

void
IntcodeComputer::runTheProgram() {
  int position = 0;
  bool halted = false;
  while ( ! halted ) {
    int instructionInputValue = read( position );
    auto instruction = createInstruction( instructionInputValue );
    halted = instruction->perform( this, position );
  }
}

std::unique_ptr<Instruction>
IntcodeComputer::createInstruction( int instructionInputValue ) const {
  int opCode = instructionInputValue % 100;
  switch ( opCode ) {
    case ( 1 ) : return std::make_unique<AddInstruction>(); break;
    case ( 2 ) : return std::make_unique<MultiplyInstruction>(); break;
    case ( 3 ) : return std::make_unique<InputInstruction>(); break;
    case ( 4 ) : return std::make_unique<OutputInstruction>(); break;
    case ( 5 ) : return std::make_unique<JumpIfTrueInstruction>(); break;
    case ( 6 ) : return std::make_unique<JumpIfFalseInstruction>(); break;
    case ( 7 ) : return std::make_unique<LessThanInstruction>(); break;
    case ( 8 ) : return std::make_unique<EqualsInstruction>(); break;
    case ( 99 ) : return std::make_unique<HaltInstruction>(); break;
    default: throw "unknown opCode";
  }
}

bool
Instruction::perform( IntcodeComputer* computer, int& position ) const {
  //check consistency, read modes
  int instructionInputValue = computer->read( position );
  int opCode = instructionInputValue % 100;
  if ( opCode != opCodeOfThis() ) throw "inconsistent opCodes";
  int modesValue = instructionInputValue / 100;

  //determine the actual values of the instruction paramaters
  std::vector<int> params;
  for ( int i = 0; i < inputParamsCount(); ++i ) {
    int curModeValue = modesValue % 10;
    modesValue = modesValue / 10;
    int paramPositionValue = computer->read( position + i + 1 );
    if ( curModeValue == 0 ) {
      params.push_back( computer->read( paramPositionValue ) );
    } else {
      params.push_back( paramPositionValue );
    }
  }

  //count and possibly write the instruction result
  int result = countTheResult( computer, params );
  if ( hasOutput() ) {
    int outputPosition = computer->read( position + inputParamsCount() + 1 );
    computer->write( outputPosition, result );
  }
  position = getNewPosition( position );
  return halts();
};
