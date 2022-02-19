#include <iostream>
#include <vector>
#include <map>
#include <string>

using std::map;
using std::string;
using std::vector;


int calculate_orbits(vector<vector<int> > &parent_vec, vector<int> &orbit_vec, int i)
{
    if (orbit_vec[i] !=-1) {
        return orbit_vec[i];
    } else {
        int count = 0;
        for (auto p: parent_vec[i]) {
            count += calculate_orbits(parent_vec,orbit_vec,p) + 1;
        }
        orbit_vec[i] = count;
        return count;
    }
}

int calculate_distance_from(int target, int source, 
    vector<vector<int> > &parent_vec, vector<int> &distance_vec)
{
  //  std::cout << "calculating distance to target " << target << " from to source " << source << std::endl;
    if (source == target) {
        return 0;
    }
    if (distance_vec[source] != -1) {
        return distance_vec[source];
    }
    int closest = INT_MAX;
    for (auto p:parent_vec[source]) {
        int dist = calculate_distance_from(target,p,parent_vec,distance_vec);
        if (dist!= INT_MAX) { //avoid overflow...
            ++dist;
        }
        if (dist<closest) { //probably redundant (only exist one path)
            closest=dist;
        }
    }
  //  distance_vec[source] = closest;
    return closest;
}


int main()
{
    map<string,uint> dict;
    vector<vector<int> > parent_vec;
    //Read data
    string line;
    int number_of_nodes = 0;
    int source_nbr, dest_nbr;
    while (std::cin >> line) {
        string source = line.substr(0,3);
        string dest = line.substr(4,3);
        auto source_id = dict.find(source);
        if (source_id == dict.end()) {
            source_nbr = number_of_nodes;
            dict[source] = number_of_nodes;
            ++number_of_nodes;
            vector<int> parents;
            parent_vec.push_back(parents);
           // std::cout << "Inserting " << source << " into map" << std::endl;
        } else {
            source_nbr = source_id->second;
        }
        auto dest_id = dict.find(dest);
        if (dest_id == dict.end()) {
            dest_nbr = number_of_nodes;
            dict[dest] = number_of_nodes;
            ++number_of_nodes;
            vector<int> parents;
            parent_vec.push_back(parents);
         //   std::cout << "Inserting " << dest << " into map" << std::endl;
        } else {
            dest_nbr = dest_id->second;
        }
         parent_vec[dest_nbr].push_back(source_nbr);
    }
    std::cout << parent_vec[0].size() <<std::endl;
   
    vector<int> orbits;
    for (int i =0; i<number_of_nodes;++i) {
        orbits.push_back(-1);
    }
    int count = 0;
    for (int i =0; i<number_of_nodes;++i) {
        count += calculate_orbits(parent_vec,orbits,i);
    }
    std::cout << "Number of orbits: " << count <<std::endl;

    int you_id = dict.find("YOU")->second;
    std::cout << "You parents size " << parent_vec[you_id][0] << std::endl;
    int santa_id = dict.find("SAN")->second;
    
    vector<int> distance_you;
    vector<int> distance_santa;
    for (int i =0; i<number_of_nodes;++i) {
        distance_you.push_back(-1);
        distance_santa.push_back(-1);
    }

    int shortest = INT_MAX;
    std::cout << "number of nodes: " << number_of_nodes <<std::endl;
    for (int i =0; i<number_of_nodes;++i) {
        int you = calculate_distance_from(i,you_id,parent_vec,distance_you);
        if (you!= INT_MAX) {
            std::cout << you_id << " you |  i  " << i <<std::endl;
        }
        int santa = calculate_distance_from(i,santa_id,parent_vec,distance_santa);
        if (santa!= INT_MAX) {
            std::cout << santa_id << " santa |  i  " << i <<std::endl;
        }
        if ((you!= INT_MAX && santa != INT_MAX) &&you+santa<shortest) {
            std::cout << you << std::endl;
            shortest = you+santa;
        }
    }
    std::cout << "Number of switches " << (shortest -2) << " int max " << INT_MAX << std::endl;
    

}