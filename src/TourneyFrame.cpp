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
    wxSizerItem* bracketSpacer = bracketSizer->Add(1000, 1000, 1);
    //bracketSpacer->AssignSpacer(wxSize(2000, 2000)); <-- how to change size of bracketPanel
    bracketPanel->SetSizer(bracketSizer);
    hbox->Add(bracketPanel, 3, wxEXPAND | wxLEFT, 0);
    this->SetSizer(hbox);

    Bind(wxEVT_BUTTON, &TourneyFrame::OnCreationFinish, this, ID_finishButton);
    Bind(wxEVT_BUTTON, &TourneyFrame::OnCreationCancel, this, ID_cancelButton);
    bracketPanel->Bind(wxEVT_PAINT, &TourneyFrame::OnBracketPanelPaint, this);
}

TourneyFrame::~TourneyFrame(){
    delete manager;
}

void TourneyFrame::OnCreationFinish(wxCommandEvent& event){
    manager = creation->getBracketManager();
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
    manager->drawBracket(dc, 1000, 1000);
}

