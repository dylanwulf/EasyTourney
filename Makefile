BD = build
ID = include
SRC = src
INC = `wx-config --cppflags` -I./$(ID)
LIBS = `wx-config --static --libs`

$(BD)/EasyTourney: $(BD)/TourneyApp.o $(BD)/TourneyFrame.o $(BD)/CreationFrame.o $(BD)/Player.o
	g++ $^ -o $@ $(LIBS)

$(BD)/TourneyApp.o: $(SRC)/TourneyApp.cpp $(ID)/TourneyApp.h $(ID)/TourneyFrame.h
	g++ $(INC) -c $< -o $@

$(BD)/TourneyFrame.o: $(SRC)/TourneyFrame.cpp $(ID)/TourneyFrame.h
	g++ $(INC) -c $< -o $@

$(BD)/CreationFrame.o: $(SRC)/CreationFrame.cpp $(ID)/CreationFrame.h
	g++ $(INC) -c $< -o $@

$(BD)/Player.o: $(SRC)/Player.cpp $(ID)/Player.h
	g++ $(INC) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(BD)/*

run: $(BD)/EasyTourney
	$<
