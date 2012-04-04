
GLLIBS = -lGL -lGLU -lglut

.SUFFIXES: .c .cpp .h .cpp

all: index.cpp roomModel.h roomModel.cpp robot.h robot.cpp hand.h hand.cpp head.h head.cpp wheel.h wheel.cpp
	g++ index.cpp roomModel.cpp robot.cpp hand.cpp head.cpp wheel.cpp -o smalle $(GLLIBS) #-lGLEW

#smalle: smalle.o robot.o head.o hand.o wheel.o
#	g++ -o smalle smalle.o robot.o head.o hand.o wheel.o
	
#smalle.o: index.cpp robot.h robot.cpp 
#	g++ -c index.cpp $@ $(GLLIBS) 
	
#robot.o: robot.cpp robot.h wheel.h wheel.cpp head.h head.cpp  hand.h hand.cpp  
#	g++ -c robot.cpp $@ $(GLLIBS) 

#hand.o: hand.cpp hand.h
#	g++ -c hand.cpp $@ $(GLLIBS) 

#head.o: head.cpp head.h 
#	g++ -c head.cpp $@ $(GLLIBS) 

#wheel.o: wheel.cpp wheel.h
#	g++ -c wheel.cpp $@ $(GLLIBS) 


clean:
	rm -f smalle
	rm -f *.o
	rm -f *~
	
	
#smalle: head.h head.cpp hand.h hand.cpp wheel.h wheel.cpp robot.h robot.cpp index.cpp
#	g++ -Wall -g index.cpp -o $@ $(GLLIBS)
	
