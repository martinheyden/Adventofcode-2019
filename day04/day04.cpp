#include <iostream>

bool two_adjacent(int nbr, int prev)
{
    if (nbr == 0) {
        return false;
    } else if (nbr%10 == prev)  {
        return true;    
    } else {
        return two_adjacent(nbr/10,nbr%10);
    }
}

bool exact_two_adjacent(int nbr, int prev, int count)
{
    if (nbr == 0) {
        if (count == 1) {
            return true;
        } else {
            return false;
        }
    } else if (nbr%10 == prev)  {
        return exact_two_adjacent(nbr/10,nbr%10,++count);
    } else if (nbr%10 != prev && count ==1 ){
        return true;
    } else {
        return exact_two_adjacent(nbr/10,nbr%10,0);
    }
}

bool non_decreasing(int nbr,int prev)
{
    if (nbr == 0) {
        return true;
    } else if (nbr%10<=prev) {
        return non_decreasing(nbr/10,nbr%10);
    } else {
        return false;
    }
}

int main()
{
    int low = 134792;
    int high = 675810;

    int count = 0;
    for (int i = low; i<= high; ++i) {
        if (non_decreasing(i,10) && exact_two_adjacent(i,10,0)) {
            ++count;
        }
    }
    std::cout << "Number valid passwords: " << count << std::endl;
    return 0;
}