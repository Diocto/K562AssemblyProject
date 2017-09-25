.SUFFIXES : .cc.o

RM = rm -rf
CXX = g++
CPPFLAGS = -std=c++11
VPATH = datareader hash datastructure datapr
SRCS = assemble.cc datareader.cc hash.cc kmerlist.cc datapr.cc
SRCS2 = make_fa.cc
SRCS3 = extract_bp.cc
OBJS = $(SRCS:.cc=.o)
OBJS2 = $(SRCS2:.cc=.o)
OBJS3 = $(SRCS3:.cc=.o)
LDFLAGS = -lpthread
TARGET1 = assemble
TARGET2 = make_fa 
TARGET3 = extract_bp

all : $(TARGET1) $(TARGET2)$(TARGET3)

$(TARGET1): $(OBJS) 
	$(CXX) $(CPPFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(TARGET2): $(OBJS2) 
	$(CXX) $(CPPFLAGS) -o $@ $(OBJS2) $(LDFLAGS) 

$(TARGET3): $(OBJS3) 
	$(CXX) $(CPPFLAGS) -o $@ $(OBJS3) $(LDFLAGS) 

.cc.o:
	$(CXX) $(CPPFLAGS) -c $< $(LDFLAGS)

assemble.o : assemble.cc
datareader.o: datareader.cc datareader.h
hash.o: hash.cc hash.h
kmerlist.o: kmerlist.cc kmerlist.h
datapr.o: datapr.cc datapr.h

make_fa.o : make_fa.cc

extract_bp.o : extract_bp.cc

clean:
	$(RM) $(TARGET1) $(TARGET2) $(TARGET3) $(OBJS) $(OBJS2) $(OBJS3)

