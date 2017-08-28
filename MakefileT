all: assemble 

assemble: assemble.o datareader.o hash.o kmerlist.o datapr.o
	g++ -std=c++11 -o assemble assemble.o datareader.o hash.o kmerlist.o datapr.o -lpthread

assemble.o: assemble.cc
	g++ -std=c++11 -c assemble.cc -lpthread

datareader.o:
	g++ -std=c++11 -c datareader/datareader.cc -lpthread

hash.o:
	g++ -std=c++11 -c hash/hash.cc -lpthread

kmerlist.o:
	g++ -std=c++11 -c datastructure/kmerlist.cc -lpthread

datapr.o:
	g++ -std=c++11 -c datapr/datapr.cc -lpthread

clean:
	rm -rf *.o

cleantemp:
	rm -rf output/*.txt
