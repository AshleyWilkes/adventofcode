#include "max_thruster_signal.hpp"
#include<algorithm>

IntcodeComputersLoop::IntcodeComputersLoop( int computersCount, const Program& program ) {
  for ( int i = 0; i < computersCount; ++i ) {
    computers_.push_back({ program });
  }
  for ( int i = 0; i < computersCount - 1; ++i ) {
    getComputer( i ).linkOutputToInputOf( &getComputer( i + 1 ) );
  }
  getComputer( computersCount - 1).linkOutputToInputOf( &getComputer( 0 ) );
}

void IntcodeComputersLoop::run() {
  for ( auto& comp : computers_ ) {
    comp.start();
  }
  while ( ! isHalted() ) {
    for ( auto& comp : computers_ ) {
      if ( comp.getStatus() == IntcodeComputer::Status::Suspended ) {
        comp.resume();
      }
    }
  }
}

bool IntcodeComputersLoop::isHalted() const {
  return std::all_of( computers_.begin(), computers_.end(), []( const IntcodeComputer& c ) { return c.getStatus() == IntcodeComputer::Status::Halted; } );
}

int getThrusterSignalNoLoop( const Program& program, std::array<int, 5> phaseSettingSequence ) {
  //program bere 2 vstupy: prvni je hodnota z phaseSettingSequence, druhy je aktualni vypoctena hodnota (na zacatku je to 0)
  //potrebuju udelat postupne 5 instanci computeru s programem, kazdy instanci dat spravne inputy a rict si ji o vysledek; ten bude druhym inputem nasledujici instance anebo navratova hodnota, pokud ho vratila uz pata instance
  int curResult = 0;
  for ( int phase : phaseSettingSequence ) {
    IntcodeComputer comp{ program };
    comp.pushInput( phase );
    comp.pushInput( curResult );
    comp.start();
    curResult = comp.popOutput();
  }
  return curResult;
}

int findMaxThrusterSignalNoLoop( const Program& program ) {
  std::array<int, 5> permutation;
  int max = -1;
  std::generate( permutation.begin(), permutation.end(), [ n = 0 ] () mutable { return n++; } );
  do {
    int curThrust = getThrusterSignalNoLoop( program, permutation );
    max = std::max( max, curThrust );
  } while ( std::next_permutation( permutation.begin(), permutation.end() ) );
  return max;
}

int getThrusterSignalWithLoop( const Program& program, std::array<int, 5> phaseSettingSequence ) {
  IntcodeComputersLoop loop{ 5, program };
  //kazdy dat do vstupu hodnotu phase setting
  for ( int i = 0; i < 5; ++i ) {
    loop.getComputer( i ).pushInput( phaseSettingSequence.at( i ) );
  }
  //prvni dat do vstupu 0
  loop.getComputer( 0 ).pushInput( 0 );
  loop.run();
  //az jsou vsechny instance zahaltovane, vratit posledni vystup 5. instance
  return loop.getComputer( 0 ).popInput();
}

int findMaxThrusterSignalWithLoop( const Program& program ) {
  std::array<int, 5> permutation;
  int max = -1;
  std::generate( permutation.begin(), permutation.end(), [ n = 5 ] () mutable { return n++; } );
  do {
    int curThrust = getThrusterSignalWithLoop( program, permutation );
    max = std::max( max, curThrust );
  } while ( std::next_permutation( permutation.begin(), permutation.end() ) );
  return max;
}
