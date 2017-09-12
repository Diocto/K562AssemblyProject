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
 kmernode* temp = list_start;
 vector<string> temp_kmers;
 int hash_num = 0;
 while(temp != NULL){
  temp_kmers = temp->getKmers();
  for (int i = 0; i<temp_kmers.size(); i++){
    hash_num =  hash_function::djb2_hash(temp_kmers[i],kmer_size,5841)%(READ_HASH_SIZE);
        if (hashed_list[hash_num] == NULL){
 	hashed_list[hash_num] = new readList;
        }
    hashed_list[hash_num] -> add(temp->getRead(),temp->getStart());
    if ( temp->next == NULL){
    cout << "DONEEEEE" << endl;
      return;}
    temp = temp->next;
 }

}
}
void datapr::process_Out()
{
 for ( int i =0; i<READ_HASH_SIZE; i++){
   if (hashed_list[i] != NULL) {
   for ( int j=0; j<hashed_list[i]->size();j++){
  cout << "HASHED SIZE : " << hashed_list[i]->size() << endl;
  cout << " I is : " << i << " J is : " << j <<endl;
  hashed_list[i]->get(j);
  }}}
}


void datapr::make_nodab_fq_wrapper(string pair1, string pair2)
{
  ifstream read_pair1(pair1.c_str(),ifstream::in);
  ifstream read_pair2(pair2.c_str(),ifstream::in);
  ofstream write_pair1("output/nodabread_1.fastq",ofstream::out);
  ofstream write_pair2("output/nodabread_2.fastq",ofstream::out);

  for(int i = 0; i<READ_HASH_SIZE;i++)
  {
    if(hashed_list[i] != NULL){
      hashed_list[i] -> make_nodab_fq(read_pair1,read_pair2,write_pair1,write_pair2);
    }
  }
} 
    


