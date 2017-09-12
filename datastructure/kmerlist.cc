#include<iostream>
#include<string>
#include "kmerlist.h"
#include "../hash/hash.h"
#include <fstream>
#define kmer_size 31
using namespace std;

kmernode* list_start; 
kmernode* list_last = new kmernode(); 
int kmerlist::node_number = 0;

kmernode::kmernode()
{
  read = ""; 
  next = NULL;
}

kmernode::kmernode(string abno_read)
: read(abno_read)
{
  next = NULL;
}
string kmernode:: getRead()
{
 return read;
}
vector <string> kmernode::getKmers()
{
 vector<string> temp;
 for(int i=0; i<kmer_ptrs.size(); i++){
   string temp_sub = read.substr(kmer_ptrs[i],kmer_size);
  temp.push_back(temp_sub);
 }
 return temp;
}

void kmernode::add_ptr(int kmer_ptr)
{
  kmer_ptrs.push_back(kmer_ptr);
}

void kmernode::print_node()
{
  cout<< read <<endl;
  int size = kmer_ptrs.size();
  for(int i = 0; i<size; i++){
    cout<<kmer_ptrs[i]<<' ';
  }
  cout <<endl;
}
void kmernode::add_start_ptr(int start)
{
  start_ptr = start;
}
kmernode* kmerlist:: add_node(string genome_seq)
{
  kmernode* node = new kmernode(genome_seq);
  list_last -> next = node;
  list_last = node;
  if(node_number == 0)
    list_start = node;
  node_number++;
  return node;
}
unsigned long long kmernode::getStart()
{
  return start_ptr;
}
void kmerlist::print_list()
{
 cout<<node_number;/*
 kmernode* node = list_start;
 while(node -> next != NULL){
   node->print_node(); 
   node = node ->next;
 }*/
}

void kmerlist::delete_node(kmernode* before, kmernode* del)
{
  before->next = del->next;
  node_number--;
  delete del;
}

readList::readList()
{
	Head->nextNode = NULL;
	readList::Count = 0;
}
string readList::get(int index)
{
	Node* temp = Head;
	for(int i=0; i<=index; i++){
		temp = temp->nextNode;
	}
        cout<<temp->data<<endl;
        cout<<temp->start_ptr<<endl; 
	return temp->data;
}
void readList::add(string Data, unsigned long long start)
{
        Node* NewNode = new Node;
	NewNode->data = Data;
        NewNode->start_ptr = start;
	NewNode->nextNode = NULL;
	if (Head->nextNode == NULL){
		Head->nextNode = NewNode;
	}
	else
	{
		Node* temp = Head;
		while (temp->nextNode != NULL){
			temp = temp->nextNode;
		}
		temp->nextNode = NewNode;
	}
	readList::Count++;
}
int readList::size()
{
  return Count;
}

void readList::make_nodab_fq(ifstream& rpair1, ifstream& rpair2, ofstream& wpair1, ofstream& wpair2)
{
   Node* node = Head->nextNode;
   string id, read, plus, quality; 
   while(node != NULL){
     rpair1.seekg(node ->start_ptr);
     rpair2.seekg(node ->start_ptr);
     rpair1 >> id >> read >> plus >> quality;
     wpair1 << id << endl << read << endl << plus << endl  << quality << endl;
     rpair2 >> id >> read >> plus >> quality;
     wpair2 << id << endl << read << endl << plus << endl  << quality << endl;
     node = node -> nextNode;
   }
}
