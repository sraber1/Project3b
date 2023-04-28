#include "LinearMap.h"

LinearMap::LinearMap()
{
    // initialize all variables
    count = 0;
    currentLoadFactor = 0;
    capacity = 10;
    games = new pair<string, int>[capacity];
}

unsigned int LinearMap::hash(std::string console)
{
    // sum all ascii values of the letters in console and mod by capacity to get hash
    unsigned int hash = 0;
    for (char c : console) {
        hash += c;
    }
    hash = hash % capacity;
    return hash;
}

void LinearMap::rehash()
{
    // create new array and rehash all the old values into it
    unsigned int newCapacity = capacity * 2;
    auto newBuckets = new pair<std::string, int>[newCapacity];
    for (unsigned int i = 0; i < capacity; i++){
        if (!games[i].first.empty()){
            capacity = newCapacity;
            unsigned int index = hash(games[i].first);
            capacity /= 2;
            while (!newBuckets[index].first.empty()){
                index++;
                if(index >= capacity){
                    index = 0;
                }
            }
            newBuckets[index] = games[i];
        }
    }
    // delete old array and replace it with new one with rehashed values
    delete[] games;
    capacity = newCapacity;
    games = newBuckets;
    currentLoadFactor = (float)count/(float)capacity;
}

void LinearMap::insert(pair<std::string, int> game)
{
    // get the index from the hash function, then use linear probing to find next available index
    unsigned int index = hash(game.first);
    while (!games[index].first.empty()){
        index++;
        if(index >= capacity){
            index = 0;
        }
    }
    // add game to array and check if rehashing is necessary
    games[index] = game;
    count++;
    currentLoadFactor = (float) count / (float) capacity;
    if (currentLoadFactor >= maxLoadFactor) {
        rehash();
    }
}

unsigned int LinearMap::size()
{
    // return current size
    return count;
}

float LinearMap::loadFactor()
{
    // return current load factor
    return currentLoadFactor;
}

vector<pair<string, int>> LinearMap::getGames(std::string console) {
    // return a vector of all the games on a specific console
    vector<pair<string, int>> output;
    for(unsigned int i = 0; i < capacity; i++){
        if(games[i].first == console){
            output.push_back(games[i]);
        }
    }
    return output;
}