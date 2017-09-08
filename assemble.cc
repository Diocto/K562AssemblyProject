#include<iostream>
#include"time.h"
#include<fstream>
#include<cassert>
#include<cstdlib>
#include<cstring>
#include"datareader/datareader.h"
#include"datastructure/kmerlist.h"
#include"datapr/datapr.h"
#include"hash/hash.h"
#include<pthread.h>
#include<unistd.h>
#include<time.h>
using namespace std;
int main(int argc, char* argv[])
{
  
  assert( argc == 5 && "please input 4 argments \n");
  //////// parameter setting////////////////////////
  string ref_fn(argv[1]);
  string fq1_fn(argv[2]);
  string fq2_fn(argv[3]);
  int km = atoi(argv[4]);
  int start_sizeA;
  int start_sizeQ;
  thread_para th_p;
  datapr* dataPr = new datapr();
  
  th_p.dr = new reader(ref_fn,fq1_fn,fq2_fn ,km);  
  th_p.dr -> find_start_fasta();
  th_p.dr -> find_start_fastq(0);
  start_sizeA = th_p.dr -> get_start_size();
  start_sizeQ = th_p.dr -> get_NumThread();  
  pthread_t thrdA[start_sizeA];
  pthread_t thrd1Q[start_sizeQ];
  pthread_t thrd2Q[start_sizeQ];
  ///////// parameter setting////////////////////////
   
  ///////// fasta read proccess//////////////////////
  for(int i = 0; i<start_sizeA; i++){
    pthread_create(&thrdA[i], NULL, &FastaReaderWrapper, &th_p);
  }

  for(int i = 0; i<start_sizeA; i++){
    pthread_join(thrdA[i], NULL );
  } 
  ///////// fasta read proccess//////////////////////
   
  ///////// fastq read proccess//////////////////////
  for(int i = 0; i<start_sizeQ; i++){
    pthread_create(&thrd1Q[i], NULL, &FastqReaderWrapper,&th_p);
  }
  th_p.number++;
  for(int i = 0; i<start_sizeQ; i++){
    pthread_create(&thrd2Q[i], NULL, &FastqReaderWrapper,&th_p);
  }

  for(int i = 0; i<start_sizeQ; i++){
    pthread_join(thrd1Q[i], NULL );
  } 
  for(int i = 0; i<start_sizeQ; i++){
    pthread_join(thrd2Q[i], NULL );
  } 

//bloom filter.//
  vector<int> primes = hash_function::prime_generator(km-30);
  hash_function::bloom_filter_hash(km-30, primes,list_start);
  kmerlist::print_list();

  dataPr->kmerProcess();
  dataPr->process_Out(); 

  return 0;
}
