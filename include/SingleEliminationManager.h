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

#include <BracketManager.h>
#include <BracketTree.h>

#ifndef SingleEliminationManager_h
#define SingleEliminationManager_h
class SingleEliminationManager: public BracketManager{
    public:
    
        //Constructor takes arguments:
        //playerList: list of all players entered
        //numPlayers: how many players entered
        //randomize: whether to shuffle the array
        SingleEliminationManager(Player* playerList[], unsigned int numPlayers, bool randomize);
        
        //Destructor
        ~SingleEliminationManager();
        
        //Draw bracket and names on screen
        void drawBracket(wxDC& dc);
        
        //Get the player located here, if any
        Player* processClick(int x, int y);
        
        //Advance player up the bracket
        void playerWon(Player* p);
        
        //Shuffle the order of the players
        void randomizePlayers(Player*[], int);
        
    private:
        BracketTree* playerTree;
};
#endif
