#include "asteroids_map.hpp"
#include <algorithm>
#include <cmath>

AsteroidsMap::AsteroidsMap( const InputableMap& map, std::vector<char> ignoredChars ) {
  for ( int col = 0; col < map.getColsCount(); ++col ) {
    for ( int row = 0; row < map.getRowsCount(); ++row ) {
      if ( std::find( ignoredChars.begin(), ignoredChars.end(), map.element( col, row ) ) == ignoredChars.end() ) {
        asteroids_.push_back( Point{ col, row } );
      }
    }
  }
}

std::vector<LineOfSight> AsteroidsMap::getLinesOfSightFrom( const Point& point ) const {
  std::vector<LineOfSight> result;
  for ( auto asteroid : asteroids_ ) {
    Point normalized = normalize( asteroid, point );
    if ( normalized == Point{ 0, 0 } ) continue;
    auto lOSIt = std::find_if( result.begin(), result.end(),
        [ normalized ]( auto lOS ) { return lOS.canContain( normalized ); } );
    if ( lOSIt == result.end() ) {
      result.push_back( LineOfSight( normalized ) );
    } else {
      lOSIt->addAsteroid( normalized );
    }
  }
  return result;
}

std::vector<LineOfSight> AsteroidsMap::getSortedLinesOfSightFrom( const Point& point ) const  {
  auto result = getLinesOfSightFrom( point );
  std::sort( result.begin(), result.end(), []( auto lOS1, auto lOS2 ) {
      auto near1 = lOS1.nearest(); auto near2 = lOS2.nearest();
      return atan2( near1.first, near1.second ) > atan2( near2.first, near2.second ); } );
  return result;
}

ObservatoryLocation AsteroidsMap::countBestObservatoryLocation() const {
  ObservatoryLocation result{ Point{ -1, -1 }, -1 };
  for ( auto asteroid : asteroids_ ) {
    int newCount = countLinesOfSightFrom( asteroid );
    if ( newCount > result.count() ) {
      result = { asteroid, newCount };
    }
  }
  return result; 
}
