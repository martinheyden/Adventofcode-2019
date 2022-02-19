#include <iostream>
#include <vector>
#include <map>
#include <memory>

using std::vector;
using std::string;
using std::map;
using std::unique_ptr;

struct Node {
    vector<unique_ptr<Node>> children;
};

unique_ptr<Node> new_node() 
{
    vector<unique_ptr<Node>> v;
    return std::make_unique<Node>(v);
}

Node parse_graph(vector<string> vs)
{
    map<string,Node *> dict;
    for (string s :vs) {
        string source = "todo";
        string dest = "todo";
        auto node_p = dict.find(source);
        if (node_p == dict.end()) {

        }
    }
}


int main() 
{

    return 0;
}