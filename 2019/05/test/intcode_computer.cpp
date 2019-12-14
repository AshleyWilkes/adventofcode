#include "gtest/gtest.h"
#include "intcode_computer.hpp"

namespace {

void testProgram( const std::vector<int>& in, const std::vector<int>& out ) {
  IntcodeComputer comp{ in };
  comp.runTheProgram();
  EXPECT_EQ( comp.getProgram(), out );
}

TEST(IntcodeComputer, Example1) {
  std::vector<int> input{ 1, 0, 0, 0, 99 };
  std::vector<int> output{ 2, 0, 0, 0, 99 };
  testProgram( input, output );
}

TEST(IntcodeComputer, Example2) {
  std::vector<int> input{ 2, 3, 0, 3, 99 };
  std::vector<int> output{ 2, 3, 0, 6, 99 };
  testProgram( input, output );
}

TEST(IntcodeComputer, Example3) {
  std::vector<int> input{ 2, 4, 4, 5, 99, 0 };
  std::vector<int> output{ 2, 4, 4, 5, 99, 9801 };
  testProgram( input, output );
}

TEST(IntcodeComputer, Example4) {
  std::vector<int> input{ 1, 1, 1, 4, 99, 5, 6, 0, 99 };
  std::vector<int> output{ 30, 1, 1, 4, 2, 5, 6, 0, 99 };
  testProgram( input, output );
}

TEST(IntcodeComputer, Example0) {
  std::vector<int> input{ 1, 9, 10, 3, 2, 3, 11, 0, 99, 30, 40, 50 };
  std::vector<int> output{ 3500, 9, 10, 70, 2, 3, 11, 0, 99, 30, 40, 50 };
  testProgram( input, output );
}

}
