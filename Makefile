WX_BUILD = /home/dylan/libs/wxWidgets/wxWidgets-3.0.2/build-gtk2
WX_CONFIG = $(WX_BUILD)/wx-config
BD = build
ID = include
SRC = src
CPP = g++
INC = `$(WX_CONFIG) --cppflags` -I./$(ID)
LIBS = `$(WX_CONFIG) --static --libs`
OBJS = $(BD)/TourneyApp.o $(BD)/TourneyFrame.o $(BD)/CreationFrame.o $(BD)/Player.o $(BD)/BracketTree.o $(BD)/SingleEliminationManager.o $(BD)/BracketManager.o

$(BD)/EasyTourney: $(OBJS)
	$(CPP) $^ -o $@ $(LIBS)

debug: $(OBJS)
	$(CPP) -g -O0 $^ -o $(BD)/EasyTourney $(LIBS)

$(BD)/TourneyApp.o: $(SRC)/TourneyApp.cpp $(ID)/TourneyApp.h $(ID)/TourneyFrame.h 
	$(CPP) $(INC) -c $< -o $@

$(BD)/TourneyFrame.o: $(SRC)/TourneyFrame.cpp $(ID)/TourneyFrame.h $(ID)/BracketManager.h $(ID)/CreationFrame.h $(ID)/Player.h
	$(CPP) $(INC) -c $< -o $@

$(BD)/CreationFrame.o: $(SRC)/CreationFrame.cpp $(ID)/CreationFrame.h $(ID)/BracketManager.h $(ID)/SingleEliminationManager.h $(ID)/DoubleEliminationManager.h
	$(CPP) $(INC) -c $< -o $@

$(BD)/Player.o: $(SRC)/Player.cpp $(ID)/Player.h
	$(CPP) $(INC) -c $< -o $@

$(BD)/BracketTree.o: $(SRC)/BracketTree.cpp $(ID)/BracketTree.h $(ID)/Player.h
	$(CPP) $(INC) -c $< -o $@

$(BD)/SingleEliminationManager.o: $(SRC)/SingleEliminationManager.cpp $(ID)/SingleEliminationManager.h $(ID)/BracketManager.h
	$(CPP) $(INC) -c $< -o $@

$(BD)/BracketManager.o: $(SRC)/BracketManager.cpp $(ID)/BracketManager.h
	$(CPP) $(INC) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(BD)/*

run: $(BD)/EasyTourney
	$<
