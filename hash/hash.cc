#include<iostream>
#include<string>
#include<string.h>
#include "hash.h"
#include "../datastructure/kmerlist.h"
using namespace std;
std::bitset<BLOOM_SIZE> bloom_hash_table;

unsigned long hash_function:: djb2_hash(string kmer, int kmer_size, int hash)
{
  //unsigned long hash = 5381;
  for(int i = 0; i<kmer_size;i++){
    hash = ((hash<<5) + hash)+kmer[i];
  }  
  return hash;
}

vector<int> hash_function::prime_generator(int kmersize)
{
  int max = 10000;  
  vector<int> primes;
  char *sieve;
  sieve = new char[max/8+1];
  memset(sieve, 0xFF, (max/8+1) * sizeof(char));
  for(int x = 2; x <= max; x++)
      if(sieve[x/8] & (0x01 << (x % 8))){
          primes.push_back(x);
          for(unsigned long j = 2*x; j <= max; j += x)
            sieve[j/8] &= ~(0x01 << (j % 8));
  }
  delete[] sieve;
  return primes;
}

void hash_function::print_primes(vector<int> primes)
{
  int size = primes.size();
  for(int i = 0; i<size;i++){
    cout<<primes[i]<<endl;
  }
}

void hash_function:: bloom_filter_hash(int kmer_size,vector<int> primes, kmernode* start)
{
  int number;
  kmernode* before = NULL;
  kmernode* node = start;
  kmernode* temp = NULL;
  unsigned long long hash_value ;
  while(node != NULL){
   number = 0;
   for(int i = 0; i<kmer_size;i++){
     hash_value = djb2_hash(node->get_read(),100,primes[i]) % BLOOM_SIZE ;
     if(bloom_hash_table[hash_value] == 1)
       number++;
     else
       bloom_hash_table[hash_value] = 1;
   }
   temp = node;
   node = node->get_next();
   if(number == kmer_size)
     kmerlist::delete_node(before,temp);
   else
     before = temp;  
  }
}

unsigned int hash_function::SDBMHash(string str)
{
	unsigned int hash = 0;
	unsigned int i = 0;
	unsigned int len = str.length();

	for (i = 0; i < len; i++)
	{
		hash = (str[i]) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

