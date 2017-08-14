#include<iostream>
#include<fstream>
#include<cassert>
#include<cstdlib>
#include<cstring>
#include"datareader/datareader.h"
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
  int start_size;

  reader* dr = new reader(ref_fn,fq1_fn,fq2_fn ,km);  
  dr -> find_start_fasta();
  start_size = dr -> get_start_size();
  
  pthread_t thrd[start_size];
  ///////// parameter setting////////////////////////
  
  ///////// file read proccess//////////////////////
   
  for(int i = 0; i<start_size; i++){
    pthread_create(&thrd[i], NULL, &FastReaderWrapper, dr);
  }

  for(int i = 0; i<start_size; i++){
    pthread_join(thrd[i], NULL );
  } 
  print_hash();
  return 0;
}
