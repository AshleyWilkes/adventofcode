#include "gtest/gtest.h"
#include "orbit_map.hpp"
#include<sstream>

namespace {

std::string input = 
  "COM)B\n"
  "B)C\n"
  "C)D\n"
  "D)E\n"
  "E)F\n"
  "B)G\n"
  "G)H\n"
  "D)I\n"
  "E)J\n"
  "J)K\n"
  "K)L";

TEST(OrbitMap, ReadingInputInitializedAllObjects) {
  std::stringstream inputStream{ input };
  OrbitMap orbitMap{ inputStream };
  EXPECT_EQ( orbitMap.size(), 12 );
  EXPECT_EQ( orbitMap.get( "COM" ).satellites(), std::vector<std::string>{ "B" });
}

TEST(OrbitMap, RecursionSetDistanceOfAllObjects) {
  std::stringstream inputStream{ input };
  OrbitMap orbitMap{ inputStream };
  orbitMap.countDistances();
  for ( auto obj : orbitMap ) {
    EXPECT_TRUE( obj.second.distanceIsSet() );
  }
}

TEST(OrbitMap, TotalOrbitsCount) {
  std::stringstream inputStream{ input };
  OrbitMap orbitMap{ inputStream };
  orbitMap.countDistances();
  EXPECT_EQ( orbitMap.totalOrbitsCount(), 42 );
}

std::string inputWithSanAndYou = 
  "COM)B\n"
  "B)C\n"
  "C)D\n"
  "D)E\n"
  "E)F\n"
  "B)G\n"
  "G)H\n"
  "D)I\n"
  "E)J\n"
  "J)K\n"
  "K)L\n"
  "K)YOU\n"
  "I)SAN";

TEST(OrbitMap, RequiredTransfers) {
  std::stringstream inputStream{ inputWithSanAndYou };
  OrbitMap orbitMap{ inputStream };
  EXPECT_EQ( orbitMap.getMinimalOrbitTransfers( "SAN", "YOU" ), 6 );
}
}
