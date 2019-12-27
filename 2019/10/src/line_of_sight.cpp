#include "line_of_sight.hpp"

LineOfSight::LineOfSight( const Point& point ) : nearest_{ point }, asteroids_{ point } {
  if ( point.first == 0 && point.second == 0 ) throw std::invalid_argument{ "Can't construct line of sight from [0, 0]" };
}

bool LineOfSight::canContain( const Point& point ) const {
  if ( sameVertical( nearest_, point ) || sameHorizontal( nearest_, point ) ) {
    return true;
  } else {
    return ( 
        sgns( nearest_ ) == sgns( point ) 
        && ( nearest_.first * point.second == point.first * nearest_.second ) );
  }
}

void LineOfSight::addAsteroid( const Point& point ) {
  asteroids_.push_back( point );

  int maxOfPoint = std::max( std::abs( point.first ), std::abs( point.second ) );
  int maxOfNearest = std::max( std::abs( nearest_.first ), std::abs( nearest_.second ) );
  if ( maxOfPoint < maxOfNearest ) {
    nearest_ = point;
  }
}

int LineOfSight::sgn( int value ) const {
  return ( 0 < value ) - ( value < 0 );
}

Point LineOfSight::sgns( const Point& point ) const {
  return { sgn( point.first), sgn( point.second ) };
}

bool LineOfSight::sameVertical( const Point& point1, const Point& point2 ) const {
  return sgns( point1 ) == Point{ 1, 0 } && sgns( point2 ) == Point{ 1, 0 };
}

bool LineOfSight::sameHorizontal( const Point& point1, const Point& point2 ) const {
  return sgns( point1 ) == Point{ 0, 1 } && sgns( point2 ) == Point{ 0, 1 };
}
