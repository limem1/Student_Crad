#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std ;


class Student
{
  int rollno ;
  char name [50];
  int p_marks , c_marks , m_marks , e_marks , cs_marks ;
  double grade ;
  double per ;
  void calculate();
public:
  void getdata() ;
  void showdata()const ;
  void show_tabular() const ;
  int retrollno()const ;

};
void Student::calculate()
{
      per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
      if(per>=60)
         grade ='A';
      else if (per >=50)
         grade = 'B';
      else if (per >= 33)
         grade = 'C';
      else
         grade = 'F' ;
}
void Student::getdata()
{
  cout <<"\nEnter The roll number of Student :";
  cin>>rollno ;
  cout <<"\nEnter The name of Student :";
  cin.ignore();
  cin.getline(name, 50);
  cout<<"\nEnter The marks in physics out of 100 :";
  cin>>p_marks;
  cout<<"\nEnter The marks in chemistry out of 100 : ";
	cin>>c_marks;
	cout<<"\nEnter The marks in maths out of 100 : ";
	cin>>m_marks;
	cout<<"\nEnter The marks in english out of 100 : ";
	cin>>e_marks;
	cout<<"\nEnter The marks in computer science out of 100 : ";
	cin>>cs_marks;
	calculate();
}
void Student::showdata() const 
{
  cout<<"\nRoll number of student : "<<rollno ;
  cout<<"\nName of Student : "<<name;
  cout<<"\nMarks in Physics : "<<p_marks;
	cout<<"\nMarks in Chemistry : "<<c_marks;
	cout<<"\nMarks in Maths : "<<m_marks;
	cout<<"\nMarks in English : "<<e_marks;
	cout<<"\nMarks in Computer Science :"<<cs_marks;
	cout<<"\nPercentage of student is  :"<<per;
	cout<<"\nGrade of student is :"<<grade;
}
void Student :: show_tabular()const
{
  cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<p_marks<<setw(4)<<c_marks<<setw(4)<<m_marks<<setw(4)<<e_marks<<setw(4)<<cs_marks<<setw(8)<<per<<setw(6)<<grade<<endl;

}
int Student::retrollno() const
{return rollno ;}

void write_student();
void display_all();
void display_sp(int);
void modify_student(int);
void delete_student();
void class_result();
void result();


void entry_menu();


int  main(int argc, char const *argv[]) {
  char ch ;
  cout.setf(ios::fixed|ios::showpoint);
  cout<<setprecision(20);
  

  do
  {
    system("cls");
    cout<<"\n\n\n\tMAIN MENU";


    cout<<"\n\n\t01.RESULT MENU";
    cout<<"\n\n\t02.ENTRY/EDIT MENU";
    cout<<"\n\n\t03.EXIT";
    cout<<"\n\n\tPlease Select Your Option (1-3)" ;
    cin>>ch ;
    switch(ch)
    {
      case '1' : result();
                 break;
      case '2' : entry_menu();
                   break ;
      case '3' :
                 break;
      default : cout<<"\a";

    }
  }while (ch!=3) ;
    return 0;
}
void write_student()
{
  Student st ;
  ofstream outFile;
  outFile.open("Student.dat", ios::binary | ios::app);
  st.getdata();
  outFile.write(reinterpret_cast<char *> (&st) , sizeof(Student));
  outFile.close();
  cout<<"\n\nStudent record has been Created ";
  cin.ignore();
  cin.get();

}
void display_all()
{
  Student st ;
  ifstream inFile;
  inFile.open("Student.dat", ios::binary);
  if(!inFile)
  {
    cout<<"File coild not be open !! Press any key :)";
    cin.ignore();
    cin.get();


    return ;

  }
  cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
  while(inFile.read(reinterpret_cast<char *>(&st) , sizeof(Student))){
      st.showdata();
    cout<<"\n\n==========================\n";
  }
    inFile.close();
    inFile.ignore();
    inFile.get();

}

void display_sp(int n)
{
  Student st ;
  ifstream inFile ;
  inFile.open("Student.dat", ios::binary);
  if(!inFile)
  {
    cout<<"\nCould not be open !! Press any key" ;
    cin.ignore();
    cin.get();
  }
  bool flag = false ;
  while (inFile.read(reinterpret_cast<char *>  (&st), sizeof(Student)))
  {
    if(st.retrollno()==n)
     {
      st.showdata();
      flag = true ;

     }
   }
    inFile.close();
    if(flag==false)
         {cout <<"\n\nrecord not exist!";}
    cin.ignore();
    cin.get();

}
void modify_student(int n )
{
  bool found =false ;
  Student st ;
  fstream File ;
  File.open("Student.dat", ios::binary | ios::in | ios::out);
  if(!File)
  {
    cout <<"File could not be open !! Press any key" ;
    cin.ignore();
    cin.get();

  }
  while (!File.eof() && found == false)
  {
    File.read(reinterpret_cast<char *> (&st), sizeof(Student));
    if(st.retrollno()==n)
    {
      st.showdata();
      cout<<"\n\nPlease Enter The New details of Student "<<endl ;
      st.getdata();
      int pos =(-1)*static_cast<int>(sizeof(st));
      File.seekg(pos , ios::cur);
      File.write(reinterpret_cast<char *> (&st),sizeof(Student));
      cout <<"\n\n\tRecord Updated";
      found = true ;

    }
  }
  File.close();
  if(found = false)
  {
    cout <<"\n\nRecord Not Found " ;
    cin.ignore();
    cin.get();
  }
}
void delete_student(int n)
{
  Student st ;
  ifstream inFile ;
  inFile.open("Student.dat", ios::binary);
  if(!inFile)
  {
    cout <<"File could not be open !! Press any key ";
    cin.ignore();
    cin.get();

  }
  ofstream outFile ;
  outFile.open("temp.dat", ios::out);
  inFile.seekg(0,ios::beg);
  while (inFile.read(reinterpret_cast<char *> (&st) , sizeof(Student)))
  {
    if(st.retrollno()!= n)
    {
        outFile.write(reinterpret_cast<char *> (&st) , sizeof(Student));
    }
  }
  outFile.close();
  inFile.close();
  remove("Student.dat");
  rename("temp.dat", "Student.dat");
  cout<<"\n\n\tRecord Deleted ..";
  cin.ignore();
  cin.get();

}
void class_result()
{
  Student st ;
  ifstream inFile;
  inFile.open("Student.dat", ios::binary);
  if(!inFile)
  {
    cout <<"File could not be open !! Press any key";
    cin.ignore();
    cin.get();

  }
  cout<<"\n\n\tALL STUDENT RESULT \n\n";
  cout<<"=========================================================================\n";
  cout<<"R.No           Name          P   C   M   E  CS   &age          Garde"<<endl ;
  cout<<"====================================================================";
  while (inFile.read(reinterpret_cast<char *> (&st), sizeof(Student)))
  {
    st.show_tabular();

  }
  cin.ignore();
  cin.get();


  inFile.close();
}
void result()
{
  char ch ;
  int rno ;
  system("cls");
  cout<<"\n\n\n\tRESULT MENU";
  cout<<"\n\n\n\t1. Class result";
  cout<<"\n\n\t2. Student Report Card";
  cout<<"\n\n\t3.BAck to Main Menu";
  cout<<"\n\n\n\tEnter Choice(1/2/3)? ";
  cin>>ch ;
  system("cls");
  switch (ch) {
    case '1': class_result(); break ;
    case '2': cout <<"\n\n\tEnter Roll Number Of Student :"; cin>>rno ;
              display_sp(rno);break ;
    case '3': break ;
    default: cout<<"\a" ;
  }
}

void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			display_sp(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
			delete_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}
