#include "intcode_computer.hpp"

void
IntcodeComputer::start() {
  if ( status_ != Status::Created ) throw "run() called in non-Created state";
  run();
}

void
IntcodeComputer::resume() {
  if ( status_ != Status::Suspended ) throw "resume() called in non-Suspended state";
  run();
}

void
IntcodeComputer::resize( IntcodeType position ) {
  if ( position >= ( long long int ) program_.size() ) {
    program_.resize( position + 1, 0 );
  }
}

std::unique_ptr<Instruction>
IntcodeComputer::createInstruction( IntcodeType instructionInputValue ) const {
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
    case ( 9 ) : return std::make_unique<AdjustRelativeBaseInstruction>(); break;
    case ( 99 ) : return std::make_unique<HaltInstruction>(); break;
    default: throw "unknown opCode";
  }
}

void IntcodeComputer::pushOutput( IntcodeType output ) {
  if ( consumer_ ) {
    consumer_->pushInput( output );
  } else {
    outputs_.push_back( output );
  }
}

void
IntcodeComputer::run() {
  status_ = Status::Running;
  while ( status_ == Status::Running ) {
    IntcodeType instructionInputValue = read( position_ );
    auto instruction = createInstruction( instructionInputValue );
    instruction->perform( this );
  }
}

bool
Instruction::perform( IntcodeComputer* computer ) const {
  //check consistency, read modes
  IntcodeType instructionInputValue = computer->read( computer->position_ );
  int opCode = instructionInputValue % 100;
  if ( opCode != opCodeOfThis() ) throw "inconsistent opCodes";
  IntcodeType modesValue = instructionInputValue / 100;

  //determine the actual values of the instruction paramaters
  std::vector<IntcodeType> params;
  for ( int i = 0; i < inputParamsCount(); ++i ) {
    int curModeValue = modesValue % 10;
    modesValue = modesValue / 10;
    IntcodeType paramPositionValue = computer->read( computer->position_ + i + 1 );
    if ( curModeValue == 0 ) {
      params.push_back( computer->read( paramPositionValue ) );
    } else if ( curModeValue == 1 ) {
      params.push_back( paramPositionValue );
    } else {
      params.push_back( computer->read( paramPositionValue + computer->relativeBase_ ) );
    }
  }

  //count and possibly write the instruction result
  IntcodeType result = countTheResult( computer, params );
  if ( hasOutput() ) {
    IntcodeType outputPosition = computer->read( computer->position_ + inputParamsCount() + 1 );
    if ( modesValue == 0 ) {
      computer->write( outputPosition, result );
    } else if ( modesValue == 2 ) {
      computer->write( outputPosition + computer->relativeBase_, result );
    } else {
      throw "unknown mode for output";
    }
  }
  computer->position_ = getNewPosition( computer->position_ );
  return halts();
};
