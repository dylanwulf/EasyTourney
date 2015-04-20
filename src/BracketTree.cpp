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

#include <BracketTree.h>
#include <cmath>
#include <stdlib.h>

BracketTree::BracketTree(Player* playersList[], int nPlayers){
    numPlayers = nPlayers;
    int log2Smashers = (int) ceil(log2(numPlayers));
    playerTreeSize = (int) pow(2, log2Smashers + 1);
    playerTree = (Player**) malloc(sizeof(Player*) * playerTreeSize);
    numLevels = (int) round(log2(playerTreeSize));
    int numFirstRoundSpaces = playerTreeSize / 2;
    int numSecondRounders = playerTreeSize / 4;
    int numLeftovers = numPlayers - numSecondRounders;
    int numFirstRounders = numLeftovers * 2;
    for (int i = 0; i < numFirstRounders; i++){
        playerTree[i] = playersList[i];
    }

    for (int i = 0; i < numSecondRounders - numLeftovers; i++){
        playerTree[numFirstRoundSpaces + numLeftovers + i] = playersList[numFirstRounders + i];
    }

}

BracketTree::~BracketTree(){
    free(playerTree);
}

Player* BracketTree::getPlayerAt(const unsigned int level, const unsigned int pos){
    unsigned int treePos = playerTreeSize - playerTreeSize / pow(2, level) + pos;
    return playerTree[treePos];
}

unsigned int BracketTree::getNumLevels(){
    return numLevels;
}

unsigned int BracketTree::getNumPlayers(){
    return numPlayers;
}

