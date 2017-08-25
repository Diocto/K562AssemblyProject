#ifndef DATAPR_H
#define DATAPR_H
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include "../datastructure/kmerlist.h"
#include "../hash/hash.h"
using namespace std;
class readList;

class datapr
{
 private:
  readList hashed_list[HASH_SIZE];
 public:
  datapr();
  void kmerProcess();
  void process_Out();
};

#endif
