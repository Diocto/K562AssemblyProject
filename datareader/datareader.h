#ifndef DATAREADER_H
#define DATAREADER_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

static int sequence = 0;
void* FastReaderWrapper(void* readerObj);
void print_hash();
class reader{
  private:
    string ref;
    string fq1;
    string fq2;
    int kmer_size;
    int gts_cnt;
    vector<unsigned long long> start;

  public:
    reader(string fn,string fq1_fn, string fq2_fn, int kms);
    void FastqReader();
    void FastaReader(int seq_num);
    void find_start_fasta();
    int get_start_size(){
      return start.size();
    }
};

#endif
