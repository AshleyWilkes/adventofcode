#pragma once
#include<memory>
#include<iostream>
#include<vector>

using Program = std::vector<int>;

class Instruction;

class IntcodeComputer {
  public:
    IntcodeComputer( const Program& program ) : program_{ program } {}
    Program getProgram() const { return program_; }
    void runTheProgram();
    int read( int position ) { return program_.at( position ); }
    void write( int position, int value ) { program_.at( position ) = value; }
    std::unique_ptr<Instruction> createInstruction( int position ) const;
    void setInput( int input ) const { input_ = input; }
    int getInput() const { return input_; }
    void writeOutput( int output ) const { std::cout << output << '\n'; output_ = output; }
    int getOutput() const { return output_; }
  private:
    std::vector<int> program_;
    mutable int output_;
    mutable int input_;
};

class Instruction {
  public:
    bool perform( IntcodeComputer* computer, int& position ) const;
    int outputParamsCount() const { return hasOutput() ? 1 : 0; }
    int totalPositionsCount() const { return inputParamsCount() + outputParamsCount() + 1; }
    virtual int getNewPosition( int position ) const { return position + totalPositionsCount(); }

    virtual int opCodeOfThis() const = 0;
    virtual bool halts() const = 0;
    virtual int inputParamsCount() const = 0;
    virtual bool hasOutput() const = 0;
    virtual int countTheResult( IntcodeComputer const *computer, const std::vector<int>& params ) const = 0;
};

class AddInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 1; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 2; }
    bool hasOutput() const override { return true; }
    int countTheResult( IntcodeComputer const *, const std::vector<int>& params ) const {
      return params.at( 0 ) + params.at( 1 );
    }
};

class MultiplyInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 2; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 2; }
    bool hasOutput() const override { return true; }
    int countTheResult( IntcodeComputer const *, const std::vector<int>& params ) const {
      return params.at( 0 ) * params.at( 1 );
    }
};

class InputInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 3; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 0; }
    bool hasOutput() const override { return true; }
    int countTheResult( IntcodeComputer const *computer, const std::vector<int>& ) const {
      return computer->getInput();
    }
};

class OutputInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 4; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 1; }
    bool hasOutput() const override { return false; }
    int countTheResult( IntcodeComputer const *computer, const std::vector<int>& params ) const {
      computer->writeOutput( params.at( 0 ) );
      return -1;
    }
};

class JumpIfTrueInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 5; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 2; }
    bool hasOutput() const override { return false; }
    int countTheResult( IntcodeComputer const*, const std::vector<int>& params ) const {
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
    int countTheResult( IntcodeComputer const*, const std::vector<int>& params ) const {
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
    int countTheResult( IntcodeComputer const*, const std::vector<int>& params ) const {
      return params.at( 0 ) < params.at( 1 );
    }
};

class EqualsInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 8; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 2; }
    bool hasOutput() const override { return true; }
    int countTheResult( IntcodeComputer const*, const std::vector<int>& params ) const {
      return params.at( 0 ) == params.at( 1 );
    }
};

class HaltInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 99; }
    bool halts() const override { return true; }
    int inputParamsCount() const override { return 0; }
    bool hasOutput() const override { return false; }
    int countTheResult( IntcodeComputer const *, const std::vector<int>& ) const {
      return -1;
    }
};
