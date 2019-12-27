#include "gtest/gtest.h"
#include "asteroids_map.hpp"
#include "line_of_sight.hpp"

namespace {

std::vector<LineOfSight> readLinesOfSight( std::istream& input ) {
  InputableMap inputMap{ input };
  std::vector<LineOfSight> result;
  std::map<char, int> resultIndices;
  for ( int row = 0; row < inputMap.getRowsCount(); ++row ) {
    for ( int col = 0; col < inputMap.getColsCount(); ++col ) {
      char c = inputMap.element( row, col );
      if ( c != '.' && c != '#' ) {
        if ( resultIndices.find( std::toupper( c ) ) == resultIndices.end() ) {
          resultIndices.insert({ std::toupper( c ), result.size() } );
          result.push_back( LineOfSight{ Point{ row, col } } );
        } else {
          result.at( resultIndices.at( std::toupper( c ) ) ).addAsteroid( { row, col } );
        }
      }
    }
  }
  return result;
}

void test_maps_equivalence( std::vector<LineOfSight> map1, std::vector<LineOfSight> map2 ) {
  //museji mit stejny pocet prvku
  ASSERT_EQ( map1.size(), map2.size() );
  //pro kady prvek z map1 musi existovat prvek v map2 se stejnymi asteroidy
  //  implementace trochu zjednodusuje
  for ( auto los1 : map1 ) {
    auto los2It = std::find_if( map2.begin(), map2.end(),
        [ los1 ]( LineOfSight los2 ) {
        return los1.nearest().first == los2.nearest().second
        && los1.nearest().second == los2.nearest().first; } );
    EXPECT_NE( los2It, map2.end() );
  }
}

TEST(AsteroidsMap, Example1) {
  std::istringstream mapInputStream {
    ".#..#\n"
    ".....\n"
    "#####\n"
    "....#\n"
    "...##" };
  AsteroidsMap asteroidsMap{ mapInputStream };
  std::istringstream countsInputStream {
    ".7..7\n"
    ".....\n"
    "67775\n"
    "....7\n"
    "...87" };
  InputableMap countsMap{ countsInputStream };
  for ( auto asteroid : asteroidsMap.getAsteroids() ) {
    EXPECT_EQ( asteroidsMap.countLinesOfSightFrom( asteroid ), countsMap.element( asteroid.second, asteroid.first ) - '0' );
  }
}

TEST(AsteroidsMap, Example2) {
  std::string inputString {
    "#.........\n"
    "...A......\n"
    "...B..a...\n"
    ".EDCG....a\n"
    "..F.c.b...\n"
    ".....c....\n"
    "..efd.c.gb\n"
    ".......c..\n"
    "....f...c.\n"
    "...e..d..c"
  };
  std::istringstream mapInputStream{ inputString };
  AsteroidsMap asteroidsMap{ mapInputStream };
  std::istringstream linesOfSightInputStream{ inputString };
  std::vector<LineOfSight> linesOfSight = readLinesOfSight( linesOfSightInputStream );
  test_maps_equivalence( asteroidsMap.getLinesOfSightFrom( { 0, 0 } ), linesOfSight );
}

TEST(AsteroidsMap, Example3) {
  std::istringstream mapInputStream {
    "......#.#.\n"
    "#..#.#....\n"
    "..#######.\n"
    ".#.#.###..\n"
    ".#..#.....\n"
    "..#....#.#\n"
    "#..#....#.\n"
    ".##.#..###\n"
    "##...#..#.\n"
    ".#....####" };
  AsteroidsMap asteroidsMap{ mapInputStream };
  auto location = asteroidsMap.countBestObservatoryLocation();
  EXPECT_EQ( location.point(), ( Point{ 5, 8 } ) );
  EXPECT_EQ( location.count(), 33 );
}

TEST(AsteroidsMap, Example4) {
  std::istringstream mapInputStream {
    "#.#...#.#.\n"
    ".###....#.\n"
    ".#....#...\n"
    "##.#.#.#.#\n"
    "....#.#.#.\n"
    ".##..###.#\n"
    "..#...##..\n"
    "..##....##\n"
    "......#...\n"
    ".####.###." };
  AsteroidsMap asteroidsMap{ mapInputStream };
  auto location = asteroidsMap.countBestObservatoryLocation();
  EXPECT_EQ( location.point(), ( Point{ 1, 2 } ) );
  EXPECT_EQ( location.count(), 35 );
}

TEST(AsteroidsMap, Example5) {
  std::istringstream mapInputStream {
    ".#..#..###\n"
    "####.###.#\n"
    "....###.#.\n"
    "..###.##.#\n"
    "##.##.#.#.\n"
    "....###..#\n"
    "..#.#..#.#\n"
    "#..#.#.###\n"
    ".##...##.#\n"
    ".....#.#.." };
  AsteroidsMap asteroidsMap{ mapInputStream };
  auto location = asteroidsMap.countBestObservatoryLocation();
  EXPECT_EQ( location.point(), ( Point{ 6, 3 } ) );
  EXPECT_EQ( location.count(), 41 );
}

TEST(AsteroidsMap, Example6) {
  std::istringstream mapInputStream {
    ".#..##.###...#######\n"
    "##.############..##.\n"
    ".#.######.########.#\n"
    ".###.#######.####.#.\n"
    "#####.##.#.##.###.##\n"
    "..#####..#.#########\n"
    "####################\n"
    "#.####....###.#.#.##\n"
    "##.#################\n"
    "#####.##.###..####..\n"
    "..######..##.#######\n"
    "####.##.####...##..#\n"
    ".#####..#.######.###\n"
    "##...#.##########...\n"
    "#.##########.#######\n"
    ".####.#.###.###.#.##\n"
    "....##.##.###..#####\n"
    ".#.#.###########.###\n"
    "#.#.#.#####.####.###\n"
    "###.##.####.##.#..##" };
  AsteroidsMap asteroidsMap{ mapInputStream };
  auto location = asteroidsMap.countBestObservatoryLocation();
  EXPECT_EQ( location.point(), ( Point{ 11, 13 } ) );
  EXPECT_EQ( location.count(), 210 );
}

}
