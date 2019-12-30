#pragma once
#include <cmath>
#include <numeric>
#include <vector>

auto add_abs = []( int res, int cur ) { return res + std::abs( cur ); };

class Body{
  public:
    Body( const std::vector<int>& initialStatus ) : pos_{ initialStatus }, vel_{ 0, 0, 0 } {}

    std::vector<int> pos() const { return pos_; }
    std::vector<int> vel() const { return vel_; }

    int pot() const { return std::accumulate( pos_.begin(), pos_.end(), 0, add_abs ); }
    int kin() const { return std::accumulate( vel_.begin(), vel_.end(), 0, add_abs ); }

    int getTotalEnergy() const { return pot() * kin(); }

    void applyVelocity();

    void adjustVelocity( int coordIndex, bool increase ) { vel_.at( coordIndex ) += increase ? 1 : -1 ; }
  private:
    std::vector<int> pos_;
    std::vector<int> vel_;
};

class NBodyEngine{
  public:
    NBodyEngine( const std::vector<std::vector<int>>& initialStatus );
    int bodyCount() const { return bodies_.size(); }
    const Body& getBody( int index ) const { return bodies_.at( index ); }
    int getTotalEnergy() const { return std::accumulate( bodies_.begin(), bodies_.end(), 0, []( int res, Body body ) { return res + body.getTotalEnergy(); } ); }
    void step();
    void steps( int numSteps ) { for ( int i = 0; i < numSteps; ++i ) step(); }
    void applyGravity( Body& b1, Body& b2 );
  private:
    std::vector<Body> bodies_;
};
