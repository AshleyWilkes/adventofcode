#include "max_thruster_signal.hpp"
#include<algorithm>

int getThrusterSignal( const Program& program, std::array<int, 5> phaseSettingSequence ) {
  //program bere 2 vstupy: prvni je hodnota z phaseSettingSequence, druhy je aktualni vypoctena hodnota (na zacatku je to 0)
  //potrebuju udelat postupne 5 instanci computeru s programem, kazdy instanci dat spravne inputy a rict si ji o vysledek; ten bude druhym inputem nasledujici instance anebo navratova hodnota, pokud ho vratila uz pata instance
  int curResult = 0;
  for ( int phase : phaseSettingSequence ) {
    IntcodeComputer comp{ program };
    comp.pushInput( phase );
    comp.pushInput( curResult );
    comp.runTheProgram();
    curResult = comp.popOutput();
  }
  return curResult;
}

int findMaxThrusterSignal( const Program& program ) {
  std::array<int, 5> permutation;
  int max = -1;
  std::generate( permutation.begin(), permutation.end(), [ n = 0 ] () mutable { return n++; } );
  do {
    int curThrust = getThrusterSignal( program, permutation );
    if ( curThrust > max ) max = curThrust;
  } while ( std::next_permutation( permutation.begin(), permutation.end() ) );
  return max;
}
