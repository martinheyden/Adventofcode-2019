#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

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

int main()
{
    string input;
    std::cin >> input;
    vector<int> nbrs_og = parse_numbers(input);
    size_t i = 0;
    vector<int> nbrs = nbrs_og;
    nbrs[1] = 12;
    nbrs[2] = 2;
    while (i< nbrs.size()) {
        if (nbrs[i] == 99) {
            break;
        } else if (nbrs[i] == 1) {
            nbrs[nbrs[i+3]] = nbrs[nbrs[i+1]] + nbrs[nbrs[i+2]];
        } else if (nbrs[i] == 2) {
            nbrs[nbrs[i+3]] = nbrs[nbrs[i+1]] * nbrs[nbrs[i+2]];
        } else {
            std::cout << "invalid instruction" <<std::endl;
            return -1;
        }
        i = i+4;
    }
    std::cout << "Value at position 0 " << nbrs[0] << std::endl;
    for (int i=0; i<=99;++i) {
        for (int j =0;j<=99;++j) {
            nbrs = nbrs_og;
            nbrs[1]= i;
            nbrs[2] = j;
            size_t it = 0;
            bool invalid = false;
            while (it< nbrs.size()) {
                if (nbrs[it] == 99) {
                    break;
                } else if (nbrs[it] == 1) {
                    nbrs[nbrs[it+3]] = nbrs[nbrs[it+1]] + nbrs[nbrs[it+2]];
                } else if (nbrs[it] == 2) {
                    nbrs[nbrs[it+3]] = nbrs[nbrs[it+1]] * nbrs[nbrs[it+2]];
                } else {
                    std::cout << "invalid instruction" <<std::endl;
                    invalid = true;
                    break;
                }
                it = it+4;
            }
            if (nbrs[0] == 19690720 && !invalid) {
                std::cout << "noun *verb: " << 100*i+j << std::endl; 
                return 0;
            }
        }
    }
}

