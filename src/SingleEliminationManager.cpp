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

SingleEliminationManager::SingleEliminationManager(Player* playerList[], unsigned int numPlayers, bool randomize){
    playerTree = new BracketTree(playerList, numPlayers);

}

void SingleEliminationManager::drawBracket(wxDC& dc, int width, int height){
    int numLevels = playerTree->getNumLevels();
    int numPlayers = pow(2, numLevels - 1);
    int currPlayers = numPlayers;
    int currLevel = 0;
    double levelWidth = (double) width / (log2(numPlayers) + 1);

    while (currPlayers >= 1){
        
        double branchHeight = (double) height / currPlayers;
        int x1 = levelWidth * currLevel;
        int x2 = levelWidth * (currLevel + 1);

        for (int i = 0; i < currPlayers; i++){
            
            int y1 = branchHeight * i + branchHeight / 2;
            int y2 = y1;

            dc.DrawLine(x1, y1, x2, y2); //Draw horizontal lines

            if (i % 2 == 0 && i < currPlayers - 1)
                dc.DrawLine(x2, y1, x2, y1 + branchHeight);
                //Draw vertical lines
        }
        currPlayers /= 2;
        currLevel++;
    }
}

SingleEliminationManager::~SingleEliminationManager(){
    delete playerTree;
}

void SingleEliminationManager::processClick(int x, int y){

}

void SingleEliminationManager::playerWon(Player* p){

}
