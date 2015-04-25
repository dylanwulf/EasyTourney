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

#include <TourneyFrame.h>

//Constructor
TourneyFrame::TourneyFrame(const wxString& title, const wxSize& size): wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, size) {
    creation = new CreationFrame(this, "Create a New Tournament", wxSize(300, 600));
    creation->Show(true);
    this->SetBackgroundColour(*wxWHITE);
    hbox = new wxBoxSizer(wxHORIZONTAL);

    ctrlPanel = new wxScrolledWindow(this, ID_ctrlPanel, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    hbox->Add(ctrlPanel, 1, wxEXPAND | wxRIGHT, 0);
    ctrlPanel->SetScrollRate(5, 10);

    bracketPanel = new wxScrolledCanvas(this, ID_bracketPanel, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    bracketPanel->SetBackgroundColour(*wxWHITE);
    bracketPanel->SetScrollRate(10, 10);
    wxBoxSizer* bracketSizer = new wxBoxSizer(wxHORIZONTAL);
    bracketPanel->SetSizer(bracketSizer);
    hbox->Add(bracketPanel, 3, wxEXPAND | wxLEFT, 0);
    this->SetSizer(hbox);

    wxBoxSizer* ctrlSizer = new wxBoxSizer(wxVERTICAL);
    nameBox = new wxTextCtrl(ctrlPanel, wxID_ANY, "--Select Player--", wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_CENTRE);
    ctrlSizer->Add(nameBox, 0, wxEXPAND | wxALL, 10);

    descBox = new wxTextCtrl(ctrlPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1, 120), wxTE_MULTILINE | wxTE_READONLY);
    ctrlSizer->Add(descBox, 0, wxEXPAND | wxALL, 10);

    wxButton* zoomInButton = new wxButton(ctrlPanel, ID_zoomInButton, "Zoom In");
    ctrlSizer->Add(zoomInButton, 0);
    wxButton* zoomOutButton = new wxButton(ctrlPanel, ID_zoomOutButton, "Zoom Out");
    ctrlSizer->Add(zoomOutButton, 0);
    ctrlPanel->SetSizer(ctrlSizer);

    Bind(wxEVT_BUTTON, &TourneyFrame::OnZoomIn, this, ID_zoomInButton);
    Bind(wxEVT_BUTTON, &TourneyFrame::OnZoomOut, this, ID_zoomOutButton);
    Bind(wxEVT_BUTTON, &TourneyFrame::OnCreationFinish, this, ID_finishButton);
    Bind(wxEVT_BUTTON, &TourneyFrame::OnCreationCancel, this, ID_cancelButton);
    bracketPanel->Bind(wxEVT_LEFT_DOWN, &TourneyFrame::OnClick, this, wxID_ANY);
    bracketPanel->Bind(wxEVT_PAINT, &TourneyFrame::OnBracketPanelPaint, this);
}

//Destructor
TourneyFrame::~TourneyFrame(){
    if (this->IsShown())
        delete manager;
    DestroyChildren();
}

void TourneyFrame::OnCreationFinish(wxCommandEvent& event){
    manager = creation->getBracketManager();
    wxSizerItem* bracketSpacer = bracketPanel->GetSizer()->Add(800, 800, 1);
    manager->setSpacer(bracketSpacer);
    creation->Destroy();
    this->Show(true);
}

void TourneyFrame::OnCreationCancel(wxCommandEvent& event){
    creation->Close(true);
    this->Close(true);
}

void TourneyFrame::OnBracketPanelPaint(wxPaintEvent& event){
    wxPaintDC dc(bracketPanel);
    bracketPanel->DoPrepareDC(dc);
    manager->drawBracket(dc);
}

void TourneyFrame::OnClick(wxMouseEvent& event){
    event.Skip(); //Necessary so that the window still gains focus when clicked
    int x = 0;
    int y = 0;
    bracketPanel->CalcUnscrolledPosition(event.GetX(), event.GetY(), &x, &y);
    Player* p = manager->processClick(x, y);
    if (p == NULL){
        nameBox->SetValue("--Select Player--");
        descBox->SetValue(wxEmptyString);
    }
    else{
        nameBox->SetValue(p->getName());
        descBox->SetValue(p->getDescription());
    }
}

void TourneyFrame::OnZoomIn(wxCommandEvent& event){
    manager->zoomIn();
    
    //force window to update so it shows newly zoomed
    //bracket and adjusted scrollbars
    hbox->Layout();
    bracketPanel->Refresh();
}

void TourneyFrame::OnZoomOut(wxCommandEvent& event){
    manager->zoomOut();
    
    //force window to update so it shows newly zoomed
    //bracket and adjusted scrollbars
    hbox->Layout();
    bracketPanel->Refresh();
}
