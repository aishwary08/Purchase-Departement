#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <conio>
#include <unistd.h>
#include <iomanip>
using namespace std;

class pd
{
 protected:
  char pname[50];
  char pid[50];
  char count[50];
  char pdept[50]; 
  char ptype;
 public:
  void update();
  void show();
  void show1();
  void del();
  void insert(int);
  friend void mkreq();
}p;

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
  void vshow1();
  void vdel();
  friend void mkreq();
}v;

class usr:public pd,public vd
{
  char qua[6];
  char rname[50];
  char spec1[50];
  char spec2[50];
  char spec3[50];
  char spec4[50];
  char spec5[50];
  char dept[5];
 public:
  void req();
  void showreq();
}u;
 
struct feed
{
 char fbk[300];
 char dept[5];
}f;

void admin();
void user();

void header()
{ 
  int i;
  gotoxy(55,9);
  for(i=0;i<85;i++) printf("=");
  gotoxy(68,10);
  printf(" *******WELCOME TO PURCHASE DEPARTMENT SOFTWARE******* ");
  gotoxy(55,11);
  for(i=0;i<85;i++) printf("=");
}

void ty()
{
 int i;
  clrscr();
  gotoxy(55,25);
  for (i=0;i<79;i++) printf("=");
  gotoxy(80,27);
  printf(" ******THANK YOU!****** ");
  gotoxy(82,28);
  printf(" Have a Nice Day :) ");
  gotoxy(80,29);
  printf(" Please Visit Us Again ");
  gotoxy(55,31);
  for (i=0;i<79;i++) printf("=");
}


void pd::update()
{
 ofstream fout("pro.txt",ios::app);
 int n,ch;
 for(;;)
 {
 clrscr();
 header();
 cout<<"\n\n\n\n\t PRODUCT MENU ";
 cout<<"\n\n\t 1. NEW DATA ENTRY \n\n\t 2. MODIFY \n\n\t 3. DELETE AN ENTRY \n\n\t 4. SEARCH A PRODUCT \n\n\t 5. SHOW PRODUCT LIST \n\n\t 6. EXIT";
 cout<<"\n\n\t Enter Choice: ";
 cin>>ch;
 switch(ch)
 {
  case 1:{
          pd p1;
	  char last='y';
	  cout<<"\n\n\t Enter the number of entries: ";
	  cin>>n;
          for(int i=0;i<n;i++)
	  {
	   ifstream fin("pro.txt");
           ofstream fout("temp.txt");
	   p1.insert(i);
           while(fin.read((char*)&p,sizeof(p)))
           {
            if(strcasecmp(p1.pname,p.pname)<=0)
            {
             fout.write((char*)&p1,sizeof(p1));
             fout.write((char*)&p,sizeof(p));
             last='n';
             break;
            }
            else
             fout.write((char*)&p,sizeof(p));
           }
           if(last=='y')
            fout.write((char*)&p1,sizeof(p1));
           else if(!fin.eof())
           {  
            while(fin.read((char*)&p,sizeof(p)))
            fout.write((char*)&p,sizeof(p));
           }
           fin.close();
           fout.close();
           remove("pro.txt");
           rename("temp.txt","pro.txt");
	  }
	  fout.close();
 	  break;
         }
 case 2: {
	  int flag=0,mch; 
	  char npid[50],npname[50],temp[50],ncount[50],ndept[50];
          fstream fin("pro.txt",ios::in|ios::out|ios::binary);
 	  cout<<"\n\n\t Enter PID of the product: ";
	  cin>>temp;
	  while(fin.read((char*)&p,sizeof(p)))
          {
	   int pos=fin.tellg();
           if(strcasecmp(temp,pid)==0)
           { 
	    show1();
	    flag=1;
	    cout<<"\n\n\t What do you want to modify? ";
	    cout<<"\n\n\t 1. Product Name \n\n\t 2. Product ID \n\n\t 3. Count \n\n\t 4. Department \n\n\t 5. Exit";
	    cout<<"\n\n\t Enter here: ";
	    cin>>mch;
            switch(mch)
	    {
    	     case 1: cout<<"\n\n\t Enter New Product Name: ";
	             getchar();
	             cin.getline(npname,sizeof(npname));
	             strcpy(pname,npname);
  		     fin.seekg(pos-sizeof(p));
		     fin.write((char*)&p,sizeof(p));
		     break;
	     case 2: cout<<"\n\n\t Enter New Product ID : ";
		     getchar();
	             cin.getline(npid,sizeof(npid));
	             strcpy(pid,npid);
	 	     fin.seekg(pos-sizeof(p));
		     fin.write((char*)&p,sizeof(p));
		     break;
	     case 3: cout<<"\n\n\t Enter New Count : ";
		     getchar();
	             cin.getline(ncount,sizeof(ncount));
		     strcpy(count,ncount);
		     fin.seekg(pos-sizeof(p));
		     fin.write((char*)&p,sizeof(p));
		     break;
	     case 4: cout<<"\n\n\t Enter New Department: ";
		     getchar();
	             cin.getline(ndept,sizeof(ndept));
		     strcpy(pdept,ndept);
		     fin.seekg(pos-sizeof(p));
		     fin.write((char*)&p,sizeof(p));
		     break;
 	     case 5: fin.close();
		     return ;
            default: cout<<"\n\n\t You have entered wrong choice ";
                     cout<<"\n\n\t Please try again! ";
                     getch(); getch();
                     break;
            }
           }
	  if(flag==1)
	  break;
         }
         if(flag==0)
	 { cout<<"\n\n\t Product ID was not found in our database!! "; getch(); getch();}
         else
 	 { cout<<"\n\n\t Modified!! "; getch(); }
         fin.close();
	 break;
       }
   case 3: p.del();
	   break; 
   case 4: {
	    ifstream fin("pro.txt",ios::in|ios::binary);
 	    char temp[20]; int flag=0;
	    cout<<"\n\n\t Enter PID of the Product: ";
	    cin>>temp;
	    fin.seekg(0,ios::beg);
	    while(fin.read((char*)&p,sizeof(p)))
            {
             if(strcasecmp(temp,pid)==0)
	     { 
  	      flag=1;
	      show1();
	     }
            }
	    if(flag==0)
	    cout<<"\n\n\t Requested PID was not found in our database!! ";
	    getch(); getch();
	    fin.close();
	    break;
	   }
   case 5: p.show();
	   break;	   
   case 6: fout.close();
	   return;  
  default: cout<<"\n\n\t You have entered wrong choice ";
           cout<<"\n\n\t Please try again! ";
           getch(); getch();
           break;
  }	  
}
}

void pd::insert(int i)
{
 clrscr();
 header();
 gotoxy(78,17);
 printf("Enter The Details for Product *%d*\n\n",i+1);
 cout<<"\n\n\t Enter Product Name: ";
 getchar(); cin.getline(pname,sizeof(pname));
 cout<<"\n\n\t Enter Product ID: ";
 cin.getline(pid,sizeof(pid));
 cout<<"\n\n\t Enter The Count: ";
 cin.getline(count,sizeof(count));
 cout<<"\n\n\t Enter The Department: ";
 cin.getline(pdept,sizeof(pdept));
 cout<<"\n\n\t Enter The Type: ";
 cin>>ptype;
}

void pd::show1()
{ 
 cout<<"\n\n \t "<<setw(40)<<left<<"Product Name"<<setw(30)<<left<<"Product ID"<<setw(25)<<left<<"Product Count"<<setw(30)<<left<<"Department"<<setw(10)<<left<<"Type"<<endl<<endl;
 cout<<" \t "<<setw(40)<<left<<p.pname<<setw(30)<<left<<p.pid<<setw(25)<<left<<p.count<<setw(30)<<left<<p.pdept<<setw(0)<<left<<p.ptype<<endl;
}

void pd::show()
{
 ifstream fin("pro.txt"); 
 cout<<" \t "<<setw(40)<<left<<"Product Name"<<setw(30)<<left<<"Product ID"<<setw(25)<<left<<"Product Count"<<setw(30)<<left<<"Department"<<setw(10)<<left<<"Type"<<endl<<endl;
 while(fin.read((char*)&p,sizeof(p)))
 {
  cout<<" \t "<<setw(40)<<left<<p.pname<<setw(30)<<left<<p.pid<<setw(25)<<left<<p.count<<setw(30)<<left<<p.pdept<<setw(10)<<left<<p.ptype<<endl;
 }
 getch(); getch();
 fin.close();
}


void pd::del()
{
 ifstream f("pro.txt",ios::in);
 ofstream fo("temp.txt",ios::out);
 char temp[50];
 int flag=0; char conf='n';
 cout<<"\n\n\t Enter PID of the product: ";
 cin>>temp;
 while(f.read((char*)&p,sizeof(p)))
 { 
  if(strcasecmp(temp,pid)==0)
  {
   show1();
   flag=1;
   cout<<"\n\n\t Are you sure you want to delete this record?(Y/N): ";
   cin>>conf;
   conf=toupper(conf);
   if(conf=='N')
    fo.write((char*)&p,sizeof(p));
  }
  else
   fo.write((char*)&p,sizeof(p));
 }
 if(flag==0)
 cout<<"\n\n\t Requested PID was not found in our database!! ";
 f.close();
 fo.close();
 remove("pro.txt");
 rename("temp.txt","pro.txt");
 if(conf!='N') cout<<"\n\n\t Deleted!! ";
 else cout<<"\n\n\t Thank You!! ";
 getch(); getch();
}



void vd::vupdate()
{
 ofstream fout("vndr.txt",ios::app);
 int n,ch;
 for(;;)
 {
 clrscr();
 header();
 cout<<"\n\n\n\n\t VENDOR MENU ";
 cout<<"\n\n\t 1. NEW DATA ENTRY \n\n\t 2. MODIFY \n\n\t 3. DELETE AN ENTRY \n\n\t 4. SEARCH A VENDOR \n\n\t 5. SHOW VENDOR LIST \n\n\t 6. EXIT";
 cout<<"\n\n\t Enter Choice: ";
 cin>>ch;
 switch(ch)
 {
 case 1:{
          cout<<"\n\n\t Enter the number of entries: ";
	  cin>>n;
          ofstream fout("vndr.txt",ios::app);
 	  for(int i=0;i<n;i++)
	  {
           clrscr();
	   header();
           gotoxy(78,17);
           printf("Enter The Details for Vendor *%d*\n\n",i+1);
	   getchar();
	   cout<<"\n\n\t Enter Vendor Name: ";
  	   cin.getline(vname,sizeof(vname));
	   cout<<"\n\n\t Enter Vendor ID: ";
	   cin.getline(vid,sizeof(vid));
	   cout<<"\n\n\t Enter Vendor Address: ";
 	   cin.getline(add,sizeof(add));
	   cout<<"\n\n\t Enter The Vendor Type: ";
	   cin>>type;
	   fout.write((char*)&v,sizeof(v));
	  }
	  fout.close();
 	  break;
         }
 case 2: {
	  int flag=0,mch; 
	  char nvid[50],nvname[50],temp[50],nadd[300],ntype;
          fstream fin("vndr.txt",ios::in|ios::out|ios::binary);
 	  cout<<"\n\n\t Enter VID of the Vendor: ";
	  cin>>temp;
	  while(fin.read((char*)&v,sizeof(v)))
          {
	   int pos=fin.tellg();
           if(strcasecmp(temp,vid)==0)
           { 
	    vshow1();
	    flag=1;
	    cout<<"\n\n\t What do you want to modify? ";
	    cout<<"\n\n\t 1. Vendor Name \n\n\t 2. Vendor ID \n\n\t 3. Vendor Address \n\n\t 4. Type \n\n\t 5. Exit";
	    cout<<"\n\n\t Enter here: ";
	    cin>>mch;
            switch(mch)
	    {
    	     case 1: cout<<"\n\n\t Enter New Vendor Name: ";
	             getchar();
	             cin.getline(nvname,sizeof(nvname));
	             strcpy(vname,nvname);
  		     fin.seekg(pos-sizeof(v));
		     fin.write((char*)&v,sizeof(v));
		     break;
	     case 2: cout<<"\n\n\t Enter New Vendor ID : ";
		     getchar();
	             cin.getline(nvid,sizeof(nvid));
	             strcpy(vid,nvid);
	 	     fin.seekg(pos-sizeof(v));
		     fin.write((char*)&v,sizeof(v));
		     break;
	     case 3: cout<<"\n\n\t Enter New Address : ";
		     getchar();
	             cin.getline(nadd,sizeof(nadd));
		     strcpy(add,nadd);
		     fin.seekg(pos-sizeof(v));
		     fin.write((char*)&v,sizeof(v));
		     break;
	     case 4: cout<<"\n\n\t Enter New Type: ";
	             cin>>ntype;
		     type=ntype;
		     fin.seekg(pos-sizeof(v));
		     fin.write((char*)&v,sizeof(v));
		     break;
 	     case 5: fin.close();
		     return ;
	    default:  cout<<"\n\n\t Please Enter any valid key";
		      break;
            }
           }
	  if(flag==1)
	  break;
         }
         if(flag==0)
	 cout<<"\n\n\t Vendor ID was not found in our database!! ";
         fin.close();
	 break;
       }
   case 3: v.vdel();
	   break;
   case 4: {
	    ifstream fin("vndr.txt",ios::in|ios::binary);
 	    char temp; int flag=0,c=0;
	    cout<<"\n\n\t Enter type of the Vendor: ";
	    cin>>temp;
 	    temp=toupper(temp);
	    while(fin.read((char*)&v,sizeof(v)))
            {
             if(temp==type)
	     { 
	      flag=1;
	      if(c==0)
	      { cout<<"\n\n \t "<<setw(40)<<left<<"Vendor Name"<<setw(30)<<left<<"Vendor ID"<<setw(40)<<left<<"Vendor Address"<<setw(20)<<left<<"Type"<<endl<<endl; c++; }
	       cout<<" \t "<<setw(40)<<left<<v.vname<<setw(30)<<left<<v.vid<<setw(40)<<left<<v.add<<setw(20)<<left<<v.type<<endl; 	
	     }
            }
	    if(flag==0)
	    cout<<"\n\n\t Requested type was not found in our database!! ";
	    getch(); getch();
	    fin.close();
	    break;
	   }	
   case 5: v.vshow();
	   break;   
   case 6: fout.close();
	   return; 
  default: cout<<"\n\n\t You have entered wrong choice ";
           cout<<"\n\n\t Please try again! ";
           getch(); getch();
           break;
  }	  
}
}

void vd::vshow1()
{ 
 cout<<"\n\n \t "<<setw(40)<<left<<"Vendor Name"<<setw(30)<<left<<"Vendor ID"<<setw(40)<<left<<"Vendor Address"<<setw(20)<<left<<"Type"<<endl<<endl;
 cout<<" \t "<<setw(40)<<left<<v.vname<<setw(30)<<left<<v.vid<<setw(40)<<left<<v.add<<setw(20)<<left<<v.type<<endl; 
}

void vd::vshow()
{
 ifstream fin("vndr.txt"); 
 char ct=' ';
 cout<<"\n\n \t "<<setw(40)<<left<<"Vendor Name"<<setw(30)<<left<<"Vendor ID"<<setw(40)<<left<<"Vendor Address"<<setw(20)<<left<<"Type"<<endl<<endl;
 while(fin.read((char*)&v,sizeof(v)))
 {
  if(ct!=type)
  cout<<"\n";
  cout<<" \t "<<setw(40)<<left<<vname<<setw(30)<<left<<vid<<setw(40)<<left<<add<<setw(20)<<left<<type<<endl; 
  ct=type;
 }
 fin.close();
 getch(); getch();
}

void vd::vdel()
{
 ifstream f("vndr.txt",ios::in);
 ofstream fo("vtemp.txt",ios::out);
 char temp[50]; int flag=0; char conf='n';
 cout<<"\n\n\t Enter VID of the vendor: ";
 cin>>temp;
 while(f.read((char*)&v,sizeof(v)))
 { 
  if(strcasecmp(temp,vid)==0)
  {
   vshow1();
   flag=1;
   cout<<"\n\n\t Are you sure you want to delete this record?(Y/N): ";
   cin>>conf;
   conf=toupper(conf);
   if(conf=='N')
    fo.write((char*)&v,sizeof(v)); 
  }
  else 
   fo.write((char*)&v,sizeof(v));
 }
 if(flag==0)
  cout<<"\n\n\t Requested VID was not found in our database!! ";
 f.close();
 fo.close();
 remove("vndr.txt");
 rename("vtemp.txt","vndr.txt");
 if(conf!='N') cout<<"\n\n\t Deleted!! ";
 else cout<<"\n\n\t Thank You!! ";
 getch(); getch();
}

void usr::req()
{
 ofstream fout("req.txt",ios::app);
 char ch='y';
 char temp[50];
 do
 {
  clrscr();
  header();
  cout<<"\n\n\t Enter Your Depatment Name: ";
  getchar(); cin.getline(dept,sizeof(dept));
  cout<<"\n\n\t Enter the Product Name you want: ";
  cin.getline(temp,sizeof(temp));
  cout<<"\n\n\t Enter the Quantity: ";
  cin>>qua; getchar();
  cout<<"\n\n\t I want a product with following specifications:- ";
  cout<<"\n\t (Please Enter in 5 points. If u have less than 5 points, Enter NA)";
  cout<<"\n\n\t 1. "; getchar(); cin.getline(spec1,sizeof(spec1));
  cout<<"\n\n\t 2. "; cin.getline(spec2,sizeof(spec2));
  cout<<"\n\n\t 3. "; cin.getline(spec3,sizeof(spec3));
  cout<<"\n\n\t 4. "; cin.getline(spec4,sizeof(spec4));
  cout<<"\n\n\t 5. "; cin.getline(spec5,sizeof(spec5));
  strcpy(rname,temp);
  fout.write((char*)&u,sizeof(u)); 
  cout<<"\n\n\t Do yo want to request more products?(Y/N):  ";
  cin>>ch;
 }while(ch=='y' || ch=='Y'); 
 fout.close();
}

void usr::showreq()
{
 ifstream fin("req.txt",ios::in);
 int count=0; int q=1,j=22,i=115;
 clrscr();
 header();
 gotoxy(30,18);
 cout<<setw(20)<<left<<"Request No"<<setw(35)<<left<<"Product Name"<<setw(30)<<left<<"Quantity"<<setw(39)<<left<<"Specification Required"<<setw(10)<<right<<"From"<<endl<<endl;
 while(fin.read((char*)&u,sizeof(u)))
 {  
  count++;
  gotoxy(30,j);
  cout<<setw(20)<<left<<count<<setw(35)<<left<<rname<<setw(30)<<left<<qua<<setw(3)<<left<<"1. "<<setw(25)<<left<<spec1<<setw(20)<<right<<dept<<endl;
  j+=2; gotoxy(i,j);
  cout<<"2. "<<spec2<<endl;  
  j+=2; gotoxy(i,j);
  cout<<"3. "<<spec3<<endl;  
  j+=2; gotoxy(i,j);
  cout<<"4. "<<spec4<<endl;  
  j+=2; gotoxy(i,j);
  cout<<"5. "<<spec5<<endl;  
  j+=3;
  if(count==3*q) 
  { 
   getch(); if(q==1)getch(); clrscr(); header(); q++; j=22; 
   gotoxy(30,18);
   cout<<setw(20)<<left<<"Request No"<<setw(35)<<left<<"Product Name"<<setw(30)<<left<<"Quantity"<<setw(39)<<left<<"Specification Required"<<setw(10)<<right<<"From"<<endl<<endl;
  }
 }
 if(q!=3*q)  getch(); if(q==1) getch();
 fin.close();
}
  
void mkreq()
{
 ifstream fin("pro.txt");
 ifstream fi("vndr.txt");
 char temp[50]; int flag=0,vr=0; char ctemp=' '; int count=1;
 cout<<"\n\n\t Enter the Product Name you want to request for: ";
 getchar(); cin.getline(temp,sizeof(temp));
 while(fin.read((char*)&p,sizeof(p)))
 {
  if(strcasecmp(temp,p.pname)==0)
  {
   flag=1;
   ctemp=p.ptype;
  }
 }
 if(flag==0)
 {
  cout<<"\n\n\n\t Requested Product was not found in our database!! ";
  fin.close();
  fi.close();
  return;
 }
 //cout<<"\n\n\t "<<setw(20)<<left<<"Serial No."<<setw(50)<<left<<" Vendor Name"<<setw(30)<<left<<" Vendor ID"<<setw(25)<<left<<"Vendor Address"<<endl<<endl;
 while(fi.read((char*)&v,sizeof(v)))
 { 
  if(flag==1 && ctemp==v.type)
  {
   vr=1;
   if(count==1)
   cout<<"\n\n\t "<<setw(20)<<left<<"Serial No."<<setw(50)<<left<<" Vendor Name"<<setw(30)<<left<<" Vendor ID"<<setw(25)<<left<<"Vendor Address"<<endl<<endl;  
   cout<<"\t  "<<setw(20)<<left<<count<<setw(50)<<left<<v.vname<<setw(30)<<left<<v.vid<<setw(25)<<left<<v.add<<endl;
   count++;
  }
 }
 if(vr==0)
  cout<<"\n\n\n\t No vendor was found for this partiular product!! ";
 getch();
 fin.close();
 fi.close();
}

void feedback()
{
 ofstream fout("feed.txt",ios::app);
 gotoxy(10,24);
 cout<<"Enter Your Department: ";
 cin>>f.dept;
 gotoxy(10,27);
 cout<<"Enter Your Feedback Here[Press 'TAB' to Submit]:";
 char ch,buf[300];
 int x=10,y=29,j,i=300,nw,nwc,flag=0;
 getchar();
 gotoxy(180,27);
 cout<<"[" <<i<< "] characters left ";
 for(j=0;j<300;)
 {
  gotoxy(x,y);
  ch=getch();
  if(ch==9) 
  {
   buf[j]='\0';
   break;
  }
  if(ch!=127)
  {
   if(ch=='\n')
   {
    flag=1; nw=j+1;
    y++;
    x=10;
    i--; nwc=i;
    buf[j]=ch;
    j++;
    gotoxy(180,27);
    cout<<"[" <<i<< "] characters left ";
    continue;
   }
   buf[j]=ch;
   cout<<buf[j];
   i--; j++;
   gotoxy(180,27);
   cout<< "[" <<i<< "] characters left ";
   x++;
  }
  else
  {
   if(flag==1 && j<=nw)
   j=nw;
   else
   j--;
   if(j<0)
   { j++; if(flag==1) i=nwc; else i=300; } 
   else
   { 
    if(x==10) continue; 
    gotoxy(x,y); x--; 
    printf("\b \b");
    gotoxy(180,27); i++;
    cout<<"[" <<i<< "] characters left "; 
   }
  } 
 }
 strcpy(f.fbk,buf);
 fout.write((char*)&f,sizeof(f));
 getch(); getch();
 fout.close();
}

void readfeed()
{
 ifstream fin("feed.txt");
 int count=1;
 while(fin.read((char*)&f,sizeof(f)))
 {
  cout<<"\n\n\t "<<"No. "<<count<<"\t"; for(int i=0;i<strlen(f.fbk);i++) { if(f.fbk[i-1]==10) cout<<"\t\t";  cout<<f.fbk[i]; }
  cout<<"\n\n\t "<<"By: "<<f.dept<<" DEPARTMENT \n";
  count++;
 }
 getch(); getch();
 fin.close();
}

int o=0;
void login()
{
 char log[10]="";
 char pre[10]="PURCHASE";
 char pas[12]="DEPARTMENT";
 int i,flag=1;
 char c;
 char buf[20];
 clrscr();
 header();
 gotoxy(20,15);
 printf("LOGIN ID: ");
 if(o==0)
 { getch(); o++; }
 cin.getline(log,sizeof(log));
 gotoxy(20,17);
 printf("PASSWORD: ");
 for(i=0;(c=getch())!='\n';)
 {
  if(c!=127)
  {
   buf[i]=c;
   printf("*");
   i++;
  }
  else
  {
   i--;
   if(i<0)
    i++;
   else
    printf("\b \b");
  }
 }
 buf[i]='\0';
 gotoxy(20,19);
 int res1=strcmp(pre,log);
 int res2=strcmp(pas,buf);
 if((res1==0) && (res2==0))
 {
  gotoxy(20,19);
  cout<<"LOGIN SUCCESFULL ";
  o=0;
  getch();
  admin();
 }
 else
 {
  static int wr=0,q1=1;
  wr++;
  gotoxy(20,19);
  cout<<"LOGIN UNSUCCESFULL ";
  getch();
  if(wr==(3*q1))
  {
   gotoxy(20,22);
   cout<<"You Have Exceeded Maximum Number of Tries!! ";
   gotoxy(20,24);
   cout<<"Thank You!! \n\n\n";
   gotoxy(20,27);
   int x1=20,y1=27;
   for(int j=30;j>=0;j--)
   {
    gotoxy(x1,y1);
    cout<<"Try again in "<<j<<" seconds. \n";
    cout.flush();
    //getch();
    //clrscr();
    //header();
    //cout.flush();
    sleep(1);
   }
   //getch();
   o=0;
   q1++;
   return;
  }
  login();
 }
}

void admin()
{
 int ach;
 for(;;)
 {
  clrscr();
  header();
  cout<<"\n\n\t MENU ";
  cout<<"\n\n\t 1. PRODUCT MANAGER";
  cout<<"\n\n\t 2. VENDOR MANAGER";
  cout<<"\n\n\t 3. REQUESTS";
  cout<<"\n\n\t 4. FEEDBACK RECEIVED";
  cout<<"\n\n\t 5. EXIT ";
  cout<<"\n\n\t Enter Choice: ";
  cin>>ach;
  switch(ach)
  {
   case 1: p.update();
           break;
   case 2: v.vupdate();
           break;
   case 3: {
 	    int rch;
 	    for(;;)
            {
 	     clrscr();
	     header();
	     cout<<"\n\n\t REQUEST MENU ";
	     cout<<"\n\n\t 1. SHOW REQUESTS ";
	     cout<<"\n\n\t 2. MAKE REQUEST TO VENDOR ";
	     cout<<"\n\n\t 3. EXIT ";
	     cout<<"\n\n\t Enter Choice: ";
	     cin>>rch;
             if(rch==1)
             {  u.showreq(); break; }
             if(rch==2)
	     { mkreq(); break; }
             break;
	    }
	   break;
 	  }
   case 4: readfeed();
 	   break;
   case 5: return; break;
   default: cout<<"\n\n\t You have entered wrong choice ";
            cout<<"\n\n\t Please try again! ";
            getch(); getch();
            break;
  }
 }
}

void user()
{
 int uch;
 for(;;)
 {
 clrscr();
 header();
 cout<<"\n\n\t MENU ";
 cout<<"\n\n\t 1. MAKE A REQUEST";
 cout<<"\n\n\t 2. FEEDBACK";
 cout<<"\n\n\t 3. EXIT";
 cout<<"\n\n\t Enter Choice: ";
 cin>>uch;
 switch(uch)
 {
  case 1: u.req();
          break;
  case 2: feedback();
          break;
  case 3: return;
          break;
 default: cout<<"\n\n\t You have entered wrong choice ";
          cout<<"\n\n\t Please try again! ";
          getch(); getch();
          break;
 }
}
}


int main()
{
 int lch;
 for(;;)
 {
  clrscr();
  header();
  cout<<"\n\n\t MAIN MENU ";
  cout<<"\n\n\t 1. ADMIN LOGIN ";
  cout<<"\n\n\t 2. USER LOGIN ";
  cout<<"\n\n\t 3. Exit ";
  cout<<"\n\n\t Enter Choice: ";
  cin>>lch;
  switch(lch)
  {
   case 1: login(); 
	   admin();cout<<"hey";
           break;
   case 2: user();
           break;
   case 3: textcolor(YELLOW);
	   ty();
           getch(); getch(); printf("\n\n");
           textcolor(WHITE);
           exit(0);
  default: cout<<"\n\n\t You have entered wrong choice ";
           cout<<"\n\n\t Please try again! ";
           getch(); getch();
           break;
  }
 }
 return 0;
}
