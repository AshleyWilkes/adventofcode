#include "gtest/gtest.h"
#include "line_of_sight.hpp"

namespace {

TEST(LineOfSight, Ok) {
  LineOfSight lOS{ { 1, 1 } };
  ASSERT_TRUE( lOS.canContain( { 2, 2 } ) );

  LineOfSight vert{ { 1, 0 } };
  ASSERT_TRUE( vert.canContain( { 2, 0 } ) );

  LineOfSight hor{ { 0, 1 } };
  ASSERT_TRUE( hor.canContain( { 0, 2 } ) );
}

TEST(LineOfSight, NotOk_Opposite) {
  LineOfSight lOS{ { 1, 1 } };
  ASSERT_FALSE( lOS.canContain( { -2, 2 } ) );

  LineOfSight vert{ { 1, 0 } };
  ASSERT_FALSE( vert.canContain( { -2, 0 } ) );

  LineOfSight hor{ { 0, 1 } };
  ASSERT_FALSE( hor.canContain( { 0, -2 } ) );
}

TEST(LineOfSight, NotOk_DifferentSlope) {
  LineOfSight lOS{ { 1, 1 } };
  ASSERT_FALSE( lOS.canContain( { 1, 2 } ) );
}

}
