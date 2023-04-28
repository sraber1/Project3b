#include "ChainingMap.h"

ChainingMap::ChainingMap() {
    // initialize capacity, size, and create the array of lists
    capacity = 10;
    size = 0;
    lists = new std::list<std::pair<std::string, int>>[capacity];
}

void ChainingMap::Resize() {
    // resize map if the load factor is reached
    unsigned int newCapacity = capacity * 2;
    std::list<std::pair<std::string, int>>* newLists = new std::list<std::pair<std::string, int>>[newCapacity];
    for (int i = 0; i < capacity; i++) {
        if(!lists[i].empty()){
            // rehash and move list in new array
            int index = Hash(lists[i].front().first);
            newLists[index] = lists[i];
        }
    }
    // delete old array and assign lists to new one
    delete[] lists;
    capacity = newCapacity;
    lists = newLists;
}

int ChainingMap::Hash(std::string console) {
    // find bucket based on console
    // sum ascii values of each character and get the remainder when dividing by the size to get the index
    int hash = 0;
    for(char c : console){
        hash += c;
    }
    hash = hash % capacity;
    return hash;
}

void ChainingMap::Insert(std::pair<std::string, int> game) {
    // get index from hash function
    int index = Hash(game.first);
    lists[index].push_back(game);
    size++;
    // check to make sure the max load factor is not exceeded, if it is, resize the array
    float loadFactor = (float) size / (float) capacity;
    if(loadFactor >= maxLoadFactor){
        Resize();
    }
}

std::list<std::pair<std::string, int>> ChainingMap::GetList(std::string console) {
    // return all the games on a single console
    int index = Hash(console);
    return lists[index];
}

float ChainingMap::GetLoadFactor() {
    // return the current load factor
    return (float) size / (float) capacity;
}