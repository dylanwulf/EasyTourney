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
        
        //Event handlers
        void OnCreationFinish(wxCommandEvent&);
        void OnCreationCancel(wxCommandEvent&);
        void OnBracketPanelPaint(wxPaintEvent&);
        void OnPlayerWon(wxCommandEvent&);
        void OnZoomIn(wxCommandEvent&);
        void OnZoomOut(wxCommandEvent&);
        void OnBracketClick(wxMouseEvent&);
        void OnBracketDoubleClick(wxMouseEvent&);
        void OnBracketMouseUp(wxMouseEvent&);
        void OnBracketMouseMove(wxMouseEvent&);
};

enum {
    ID_ctrlPanel = ID_cancelButton + 1, 
    ID_bracketPanel,
    ID_playerWonButton,
    ID_zoomInButton,
    ID_zoomOutButton
};

#endif
