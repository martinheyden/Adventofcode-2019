#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using std::string;
using std::cin;
using std::cout;
using std::vector;

struct Line_segment{
    int x0, y0, x1, y1, total_dist;
};


//A comma has been appended to each line
vector<Line_segment> find_segments(string s)
{
    vector<Line_segment> segments;
    int x=0, y=0;
    size_t begin = 0;
    auto end = s.length();
    size_t len = 0;
    int dx=0,dy=0;
    int total_dist = 0;
    while (begin+len != end) {
        if (s[begin+len] == ',') {

            int dist = stoi(s.substr(begin+1,len));
            switch(s[begin]) {
                case 'U':
                    dy = 1;
                    dx = 0;
                    break;
                case 'D':
                    dy = -1;
                    dx = 0;
                    break;
                case 'L':
                    dy = 0;
                    dx = -1;  
                    break;  
                case 'R':
                    dy = 0;
                    dx = 1;
                    break;
                default:
                    throw std::invalid_argument("Invalid direction: " + s.substr(begin,1));
            }
            Line_segment ls{x,y,x+dx*dist,y+dy*dist, total_dist};
            x = ls.x1;
            y = ls.y1;
            total_dist += dist;
            segments.push_back(ls);
            begin = begin+len+1;
            len = 0;
        } else {
            ++len;
        }
    }
    return segments;
}

int find_intersection(Line_segment s1, Line_segment s2)
{
    //Lets assume  only pointwise intersections for now...
    if (s1.x0!= s1.x1 && s2.y0 != s2.y1) {
        if (s2.x1 > std::min(s1.x0,s1.x1) && s2.x1 < std::max(s1.x0,s1.x1) 
            && s1.y1 > std::min(s2.y0,s2.y1) && s1.y1 < std::max(s2.y0,s2.y1)  ) {
                return s1.y0+s2.x0;
            } else {
                return INT_MAX;
            }
    } else if (s1.y0!=s1.y1 && s2.x0 != s2.x1) {
        if (s2.y1 > std::min(s1.y0,s1.y1) && s2.y1 < std::max(s1.y0,s1.y1) 
            && s1.x1 > std::min(s2.x0,s2.x1) && s1.x1 < std::max(s2.x0,s2.x1)  ) {
                return s1.x0+s2.y0;
            } else {
                return INT_MAX;
            }
    } else { //Parallel segments
        return INT_MAX;
    }
}

int find_intersection_delay(Line_segment s1, Line_segment s2)
{
    //Lets assume  only pointwise intersections for now...
    if (s1.x0!= s1.x1 && s2.y0 != s2.y1) {
        if (s2.x1 > std::min(s1.x0,s1.x1) && s2.x1 < std::max(s1.x0,s1.x1) 
            && s1.y1 > std::min(s2.y0,s2.y1) && s1.y1 < std::max(s2.y0,s2.y1)  ) {
                return s1.total_dist+s2.total_dist + std::abs(s1.y0-s2.y0) + std::abs(s2.x0-s1.x0);
            } else {
                return INT_MAX;
            }
    } else if (s1.y0!=s1.y1 && s2.x0 != s2.x1) {
        if (s2.y1 > std::min(s1.y0,s1.y1) && s2.y1 < std::max(s1.y0,s1.y1) 
            && s1.x1 > std::min(s2.x0,s2.x1) && s1.x1 < std::max(s2.x0,s2.x1)  ) {
                return s1.total_dist+s2.total_dist + std::abs(s1.x0-s2.x0) + std::abs(s2.y0-s1.y0);
            } else {
                return INT_MAX;
            }
    } else { //Parallel segments
        return INT_MAX;
    }
}

int find_closest_intersection(vector<Line_segment> vs1, vector<Line_segment> vs2)
{
    int min_dist = INT_MAX;
    for (auto s1 : vs1) {
        for (auto s2 : vs2) {
            int dist = find_intersection_delay(s1,s2);
            if (dist <min_dist && dist != 0)
                min_dist = dist;
        }
    }
    return min_dist;
}

int main()
{
    string line1, line2;
    cin >> line1 >> line2;
    vector<Line_segment> seg1 = find_segments(line1);
    vector<Line_segment> seg2 = find_segments(line2);
    cout << "Closest segment " << find_closest_intersection(seg1,seg2) << "   int max " << INT_MAX << std::endl;
}