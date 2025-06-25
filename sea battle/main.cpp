/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <cstdlib>

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
                cout << "■ ";
                break;
                case 2:
                cout << "X ";
                break;
            }
            cout << "| ";
        }
        cout << endl;
    }
}

vector <vector<int>> changeValue(vector <vector<int>> map, string pos, int value){
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
    return map;
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
    pos += 'a' + row;
    pos += to_string(col+1);
}

// bool placeCheck(vector <vector<int>> map, string pos, int shipSize){
//     vector <string> vec;
//     for(int i = 0; i < 10; i++){
//         for (int j = 0; j < 10; j++){
//             if(map[i][j] == 1){
//                 vec.push_back(getPos(i, j))
                
//             }
//         }
//     }
// }

vector <vector<int>> fillMap(vector <vector<int>> map){
    int ship4Count = 1;
    int ship3Count = 2;
    int ship2Count = 3;
    int ship1Count = 4;
    
    int choice = -1;
    
    while(ship1Count > 0 || ship2Count > 0 || ship3Count > 0 || ship4Count > 0){
        
        string pos;
        
        showPlayerMap(map);
        
        cout << "\nSHIPS LEFT:\n■■■■ x" << ship4Count << "\n■■■  x" << ship3Count << "\n■■   x" << ship2Count << "\n■    x" << ship1Count << endl;
        
        cout << "\nChoose the ship you want to place (enter its size 1 - 4) ";
        cin >> choice;
        
        switch(choice){
            case 1:
            if(ship1Count == 0){
                cout << "You have 0 small ships left";
                break;
            }else{
                pos = askForPos();
                map = changeValue(map, pos, 1);
                ship1Count--;
                break;
            }
            break;
            case 2:
            if(ship2Count == 0){
                cout << "You have 0 medium ships left";
                break;
            }else{
                pos = askForPos();
                map = changeValue(map, pos, 1);
                ship2Count--;
                pos = posPlus1l(pos);
                map = changeValue(map, pos, 1);
                break;
            }
            break;
            case 3:
            if(ship3Count == 0){
                cout << "You have 0 big ships left";
                break;
            }else{
                pos = askForPos();
                map = changeValue(map, pos, 1);
                ship3Count--;
                for(int i = 0; i < 2; i++){
                    pos = posPlus1l(pos);
                    map = changeValue(map, pos, 1);
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
                map = changeValue(map, pos, 1);
                ship4Count--;
                for(int i = 0; i < 3; i++){
                    pos = posPlus1l(pos);
                    map = changeValue(map, pos, 1);
                }
                break;
            }
            break;
        }
        
    }
    return map;
}

int main()
{
    // showPlayerMap(createEmptyMap());
    fillMap(createEmptyMap());

    return 0;
}