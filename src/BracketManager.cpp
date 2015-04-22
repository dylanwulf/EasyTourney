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

BracketManager::BracketManager(){}

BracketManager::~BracketManager(){

}

//The spacer is necessary to zoom and draw correctly.
void BracketManager::setSpacer(wxSizerItem* canvasSpacer){
    spacer = canvasSpacer;
    canvasWidth = spacer->GetSpacer().GetWidth();
    canvasHeight = spacer->GetSpacer().GetHeight();
}

//Increase size of canvas where bracket is drawn by zoomIncrease
void BracketManager::zoomIn(){
    canvasWidth += zoomIncrease;
    canvasHeight += zoomIncrease;
    spacer->AssignSpacer(canvasWidth, canvasHeight);
}

//Decrease size of canvas by zoomIncrease
void BracketManager::zoomOut(){
    canvasWidth -= zoomIncrease;
    canvasHeight -= zoomIncrease;
    spacer->AssignSpacer(canvasWidth, canvasHeight);
}
