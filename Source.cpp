#include <conio.h>
#include <string.h>
#include <iomanip.h>
#include <process.h>
#include <fstream.h>
class pass
{
	char uname[100];
	char passw[50];
	public:
	pass()
	{
		strcpy(uname,"admin");
		strcpy(passw,"admin");
	}
	void getpass()
	{ 
		cout<<endl<<endl<<"Enter New Username : ";
		gets(uname);
		cout<<endl<<"Enter New Password : ";
		gets(passw);
	}
	char* retpass()
	{
		return passw;
	}
	char* retuname()
	{
		return uname;
	}	
};
class emp
{  
	long empno ;
	char name[40] ;
	float bsal;
	float hra_p,da_p,itax_p,hra,da,itax,netsal;
	char address[100];
	char dept[50];
	public:
	void read()
	{
	cout <<"Enter the employee's name : ";
	gets(name);
	cout <<"Enter Employee Number: ";
	cin>>empno;
	cout<<"Enter the Department of the Employee: ";
	gets(dept);
	cout<<"Enter the Basic Salary of the Employee: ";
	cin>>bsal;
	cout<<"Enter the Address of the Employee: ";
	gets(address);
	system("CLS");
	}
	void readsaldet()
	{
	cout<<"Enter the current HRA : ";cin>>hra;cout<<endl<<"Enter the current DA Percentage: ";cin>>da_p;cout<<endl<<"Enter the Income Tax Percentage: ";cin>>itax_p;	    
    da=(da_p/100)*bsal;    
    itax=(itax_p/100)*bsal;
    netsal=(bsal+da+hra)-itax;
	}
	void show()
	{
	cout <<endl<<endl<<"          Employee's name : ";
	puts(name);
	cout <<"          Employee number: "<<empno<<endl;
	cout<<"          Department of the employee: ";
	puts(dept);
	cout<<"          Basic Salary of the employee: "<<bsal;	
	cout<<endl<<"          Address of the employee: ";
	puts(address);
	}
	int retempno()
	{
	return empno;	
	}
	char* retempname()
	{
		return name;
	}
	float modsalary(float x)
	{
	bsal=bsal+((x*bsal)/100);
	return bsal;	
	}
	void salslip()
	{ 
	system("CLS");
	    cout<<endl<<"=========================================================== SALARY SLIP ============================================================ "<<endl;
		cout<<endl<<"Name"<<"       Employee ID"<<"       Department"<<"       Basic Salary"<<"       HRA"<<"       Dearness Allowance"<<"       Income Tax"<<"       Net Salary" ; 
		cout<<endl<<"____________________________________________________________________________________________________________________________________";
		cout<<endl<<endl<<""<<name<<"             "<<empno<<"             "<<dept<<"           Rs."<<bsal<<"        Rs."<<hra<<"       Rs."<<da<<"             Rs."<<itax<<"        Rs."<<netsal;
	    cout<<endl<<"====================================================================================================================================";
	}
	
}; 
    void writedefpass()
    {
        pass p;
	    ofstream fout;
	    fout.open("PASS.dat", ios::binary|ios::trunc);
	    fout.write((char*)&p,sizeof(p));
	    fout.close();	
    }
    void writepass()
    {
        pass p;
	    ofstream fout;
	    fout.open("PASS.dat", ios::binary|ios::trunc);
	    p.getpass();
	    fout.write((char*)&p,sizeof(p));
	    fout.close();	
    }
    int verifypass(char entereduname[],char enteredpass[])
    {
    int auth;
   	pass p;
	ifstream fin;
	fin.open("PASS.dat",ios::binary);
	while(fin.read((char*)&p,sizeof(p)))
	{
    if(strcmp(p.retuname(),entereduname)==0 && strcmp(p.retpass(),enteredpass)==0)
	auth=1;
	else
	auth=0;
	}
	fin.close();
	return auth;
    }
    
    void gensalslip(int n)
    {
	emp e;
	int flag=0 ;
	system("CLS");
   	ifstream fin;
	fin.open("EMPLOYEE.dat",ios::binary);
	while(fin.read((char*)&e,sizeof(e)))
	{
		if (e.retempno()==n)
		{
		flag=1;
		e.readsaldet();
		e.salslip();
		}
    }
    if (flag==0)
    cout<<endl<<endl<<"RECORD NOT FOUND."<<endl;
    }
    void readfil()  
	{
	emp e;
	ifstream fin;
	fin.open("EMPLOYEE.dat",ios::binary);
	while(fin.read((char*)&e,sizeof(e)))
	{
	cout<<endl<<"======================================================";
	e.show();
	cout<<endl<<"======================================================";
	}
	fin.close();		
	}
	void writefil() 
	{
	emp e;
	ofstream fout;
	fout.open("EMPLOYEE.dat", ios::binary|ios::app);
	e.read();
	fout.write((char*)&e,sizeof(e));
	fout.close();
	}
	void searchbyempno(int n)  
	{
	emp e;
	int flag=0 ;
	ifstream fin;
	fin.open("EMPLOYEE.dat",ios::binary);
	while(fin.read((char*)&e,sizeof(e)))
	{
		if (e.retempno()==n)
		{
			flag=1;
		e.show();
		}
		else
		cout<<endl;
	}
	if (flag==0)
	cout<<endl<<endl<<"RECORD NOT FOUND"<<endl;	
	fin.close();
	}
	void searchbyempname(char charactername[])  
	{
	int x;
	int flag=0 ;
	emp e;
	ifstream fin;
	fin.open("EMPLOYEE.dat",ios::binary);
	fin.seekg(-1,ios::beg) ;
	while(fin.read((char*)&e,sizeof(e)))
	{
	x=strcmp(charactername,e.retempname());
	if(x==0)
	{
    flag=1 ;
	e.show();
	}
	}
	if(flag==0)
	cout<<endl<<endl<<"RECORD NOT FOUND"<<endl;	
	fin.close();
	}
	void del(int n)   
	{
		emp e;
		int flag=0 ;
		ifstream fin;
		fin.open("EMPlOYEE.dat",ios::binary);
		ofstream fout;
		fout.open("tempdel.dat",ios::binary|ios::out|ios::app);
		fin.seekg(0,ios::beg);
		while(fin.read((char*)&e,sizeof(e)))
		{
			if(e.retempno()!=n)
			{flag=1 ;
			fout.write((char*)&e,sizeof(e));}
		}
		if (flag==0)
		cout<<endl<<endl<<"RECORD NOT FOUND"<<endl;
		fin.close();
		fout.close();
		remove("EMPLOYEE.dat");
		rename("tempdel.dat","EMPLOYEE.dat");
	}
	void mod(int n)   
	{
	emp e;
	int flag=0 ;
	ifstream fin;
	ofstream fout;
	fin.open("EMPlOYEE.dat",ios::binary|ios::in);
	fout.open("TEMP.dat",ios::binary|ios::out|ios::app);
	while(fin.read((char*)&e,sizeof(e)))	
	{
		if(e.retempno()==n)
		{
			flag=1;
		fout.seekp(-1*sizeof(e),ios::cur);
		e.read();
		}
		fout.write((char*)&e,sizeof(e));
	}
	if (flag==0)
	cout<<endl<<endl<<"RECORD NOT FOUND"<<endl;
	fin.close();
	fout.close();
	remove("EMPLOYEE.dat");
	rename("TEMP.dat","EMPLOYEE.dat");
	}
	void salarychange(float s) 
	{
		emp e;
		ifstream fin;
		fin.open("EMPLOYEE.dat",ios::binary|ios::in);
		ofstream fout;
		fout.open("saltemp.dat",ios::binary|ios::out);
		while(fin.read((char*)&e,sizeof(e)))
		{
		e.modsalary(s);	
		fout.write((char*)&e,sizeof(e));
		}
	fin.close();
	fout.close();
	remove("EMPLOYEE.dat");
	rename("saltemp.dat","EMPLOYEE.dat");
	}
void main()   
{
system("color 70") ;  
char choice;
int choice3;
emp e;
pass p;
char nametobesearched[50];
char userpass[50],username[50];
int n,ch,i,salinc;
int x=0;
int nchoice;
do
{
cout<<endl<<endl<<"=========================================  THE EMPLOYEE MANAGEMENT PROGRAM    ========================================"<<endl<<endl;
cout<<"Enter Your Choice: "<<endl<<endl<<endl<<"      1.Enter New Employee Data"<<endl<<"      2.Display Data of All Employees"<<endl<<"      3.Display (Search) Data of a Specific Employee"<<endl<<"      4.Generate Salary Slip of an Employee"<<endl<<"      5.EXIT"<<endl<<"============================================="<<endl<<"      6.ADMIN MENU (PASSWORD PROTECTED)"<<endl<<"=============================================";
cout<<endl<<endl<<"Enter Your Choice (1,2,3...) : ";
ch=getch();
system("CLS");
if(ch=='4')
{
	system("CLS");
	cout<<endl<<endl<<"Enter The Employee Number of The Employee Whose Salary Slip is to be Generated (Press -1 for main menu) : ";
	cin>>n;
	cout<<endl;
	gensalslip(n);
}
else if(ch=='5')
exit(1);
else if(ch=='6')
{
	system("CLS");
	system ("color 79");
	ifstream fin;
	fin.open("PASS.dat",ios::binary);
	if(!fin)
	{
	writedefpass();
	fin.close();	
	}
	else 
	fin.close();
	cout<<endl<<"THE DEFAULT USERNAME AND PASSWORD IS - 'admin,admin' RESPECTIVELY.";
	cout<<endl<<endl<<"Enter Administrator Username : ";
	gets(username);
	cout<<"Enter Administrator Password : ";
	gets(userpass);
	int mainauth=verifypass(username,userpass);
	if (mainauth==1)
    {
system("CLS");
cout<<endl<<endl<<"=========================================  ADMINISTRATOR MENU    ======================================================"<<endl<<endl;
cout<<endl<<"      1.Delete Data of an Employee"<<endl<<"      2.Modify Data of an Employee" <<endl<<"      3.Delete All Data"<<endl<<"      4.Modify Data With Respect to Increase or Decrease in Salary"<<endl<<"      5.Change Default Username and Password."<<endl<<endl<<endl<<"============================================="<<endl<<"      6.BACK TO MAIN MENU"<<endl<<"=============================================";
cout<<endl<<endl<<"Enter your choice (1,2,3...) : ";
nchoice=getch();
system("CLS");
if(nchoice=='1')
{
cout<<endl<<endl<<"Enter the employee number of the employee to be deleted (Press -1 for main menu) : ";
cin>>n;
del(n);	
cout<<endl<<endl<<"EMPLOYEE DATA DELETED.";
}
else if(nchoice=='4')
{
cout<<"Enter the percentage of salary to be increased/decreased for all employees (for decrease, use a negative sign before the percentage) (Press - for main menu) :  ";
cin>>salinc;
salarychange(salinc);
if (salinc>0)
cout<<endl<<"Salary has been increased by "<<salinc<< "%";
else if (salinc<0)
cout<<endl<<"Salary has been decreased by "<<salinc<< "%";	
} 
else if(nchoice=='2')
{
	cout<<"Enter the Employee Number of the Employee Whose Data is to be Modified (Re-enter the data which you do not want to modify) (Press - for main menu): ";
	cin>>n;
	cout<<endl<<"Already Existing Data --";
	cout<<endl<<"======================================================";
	searchbyempno(n);
	cout<<"======================================================";
	cout<<endl<<endl<<"Enter The Modified Data (Press - for main menu) -- "<<endl<<"______________________________"<<endl<<endl;
	mod(n);
}
else if(nchoice=='3')
{
cout<<endl<<"Are you sure? (Y/N) (Press - for main menu)";
int delch=getch();
if (delch=='y'||delch=='Y')
{remove("EMPLOYEE.dat");
cout<<endl<<endl<<endl<<"ALL DATA DELETED";}
else if (delch!='y'||delch!='Y')
cout<<endl<<endl<<"Data Not Deleted.";
}
else if(nchoice=='5')
{
writepass();		
}
}
else if (mainauth!=1)
cout<<endl<<endl<<"WRONG USERNAME OR PASSWORD.";
}
else if(ch=='1')
{
	cout<<"Enter the Number of Employees you need to Enter the Data of (Press 0 for main menu) : ";
	cin>>x;
	system("CLS");
	for(i=0;i<x;i++)
	{
	writefil();	
    }
}
else if(ch=='2')
{
	readfil();
}
else if (ch=='3')
{
	cout<<"1.Search by Employee Number"<<endl;
	cout<<"2.Search by Employee Name"<<endl;
	cout<<endl<<"Enter your choice (1 or 2) (Press - to cancel): ";
	choice3=getch();
	if (choice3=='1')
	{
	system("CLS");
	cout<<endl<<"Enter the employee number of the employee to be searched (Press - for main menu): ";
	cin>>n;
	cout<<"==========================================================";
	searchbyempno(n);
	cout<<"==========================================================";
	}
	else if(choice3=='2')
	{
	system("CLS");
	cout<<endl<<"Enter the name of the employee to be searched (Press - for main menu): ";
	gets(nametobesearched);
	cout<<"==========================================================";
	searchbyempname(nametobesearched);
	cout<<"==========================================================";
	}
}
else 
cout<<"WRONG KEYWORD!";
cout<<endl<<endl<<"Back to main menu? (Y or N) "; 
choice=getch();
system("color 70") ; 
system("CLS");
if(choice=='n'||choice=='N')
exit(0);
else
cout<<"Wrong Keyword." ;
system("CLS");
system("color 70") ; 
}while(choice=='y'||choice=='Y'||nchoice=='6');
getch();
}
