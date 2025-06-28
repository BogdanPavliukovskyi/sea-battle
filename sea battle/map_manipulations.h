#ifndef map_manipulations_h
#define map_manipulations_h

#include <vector>
using namespace std;

vector <vector<int>> createEmptyMap();
void showMap(vector <vector<int>> map);
void showPlayerMap(vector <vector<int>> map);
void showAiMap(vector <vector<int>> map);
void changeValue(vector <vector<int>>& map, string pos, int value);
string askForPos();
string posPlus1n(string pos);
string posPlus1l(string pos);
string posMinus1n(string pos);
string posMinus1l(string pos);
string getPos(int row, int col);
bool checkSurrounding(const vector<vector<int>> map, int row, int col);
bool placeCheck(vector<vector<int>> map, string pos, int shipSize);
void addShip(vector <vector<int>>& map, string pos, int shipSize);
void fillMap(vector <vector<int>>& map);
void autoFillMap(vector <vector<int>>& map);
void attack(vector <vector<int>>& map, string pos);


#endif