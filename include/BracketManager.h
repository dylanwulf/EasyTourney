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
#include <wx/dc.h>

#ifndef BracketManager_h
#define BracketManager_h
class BracketManager{
    public:
        BracketManager();
        virtual ~BracketManager() = 0;
        
        //Draws the shape of the bracket and names of players on the screen
        virtual void drawBracket(wxDC& dc, int canvasWidth, int canvasHeight) = 0;
        
        //Selects a player at the specified location and returns a pointer to it
        virtual Player* selectPlayer(int x, int y, int canvasWidth, int canvasHeight) = 0;
        
        //Advances a player up the bracket
        virtual bool selectedPlayerWon() = 0;

        virtual bool unAdvanceSelectedPlayer() = 0;
};
#endif
