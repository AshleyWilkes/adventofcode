#include "n_body_engine.hpp"

void Body::applyVelocity() {
  for ( int coordIndex = 0; coordIndex < 3; ++coordIndex ) {
    pos_.at( coordIndex ) = pos_.at( coordIndex ) + vel_.at( coordIndex );
  }
}

NBodyEngine::NBodyEngine( const std::vector<std::vector<int>>& initialStatus ) {
  for ( auto bodyStatus : initialStatus ) {
    bodies_.push_back( Body( bodyStatus ) );
  }
}

void NBodyEngine::step() {
  //pro kazdou dvojici applyGravity
  for ( std::size_t i = 0; i < bodies_.size(); ++i ) {
    for ( std::size_t j = i + 1; j < bodies_.size(); ++j ) {
      applyGravity( bodies_.at( i ), bodies_.at( j ) );
    }
  }
  //pro kazde body applyVelocity
  for ( auto& body : bodies_ ) {
    body.applyVelocity();
  }
}

void NBodyEngine::applyGravity( Body& b1, Body& b2 ) {
  std::vector<int> pos1 = b1.pos();
  std::vector<int> pos2 = b2.pos();
  for ( int coordIndex = 0; coordIndex < 3; ++coordIndex ) {
    int diff = pos1.at( coordIndex ) - pos2.at( coordIndex );
    if ( diff != 0 ) {
      b1.adjustVelocity( coordIndex, diff < 0 );
      b2.adjustVelocity( coordIndex, diff > 0 );
    }
  }
}
