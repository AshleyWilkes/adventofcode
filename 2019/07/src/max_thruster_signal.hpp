#include "intcode_computer.hpp"

class IntcodeComputersLoop {
  public:
    IntcodeComputersLoop( int computersCount, const Program& program );
    IntcodeComputer& getComputer( int i ) { return computers_.at( i ); }
  //vsechny instance spustit (start)
  //prochazet postupne jednotlive instance tak dlouho, dokud vsechny neskonci haltem
  //  pokud je instance suspended, zavolat resume()
    void run();
    bool isHalted() const;
  private:
    std::vector<IntcodeComputer> computers_;
};

int getThrusterSignalNoLoop( const Program& program, std::array<int, 5> phaseSettingSequence );
int findMaxThrusterSignalNoLoop( const Program& program );

int getThrusterSignalWithLoop( const Program& program, std::array<int, 5> phaseSettingSequence );
int findMaxThrusterSignalWithLoop( const Program& program );
