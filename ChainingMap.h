#include <iostream>
#include <list>
#include <vector>

class ChainingMap {
    // map will be an array of lists of pairs for each game
    // hash by console, then know which bucket is which based on hash function
    std::list<std::pair<std::string, int>>* lists;
    int size;
    unsigned int capacity;
    const float maxLoadFactor = 0.7;
    void Resize();
    int Hash(std::string console);
public:
    ChainingMap();
    void Insert(std::pair<std::string, int> game);
    std::list<std::pair<std::string, int>> GetList(std::string console);
    float GetLoadFactor();
};