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

#include <Player.h>

#ifndef BracketTree_h
#define BracketTree_h
class BracketTree{
    public:
        //Constructor which takes two arguments:
        //playersList: array of Player pointers
        //numPlayers: how many Players* in the list
        BracketTree(Player* playersList[], int numPlayers);
        
        //Destructor
        ~BracketTree();
        
        //Returns a pointer to the Player object at the specified position
        //in the bracket
        Player* getPlayerAt(unsigned int level, unsigned int pos);
        
        //Checks if the player at the specified location can advance
        bool canPlayerAdvance(unsigned int level, unsigned int pos);

        //Advance the player at the specified location up the bracket
        //Returns true if successful, false otherwise
        bool playerWon(unsigned int level, unsigned int pos);
        
        unsigned int getNumLevels();
        
        unsigned int getNumPlayers();
        
    private:
        Player** playerTree;
        Player** playersList;
        unsigned int playerTreeSize;
        unsigned int nextWinnerPos;
        unsigned int numLevels;
        unsigned int numPlayers;
};
#endif
