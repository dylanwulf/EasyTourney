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

#include <CreationFrame.h>
#include <BracketManager.h>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#ifndef TourneyFrame_h
#define TourneyFrame_h

class TourneyFrame: public wxFrame {
    public:
        
        //Constructor
        TourneyFrame(const wxString& title, const wxSize& size);
        
        //Destructor
        ~TourneyFrame();
    private:
        CreationFrame* creation;
        wxBoxSizer* hbox;
        wxScrolledWindow* ctrlPanel;
        wxTextCtrl* nameBox;
        wxTextCtrl* descBox;
        wxScrolledCanvas* bracketPanel;
        int bracketCanvasWidth;
        int bracketCanvasHeight;
        int mousePrevX;
        int mousePrevY;
        int scrollRateX;
        int scrollRateY;
        wxSizerItem* bracketSpacer;
        BracketManager* manager;

        //selects the player at the specified coordinates
        void selectPlayer(int mouseX, int mouseY);
        
        //Event handlers

        //What to do when creation frame's finish button is pressed
        void OnCreationFinish(wxCommandEvent&);

        //What to do when creation frame's cancel button is pressed
        void OnCreationCancel(wxCommandEvent&);

        //What to do for bracket panel's paint events
        void OnBracketPanelPaint(wxPaintEvent&);

        //When the player won button is pressed
        void OnPlayerWon(wxCommandEvent&);

        //When the un-advance button is pressed
        void OnUnAdvance(wxCommandEvent&);

        //When the zoom in button is pressed
        void OnZoomIn(wxCommandEvent&);

        //When the zoom out button is pressed
        void OnZoomOut(wxCommandEvent&);

        //When bracket is clicked, select player at that location and start drag scrolling
        void OnBracketClick(wxMouseEvent&);

        //When bracket is right clicked, attempt to unadvance that player
        void OnBracketRightClick(wxMouseEvent&);

        //When bracket is double clicked, attempt to advance that player
        void OnBracketDoubleClick(wxMouseEvent&);

        //When left mouse button is lifted, stop drag scrolling
        void OnBracketMouseUp(wxMouseEvent&);

        //When mouse moves, if left mouse button is down, scroll accordingly
        void OnBracketMouseMove(wxMouseEvent&);

        //When the tips option in the help menu is selected
        void OnTips(wxCommandEvent&);
};

enum {
    ID_ctrlPanel = ID_cancelButton + 1, 
    ID_bracketPanel,
    ID_tipsMenuOption,
    ID_playerWonButton,
    ID_unAdvancePlayerButton,
    ID_zoomInButton,
    ID_zoomOutButton
};

#endif
