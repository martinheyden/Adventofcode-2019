#include "IntCode.h"
#include <string>
#include <vector>
#include <iostream>
#include <climits>
#include <queue>


/**
 * @brief Runs until program terminates or an inpuit is needed
 *
 * 
 * @param inputQueue 
 * @return A std::queue<long> containing all the outputs
 */
std::queue<long> IntCode::runProgram(std::queue<long> inputQueue)
{
    needInput = false;
    inputs = inputQueue;
    output = std::queue<long>();
    while (not checkForTermination()) {
        hasJumpedThisInstruction = false;
        parseInstructionAtCurrentRegister();
        executeInstruction();
        updateCurrentRegistry();
    }
    return output;
}

bool IntCode::checkForTermination()
{
    return needInput || programDone || currentRegister >=programVector.size();
}

void IntCode::updateCurrentRegistry()
{
    // Current registry unchanged, has not jumped, and will not terminate due to needing input.
    if (programVector[currentRegister] == instruction && !hasJumpedThisInstruction && optCode != OptCode::Exit && not needInput) { //Instruction unchanged
        currentRegister += NBR_INSTRUCTIONS[optCode-1];
    }
}

bool IntCode::hasTerminated()
{
    return programDone;
}

void IntCode::parseInstructionAtCurrentRegister()
{
    instruction = programVector[currentRegister];
    setOptCode(instruction);
    setParameterMode(instruction);
}

void IntCode::setOptCode(long instruction) {
    switch (instruction%100) {
        case 1: 
            optCode = OptCode::Add;
            break;
        case 2:
            optCode = OptCode::Multiply;
            break;
        case 3:
            optCode = OptCode::Input;
            break;
        case 4:
            optCode = OptCode::Output;
            break;
        case 5:
            optCode = OptCode::JumpIfTrue;
            break;
        case 6:
            optCode = OptCode::JumpIfFalse;
            break;
        case 7:
            optCode = OptCode::LessThan;
            break;
        case 8:
            optCode = OptCode::Equal;
            break;
        case 9:
            optCode = OptCode::AdjustRelative;
            break;
        case 99:
            optCode = OptCode::Exit;
            break;
        default:
            std::cout << "Invalid Optcode " << (instruction%100) << std::endl;
            exit(1);
    }
}

void IntCode::setParameterMode(long instruction)
{
    long factor = 10;
    //Might read more modes than necessary, but this is not a problem
    for (int p =0 ; p<3;++p) {
        factor *= 10;
        int digit = (instruction%(factor*10))/factor;
        if ( digit == 1) {
            parameterMode[p] = ParameterMode::Immediate;
        } else if (digit ==2) {
            parameterMode[p] = ParameterMode::Relative;
        } else {
            parameterMode[p] = ParameterMode::Position;
        }
    }
}

void IntCode::executeInstruction()
{
    long i = currentRegister;
    switch (optCode) {
        case OptCode::Add: 
            getWriteLocationReference(3) = getValueOfArgument(1) + getValueOfArgument(2);
            break;
        case OptCode::Multiply: 
            getWriteLocationReference(3) = getValueOfArgument(1) * getValueOfArgument(2);
            break;
        case OptCode::Input: 
            if (inputs.size()!=0) {
                getWriteLocationReference(1) = inputs.front();
                inputs.pop();
            } else {
                needInput = true;
            }
            break;
        case OptCode::Output: 
            output.push(getValueOfArgument(1));
            break;
        case OptCode::JumpIfTrue: 
            if (getValueOfArgument(1)!=0) {
                currentRegister = getValueOfArgument(2);
                hasJumpedThisInstruction = true;
            } 
            break;
        case OptCode::JumpIfFalse: 
            if (getValueOfArgument(1)==0) {
                currentRegister = getValueOfArgument(2);
                hasJumpedThisInstruction = true;
            }
            break;
        case OptCode::LessThan: 
            if (getValueOfArgument(1)<getValueOfArgument(2)) {
                getWriteLocationReference(3) = 1;
            } else {
                getWriteLocationReference(3) = 0;
            }
            break;
        case OptCode::Equal: 
            if (getValueOfArgument(1)==getValueOfArgument(2)) {
                getWriteLocationReference(3) = 1;
            } else {
                getWriteLocationReference(3) = 0;
            }
            break;
        case OptCode::AdjustRelative:
            relativeBase += getValueOfArgument(1);
            break;
        case OptCode::Exit:
            programDone = true;
            break;
        }
}


void IntCode::readProgramFromString(std::string input)
{
    programVector = {};
    size_t begin = 0;
    auto end = input.length();
    size_t len = 0;
    while (begin+len != end) {
        if (input[begin+len] == ',') {
            programVector.push_back(stol(input.substr(begin,len)));
            begin = begin+len+1;
            len = 0;
        } else {
            ++len;
        }
    }
    //Last number
    programVector.push_back(stoi(input.substr(begin,len)));
    currentRegister = 0;
    relativeBase = 0;
    programDone = false;
    extendedMemory = {};
}

long& IntCode::getWriteLocationReference(int offset)
{
    long instrValue = programVector[currentRegister + offset];
    if (parameterMode[offset-1] == ParameterMode::Position) {
        return getMemoryReference(instrValue);
    } else if (parameterMode[offset-1] = ParameterMode::Relative) {
        return getMemoryReference(instrValue + relativeBase);
    } else {
        std::cout << "Error in getWriteLocation" << std::endl;
        exit(1);
    }
}

long IntCode::getValueOfArgument(int offset)
{
    int registryValue = programVector[currentRegister + offset];
    switch (parameterMode[offset-1]) {
        case ParameterMode::Immediate:
            return registryValue;
            break;
        case ParameterMode::Position:
            return getMemoryValue(registryValue);
            break;
        case ParameterMode::Relative:
            return getMemoryValue(registryValue + relativeBase);
            break;
        default:
           std::cout << "invalid mode" <<std::endl;
            return -1;
    }
}

long& IntCode::getMemoryReference(long p)
{
    if (p < 0) {
        std::cout << "Trying to read from negative memory" << std::endl;
        exit(1);
    } else if (p < programVector.size()) {
        return programVector[p];
    } else {
        extendedMemory.insert({p,0}); //Only inserts if not allready in map
        return extendedMemory[p];
    }
}

long IntCode::getMemoryValue(long p)
{
    return getMemoryReference(p);
}