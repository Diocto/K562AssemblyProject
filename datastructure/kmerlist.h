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

  public:
    kmernode();
    kmernode(string abno_read);
    string getRead();
    vector <string> getKmers();
    void add_ptr(int kmer_ptr);
    void print_node();
  friend class kmerlist;  
  friend class datapr;
};

class kmerlist
{
  public:
    static int node_number ;
    static kmernode* add_node(string genome_seq);
    static void print_list();
};

class readList
{
private:
	class Node
	{
	public:
		string data;
		Node* nextNode;
	};
	void valid(int count);
	int Count;
	Node* Head = new Node;
public:
	readList();
        int size();
	string get(int index);
	void add(string Data);
	void add(int Count,string Data);
};
#endif
