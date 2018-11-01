MKDEP=$(CXX) -MM
SRCS=main.cpp Game.cpp Map.cpp Physic.cpp Sapin.cpp Animation.cpp Basic_santa.cpp
HDRS=Game.h Map.h Physic.h Sapin.h Animation.h Basic_santa.h Enemy.h PhysicObjet.h
OUTS=main.o Game.o Map.o Physic.o Sapin.o Animation.o Basic_santa.o
CFLAGS=-g

sapin: $(OUTS)
	$(CXX) $(OUTS) -lSDL -lSDL_image $(CFLAGS) -o sapin 

depend: .depend
.depend: $(SRCS) $(HDRS)
	$(MKDEP) $(CFLAGS) $(SRCS) > .depend
-include .depend
