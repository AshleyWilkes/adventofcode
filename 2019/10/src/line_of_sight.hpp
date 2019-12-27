#pragma once
#include"point.hpp"
#include<stdexcept>
#include<vector>

class LineOfSight {
  public:
    LineOfSight( const Point& point );
    bool canContain( const Point& point ) const;
    void addAsteroid( const Point& point );
    Point nearest() const { return nearest_; }

    int sgn( int val ) const;
    Point sgns( const Point& point ) const ;
    bool sameVertical( const Point& point1, const Point& point2 ) const;
    bool sameHorizontal( const Point& point1, const Point& point2 ) const;
  private:
    Point nearest_;
    std::vector<Point> asteroids_;
};
