CXX = g++
CXXFLAGS = -Wall -lX11

SRCS = bishop.cc board.cc chessmen.cc computer.cc controller.cc graphicdisplay.cc human.cc king.cc knight.cc main.cc pawn.cc player.cc queen.cc rook.cc setboard.cc setloadboard.cc setupboard.cc textdisplay.cc view.cc window.cc
OBJS = ${SRCS:.cc=.o}
EXEC = pp9k
${EXEC}: $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(CXXFLAGS)
clean:
	rm *.o $(EXEC)
