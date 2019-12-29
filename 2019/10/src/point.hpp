#pragma once
#include<utility>

using Point = std::pair<int, int>;

Point normalize( const Point& point, const Point& base );
Point unnormalize( const Point& point, const Point& base );
