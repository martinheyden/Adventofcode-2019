#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

static int POSITION = 1;
static int IMMEDIATE = 2;
static int NBR_INSTRUCTIONS[8]= {4,4,2,2,3,3,4,4};

vector<int> parse_numbers(string input) 
{
    vector<int> nbrs;
    size_t begin = 0;
    auto end = input.length();
    size_t len = 0;
    while (begin+len != end) {
        if (input[begin+len] == ',') {

            nbrs.push_back(stoi(input.substr(begin,len)));
            begin = begin+len+1;
            len = 0;
        } else {
            ++len;
        }
    }
    //Last number
    nbrs.push_back(stoi(input.substr(begin,len)));
    return nbrs;
}

int get_val(const vector<int>& data, int mode, int inp) 
{
   //     std::cout << "numbers in get val: " << data[0] << " " << data[1] << std::endl;
    if (mode == IMMEDIATE) {
      //  std::cout << "Immediate mode will return input which was " << inp << std::endl;
        return inp;
    } else if (mode == POSITION) {
        return data[inp];
    } else {
        std::cout << "invalid mode" <<std::endl;
        return -1;
    }
}

int main()
{
    string input_data;
    std::cin >> input_data;
    vector<int> nbrs_og = parse_numbers(input_data);
    size_t i = 0;
    vector<int> nbrs = nbrs_og;
    int input = 5;
    int optcode;
    int mode[3];
    bool done = false;
    bool jumped = false;
    while (i< nbrs.size() && !done) {
        jumped = false;
        //Extract optcode and mode
        int instructions = nbrs[i];
        optcode = instructions%100;
        int factor = 10;
        //Might read more modes than necessary, but this is not a problem
        for (int p =0 ; p<3;++p) {
            factor *= 10;
            if ((instructions%(factor*10))/factor == 1) {
                mode[p] = IMMEDIATE;
            } else {
                mode[p] = POSITION;
            }
        }
        switch (optcode) {
            case 1: //add
                nbrs[nbrs[i+3]] =  //Always one mode???
                    get_val(nbrs,mode[0],nbrs[i+1]) + get_val(nbrs,mode[1],nbrs[i+2]);
                break;
            case 2: // multiply
                nbrs[nbrs[i+3]] = 
                    get_val(nbrs,mode[0],nbrs[i+1]) * get_val(nbrs,mode[1],nbrs[i+2]);
                break;
            case 3: //input
                nbrs[nbrs[i+1]] = input; //Can only be in one mode??
                break;
            case 4: //output
                input = get_val(nbrs,mode[0],nbrs[i+1]);
                break;
            case 5: //Jump-if-true
                if (get_val(nbrs,mode[0],nbrs[i+1])!=0) {
                    i = get_val(nbrs,mode[1],nbrs[i+2]);
                    jumped = true;
                } 
                break;
            case 6: //Jump-if-false
                if (get_val(nbrs,mode[0],nbrs[i+1])==0) {
                    i = get_val(nbrs,mode[1],nbrs[i+2]);
                    jumped = true;
                }
                break;
            case 7: //less than
                if (get_val(nbrs,mode[0],nbrs[i+1])<get_val(nbrs,mode[1],nbrs[i+2])) {
                    nbrs[nbrs[i+3]] = 1;
                } else {
                    nbrs[nbrs[i+3]] = 0;
                }
                break;
            case 8: //less than
                if (get_val(nbrs,mode[0],nbrs[i+1])==get_val(nbrs,mode[1],nbrs[i+2])) {
                    nbrs[nbrs[i+3]] = 1;
                } else {
                    nbrs[nbrs[i+3]] = 0;
                }
                break;
            case 99:
                done = true;
                break;
            default:
                std::cout << "invalid optcode: " << optcode << std::endl;
                return -1;
        }
        //Advance counter
        if (nbrs[i]==instructions && !jumped) { //Instruction unchanged
            i = i + NBR_INSTRUCTIONS[optcode-1];
        }
    }
    std::cout << "Output was: " << input << std::endl;
}

