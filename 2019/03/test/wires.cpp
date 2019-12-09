#include "gtest/gtest.h"
#include "wires.hpp"

namespace {

void testIntersection( const std::string& wireStr1, const std::string& wireStr2, int expectedDistance ) {
  auto wireInit1 = parseInitString( wireStr1 );
  auto wireInit2 = parseInitString( wireStr2 );
  Wire wire1{ wireInit1 };
  Wire wire2{ wireInit2 };
  auto intersection = countMinimalWiresIntersection( wire1, wire2 );
  EXPECT_EQ( intersection.distance_, expectedDistance );
}

TEST(Wires, Example1) {
  std::string wireStr1 = "R8,U5,L5,D3";
  std::string wireStr2 = "U7,R6,D4,L4";
  testIntersection( wireStr1, wireStr2, 6 );
}

TEST(Wires, Example2) {
  std::string wireStr1 = "R75,D30,R83,U83,L12,D49,R71,U7,L72";
  std::string wireStr2 = "U62,R66,U55,R34,D71,R55,D58,R83";
  testIntersection( wireStr1, wireStr2, 159 );
}

TEST(Wires, Example3) {
  std::string wireStr1 = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51";
  std::string wireStr2 = "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7";
  testIntersection( wireStr1, wireStr2, 135 );
}

}
