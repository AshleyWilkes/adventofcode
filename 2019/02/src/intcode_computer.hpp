#pragma once
#include<vector>

class IntcodeComputer {
  public:
    IntcodeComputer( const std::vector<int>& program ) : program_{ program } {}
    std::vector<int> getProgram() const { return program_; }
    void runTheProgram();
    int read( int position ) { return program_.at( position ); }
    void write( int position, int value ) { program_.at( position ) = value; }
    bool performInstruction( int position );//return true if the instruction was something else than halt
  private:
    std::vector<int> program_;
};
