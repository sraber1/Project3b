#include <string>
#include <vector>
#include <iostream>
using namespace std;

class LinearMap {
    //Data structure and private variables
    pair<string, int>* games;
    unsigned int count;
    unsigned int capacity;
    float currentLoadFactor;
    const float maxLoadFactor = 0.7;
    unsigned int hash(std::string console);
    void rehash();
public:
    LinearMap();
    void insert(pair<std::string, int> game);
    unsigned int size();
    float loadFactor();
    vector<pair<std::string, int>> getGames(string console);
};