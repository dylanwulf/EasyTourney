/**************************************************************
EasyTourney -- A simple, easy to use tournament bracket manager
Copyright (C) 2015 Dylan Wulf

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
****************************************************************/

#include <SingleEliminationManager.h>
#include <cmath>
#include <cstdlib>
//the rand() function is in cstdlib

//Constructor takes arguments:
//playerList: list of all players entered
//numPlayers: how many players entered
//randomize: whether to shuffle the array
SingleEliminationManager::SingleEliminationManager(Player* playerList[], unsigned int numSpots, bool randomize): BracketManager() {
    if (randomize){
        randomizePlayers(playerList, numSpots);
    }
    playerTree = new BracketTree(playerList, numSpots);
    selectedLevel = playerTree->getNumLevels() + 1;
    selectedPos = 0;
}

//Destructor
SingleEliminationManager::~SingleEliminationManager(){
    delete playerTree;
}

//Draw bracket and names on screen
void SingleEliminationManager::drawBracket(wxDC& dc, int canvasWidth, int canvasHeight){
    int numLevels = playerTree->getNumLevels();
    int numSpots = pow(2, numLevels - 1);
    int currSpots = numSpots;
    int currLevel = 0;
    double levelWidth = (double) canvasWidth / (log2(numSpots) + 1);

    int numPlayers = playerTree->getNumPlayers();
    int numSecondRounders = pow(2, numLevels - 2);
    int numLeftovers = numPlayers - numSecondRounders;
    int numFirstRounders = numLeftovers * 2;

    //Just draw the very left (bottom) ones first
    for (int i = 0; i < numFirstRounders; i++){
        double branchHeight = (double) canvasHeight / currSpots;
        int x1 = 0;
        int x2 = levelWidth;
        int y1 = branchHeight * i + branchHeight / 2;
        int y2 = y1;

        if (currLevel == selectedLevel && i == selectedPos){
            dc.SetPen(*wxBLACK_DASHED_PEN);
            dc.DrawRectangle(x1, y1 - 20, levelWidth, 20);
            dc.SetPen(*wxBLACK_PEN);
        }
        dc.DrawLine(x1, y1, x2, y2); //horizontal lines
        if (playerTree->getPlayerAt(currLevel, i) != NULL){
            Player* p = playerTree->getPlayerAt(currLevel, i);
            dc.DrawText(p->getName(), x1 + 20, y1 - 16);
        }

        if (i % 2 == 0 && i < currSpots - 1)
            dc.DrawLine(x2, y1, x2, y1 + branchHeight + 1); //vertical lines
    }

    currSpots /= 2;
    currLevel++;

    //Then draw all the rest
    while (currSpots >= 1){
        
        double branchHeight = (double) canvasHeight / currSpots;
        int x1 = levelWidth * currLevel;
        int x2 = levelWidth * (currLevel + 1);

        for (int i = 0; i < currSpots; i++){
            
            int y1 = branchHeight * i + branchHeight / 2;
            int y2 = y1;

            if (currLevel == selectedLevel && i == selectedPos){
                dc.SetPen(*wxBLACK_DASHED_PEN);
                dc.DrawRectangle(x1, y1 - 20, levelWidth, 20);
                dc.SetPen(*wxBLACK_PEN);
             }

            dc.DrawLine(x1, y1, x2, y2); //Draw horizontal lines
            if (playerTree->getPlayerAt(currLevel, i) != NULL){
                Player* p = playerTree->getPlayerAt(currLevel, i);
                dc.DrawText(p->getName(), x1 + 20, y1 - 16);
            }

            if (i % 2 == 0 && i < currSpots - 1)
                dc.DrawLine(x2, y1, x2, y1 + branchHeight + 1);
                //Draw vertical lines
        }
        currSpots /= 2;
        currLevel++;
    }
}

//Get the player located here, if any
Player* SingleEliminationManager::selectPlayer(int x, int y, int canvasWidth, int canvasHeight){
    int level = x / ((float) canvasWidth / playerTree->getNumLevels());
    selectedLevel = level;
    int numBranches = pow(2, playerTree->getNumLevels() - level - 1);
    float branchHeight = (float) canvasHeight / numBranches;
    int pos = y / branchHeight;
    selectedPos = pos;

    Player* result = NULL;
    int lineY = pos * branchHeight + branchHeight / 2;
    if (lineY - y >= 0 && lineY - y <= 20){
        result = playerTree->getPlayerAt(level, pos);
    }
    if (result == NULL){
        selectedLevel = playerTree->getNumLevels() + 1;
    }
    return result;
}

//Advances the player (selected by selectPlayer()) up the bracket
bool SingleEliminationManager::selectedPlayerWon(){
    bool result = playerTree->playerWon(selectedLevel, selectedPos);
    if (result){
        selectedLevel = selectedLevel + 1;
        selectedPos = selectedPos / 2;
        return true;
    }
    return false;
}

//Unadvances the player (selected by selectPlayer()), which means this spot
//will be cleared if this is the highest point this player has advanced.
bool SingleEliminationManager::unAdvanceSelectedPlayer(){
    Player* p = playerTree->getPlayerAt(selectedLevel, selectedPos);
    bool result = playerTree->unAdvancePlayer(selectedLevel, selectedPos);
    if (result && p == playerTree->getPlayerAt(selectedLevel - 1, selectedPos * 2)){
        selectedLevel = selectedLevel - 1;
        selectedPos = selectedPos * 2;
        return true;
    }
    if (result && p == playerTree->getPlayerAt(selectedLevel - 1, selectedPos * 2 + 1)){
        selectedLevel = selectedLevel - 1;
        selectedPos = selectedPos * 2 + 1;
        return true;
    }
    return false;
}

//Shuffle the order of the players
void SingleEliminationManager::randomizePlayers(Player* p[], int n){
    for (int i = 0; i < n; i++){
        double random = rand()/static_cast<double>(RAND_MAX-1);
        int r = i + static_cast<int>(random * (n - i));
        Player* temp = p[i];
        p[i] = p[r];
        p[r] = temp;
    }
}

