#include <iostream>
#include <string>
#include <vector>
#include "../int_code/IntCode.h"
#include <climits>

using std::string;
using std::vector;
using std::iostream;
using std::queue;



int main()
{
    string input_data;
    std::cin >> input_data;
    IntCode intCode {};
    intCode.readProgramFromString(input_data);
    std::queue<long> input{};
    input.push(1);
    std::queue<long> output = intCode.runProgram(input);
    while (output.size() != 0) {
        std::cout << output.front() << std::endl;
        output.pop();
    }

    intCode.readProgramFromString(input_data);
    input = std::queue<long>();
    input.push(2);
    output = intCode.runProgram(input);
    while (output.size() != 0) {
        std::cout << output.front() << std::endl;
        output.pop();
    }
    

}

