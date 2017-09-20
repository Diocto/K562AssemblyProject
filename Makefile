.SUFFIXES : .cc.o

RM = rm -rf
CXX = g++
CPPFLAGS = -std=c++11
VPATH = datareader hash datastructure datapr
SRCS = assemble.cc datareader.cc hash.cc kmerlist.cc datapr.cc
SRCS2 = make_fa.cc
OBJS = $(SRCS:.cc=.o)
OBJS2 = $(SRCS2:.cc=.o)
LDFLAGS = -lpthread
TARGET1 = assemble
TARGET2 = make_fa 

all : $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJS) 
	$(CXX) $(CPPFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(TARGET2): $(OBJS2) 
	$(CXX) $(CPPFLAGS) -o $@ $(OBJS2) $(LDFLAGS) 

.cc.o:
	$(CXX) $(CPPFLAGS) -c $< $(LDFLAGS)

assemble.o : assemble.cc
datareader.o: datareader.cc datareader.h
hash.o: hash.cc hash.h
kmerlist.o: kmerlist.cc kmerlist.h
datapr.o: datapr.cc datapr.h

make_fa.o : make_fa.cc

clean:
	$(RM) $(TARGET1) $(TARGET2) $(OBJS) $(OBJS2)

