#ifndef INTCODE_H
#define INTCODE_H

#include <string>
#include <vector>
#include <iostream>
#include <queue>

class IntCode
{
public:
    void readProgramFromString(std::string);
    std::queue<long> runProgram(std::queue<long>);
    bool hasTerminated();
    
private:
    enum ParameterMode {Position, Immediate};
    enum OptCode {Add=1, Multiply=2, Input=3, Output=4, JumpIfTrue=5, JumpIfFalse=6, LessThan=7, Equal=8, Exit=99};
    std::vector<long> programVector;
    std::queue<long> inputs;
    inline constexpr static int NBR_INSTRUCTIONS[8] = {4,4,2,2,3,3,4,4};
    ParameterMode parameterMode[3];
    std::queue<long> output;
    long currentRegister;
    OptCode optCode;
    long instruction;
    bool hasJumpedThisInstruction;
    bool programDone;
    bool needInput;

    long getValue(ParameterMode, long);
    void parseInstructionAtCurrentRegister();
    void setOptCode(long);
    void setParameterMode(long);
    void executeInstruction();


};

#endif