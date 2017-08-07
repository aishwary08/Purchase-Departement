#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<conio>
#include<iomanip>
#include<unistd.h>
using namespace std;

class vd
{
 protected:
  char vname[50];
  char vid[50];
  char add[300];
  char type; 
 public:
  void vupdate();
  void vshow();
}v;

void vd::vupdate()
{
 ofstream fout("vndr.txt",ios::app);
 int n;
 cout<<"\n Enter the number of entries: ";
 cin>>n;
 //cout<<" Vendor Name \t Vendor Id \t Address \t Type \n";
 for(int i=0;i<n;i++)
 {
  cout<<" Vendor Name \t Vendor Id \t Address \t Type \n";
  getchar();
  gets(vname);
  gets(vid);
  gets(add);
  cin>>type;
  fout.write((char*)&v,sizeof(v));
 }
 fout.close();
}

void vd::vshow()
{
 ifstream fin("vndr.txt");
 cout<<"\t Vendor Name \t Vid \t Address \t Type \n";
  cout<<" \t "<<setw(40)<<left<<"Vendor Name"<<setw(30)<<left<<"Vendor ID"<<setw(40)<<left<<"Vendor Address"<<setw(20)<<left<<"Type"<<endl<<endl;
 while(fin.read((char*)&v,sizeof(v)))
 {
  //cout<<" \t "<<setw(40)<<left<<"Vendor Name"<<setw(30)<<left<<"Vendor ID"<<setw(25)<<left<<"Vendor Address"<<setw(10)<<left<<"Type"<<endl<<endl;
  cout<<" \t "<<setw(40)<<left<<"Vendor Name"<<setw(30)<<left<<"Vendor ID"<<setw(40)<<left<<"Vendor Address"<<setw(20)<<left<<"Type"<<endl<<endl;
  cout<<" \t "<<setw(40)<<left<<vname<<setw(30)<<left<<vid<<setw(40)<<left<<add<<setw(20)<<left<<type<<endl;
 //cout<<"\t "<<vname<<setw(40)<<left<<vid<<setw(30)<<left<<add<<setw(20)<<left<<type<<endl;
 }
 fin.close();
}

void z()
{
 sleep(1);
}
int main()
{ 
 clrscr();
// v.vupdate();
 int x1=20,y1=27;
 for(int i=25;i>=0;i--)
 {
  gotoxy(x1,y1);
  cout<<"Time left:"; cout<<i;
  cout.flush();
  z();
 }
 // cout<<"Time left:"; cout<<i;
 // z();
  
 //}
 v.vshow();
 return 0; 
}
