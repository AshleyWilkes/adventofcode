#pragma once
#include "inputable_map.hpp"
#include "line_of_sight.hpp"

class ObservatoryLocation {
  public:
    ObservatoryLocation( const Point& point, int count ) : point_{ point }, count_{ count } {}
    Point point() const { return point_; }
    int count() const { return count_; }
  private:
    Point point_;
    int count_;
};

class AsteroidsMap {
  public:
    AsteroidsMap( const InputableMap& map, std::vector<char> ignoredChars = { '.' } );
    AsteroidsMap( std::istream& inputStream, std::vector<char> ignoredChars = { '.' } ) : AsteroidsMap( InputableMap( inputStream ), ignoredChars ) {}
    std::vector<Point> getAsteroids() const { return asteroids_; }
    int countLinesOfSightFrom( const Point& point ) const { return getLinesOfSightFrom( point ).size(); }
    std::vector<LineOfSight> getLinesOfSightFrom( const Point& point ) const;
    std::vector<LineOfSight> getSortedLinesOfSightFrom( const Point& point ) const;
    ObservatoryLocation countBestObservatoryLocation() const;
  private:
    std::vector<Point> asteroids_;
};
