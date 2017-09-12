#ifndef KMERLIST_H
#define KMERLIST_H
#include<iostream>
#include<string>
#include<vector>
#define FASTQ_READ_SIZE 100
using namespace std;

class kmernode;
class kmerlist;
class Nodeing;
extern kmernode* list_start ;
extern kmernode* list_last ;
class readList;

class kmernode
{
  private:
    string read;
    vector <int> kmer_ptrs;  
    kmernode* next;
    unsigned long long start_ptr;
  public:
    kmernode();
    kmernode(string abno_read);
    string getRead();
    unsigned long long getStart();
    void add_start_ptr(int start);
    vector <string> getKmers();
    void add_ptr(int kmer_ptr);
    void print_node();
    kmernode* get_next()
    { 
      return next;
    }
    string get_read()
    {
      return read;
    }
  friend class kmerlist;  
  friend class datapr;
};

class kmerlist
{
  public:
    static int node_number ;
    static kmernode* add_node(string genome_seq);
    static void print_list();
    static void delete_node(kmernode* before, kmernode* del);
};

class readList
{
private:
	class Node
	{
	public:
		string data;
	        unsigned long long start_ptr;
		Node* nextNode;
	};
	void valid(int count);
	int Count;
	Node* Head = new Node;
public:
	readList();
        int size();
        void add_start_ptr(int start);
	string get(int index);
	void add(string Data,unsigned long long start);
	void add(int Count,string Data);
	void make_nodab_fq(ifstream& rpair1, ifstream& rpair2, ofstream& wpair1, ofstream& wpair2);
};
#endif
