#include <map>
#include <iostream>

using namespace std;

int main()
{
    map<int,string>m{{123,"ahmed"},{124,"omar"}};
    for(auto mm : m)
        cout << mm.first << "-" << mm.second << endl;
}