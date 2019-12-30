#include "gtest/gtest.h"
#include "n_body_engine.hpp"

void compare1BodyStatus( const Body& body,
    const std::vector<std::vector<int>>& status ) {
  ASSERT_EQ( status.size(), 2 );
  EXPECT_EQ( body.pos(), status.at( 0 ) );
  EXPECT_EQ( body.vel(), status.at( 1 ) );
}

void compareStatus( const NBodyEngine& engine,
    const std::vector<std::vector<std::vector<int>>>& status ) {
  ASSERT_EQ( engine.bodyCount(), status.size() );
  for ( int i = 0; i < ( int ) status.size(); ++i ) {
    compare1BodyStatus( engine.getBody( i ), status.at( i ) );
  }
}

void compare1Energy( const Body& body,
    const std::vector<int>& expectedEnergy ) {
  EXPECT_EQ( body.pot(), expectedEnergy.at( 0 ) );
  EXPECT_EQ( body.kin(), expectedEnergy.at( 1 ) );
}

void compareEnergy( const NBodyEngine& engine,
    const std::vector<std::vector<int>>& energies ) {
  ASSERT_EQ( energies.size(), engine.bodyCount() + 1 );
  for ( int i = 0; i < engine.bodyCount(); ++i ) {
    compare1Energy( engine.getBody( i ), energies.at( i ) );
  }
  EXPECT_EQ( engine.getTotalEnergy(), energies.at( engine.bodyCount() ).at( 0 ) );
}

TEST(NBodyEngine, Example1) {
  std::vector<std::vector<int>> initialStatus{
      { -1, 0, 2 }, 
      { 2, -10, -7 },
      { 4, -8, 8 },
      { 3, 5, -1 } };
  NBodyEngine engine { initialStatus };
  compareStatus( engine, {
      { { -1, 0, 2 }, { 0, 0, 0 } },
      { { 2, -10, -7 }, { 0, 0, 0 } },
      { { 4, -8, 8 }, { 0, 0, 0 } },
      { { 3, 5, -1 }, { 0, 0, 0 } } } );
  engine.step();
  compareStatus( engine, {
      { { 2, -1,  1 }, { 3, -1, -1 } },
      { { 3, -7, -4 }, { 1, 3, 3 } },
      { { 1, -7, 5 }, { -3, 1, -3 } },
      { { 2, 2, 0 }, { -1, -3, 1 } } } );
  engine.step();
  compareStatus( engine, {
      { { 5, -3, -1 }, { 3, -2, -2 } },
      { { 1, -2, 2 }, { -2, 5, 6 } },
      { { 1, -4, -1 }, { 0, 3, -6 } },
      { { 1, -4, 2 }, { -1, -6, 2 } } } );
  engine.step();
  compareStatus( engine, {
      { { 5, -6, -1 }, { 0, -3, 0 } },
      { { 0, 0, 6 }, { -1, 2, 4 } },
      { { 2, 1, -5 }, { 1, 5, -4 } },
      { { 1, -8, 2 }, { 0, -4, 0 } } } );
  engine.step();
  compareStatus( engine, {
      { { 2, -8, 0 }, { -3, -2, 1 } },
      { { 2, 1, 7 }, { 2, 1, 1 } },
      { { 2, 3, -6 }, { 0, 2, -1 } },
      { { 2, -9, 1 }, { 1, -1, -1 } } } );
  engine.step();
  compareStatus( engine, {
      { { -1, -9, 2 }, { -3, -1, 2 } },
      { { 4, 1, 5 }, { 2, 0, -2 } },
      { { 2, 2, -4 }, { 0, -1, 2 } },
      { { 3, -7, -1 }, { 1, 2, -2 } } } );
  engine.step();
  compareStatus( engine, {
      { { -1, -7, 3 }, { 0, 2, 1 } },
      { { 3, 0, 0 }, { -1, -1, -5 } },
      { { 3, -2, 1 }, { 1, -4, 5 } },
      { { 3, -4, -2 }, { 0, 3, -1 } } } );
  engine.step();
  compareStatus( engine, {
      { { 2, -2, 1 }, { 3, 5, -2 } },
      { { 1, -4, -4 }, { -2, -4, -4 } },
      { { 3, -7, 5 }, { 0, -5, 4 } },
      { { 2, 0, 0}, { -1, 4, 2 } } } );
  engine.step();
  compareStatus( engine, {
      { { 5, 2, -2 }, { 3, 4, -3 } },
      { { 2, -7, -5 }, { 1, -3, -1 } },
      { { 0, -9, 6 }, { -3, -2, 1 } },
      { { 1, 1, 3 }, { -1, 1, 3 } } } );
  engine.step();
  compareStatus( engine, {
      { { 5, 3, -4 }, { 0, 1, -2 } },
      { { 2, -9, -3 }, { 0, -2, 2 } },
      { { 0, -8, 4 }, { 0, 1, -2 } },
      { { 1, 1, 5 }, { 0, 0, 2 } } } );
  engine.step();
  compareStatus( engine, {
      { { 2, 1, -3 }, { -3, -2, 1 } },
      { { 1, -8, 0 }, { -1, 1, 3 } },
      { { 3, -6, 1 }, { 3, 2, -3 } },
      { { 2, 0, 4 }, { 1, -1, -1 } } } );

  compareEnergy( engine, { { 6, 6 }, { 9, 5 }, { 10, 8 }, { 6, 3 }, { 179 } } );
}

TEST(NBodyEngine, Example2) {
  std::vector<std::vector<int>> initialStatus{
      { -8, -10, 0 },
      { 5, 5, 10 },
      { 2, -7, 3 },
      { 9, -8, -3 } };
  NBodyEngine engine { initialStatus };
  compareStatus( engine, {
      { { -8, -10, 0 }, { 0, 0, 0 } },
      { { 5, 5, 10 }, { 0, 0, 0 } },
      { { 2, -7, 3 }, { 0, 0, 0 } },
      { { 9, -8, -3 }, { 0, 0, 0 } } } );
  engine.steps( 10 );
  compareStatus( engine, {
      { { -9, -10, 1 }, { -2, -2, -1 } },
      { { 4, 10, 9 }, { -3, 7, -2 } },
      { { 8, -10, -3 }, { 5, -1, -2 } },
      { { 5, -10, 3 }, { 0, -4, 5 } } } );
  engine.steps( 10 );
  compareStatus( engine, {
      { { -10, 3, -4 }, { -5, 2, 0 } },
      { { 5, -25, 6 }, { 1, 1, -4 } },
      { { 13, 1, 1 }, { 5, -2, 2 } },
      { { 0, 1, 7 }, { -1, -1, 2 } } } );
  engine.steps( 10 );
  compareStatus( engine, {
      { { 15, -6, -9 }, { -5, 4, 0 } },
      { { -4, -11, 3 }, { -3, -10, 0 } },
      { { 0, -1, 11 }, { 7, 4, 3 } },
      { { -3, -2, 5 }, { 1, 2, -3 } } } );
  engine.steps( 10 );
  compareStatus( engine, {
      { { 14, -12, -4 }, { 11, 3, 0 } },
      { { -1, 18, 8 }, { -5, 2, 3 } },
      { { -5, -14, 8 }, { 1, -2, 0 } },
      { { 0, -12, -2 }, { -7, -3, -3 } } } );
  engine.steps( 10 );
  compareStatus( engine, {
      { { -23, 4, 1 }, { -7, -1, 2 } },
      { { 20, -31, 13 }, { 5, 3, 4 } },
      { { -4, 6, 1 }, { -1, 1, -3 } },
      { { 15, 1, -5 }, { 3, -3, -3 } } } );
  engine.steps( 10 );
  compareStatus( engine, {
      { { 36, -10, 6 }, { 5, 0, 3 } },
      { { -18, 10, 9 }, { -3, -7, 5 } },
      { { 8, -12, -3 }, { -2, 1, -7 } },
      { { -18, -8, -2 }, { 0, 6, -1 } } } );
  engine.steps( 10 );
  compareStatus( engine, {
      { { -33, -6, 5 }, { -5, -4, 7 } },
      { { 13, -9, 2 }, { -2, 11, 3 } },
      { { 11, -8, 2 }, { 8, -6, -7 } },
      { { 17, 3, 1 }, { -1, -1, -3 } } } );
  engine.steps( 10 );
  compareStatus( engine, {
      { { 30, -8, 3 }, { 3, 3, 0 } },
      { { -2, -4, 0 }, { 4, -13, 2 } },
      { { -18, -7, 15 }, { -8, 2, -2 } },
      { { -2, -1, -8 }, { 1, 8, 0 } } } );
  engine.steps( 10 );
  compareStatus( engine, {
      { { -25, -1, 4 }, { 1, -3, 4 } },
      { { 2, -9, 0 }, { -3, 13, -1 } },
      { { 32, -8, 14 }, { 5, -4, 6 } },
      { { -1, -2, -8 }, { -3, -6, -9 } } } );
  engine.steps( 10 );
  compareStatus( engine, {
      { { 8, -12, -9 }, { -7, 3, 0 } },
      { { 13, 16, -3 }, { 3, -11, -5 } },
      { { -29, -11, -1 }, { -3, 7, 4 } },
      { { 16, -13, 23 }, { 7, 1, 1 } } } );
  compareEnergy( engine, { { 29, 10 }, { 32, 19 }, { 41, 14 }, { 52, 9 }, { 1940 } } );
}
