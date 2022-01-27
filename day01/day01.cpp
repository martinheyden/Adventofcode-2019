#include <iostream>
#include <vector>

using std::vector;

int additional_fuel(int w) 
{
    int new_fuel = w/3-2;
    if (new_fuel >0) {
        return new_fuel+additional_fuel(new_fuel);
    } else {
        return 0;
    }
}

int main() 
{
    vector<int> nbrs;
    int nbr = 0;
    while (std::cin >> nbr) {
        nbrs.push_back(nbr);
    }
    int agg = 0;
    int agg_b = 0;
    for (auto v : nbrs) {
        agg += v/3-2;
        agg_b += v/3-2 + additional_fuel(v/3-2);
    }
    std::cout << "The fuel requirement part a is " << agg << std::endl;
    std::cout << "The fuel requirement part b  is " << agg_b << std::endl;
}

