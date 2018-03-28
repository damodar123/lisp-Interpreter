CXX = g++

CXXFLAGS = -g -Wall -std=c++0x

COMPILE = $(CXX) $(CXXFLAGS) -c

EXE = lispintrepreter

OBJS = front-end.o EvalClass.o S_Exprsn.o 

$(EXE) : $(OBJS)
	$(CXX) $^ -o $@

clean : 
	rm *.o lispintrepreter

%.o : %.cc
	$(COMPILE) -o $@ $<

front-end.o : EvalClass.h

EvalClass.o : EvalClass.h

S_Exprsn.o : S_Exprsn.h
