#include <iostream>
#include <string>
#include <vector>
#include <climits>

using std::string;
using std::vector;

const int WIDTH = 25;
const int HEIGHT = 6;

vector<string> splitIntoLayers(string s) 
{
    vector<string> layers;
    int i = 0;
    while (i< s.size()) {
        layers.push_back(s.substr(i,WIDTH*HEIGHT));
        i += WIDTH*HEIGHT;
    }
    return layers;
}

void countDigits(string s, int (&result)[3])
{
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;
    for (char c : s) {
        switch (c) {
            case '0':
                result[0]+=1;
                break;
            case '1':
                result[1]+=1;
                break;
            case '2':
                result[2]+=1;
                break;
            default:
                std::cout << "invalid digit" << std::endl;  
        }
    }
}

int firstPart(string s) 
{
    auto layers = splitIntoLayers(s);
    int fewestZero = INT_MAX;
    int score = 0;
    int result[3] = {0,0,0};
    for (string s: layers) {
        countDigits(s, result);
        if (result[0] < fewestZero) {
            fewestZero = result[0];
            score = result[1] * result[2];
        }
    }
    return score;
}

void update(string& p, string l)
{
    for (int i = 0; i <p.size(); ++i) {
        if (p[i] == '2') {
            p[i] = l[i];
        }
    }
}

void transform(string& p)
{
    for (auto& ch:p) {
        if (ch == '0') {
            ch = ' ';
        } else if (ch == '1') {
            ch = '*';
        } else {
            ch = ' ';
        }
    }
}

void visualize(string p)
{
    int start = 0;
    for (int i =0; i<HEIGHT; i++) {
        std::cout << p.substr(start,WIDTH) << std::endl;
        start+=WIDTH;
    }
}

void secondPart(string s)
{
    auto layers = splitIntoLayers(s);
    string picture (WIDTH*HEIGHT,'2');
    for (auto l: layers) {
        update(picture,l);
    }
    transform(picture);
    visualize(picture);
}

int main()
{
    string s;
    std::cin >> s;
    
    std::cout << "Part a " << firstPart(s) << std::endl;
    secondPart(s);
}