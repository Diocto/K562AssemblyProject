#ifndef HASH_H
#define HASH_H
#include<iostream>
#include<string>
#include<bitset>
#include<vector>
#include "../datastructure/kmerlist.h"
#define HASH_SIZE 1024*1024*1024
#define BLOOM_SIZE 1024*1024
#define S_HASH_SIZE 1024
using namespace std;

extern std::bitset<HASH_SIZE> hash_table;
extern std::bitset<BLOOM_SIZE> bloom_hash_table;

class hash_function
{
  public:
    static unsigned long djb2_hash(string kmer,int kmer_size,int hash);
    static void bloom_filter_hash(int kmer_size,vector<int> primes, kmernode* start);
    static vector<int> prime_generator(int kmersize);
    static void print_primes(vector<int> primes);
    static unsigned int SDBMHash(string str);
};

#endif
