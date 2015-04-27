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
#include <Player.h>

CreationFrame::CreationFrame(wxWindow* parent, const wxString& title, const wxSize& size): wxFrame(parent, wxID_ANY, title, wxDefaultPosition, size) {

    //Create main area as a scrolled window and give it a sizer
    scrolledArea = new wxScrolledWindow(this);
    vbox = new wxBoxSizer(wxVERTICAL);
    
    //Player name input
    wxStaticText* nameLabel = new wxStaticText(scrolledArea, wxID_ANY, "Player Name: ");
    vbox->Add(nameLabel, 0, wxLEFT | wxTOP | wxALIGN_LEFT, 10);
    nameInput = new wxTextCtrl(scrolledArea, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    vbox->Add(nameInput, 0, wxALL | wxEXPAND | wxALIGN_RIGHT, 10);

    //Player info box
    wxStaticText* descriptionLabel = new wxStaticText(scrolledArea, wxID_ANY, "Player Info: ");
    vbox->Add(descriptionLabel, 0, wxLEFT | wxTOP | wxALIGN_LEFT, 10);
    descriptionInput = new wxTextCtrl(scrolledArea, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(-1, 75), wxTE_MULTILINE | wxTE_PROCESS_ENTER);
    vbox->Add(descriptionInput, 0, wxALL | wxEXPAND, 10);
    
    //Add player button
    addPlayerButton = new wxButton(scrolledArea, ID_addPlayerButton, "Add");
    vbox->Add(addPlayerButton, 0, wxALL | wxALIGN_RIGHT, 10);

    //list box which holds names of all players entered so far
    wxBoxSizer* listSizer = new wxBoxSizer(wxHORIZONTAL);
    listSizer->AddStretchSpacer(1);
    playersList = new wxListBox(scrolledArea, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_ALWAYS_SB);
    playersList->SetMinSize(wxSize(-1, 200));
    listSizer->Add(playersList, 3, wxALL | wxALIGN_CENTER | wxEXPAND, 10);
    listSizer->AddStretchSpacer(1);
    vbox->Add(listSizer, 0, wxALIGN_CENTER | wxEXPAND, 0);

    //Edit and remove buttons below list box
    wxBoxSizer* buttonBox = new wxBoxSizer(wxHORIZONTAL);
    editPlayerButton = new wxButton(scrolledArea, ID_editPlayerButton, "Edit");
    buttonBox->Add(editPlayerButton, 0, wxALL | wxALIGN_CENTER, 10);
    removePlayerButton = new wxButton(scrolledArea, ID_removePlayerButton, "Remove");
    buttonBox->Add(removePlayerButton, 0, wxALL | wxALIGN_CENTER, 10);
    vbox->Add(buttonBox, 0, wxALIGN_CENTER, 0);

    //Randomize player order checkbox
    randomizeBox = new wxCheckBox(scrolledArea, wxID_ANY, "Randomize player order");
    randomizeBox->SetValue(true);
    vbox->Add(randomizeBox, 0, wxALL, 10);

    //Tournament type radio buttons
    wxStaticText* typeLabel = new wxStaticText(scrolledArea, wxID_ANY, "Tournament type: ");
    vbox->Add(typeLabel, 0, wxALIGN_LEFT | wxLEFT, 10);
    singleRadio = new wxRadioButton(scrolledArea, wxID_ANY, "Single Elimination");
    vbox->Add(singleRadio, 0, wxALIGN_LEFT | wxLEFT, 15);
    doubleRadio = new wxRadioButton(scrolledArea, wxID_ANY, "Double Elimination");
    vbox->Add(doubleRadio, 0, wxALIGN_LEFT | wxLEFT | wxBOTTOM, 15);

    //Finish and cancel buttons
    wxBoxSizer* bottomButtons = new wxBoxSizer(wxHORIZONTAL);
    bottomButtons->AddStretchSpacer(1);
    finishButton = new wxButton(scrolledArea, ID_finishButton, "Finish");
    bottomButtons->Add(finishButton, 0, wxALIGN_RIGHT | wxALIGN_BOTTOM | wxALL, 5);
    cancelButton = new wxButton(scrolledArea, ID_cancelButton, "Cancel");
    bottomButtons->Add(cancelButton, 0, wxALIGN_RIGHT | wxALIGN_BOTTOM | wxALL, 5);
    vbox->Add(bottomButtons, 1, wxEXPAND | wxALIGN_RIGHT);

    //Finish setting up sizers
    scrolledArea->SetSizer(vbox);
    scrolledArea->SetScrollRate(5, 10);
    scrolledArea->SetBackgroundColour(*wxWHITE);
    this->SetSizeHints(wxSize(300, 400));
    vbox->Fit(this);
    
    //Bind events to event handlers
    Bind(wxEVT_BUTTON, &CreationFrame::OnAdd, this, ID_addPlayerButton);
    Bind(wxEVT_TEXT_ENTER, &CreationFrame::OnAdd, this, wxID_ANY);
    Bind(wxEVT_BUTTON, &CreationFrame::OnEdit, this, ID_editPlayerButton);
    Bind(wxEVT_BUTTON, &CreationFrame::OnRemove, this, ID_removePlayerButton);
    Bind(wxEVT_BUTTON, &CreationFrame::OnFinish, this, ID_finishButton);
    Bind(wxEVT_CLOSE_WINDOW, &CreationFrame::OnClose, this, wxID_ANY);
    closeParentWithMe = true;
}

CreationFrame::~CreationFrame(){
    DestroyChildren();
}

//Create and retern a BracketManager object pointer, which will
//hold all the logic behind the bracket behavior
BracketManager* CreationFrame::getBracketManager(){
    unsigned int numPlayers = playersList->GetCount();
    Player* playersArray[numPlayers];
    for (int i = 0; i < numPlayers; i++){
        playersArray[i] = (Player*) playersList->GetClientData(i);
    }
    BracketManager* manager = new SingleEliminationManager(playersArray, numPlayers, randomizeBox->GetValue());
    return manager;
}

void CreationFrame::OnAdd(wxCommandEvent& event){
    if (nameInput->GetValue() != ""){
        Player* player = new Player(nameInput->GetValue().ToStdString(), descriptionInput->GetValue().ToStdString());
        playersList->Append(player->getName(), player);
        nameInput->Clear();
        descriptionInput->Clear();
        nameInput->SetFocus();
        vbox->Layout();
    } 
    else{
        wxMessageDialog* addError = new wxMessageDialog(this, "Please type a name.", "Alert", wxOK);
        addError->ShowModal();
    }
}

void CreationFrame::OnEdit(wxCommandEvent& event){
    if (playersList->GetSelection() != wxNOT_FOUND){
        Player* player = (Player*) playersList->GetClientData(playersList->GetSelection());
        nameInput->SetValue(player->getName());
        descriptionInput->SetValue(player->getDescription());
        playersList->Delete(playersList->GetSelection());
        delete player;
        vbox->Layout();
    }
    nameInput->SetFocus();
}

void CreationFrame::OnRemove(wxCommandEvent& event){
    if (playersList->GetSelection() != wxNOT_FOUND){
        Player* p = (Player*) playersList->GetClientData(playersList->GetSelection());
        playersList->Delete(playersList->GetSelection());
        delete p;
        vbox->Layout();
    }
    nameInput->SetFocus();
}

//If less than 2 people have been entered, show popup and do not close.
//If >= 2 people are entered, pass event to parent
void CreationFrame::OnFinish(wxCommandEvent& event){
    if (playersList->GetCount() < 2){
        wxMessageDialog* alert = new wxMessageDialog(this, "You should have at least 2 people to play a tournament.", "Alert", wxOK);
        alert->ShowModal();
    }
    else{
        closeParentWithMe = false;
        event.Skip();
    }
}

void CreationFrame::OnClose(wxCloseEvent& event){
    event.Skip(true);
    if (closeParentWithMe){
        this->GetParent()->Close(false);
    }
}
