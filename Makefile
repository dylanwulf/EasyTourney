WX_BUILD = /home/dylan/libs/wxWidgets-3.0.2/buildgtk2
WX_CONFIG = $(WX_BUILD)/wx-config
BD = build
ID = include
SRC = src
INC = `$(WX_CONFIG) --cppflags` -I./$(ID)
LIBS = `$(WX_CONFIG) --static --libs`
OBJS = $(BD)/TourneyApp.o $(BD)/TourneyFrame.o $(BD)/CreationFrame.o $(BD)/Player.o $(BD)/BracketTree.o $(BD)/SingleEliminationManager.o $(BD)/BracketManager.o

$(BD)/EasyTourney: $(OBJS)
	g++ $^ -o $@ $(LIBS)

$(BD)/TourneyApp.o: $(SRC)/TourneyApp.cpp $(ID)/TourneyApp.h $(ID)/TourneyFrame.h
	g++ $(INC) -c $< -o $@

$(BD)/TourneyFrame.o: $(SRC)/TourneyFrame.cpp $(ID)/TourneyFrame.h
	g++ $(INC) -c $< -o $@

$(BD)/CreationFrame.o: $(SRC)/CreationFrame.cpp $(ID)/CreationFrame.h
	g++ $(INC) -c $< -o $@

$(BD)/Player.o: $(SRC)/Player.cpp $(ID)/Player.h
	g++ $(INC) -c $< -o $@

$(BD)/BracketTree.o: $(SRC)/BracketTree.cpp $(ID)/BracketTree.h
	g++ $(INC) -c $< -o $@

$(BD)/SingleEliminationManager.o: $(SRC)/SingleEliminationManager.cpp $(ID)/SingleEliminationManager.h $(ID)/BracketManager.h
	g++ $(INC) -c $< -o $@

$(BD)/BracketManager.o: $(SRC)/BracketManager.cpp $(ID)/BracketManager.h
	g++ $(INC) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(BD)/*

run: $(BD)/EasyTourney
	$<
