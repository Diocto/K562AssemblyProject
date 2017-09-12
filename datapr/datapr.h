#ifndef DATAPR_H
#define DATAPR_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include "../datastructure/kmerlist.h"
#include "../hash/hash.h"
#define READ_HASH_SIZE 1024*1024
using namespace std;
class readList;

class datapr
{
 private:
  readList* hashed_list[READ_HASH_SIZE];
 public:
  datapr();
  void kmerProcess();
  void process_Out();
  void make_nodab_fq_wrapper(string pair1, string pair2);
};

#endif
