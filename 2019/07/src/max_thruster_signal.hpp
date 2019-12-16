#include "intcode_computer.hpp"

int getThrusterSignal( const Program& program, std::array<int, 5> phaseSettingSequence );
int findMaxThrusterSignal( const Program& program );
