#ifndef DATAREADER_H
#define DATAREADER_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

static int sequenceA = 0;
static int sequenceQ = 0;
void* FastaReaderWrapper(void* th_p);
void* FastqReaderWrapper(void* th_p);
void print_hash();

class reader{
  private:
    string ref;
    string fq[2];
    int kmer_size;
    int gts_cnt;
    vector<unsigned long long> starta;
    vector<unsigned long long> startq;
    int readLine;
    int NUMTHREAD;

  public:
    reader(string fn,string fq1_fn, string fq2_fn, int kms);
    void FastqReader(int seq_num,int number);
    void FastaReader(int seq_num);
    void find_start_fasta();
    void find_start_fastq(int number);
    int get_start_size(){
      return starta.size();
    }
    int get_NumThread(){ return NUMTHREAD; }
};

typedef struct thread_para{
  int number = 0;
  reader* dr;
}thread_para;

#endif
