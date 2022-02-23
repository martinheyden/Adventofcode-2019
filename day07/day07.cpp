#include <iostream>
#include <string>
#include <vector>
#include "../int_code/IntCode.h"
#include <climits>

using std::string;
using std::vector;
using std::iostream;
using std::queue;


void appendQueue(queue<long> &q1, queue<long> &q2)
{
    while (q2.size() != 0) {
        q1.push(q2.front());
        q2.pop();
    }
}

bool isValid(vector<long> v) {
    for (int i = 0; i<5; i++) {
        int count = 0;
        for (int j = 0; j<5; j++) {
            if (v[j] == i) count += 1;
        }
        if (count != 1) return false;
    }
    return true;
} 

void generatePermutations(vector<long> &vec, int i, long &highest, string &input_data) {
    for (int j = 0; j<5; j++) {
        vec[i] = j;
        if (i < 4) {
            generatePermutations(vec,i+1,highest, input_data);
        } else if (isValid(vec)) {
            queue<long> output;
            output.push(0);
            for (int i =0; i<vec.size();++i) {
                queue<long> inputs;
                inputs.push(vec[i]);
                appendQueue(inputs,output);
                IntCode intCode {};
                intCode.readProgramFromString(input_data);
                output = intCode.runProgram(inputs);
            }
            if (output.back() > highest) highest = output.back();
        }
    }
}

void run_init(vector<long> &vec, long &highest, string &input_data)
{
    bool firstRound = true;
    queue<long> output;
    output.push(0);
    vector<IntCode> computers;
    bool go_on = true;
    while (go_on) {
        for (int i =0; i<vec.size();++i) {
         //   std::cout << "running computer " <<  i << std::endl;
            queue<long> inputs;
            if  (firstRound) {
                IntCode computer;
                computer.readProgramFromString(input_data);
                computers.push_back(computer);
                inputs.push(vec[i]+5);
                appendQueue(inputs,output);
                
            } else {
                inputs = output;
            }
            IntCode &intCode = computers[i];
            output = intCode.runProgram(inputs);
            if (i == 4 && intCode.hasTerminated()) {
                if (output.back()>highest) {
                    highest = output.back();
                }
                go_on = false;
                break;
            }
        }
        firstRound = false;
    }
}

void generatePermutations2(vector<long> &vec, long i, long &highest, string &input_data) {
    for (long j = 0; j<5; j++) {
        vec[i] = j;
        if (i < 4) {
            generatePermutations2(vec,i+1,highest, input_data);
        } else if (isValid(vec)) {
            run_init(vec, highest, input_data);
        }
    }
}


int main()
{
    string input_data;
    std::cin >> input_data;
    IntCode intCode {};
    long highest = 0;
    vector<long> order = {0,0,0,0,0};
    generatePermutations(order,0,highest,input_data);
    std::cout << "resulting thruster signal " << highest << std::endl;
    highest = 0;
    generatePermutations2(order,0,highest,input_data);
    std::cout << "resulting thruster signal " << highest  << std::endl;

}

