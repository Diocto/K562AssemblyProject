#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;
void read_garbage(int num,ifstream& is);

int main(int argc, char* argv[])
{
  string axt_file(argv[1]);
  ifstream is(axt_file.c_str(), ifstream::in);
  ifstream is2("abyss_origin/origin-8.fa", ifstream::in);
  ofstream os("extended.fa", ofstream::out);
  string garbage;
  int contig_p;
  vector<int> contig_p_vec;

//////////////////////////extract pointer/////////////
  read_garbage(15, is);
  while(!is.eof())
  {
    read_garbage(2, is);
    is >> garbage >> contig_p ;
    contig_p_vec.push_back(contig_p);
    read_garbage(4, is);
  }
  sort(contig_p_vec.begin(),contig_p_vec.end());
  set<int> contig_p_set (contig_p_vec.begin(),contig_p_vec.end());
  set<int>::iterator pos;
//////////////////////////extract pointer/////////////

//////////////////////////making fasta/////////////
  pos = contig_p_set.begin();
  int num = 0,pt,size; 
  char greater_than;
  string contig;
  while(pos != contig_p_set.end())
  {
   is2>>greater_than>>pt;
   is2>>size;
   read_garbage(1,is2); 
   is2>>contig;

   if(pt == *pos){
    os<<">"<<num<<" "<<size<<endl;
    os<<contig<<endl;   
    num++;
    pos++;
   }
  }  
//////////////////////////making fasta/////////////
  return 0;
}

void read_garbage(int num,ifstream& is)
{
  string garbage;
  for(int i = 0; i<num; i++)
  {
    getline(is,garbage);
  }
}

