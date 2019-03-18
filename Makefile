# canonical makefile for C++
# author: MKHSEG001
# March 2019

CXX 	:= g++
SRCDIR	:= src
LINKER 	:= g++
INCDIRS := -I.
CXXFLAGS:= -std=c++11 -Wall -w
SRCFILES:= $(wildcard *.cpp) 
OBJFILES:= $(patsubst %.cpp,%.o,$(SRCFILES))
DEPFILES:= $(patsubst %.cpp,%.d,$(SRCFILES))

PRODUCT := volimage # change name accordingly for each exe

$(PRODUCT): $(OBJFILES)
	$(LINKER) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

%.d: %.cpp
	$(CXX) $(INCDIRS) -MM $< > $@

-include $(DEPFILES)

clean:
	@rm -f *.o *.d $(PRODUCT) 
