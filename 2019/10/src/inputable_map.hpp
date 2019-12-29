#pragma once
#include"point.hpp"
#include<istream>
#include<vector>

class InputableMap {
  public:
    InputableMap( std::istream& istream );
    char element( int col, int row ) const { return elements_.at( row * cols_ + col ); }
    char element( const Point& point ) const { return element( point.first, point.second ); }
    int getRowsCount() const { return elements_.size() / cols_; }
    int getColsCount() const { return cols_; }
    Point coordsOfFirst( char c ) const;
  private:
    int cols_;
    std::vector<char> elements_;
};
