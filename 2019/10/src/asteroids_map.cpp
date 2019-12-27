#include "asteroids_map.hpp"
#include <algorithm>

AsteroidsMap::AsteroidsMap( const InputableMap& map ) {
  for ( int row = 0; row < map.getRowsCount(); ++row ) {
    for ( int col = 0; col < map.getColsCount(); ++col ) {
      if ( map.element( row, col ) != '.' ) {
        asteroids_.push_back( Point{ col, row } );
      }
    }
  }
}

std::vector<LineOfSight> AsteroidsMap::getLinesOfSightFrom( const Point& point ) const {
  std::vector<LineOfSight> result;
  for ( auto asteroid : asteroids_ ) {
    Point normalized{ asteroid.first - point.first, asteroid.second - point.second };
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
