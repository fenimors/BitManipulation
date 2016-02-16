CXX=g++
CXXFLAGS = -Wall -g -std=c++0x
OBJS = main.o Tools.o

tooltest:	$(OBJS)
		$(CXX) $(CXXFLAGS) $(OBJS) -o tooltest		
			
main.o:		Tools.h
Tools.o:	Tools.h
clean:
			rm -f main.o Tools.o tooltest
        
