#include "gtest/gtest.h"
#include "intcode_computer.hpp"
#include <iostream>

namespace {

void testProgram( const Program& in, const Program& out ) {
  IntcodeComputer comp{ in };
  comp.start();
  EXPECT_EQ( comp.getProgram(), out );
}

void testInputOutput( const Program& in, int input, int expectedOutput ) {
  IntcodeComputer comp{ in };
  comp.pushInput( input );
  comp.start();
  EXPECT_EQ( comp.popOutput(), expectedOutput );
}

void testInputOutput( const Program& in, const std::vector<IntcodeType>& outputs ) {
  IntcodeComputer comp{ in };
  comp.start();
  EXPECT_EQ( comp.getOutputs(), outputs );
}

//tests Example1_X are based on data from Day 2
TEST(IntcodeComputer, Example1_1) {
  Program input{ 1, 0, 0, 0, 99 };
  Program output{ 2, 0, 0, 0, 99 };
  testProgram( input, output );
}

TEST(IntcodeComputer, Example1_2) {
  Program input{ 2, 3, 0, 3, 99 };
  Program output{ 2, 3, 0, 6, 99 };
  testProgram( input, output );
}

TEST(IntcodeComputer, Example1_3) {
  Program input{ 2, 4, 4, 5, 99, 0 };
  Program output{ 2, 4, 4, 5, 99, 9801 };
  testProgram( input, output );
}

TEST(IntcodeComputer, Example1_4) {
  Program input{ 1, 1, 1, 4, 99, 5, 6, 0, 99 };
  Program output{ 30, 1, 1, 4, 2, 5, 6, 0, 99 };
  testProgram( input, output );
}

TEST(IntcodeComputer, Example1_0) {
  Program input{ 1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50 };
  Program output{ 3500, 9, 10, 70, 2, 3, 11, 0, 99, 30, 40, 50 };
  testProgram( input, output );
}

//tests Example2_X are based on data from Day 5
TEST(IntcodeComputer, Example2_5) {
  Program prog{ 3, 0, 4, 0, 99 };
  testInputOutput( prog, 1, 1 );
}

TEST(IntcodeComputer, Example2_6) {
  Program input{ 1002, 4, 3, 4, 33 };
  Program output{ 1002, 4, 3, 4, 99 };
  testProgram( input, output );
}

TEST(IntcodeComputer, Example2_7) {
  Program input{ 1101, 100, -1, 4, 0 };
  Program output{ 1101, 100, -1, 4, 99 };
  testProgram( input, output );
}

//Using position mode, consider whether input is equal to 8 (1 for true, 0 for false)
TEST(IntcodeComputer, Example2_8) {
  Program input{ 3, 9, 8, 9, 10, 9, 4, 9, 99, -1, 8 };
  testInputOutput( input, 8, 1 );
  testInputOutput( input, 1, 0 );
}

//Using position mode, consider whether input is less than 8 (1 for true, 0 for false)
TEST(IntcodeComputer, Example2_9) {
  Program input{ 3, 9, 7, 9, 10, 9, 4, 9, 99, -1, 8 };
  testInputOutput( input, 8, 0 );
  testInputOutput( input, 1, 1 );
}

//Using immediate mode, consider whether input is equal to 8 (1 for true, 0 for false)
TEST(IntcodeComputer, Example2_10) {
  Program input{ 3, 3, 1108, -1, 8, 3, 4, 3, 99 };
  testInputOutput( input, 8, 1 );
  testInputOutput( input, 1, 0 );
}

//Using immediate mode, consider whether input is less than 8 (1 for true, 0 for false)
TEST(IntcodeComputer, Example2_11) {
  Program input{ 3, 3, 1107, -1, 8, 3, 4, 3, 99 };
  testInputOutput( input, 8, 0 );
  testInputOutput( input, 1, 1 );
}

//Using position mode, consider whether input was 0 (1 for non-zero, 0 for zero)
TEST(IntcodeComputer, Example2_12) {
  Program input{ 3, 12, 6, 12, 15, 1, 13, 14, 13, 4, 13, 99, -1, 0, 1, 9 };
  testInputOutput( input, 1, 1 );
  testInputOutput( input, 0, 0 );
}

//Using immediate mode, consider whether input was 0 (1 for non-zero, 0 for zero)
TEST(IntcodeComputer, Example2_13) {
  Program input{ 3, 3, 1105, -1 ,9, 1101, 0, 0, 12, 4, 12, 99, 1 };
  testInputOutput( input, 1, 1 );
  testInputOutput( input, 0, 0 );
}

//Take one input, output 999 if input is below 8, 1000 if input is equal to 8, 1001 otherwise
TEST(IntcodeComputer, Example2_14) {
  Program input{ 3, 21, 1008, 21, 8, 20, 1005, 20, 22, 107, 8, 21, 20, 1006, 20, 31, 1106, 0, 36, 98, 0, 0, 1002, 21, 125, 20, 4, 20, 1105, 1, 46, 104, 999, 1105, 1, 46, 1101, 1000, 1, 20, 4, 20, 1105, 1, 46, 98, 99 };
  testInputOutput( input, 1, 999 );
  testInputOutput( input, 8, 1000 );
  testInputOutput( input, 10, 1001 );
}

//tests Example3_X are based on examples from day 9
TEST(IntcodeComputer, Example3_15) {
  Program input{ 109, 1, 204, -1, 1001, 100, 1, 100, 1008, 100, 16, 101, 1006, 101, 0, 99 };
  testInputOutput( input, input );
}

TEST(IntcodeComputer, Example3_16) {
  Program input{ 1102, 34915192, 34915192, 7, 4, 7, 99, 0 };
  IntcodeComputer comp{ input };
  comp.start();
  auto result = comp.popOutput();
  EXPECT_TRUE( result >= 1e15 && result < 1e16 );
} 

TEST(IntcodeComputer, Example3_17) {
  Program input{ 104, 1125899906842624, 99 };
  testInputOutput( input, std::vector<IntcodeType>{ 1125899906842624 } );
}

}
