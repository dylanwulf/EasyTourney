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
//include double elimination manager when it's finished
#include <wx/wxprec.h>
#ifndef WX_PRECOM
#include <wx/wx.h>
#endif

#ifndef CreationFrame_h
#define CreationFrame_h

class CreationFrame: public wxFrame {
    public:
        CreationFrame(wxWindow* parent, const wxString& title, const wxSize& size);
        BracketManager* getBracketManager();
    private:
        wxScrolledWindow* scrolledArea;
        wxBoxSizer* vbox;
        wxTextCtrl* nameInput;
        wxTextCtrl* descriptionInput;
        wxButton* addPlayerButton;
        wxListBox* playersList;
        wxButton* editPlayerButton;
        wxButton* removePlayerButton;
        wxCheckBox* randomizeBox;
        wxRadioButton* singleRadio;
        wxRadioButton* doubleRadio;
        wxButton* finishButton;
        bool closeParentWithMe;
        wxButton* cancelButton;
        void OnAdd(wxCommandEvent&);
        void OnEdit(wxCommandEvent&);
        void OnRemove(wxCommandEvent&);
        void OnFinish(wxCommandEvent&);
        void OnClose(wxCloseEvent&);

};

enum {
    ID_addPlayerButton = wxID_HIGHEST + 1, 
    ID_editPlayerButton, 
    ID_removePlayerButton, 
    ID_finishButton, 
    ID_cancelButton
};

#endif
