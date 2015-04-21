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
        SingleEliminationManager(Player* playerList[], unsigned int numPlayers, bool randomize);
        virtual ~SingleEliminationManager();
        void drawBracket(wxDC& dc);
        Player* processClick(int x, int y);
        void playerWon(Player* p);
        void randomizePlayers(Player*[], int);
    private:
        BracketTree* playerTree;
};
#endif
