#include "datareader.h"
#include<bitset>
#include<sstream>
#include<iostream>
#include<fstream>
#include<cstring>
#include<limits>
#include<string>
#include<pthread.h>
#include "../hash/hash.h"
using namespace std;
pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;
std::bitset<HASH_SIZE> hash_table;

void print_hash(){
  cout<<hash_table.count()<<"\n";
  cout<<hash_table.size() - hash_table.count()<<"\n";
}

void* FastReaderWrapper(void* readerObj)
{
  pthread_mutex_lock(&mt);
  reader* dr = static_cast<reader*>(readerObj);
  dr -> FastaReader(sequence++);
}


reader::reader(string fn, string fq1_fn, string fq2_fn,int kms)
  :ref(fn),fq1(fq1_fn),fq2(fq2_fn),kmer_size(kms),gts_cnt(0)
{
}

void reader::find_start_fasta()
{
  string cnt_str;
  int cnt_line = 0;

  ifstream is(ref.c_str(),ifstream::in );
    
  while(!is.eof()){
    is >> cnt_str;
    if( cnt_str.find(">") != string::npos )
       start.push_back((unsigned long long)is.tellg()) ;
  }
  is.close();
}

void reader::FastqReader()
{
}

void reader::FastaReader(int seq_num)
{
  stringstream ss;
  ss<<"output/"<<seq_num<<".txt";
  pthread_mutex_unlock(&mt);
  
  cout <<seq_num<<" thread start !!\n";
  ifstream partial_r(ref.c_str(),ifstream::in);
  //ofstream partial_w(ss.str().c_str(),ofstream::out);
  unsigned long long thread_start = start[seq_num];
  string contig;
  string line;
  string sub;
  partial_r.seekg(thread_start);

  while(true){
    partial_r>>line; 
    if( partial_r.eof() || line.front() == '>')
      break;
    contig.append(line);
  }
  unsigned long long max_ptr = contig.size() - kmer_size;  
  for(unsigned long long i = 0; i <= max_ptr ; i++){
    sub = contig.substr(i, kmer_size); 
    hash_table[hash_function::djb2_hash(sub, kmer_size)%(HASH_SIZE)] = 1;
  }
  partial_r.close();
  //partial_w.close();
}
