#pragma once
#include<memory>
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
  private:
    std::vector<int> program_;
};

class Instruction {
  public:
    bool perform( IntcodeComputer* computer, int position ) const;
    int outputParamsCount() const { return hasOutput() ? 1 : 0; }
    int totalPositionsCount() const { return inputParamsCount() + outputParamsCount() + 1; }

    virtual int opCodeOfThis() const = 0;
    virtual bool halts() const = 0;
    virtual int inputParamsCount() const = 0;
    virtual bool hasOutput() const = 0;
    virtual int countTheResult( const std::vector<int>& params ) const = 0;
};

class AddInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 1; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 2; }
    bool hasOutput() const override { return true; }
    int countTheResult( const std::vector<int>& params ) const {
      return params.at( 0 ) + params.at( 1 );
    }
};

class MultiplyInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 2; }
    bool halts() const override { return false; }
    int inputParamsCount() const override { return 2; }
    bool hasOutput() const override { return true; }
    int countTheResult( const std::vector<int>& params ) const {
      return params.at( 0 ) * params.at( 1 );
    }
};

class HaltInstruction : public Instruction {
  public:
    int opCodeOfThis() const override { return 99; }
    bool halts() const override { return true; }
    int inputParamsCount() const override { return 0; }
    bool hasOutput() const override { return false; }
    int countTheResult( const std::vector<int>& /*params*/ ) const {
      return -1;
    }
};
