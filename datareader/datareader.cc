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
#include "../datastructure/kmerlist.h"
using namespace std;
pthread_mutex_t mtA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtQ = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtL = PTHREAD_MUTEX_INITIALIZER;
std::bitset<HASH_SIZE> hash_table;

void print_hash(){
  cout<<hash_table.count()<<"\n";
  cout<<hash_table.size() - hash_table.count()<<"\n";
}

void* FastaReaderWrapper(void* th_p)
{
  pthread_mutex_lock(&mtA);
  thread_para* temp = static_cast<thread_para*>(th_p);
  temp->dr -> FastaReader(sequenceA++);
}


void* FastqReaderWrapper(void* th_p)
{
  pthread_mutex_lock(&mtQ);
  thread_para* temp = static_cast<thread_para*>(th_p);
  temp->dr -> FastqReader(sequenceQ++,temp->number);
}

reader::reader(string fn, string fq1_fn, string fq2_fn,int kms)
  :ref(fn),kmer_size(kms),gts_cnt(0)
{
  fq[0] = fq1_fn;
  fq[1] = fq2_fn;
}

void reader::find_start_fasta()
{
  string cnt_str;
  int cnt_line = 0;

  ifstream is(ref.c_str(),ifstream::in );
    
  while(!is.eof()){
    is >> cnt_str;
    if( cnt_str.find(">") != string::npos )
       starta.push_back((unsigned long long)is.tellg()) ;
  }
  is.close();
}

void reader::find_start_fastq(int number)
{
  unsigned long long file_size;
  unsigned long long section_size;
  unsigned long long position;
  NUMTHREAD = 0;
  string t;
  ifstream is(fq[number].c_str(),ifstream::in );
  int lineCount = 0;
  while(getline(is, t))
   ++lineCount;
  is.clear();
   for (int i=1000; i < lineCount ; i++){
    if(lineCount % i == 0 && (lineCount/i)%4 == 0 ) {
       NUMTHREAD = i;
       readLine = lineCount/NUMTHREAD;
       break;
    }
  }
  is.seekg(0,ios::beg);
  cout << "number of lines : " << lineCount << endl;
  cout << " read Line : " << readLine << endl;
 
  while(!is.eof()){
  for (int  i = 0; i<readLine; i++){
     getline(is, t, '\n');
     if (is.eof()){
     is.clear();
   for (int j=0; j < startq.size(); j++){
  is.seekg(startq[j]);}
  is.close();
  return;
    
}}
  startq.push_back((unsigned long long)is.tellg());
}
}

void reader::FastqReader(int seq_num,int number)
{
  pthread_mutex_unlock(&mtQ);
  ifstream partial_r(fq[number].c_str(),ifstream::in);
  unsigned long long partial_start = startq[seq_num];
  partial_r.seekg(partial_start);
  string genome_seq;
  string genome_substr;
  string garbage;
  unsigned long long start = 0;
  int distin;
  kmernode* node;
  
  for (int j =0; j < readLine/4; j++){
    start = partial_r.tellg();
    start = start++;
    getline(partial_r,garbage);
    getline(partial_r,genome_seq);
    distin = 0;
     for(int i = 0; i < 101 - kmer_size + 1; i++){
       if (genome_seq.size() != 0){
         genome_substr = genome_seq.substr(i,kmer_size);
         if ( hash_table[hash_function::djb2_hash(genome_substr, kmer_size,5381)%(HASH_SIZE)] == 0 ){
           if(distin == 0){
	     pthread_mutex_lock(&mtL);
	     node = kmerlist::add_node(genome_seq);
             node->add_start_ptr(start);
	     pthread_mutex_unlock(&mtL);
             distin++;
	   } 
	   node->add_ptr(i);
         }
       }
    }
    getline(partial_r,garbage,'\n');
    getline(partial_r,garbage,'\n');
  }
}
void reader::FastaReader(int seq_num)
{
  stringstream ss;
  ss<<"output/"<<seq_num<<".txt";
  pthread_mutex_unlock(&mtA);
  
  cout <<seq_num<<" thread start !!\n";
  ifstream partial_r(ref.c_str(),ifstream::in);
  unsigned long long thread_start = starta[seq_num];
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
    hash_table[hash_function::djb2_hash(sub, kmer_size,5381)%(HASH_SIZE)] = 1;
  }
  partial_r.close();
}
