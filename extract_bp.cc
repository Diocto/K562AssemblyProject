#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;
void read_garbage(int num,ifstream& is);
void print_error(string Error, string ref_chr_num[], string input_chr_num[], unsigned long long ref_chr_start[],unsigned long long ref_chr_end[], string contig[] );

int main(int argc, char* argv[])
{
  string axt_file(argv[1]);
  string ref(argv[2]);
  string cancer1(argv[3]);
  string cancer2(argv[4]);
  ifstream is(axt_file.c_str(), ifstream::in);

  string num ,ref_chr_num[2], input_chr_num[2], complement[2];
  unsigned long long ref_chr_start[2], ref_chr_end[2], input_chr_start[2], input_chr_end[2];
  string contig[2];

  ref_chr_num[0] = "", input_chr_num[0] = "", complement[0] = "";
  ref_chr_start[0] = 0, ref_chr_end[0] = 0, input_chr_start[0] = 0, input_chr_end[0] = 0; 
  contig[0] = "";

  read_garbage(15, is);
  unsigned long long ref_gap = 0;
  unsigned long long input_gap = 0;
  int i = 0;
 
  cout<<"#FORMAT = text"<<endl;
  cout<<"#REFERENCE = "<<ref<<endl;
  cout<<"#CANCER = "<<cancer1<<", "<<cancer2<<endl;
  cout<<"#ERROR_TYPE = Translocation"<<endl; 
  cout<<"#ERROR_TYPE = Inversion"<<endl; 
  cout<<"#ERROR_TYPE = Deletion"<<endl; 
  cout<<"#ERROR_TYPE = Insertion"<<endl<<endl<<endl; 

  while(!is.eof())
  { 
    read_garbage(2,is); 
    is >> num >> ref_chr_num[1] >> ref_chr_start[1] >> ref_chr_end[1] ;
    is >> input_chr_num[1] >> input_chr_start[1] >> input_chr_end[1] >> complement[1];  
    read_garbage(1,is);
    getline(is, contig[1]);

    if(!ref_chr_num[0].compare(ref_chr_num[1]) && !input_chr_num[0].compare(input_chr_num[1])){
      ref_gap = ref_chr_start[1] - ref_chr_end[0];
      input_gap = input_chr_start[1] - input_chr_end[0];
      
      if(ref_gap > 0 && input_gap > 0){
        if( ref_gap == input_gap && !complement[0].compare(complement[1]) && !complement[0].compare("-"))
          print_error("Translocation",ref_chr_num, input_chr_num,ref_chr_start,ref_chr_end,contig);
        else if( ref_gap < input_gap)
          print_error("Insertion",ref_chr_num, input_chr_num,ref_chr_start,ref_chr_end,contig);
        else if(ref_gap > input_gap)
          print_error("Deletion",ref_chr_num, input_chr_num,ref_chr_start,ref_chr_end,contig);
      }
    }
   
    ref_chr_num[0] = ref_chr_num[1];
    ref_chr_start[0] = ref_chr_start[1];
    ref_chr_end[0] = ref_chr_end[1];

    input_chr_num[0] = input_chr_num[1];
    input_chr_start[0] = input_chr_start[1];
    input_chr_end[0] = input_chr_end[1];
    complement[0] = complement[1];
    contig[0] = contig[1];
   
    read_garbage(2,is); 
  }
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

void print_error(string Error, string ref_chr_num[], string input_chr_num[], unsigned long long ref_chr_start[],unsigned long long ref_chr_end[], string contig[] ){
  cout<<Error<<" : " << ref_chr_num[0]<<" ";
  cout<<ref_chr_start[0]<<" "<<ref_chr_end[0]<<" "<<ref_chr_start[1]<<" "<<ref_chr_end[1]<<" contig"<<input_chr_num[0]<<endl;
  cout<< "1. " <<contig[0]<<endl<<"2. "<<contig[1]<<endl<<endl;
}
