#ifndef INTCODE_H
#define INTCODE_H

#include <string>
#include <vector>
#include <iostream>
#include <queue>
#include <map>

class IntCode
{
public:
    void readProgramFromString(std::string);
    std::queue<long> runProgram(std::queue<long>);
    bool hasTerminated();
    
private:
    enum ParameterMode {Position, Immediate, Relative};
    enum OptCode {Add=1, Multiply=2, Input=3, Output=4, JumpIfTrue=5, JumpIfFalse=6, LessThan=7, Equal=8, AdjustRelative = 9,Exit=99};
    std::vector<long> programVector;
    std::map<long,long> extendedMemory;
    std::queue<long> inputs;
    inline constexpr static int NBR_INSTRUCTIONS[9] = {4, 4, 2, 2, 3, 3, 4, 4, 2};
    ParameterMode parameterMode[3];
    std::queue<long> output;
    long currentRegister;
    OptCode optCode;
    long instruction;
    long relativeBase;
    bool hasJumpedThisInstruction;
    bool programDone;
    bool needInput;

    long getValueOfArgument(int);
    long& getMemoryReference(long);
    long getMemoryValue(long);
    long& getWriteLocationReference(int);
    bool checkForTermination();
    void updateCurrentRegistry();
    void parseInstructionAtCurrentRegister();
    void setOptCode(long);
    void setParameterMode(long);
    void executeInstruction();


};

#endif