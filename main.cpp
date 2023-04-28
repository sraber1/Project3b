//
//Members: Seth Raber, Chase LaGro, Carres LaGro
//Created on 4/26/2023
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <list>
#include <chrono>
#include "LinearMap.h"
#include "ChainingMap.h"

using namespace std;


int main() {
	//create a vector of vectors to store all of the information within the data source
    vector<vector<string>> storage;
	vector<string> row;
	string line, info;
	int count = 0;

	ifstream file ("video_games.csv", ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row.clear();
			stringstream str(line);
 
			while(getline(str, info, ',')){

				//erased the quotation marks within the .cvs file
				info.erase(remove(info.begin(), info.end(), '\"' ), info.end());
                row.push_back(info);

            }
			storage.push_back(row);
			count++;
		}
	}
    file.close();

	string option;
	cout << "              =========================================" << endl;
    cout << "              Welcome to the Game Recommendation System" << endl;
	cout << "              =========================================" << endl;
	cout << "       We will give you a game based on a console you have chosen" << endl;
	cout << "Please pick an implementation: 1 - Linear Probing | 2 - Sepacrate Chaining" << endl;
	cin >> option;

	
	// Hash functions into a map based on linear Probing
	if(option == "1") {
		LinearMap games;
        // time how long it takes to insert games
        auto start = chrono::high_resolution_clock::now();
        for(int i = 1; i < storage.size(); i++){
            // get the key value pair from the vector
            pair<string, int> game = make_pair(storage[i][12], i);
            games.insert(game);
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start);
        cout << "It took " << duration.count() << " microseconds to map the games." << endl;
        // let the user pick a console
        cout << "Pick a console number: 1. Sony PSP | 2. Nintendo DS | 3. X360 | 4. Nintendo Wii | 5. PlayStation 3" << endl;
        cin >> option;

        if(option == "1"){
            option = "Sony PSP";
        } else if(option == "2"){
            option = "Nintendo DS";
        } else if(option == "3"){
            option = "X360";
        } else if(option == "4"){
            option = "Nintendo Wii";
        } else {
            option = "PlayStation 3";
        }

        vector<pair<std::string, int>> OGames = games.getGames(option);
        // find all the games on that console and output them
        for(int i = 0; i < OGames.size(); i++){
            cout << "Game " << i+1 << ": " << storage[OGames[i].second][0] << endl;
        }
        // let the user choose a game to learn more about
        while(option != "0"){
            cout << "Type a game number to learn more about (type 0 to exit): " << endl;
            cin >> option;
            if (option == "0") continue;
            int index = stoi(option);
            index--;
            cout << "Title: " << storage[OGames[index].second][0] << endl;
            cout << "Genre: " << storage[OGames[index].second][5] << endl;
            cout << "Publisher: " << storage[OGames[index].second][7] << endl;
            cout << "Review Score: " << storage[OGames[index].second][9] << endl;
            cout << "Used Price: " << storage[OGames[index].second][11] << endl;
            cout << "Rating: " << storage[OGames[index].second][13] << endl;
            cout << "Released Year: " << storage[OGames[index].second][15] << endl;
            cout << "Average Completion Time: " << storage[OGames[index].second][16] << endl;
        }
	}

	// Hash functions into a map based on Separate Chaining
	else if(option == "2") {
        ChainingMap games;
        auto start = chrono::high_resolution_clock::now();
        for(int i = 1; i < storage.size(); i++){
            // get the key value pair from the vector
            pair<string, int> game = make_pair(storage[i][12], i);
            games.Insert(game);
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<std::chrono::microseconds>(end - start);
        cout << "It took " << duration.count() << " microseconds to map the games." << endl;
        // let the user pick a console
        cout << "Pick a console number: 1. Sony PSP | 2. Nintendo DS | 3. X360 | 4. Nintendo Wii | 5. PlayStation 3" << endl;
        cin >> option;

        if(option == "1"){
            option = "Sony PSP";
        } else if(option == "2"){
            option = "Nintendo DS";
        } else if(option == "3"){
            option = "X360";
        } else if(option == "4"){
            option = "Nintendo Wii";
        } else {
            option = "PlayStation 3";
        }

        std::list<std::pair<std::string, int>> OGames = games.GetList(option);
        // find all the games on that console and output them
        int numGames = 1;
        for(auto it : OGames){
            cout << "Game " << numGames++ << ": " << storage[it.second][0] << endl;
        }
        // let the user choose a game to learn more about
        while(option != "0"){
            cout << "Type a game number to learn more about (type 0 to exit): " << endl;
            cin >> option;
            if (option == "0") continue;
            int index = stoi(option);
            // iterate over the list and find the indexth game
            index--;
            auto iter = OGames.begin();
            advance(iter, index);
            int a = iter->second;
            cout << "Title: " << storage[a][0] << endl;
            cout << "Genre: " << storage[a][5] << endl;
            cout << "Publisher: " << storage[a][7] << endl;
            cout << "Review Score: " << storage[a][9] << endl;
            cout << "Used Price: " << storage[a][11] << endl;
            cout << "Rating: " << storage[a][13] << endl;
            cout << "Released Year: " << storage[a][15] << endl;
            cout << "Average Completion Time: " << storage[a][16] << endl;
        }
    } else {
		cout << "You have chose an incorrect value, Please leave and come back again" << endl;
		return 0;
	}

	return 0;
}