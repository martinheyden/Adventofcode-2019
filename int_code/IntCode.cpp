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
    //long NBR_INSTRUCTIONS[8] = {4,4,2,2,3,3,4,4}; 
    needInput = false;
    inputs = inputQueue;
    output = std::queue<long>();
    while (currentRegister < programVector.size() && not programDone) {
        hasJumpedThisInstruction = false;
        parseInstructionAtCurrentRegister();
        executeInstruction();
        if (needInput) {
            return output;
        }   
        if (programVector[currentRegister] == instruction && !hasJumpedThisInstruction && optCode != OptCode::Exit) { //Instruction unchanged
            currentRegister += NBR_INSTRUCTIONS[optCode-1];
        }
    }
    return output;
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
        case 99:
            optCode = OptCode::Exit;
            //output = LONG_MAX;
            break;
        default:
            std::cout << "Invalid Optcode " << (instruction%100) << std::endl;
    }
    
}

void IntCode::setParameterMode(long instruction)
{
    long factor = 10;
    //Might read more modes than necessary, but this is not a problem
    for (int p =0 ; p<3;++p) {
        factor *= 10;
        if ((instruction%(factor*10))/factor == 1) {
            parameterMode[p] = ParameterMode::Immediate;
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
            programVector[programVector[i+3]] =  //Always one mode???
                getValue(parameterMode[0],programVector[i+1]) + getValue(parameterMode[1],programVector[i+2]);
            break;
        case OptCode::Multiply: 
            programVector[programVector[i+3]] = 
                getValue(parameterMode[0],programVector[i+1]) * getValue(parameterMode[1],programVector[i+2]);
            break;
        case OptCode::Input: 
            if (inputs.size()!=0) {
                programVector[programVector[i+1]] = inputs.front(); //Can only be in one parameterMode??
                inputs.pop();
            } else {
                needInput = true;
            }
            break;
        case OptCode::Output: 
            output.push(getValue(parameterMode[0],programVector[i+1]));
            break;
        case OptCode::JumpIfTrue: 
            if (getValue(parameterMode[0],programVector[i+1])!=0) {
                currentRegister = getValue(parameterMode[1],programVector[i+2]);
                hasJumpedThisInstruction = true;
            } 
            break;
        case OptCode::JumpIfFalse: 
            if (getValue(parameterMode[0],programVector[i+1])==0) {
                currentRegister = getValue(parameterMode[1],programVector[i+2]);
                hasJumpedThisInstruction = true;
            }
            break;
        case OptCode::LessThan: 
            if (getValue(parameterMode[0],programVector[i+1])<getValue(parameterMode[1],programVector[i+2])) {
                programVector[programVector[i+3]] = 1;
            } else {
                programVector[programVector[i+3]] = 0;
            }
            break;
        case OptCode::Equal: 
            if (getValue(parameterMode[0],programVector[i+1])==getValue(parameterMode[1],programVector[i+2])) {
                programVector[programVector[i+3]] = 1;
            } else {
                programVector[programVector[i+3]] = 0;
            }
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

            programVector.push_back(stoi(input.substr(begin,len)));
            begin = begin+len+1;
            len = 0;
        } else {
            ++len;
        }
    }
    //Last number
    programVector.push_back(stoi(input.substr(begin,len)));
    currentRegister = 0;
    programDone = false;
}

long IntCode::getValue(ParameterMode parameterMode, long input)
{
    switch (parameterMode) {
        case ParameterMode::Immediate:
            return input;
            break;
        case ParameterMode::Position:
            return this->programVector[input];
            break;
        default:
           std::cout << "invalid mode" <<std::endl;
            return -1;
    }
}