#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "map_manipulations.h"

using namespace std;

enum Mode{
    RANDOM,
    AIM,
};
struct Hit{
    int row;
    int col;
};


vector <Hit> memory = { {-1, -1}, {-1, -1}};
Mode aiMode = RANDOM;

void aiAttack(vector <vector<int>>& map, vector <Hit>& memory, Mode& aiMode){
    
    switch(aiMode){
        case RANDOM: {
        
        while(true){
            int row = rand() % 10;
            int col = rand() % 10;
            
            string pos = "";
            
            pos += 'a' + col;
            pos += to_string(row + 1);
            
            if(map[row][col] != 2 && map[row][col] != 3){
                
                attack(map, pos);
                
                if(map[row][col] == 2){
                    memory = { {row, col - 1}, {row, col + 1} };
                    
                    aiMode = AIM;
                    break;
                }
                break;
            }
        }
        break;
        }
        case AIM: {
        bool check = false;
        
        if(memory[0].row >= 10 || memory[0].col >= 10 || memory[0].row < 0 || memory[0].col < 0){
            memory[0] = {999,999};
        }
        if(memory[1].row >= 10 || memory[1].col >= 10 || memory[1].row < 0 || memory[1].col < 0){
            memory[1] = {999,999};
        }
        
        if(memory[0].row >= 0 && memory[0].col >= 0 && memory[0].row != 999){
            if(map[memory[0].row][memory[0].col] != 2 && map[memory[0].row][memory[0].col] != 3){
                string pos = "";
                pos += 'a' + memory[0].col;
                pos += to_string(memory[0].row + 1);
                attack(map, pos);
                if(map[memory[0].row][memory[0].col] == 2){
                    memory[0] = {memory[0].row, memory[0].col - 1};
                }else{
                    memory[0] = {999, 999};
                }
                return;
            }
        }
        if(memory[1].row >= 0 && memory[1].col >= 0 && memory[1].row != 999){
                string pos = "";
                pos += 'a' + memory[1].col;
                pos += to_string(memory[1].row + 1);
                attack(map, pos);
                
                if(map[memory[1].row][memory[1].col] == 2){
                    memory[1] = {memory[1].row, memory[1].col + 1};
                }else{
                    memory[1] = {999, 999};
                }
                return;
        }
        while(true){
            int row = rand() % 10;
            int col = rand() % 10;
            
            string pos = "";
            
            pos += 'a' + col;
            pos += to_string(row + 1);
            
            if(map[row][col] != 2 && map[row][col] != 3){
                
                attack(map, pos);
                
                if(map[row][col] == 2){
                    memory = { {row, col - 1}, {row, col + 1} };
                    
                    aiMode = AIM;
                    break;
                }
                break;
            }
        }
        break;
    }
    
}
}

int main()
{
    srand(time(0));
    vector <vector<int>> playerMap = createEmptyMap();
    vector <vector<int>> aiMap = createEmptyMap();
    autoFillMap(aiMap);
    
    int choice = -1;
    
    cout << "1 - I'll fill the map by myself!\n2 - Auto fill the map\n";
    cin >> choice;
    
    switch(choice){
        case 1:
        fillMap(playerMap);
        break;
        case 2:
        autoFillMap(playerMap);
        break;
        default:
        autoFillMap(playerMap);
        break;
    }
    
    cout << "\nYOUR MAP:\n";
    showPlayerMap(playerMap);
    
    cout << "\nENEMY MAP\n";
    showAiMap(aiMap);
    
    bool game = true;
    string attackPos;
    
    while (game){
        bool attackCheck = false;
        while(!attackCheck){
            cout << "Your turn!\nEnter the position you want to attack ";
            cin >> attackPos;
            int row;
            int col;
        
            if(attackPos.size() == 2){
                row = attackPos[1] - '0' - 1;
                col = attackPos[0] - 'a';
            }else{
                row = 9;
                col = attackPos[0] - 'a';
            }
            int oldValue = aiMap[row][col];
            
            attack(aiMap, attackPos);
            
            if(aiMap[row][col] == oldValue){
                cout << "Try again" << endl;
            }else{
                attackCheck = true;
            }
        }
        
        cout << "Enemy turn!" << endl;
        
        aiAttack(playerMap, memory, aiMode);
        
        cout << "\nYOUR MAP:\n";
        showPlayerMap(playerMap);
     
        cout << "\nENEMY MAP\n";
        showAiMap(aiMap);
        
        bool allPlayerShipsSunk = true;
        
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                if(playerMap[i][j] == 1){
                    allPlayerShipsSunk = false;
                    break;
                }
            }
            if(!allPlayerShipsSunk) break;
        }
        
        if(allPlayerShipsSunk){
            cout << "\nGAME OVER\n";
            game = false;
        }
        
        bool allAiShipsSunk = true;
        
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                if(aiMap[i][j] == 1){
                    allAiShipsSunk = false;
                    break;
                }
            }
            if(!allAiShipsSunk) break;
        }
        
        if(allAiShipsSunk){
            cout << "\nVICTORY\n";
            game = false;
        }
        
    }
    
    return 0;
}