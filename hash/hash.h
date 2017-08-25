#ifndef HASH_H
#define HASH_H
#include<iostream>
#include<string>
#include<bitset>

#define HASH_SIZE 1024*1024*1024
using namespace std;

extern std::bitset<HASH_SIZE> hash_table;

class hash_function
{
  public:
    static unsigned long djb2_hash(string kmer,int kmer_size);
    static unsigned long bloom_filter_hash(string kmer,int kmer_size, int seed);
};

#endif
