#include<iostream>
#include<string>
#include "kmerlist.h"
#include "../hash/hash.h"
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
	return temp->data;
}
void readList::add(string Data)
{
        Node* NewNode = new Node;
	NewNode->data = Data;
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
