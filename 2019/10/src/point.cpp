#include "point.hpp"

Point normalize( const Point& point, const Point& base ) {
  return { point.first - base.first, point.second - base.second };
}

Point unnormalize( const Point& point, const Point& base ) {
  return { point.first + base.first, point.second + base.second };
}
