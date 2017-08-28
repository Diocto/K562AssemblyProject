.SUFFIXES : .cc.o

RM = rm -rf
CXX = g++
CPPFLAGS = -std=c++11
VPATH = datareader hash datastructure datapr
SRCS = assemble.cc datareader.cc hash.cc kmerlist.cc datapr.cc
OBJS = $(SRCS:.cc=.o)
LDFLAGS = -lpthread
TARGET = assemble

$(TARGET): $(OBJS) 
	$(CXX) $(CPPFLAGS) -o $@ $(OBJS) $(LDFLAGS)

.cc.o:
	$(CXX) $(CPPFLAGS) -c $< $(LDFLAGS)

assemble.o : assemble.cc
datareader.o: datareader.cc datareader.h
hash.o: hash.cc hash.h
kmerlist.o: kmerlist.cc kmerlist.h
datapr.o: datapr.cc datapr.h

clean:
	$(RM) $(TARGET) $(OBJS) 

