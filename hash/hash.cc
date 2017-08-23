#include<iostream>
#include<string>
#include "hash.h"
using namespace std;

unsigned long hash_function:: djb2_hash(string kmer, int kmer_size)
{
  unsigned long hash = 5381;
  for(int i = 0; i<kmer_size;i++){
    hash = ((hash<<5) + hash)+kmer[i];
  }  
  return hash;
}

unsigned long hash_function:: bloom_filter_hash(string kmer, int kmer_size, int seed)
{

}
