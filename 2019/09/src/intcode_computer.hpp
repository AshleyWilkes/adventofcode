#pragma once
#include<memory>
#include<iostream>
#include<memory>
#include<queue>
#include<vector>

using IntcodeType = long long int;
using Program = std::vector<IntcodeType>;

class Instruction;

class IntcodeComputer {
  public:
    friend class Instruction;
    enum class Status { Created, Running, Suspended, Halted };
    IntcodeComputer( const Program& program ) : program_{ program } {}
    void setStatus( Status status ) { status_ = status; }
    Status getStatus() const { return status_; }
    Program getProgram() const { return program_; }
    void start();
    void resume();
    void resize( IntcodeType position );
    IntcodeType read( IntcodeType position ) { resize( position ); return program_.at( position ); }
    void write( IntcodeType position, IntcodeType value ) { resize( position ); program_.at( position ) = value; }
    std::unique_ptr<Instruction> createInstruction( IntcodeType position ) const;
    void pushInput( IntcodeType input ) { inputs_.push_back( input ); }
    bool hasInput() const { return ! inputs_.empty(); }
    IntcodeType popInput() { IntcodeType result = inputs_.front(); inputs_.pop_front(); return result; }
    void pushOutput( IntcodeType output ); 
    bool hasOutput() const { return ! outputs_.empty(); }
    IntcodeType popOutput() { IntcodeType result = outputs_.front(); outputs_.pop_front(); return result; }
    void printOutputs() { while ( ! outputs_.empty() ) std::cout << popOutput() << '\n'; }
    std::vector<IntcodeType> getOutputs() { return { outputs_.begin(), outputs_.end() }; }
    void linkOutputToInputOf( IntcodeComputer *consumer ) { consumer_ = consumer; }
    void adjustRelativeBase( int diff ) { relativeBase_ += diff; }
  private:
    void run();
    Program program_;
    std::deque<IntcodeType> outputs_;
    std::deque<IntcodeType> inputs_;
    int position_{ 0 };
    Status status_{ Status::Created };
    IntcodeComputer *consumer_{ nullptr };
    int relativeBase_{ 0 };
};

class Instruction {
  public:
    bool perform( IntcodeComputer* computer ) const;
    int outputParamsCount() const { return hasOutput() ? 1 : 0; }
    int totalPositionsCount() const { return inputParamsCount() + outputParamsCount() + 1; }
    virtual int getNewPosition( int position ) const { return position + totalPositionsCount(); }

    virtual int opCodeOfThis() const = 0;
    virtual bool halts() const = 0;
    virtual int inputParamsCount() const = 0;
    virtual bool hasOutput() const = 0;
    virtual IntcodeType countTheResult( IntcodeComputer *computer, const std::vector<IntcodeType>& params ) const = 0;
};

class AddInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 1; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 2; }
    bool hasOutput() const override { return true; }
    IntcodeType countTheResult( IntcodeComputer *, const std::vector<IntcodeType>& params ) const {
      return params.at( 0 ) + params.at( 1 );
    }
};

class MultiplyInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 2; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 2; }
    bool hasOutput() const override { return true; }
    IntcodeType countTheResult( IntcodeComputer *, const std::vector<IntcodeType>& params ) const {
      return params.at( 0 ) * params.at( 1 );
    }
};

class InputInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 3; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 0; }
    bool hasOutput() const override { return true; }
    IntcodeType countTheResult( IntcodeComputer *computer, const std::vector<IntcodeType>& ) const {
      if ( computer->hasInput() ) {
        success = true;
        computer->setStatus( IntcodeComputer::Status::Running );
        return computer->popInput();
      } else {
        success = false;
        computer->setStatus( IntcodeComputer::Status::Suspended );
        return -1;
      }
    }
    int getNewPosition( int position ) const override {
      return success ? Instruction::getNewPosition( position ) : position;
    }
  private:
    mutable bool success{ false };
};

class OutputInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 4; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 1; }
    bool hasOutput() const override { return false; }
    IntcodeType countTheResult( IntcodeComputer *computer, const std::vector<IntcodeType>& params ) const {
      computer->pushOutput( params.at( 0 ) );
      return -1;
    }
};

class JumpIfTrueInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 5; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 2; }
    bool hasOutput() const override { return false; }
    IntcodeType countTheResult( IntcodeComputer *, const std::vector<IntcodeType>& params ) const {
      if ( params.at( 0 ) != 0 ) {
        nextPosition = params.at( 1 );
      } else {
        nextPosition = -1;
      }
      return -1;
    }
    int getNewPosition( int position ) const override {
      if ( nextPosition == -1 ) {
        return Instruction::getNewPosition( position );
      } else {
        return nextPosition;
      }
    }
  private:
    mutable int nextPosition = -1;
};

class JumpIfFalseInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 6; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 2; }
    bool hasOutput() const override { return false; }
    IntcodeType countTheResult( IntcodeComputer *, const std::vector<IntcodeType>& params ) const {
      if ( params.at( 0 ) == 0 ) {
        nextPosition = params.at( 1 );
      } else {
        nextPosition = -1;
      }
      return -1;
    }
    int getNewPosition( int position ) const override {
      if ( nextPosition == -1 ) {
        return Instruction::getNewPosition( position );
      } else {
        return nextPosition;
      }
    }
  private:
    mutable int nextPosition = -1;
};

class LessThanInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 7; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 2; }
    bool hasOutput() const override { return true; }
    IntcodeType countTheResult( IntcodeComputer *, const std::vector<IntcodeType>& params ) const {
      return params.at( 0 ) < params.at( 1 );
    }
};

class EqualsInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 8; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 2; }
    bool hasOutput() const override { return true; }
    IntcodeType countTheResult( IntcodeComputer *, const std::vector<IntcodeType>& params ) const {
      return params.at( 0 ) == params.at( 1 );
    }
};

class AdjustRelativeBaseInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 9; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 1; }
    bool hasOutput() const override { return false; }
    IntcodeType countTheResult( IntcodeComputer *computer, const std::vector<IntcodeType>& params ) const {
      computer->adjustRelativeBase( params.at( 0 ) );
      return -1;
    }
};

class HaltInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 99; }
    bool halts() const override { return true; }
    int inputParamsCount() const override { return 0; }
    bool hasOutput() const override { return false; }
    IntcodeType countTheResult( IntcodeComputer *computer, const std::vector<IntcodeType>& ) const {
      computer->setStatus( IntcodeComputer::Status::Halted );
      return -1;
    }
};
