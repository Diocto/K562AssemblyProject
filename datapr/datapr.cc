#include "../datareader/datareader.h"
#include<bitset>
#include<vector>
#include<sstream>
#include<iostream>
#include<fstream>
#include<cstring>
#include<limits>
#include<string>
#include<pthread.h>
#include "datapr.h"
#include "../hash/hash.h"
#include "../datastructure/kmerlist.h"
#define kmer_size 31
using namespace std;
datapr::datapr()
{}
void datapr::kmerProcess()
{
 cout << "DONE 2" << endl;
 kmernode* temp = list_start;
 vector<string> temp_kmers;
 int number = 0;
 while(temp != NULL){
  temp_kmers = temp->getKmers();
  for (int i = 0; i<temp_kmers.size(); i++){
  hashed_list[hash_function::djb2_hash(temp_kmers[i],kmer_size)%(HASH_SIZE)].add(temp->getRead());
 temp = temp->next;
 }
 number++;
 if(number >= 10000){
   number = 0;
   cout << "million! Cong!" << endl;
 }

 cout << "DOEN 3" << endl;
} 
}
void datapr::process_Out()
{
 cout << "DONE 4" << endl;
 for ( int i =0; i<HASH_SIZE; i++){
   for ( int j=0; j<hashed_list[i].size();i++){
  cout << i << " LINE READ : " <<  hashed_list[i].get(j) << endl;
  }}
 cout << "DONE 5" << endl;
}

