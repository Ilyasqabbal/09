#include <map>
#include <iostream>

using namespace std;

int main()
{
    map<int,string>m{{123,"ahmed"},{124,"omar"}};
    for(auto mm : m)
        cout << mm.first << "-" << mm.second << endl;
}





#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> myMap;

    myMap[1] = "apple";
    myMap[2] = "banana";
    myMap[3] = "cherry";
    myMap[4] = "date";
    myMap[5] = "elderberry";

    // Find the first element with a key >= 3
    auto it = myMap.lower_bound(3);

    // Print out all elements from the lower bound to the end
    for (; it != myMap.end(); ++it) {
        std::cout << it->first << ": " << it->second << std::endl;
    }

    return 0;
}
