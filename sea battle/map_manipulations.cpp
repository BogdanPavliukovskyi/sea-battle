#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector <vector<int>> createEmptyMap(){
    return vector <vector<int>>(10, vector<int>(10, 0));
}

void showMap(vector <vector<int>> map){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}
void showPlayerMap(vector <vector<int>> map){
    cout << "     a   b   c   d   e   f   g   h   i   j\n";
    for (int i = 0; i < 10; i++){
        if(i != 9){
            cout << i+1 << "  | ";
        }else{
            cout << i+1 << " | ";
        }
        for (int j = 0; j < 10; j++){
            switch(map[i][j]){
                case 0:
                cout << "  ";
                break;
                case 1:
                cout << "# ";
                break;
                case 2:
                cout << "X ";
                break;
                case 3:
                cout << "+ ";
                break;
            }
            cout << "| ";
        }
        cout << endl;
    }
}
void showAiMap(vector <vector<int>> map){
    cout << "     a   b   c   d   e   f   g   h   i   j\n";
    for (int i = 0; i < 10; i++){
        if(i != 9){
            cout << i+1 << "  | ";
        }else{
            cout << i+1 << " | ";
        }
        for (int j = 0; j < 10; j++){
            switch(map[i][j]){
                case 0:
                cout << "  ";
                break;
                case 1:
                cout << "  ";
                break;
                case 2:
                cout << "X ";
                break;
                case 3:
                cout << "+ ";
                break;
            }
            cout << "| ";
        }
        cout << endl;
    }
}

void changeValue(vector <vector<int>>& map, string pos, int value){
    int row;
    int col;
    
    if(pos.size() == 2){
        row = pos[1] - '0' - 1;
        col = pos[0] - 'a';
    }else{
        row = 9;
        col = pos[0] - 'a';
    }
    map[row][col] = value;
}

string askForPos(){
    string pos = " ";
    while(pos.size() != 2 && pos.size() != 3){
        cout << "Enter position ";
        cin >> pos;
    }
    return pos;
}
string posPlus1n(string pos){
    if(pos[1] != '9'){
       pos[1] = (pos[1] - '0' + 1) + '0'; 
    }else{
        pos[1] = '1';
        pos += '0';
    }
    return pos;
}
string posPlus1l(string pos){
    pos[0]++;
    return pos;
}
string posMinus1n(string pos){
    if(pos[1] != '1' || pos[2] != '0'){
       pos[1] = (pos[1] - '0' - 1) + '0'; 
    }else{
        pos[1] = '9';
    }
    return pos;
}
string posMinus1l(string pos){
    pos[0]--;
    return pos;
}

string getPos(int row, int col){
    string pos = "";
    pos += 'a' + col ;
    pos += to_string(row+1);
    return pos;
}



bool checkSurrounding(const vector<vector<int>> map, int row, int col){
    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            int r = row + i;
            int c = col + j;
            if(r >= 0 && r < 10 && c >= 0 && c < 10){
                if(map[r][c] != 0){
                    return false;
                }
            }
        }
    }
    return true;
}

bool placeCheck(vector<vector<int>> map, string pos, int shipSize){
    int row;
    int col;

    if(pos.size() == 2){
        row = pos[1] - '0' - 1;
        col = pos[0] - 'a';
    }else{
        row = 9;
        col = pos[0] - 'a';
    }

    if(col + shipSize > 10){
        return false;
    }

    for(int i = 0; i < shipSize; i++){
        if(!checkSurrounding(map, row, col + i)){
            return false;
        }
    }

    return true;
}

void addShip(vector <vector<int>>& map, string pos, int shipSize){
    if(!placeCheck(map, pos, shipSize)){
        return;
    }else{
        int row;
        int col;

        if(pos.size() == 2){
            row = pos[1] - '0' - 1;
            col = pos[0] - 'a';
        }else{
            row = 9;
            col = pos[0] - 'a';
        }
        
        if(col + shipSize > 10){
            cout << "The ship is too big" << endl;
            return;
        }
        
        for (int i = 0; i < shipSize; i++){
            map[row][col + i] = 1;
        }
    }
    
}

void fillMap(vector <vector<int>>& map){
    int ship4Count = 1;
    int ship3Count = 2;
    int ship2Count = 3;
    int ship1Count = 4;
    
    int choice = -1;
    
    while(ship1Count > 0 || ship2Count > 0 || ship3Count > 0 || ship4Count > 0){
        
        string pos;
        
        showPlayerMap(map);
        
        cout << "\nSHIPS LEFT:\n#### x" << ship4Count << "\n###  x" << ship3Count << "\n##   x" << ship2Count << "\n#    x" << ship1Count << endl;
        
        cout << "\nChoose the ship you want to place (enter its size 1 - 4) ";
        cin >> choice;
        
        vector <vector<int>> oldMap = map;
        
        switch(choice){
            case 1:
            if(ship1Count == 0){
                cout << "You have 0 small ships left";
                break;
            }else{
                pos = askForPos();
                addShip(map, pos, 1);
                if(map != oldMap){
                    ship1Count--;
                }
                break;
            }
            break;
            case 2:
            if(ship2Count == 0){
                cout << "You have 0 medium ships left";
                break;
            }else{
                pos = askForPos();
                addShip(map, pos, 2);
                if(map != oldMap){
                    ship2Count--;
                }
                break;
            }
            break;
            case 3:
            if(ship3Count == 0){
                cout << "You have 0 big ships left";
                break;
            }else{
                pos = askForPos();
                addShip(map, pos, 3);
                if(map != oldMap){
                    ship3Count--;
                }
                break;
                
            }
            break;
            case 4:
            if(ship4Count == 0){
                cout << "You have 0 massive ships left";
                break;
            }else{
                pos = askForPos();
                addShip(map, pos, 4);
                if(map != oldMap){
                    ship4Count--;
                }
                break;
            }
            break;
        }
        
    }
}

void autoFillMap(vector <vector<int>>& map){
    
    int ship4Count = 1;
    int ship3Count = 2;
    int ship2Count = 3;
    int ship1Count = 4;
    
    int shipSize;
    
    while(ship1Count > 0 || ship2Count > 0 || ship3Count > 0 || ship4Count > 0){
        
        if(ship4Count > 0){
            shipSize = 4;
        }else if(ship3Count > 0){
            shipSize = 3;
        }else if(ship2Count > 0){
            shipSize = 2;
        }else{
            shipSize = 1;
        }
        
        
        bool placed = false;
        
        while(!placed){
            int row = rand() % 10;
            int col = rand() % (11 - shipSize);
            
            string pos = "";
            
            pos += 'a' + col;
            pos += to_string(row + 1);
            
            if (placeCheck(map, pos, shipSize)){
                addShip(map, pos, shipSize);
                placed = true;
            }
        }
        
        
        if(placed){
            switch(shipSize){
                case 1:
                ship1Count--;
                break;
                case 2:
                ship2Count--;
                break;
                case 3:
                ship3Count--;
                break;
                case 4:
                ship4Count--;
            }
        }
    }
    
}
void attack(vector <vector<int>>& map, string pos){
    int row;
    int col;

    if(pos.size() == 2){
        row = pos[1] - '0' - 1;
        col = pos[0] - 'a';
    }else{
        row = 9;
        col = pos[0] - 'a';
    }
    
    if(map[row][col] == 1){
        map[row][col] = 2;
    }else if(map[row][col] == 0){
        map[row][col] = 3;
    }
}

