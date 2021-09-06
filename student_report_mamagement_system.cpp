#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;

// Class to store the data of Students-

class student{
    public:
    int rollno;
    string name;
    int eng_marks,maths_marks,history_marks,sci_marks,practical_marks;
    double average;
    char grade;
    public:
    void getdata();
    void showdata() const;
    void calculate();
    int return_rollno() const;
};

void student::calculate()
{
    average = (eng_marks + maths_marks + history_marks + sci_marks + practical_marks)/5.0;
    if(average>=90)
    grade = 'A';
    else if(average>=75)
    grade = 'B';
    else if(average >=50)
    grade = 'C';
    else
    grade = 'F';
}

void student::getdata()
{
cout<<"\n Enter student's Roll number: ";
cin>>rollno;
cout<<"\n\n  Enter student's Name: ";
cin.ignore();
cin>>name;
cout<<" \n Enter marks of subjects out of 100: ";
cout<<"\n Enter marks in English: ";
cin>>eng_marks;
cout<<"\n Enter marks in Maths: ";
cin>>maths_marks;
cout<<"\n Enter marks in  History: ";
cin>>history_marks;
cout<<"\n Enter marks in Science: ";
cin>>sci_marks;
cout<<"\n Enter marks in Practical: ";
cin>>practical_marks;
calculate();
}

void student::showdata() const
{
    cout<<"\nRoll NO . of student: "<<rollno;
    cout<<"\nName of Student: "<<name;
    cout<<"\nEnglish: "<<eng_marks;
    cout<<"\nMaths: "<<maths_marks;
    cout<<"\nHistory: "<<history_marks;
    cout<<"\nscience: "<<sci_marks;
    cout<<"\npractical: "<<practical_marks;
    cout<<"\nAverage Marks: "<<average;
    cout<<"\nGrade of student is: "<<grade;

}
int student::return_rollno() const
{
    return rollno;
}

// Functions declaration 
void create_student();
void display_sp(int); // Function to display a perticular record
void display_all(); // to display all records
void delete_student(int); // delete a perticular record
void change_student(int); // modify the pertuicular record

 // Main Function 
 int main()
 {
     char ch;
     cout<<setprecision(2); //decimal precision to be used to format floating-point values on output operations.
     do{
         char ch;
         int num;
         system("cls");
         cout<<"\n\n\n\tMENU";
         cout<<"\n\n\t1.Create Student record ";
         cout<<"\n\n\t2.Search student record ";
         cout<<"\n\n\t3.Display student record ";
         cout<<"\n\n\t4. delete student record ";
         cout<<"\n\n\t5. Modify student record ";
         cout<<"\n\n\t6. Exit ";
         cout<<"\n\n Enter yout choice (1/2/3/4/5/6): ";
         cin>>ch;
         system("cls");
         switch (ch)
         {
         case '1': create_student();
             break;
         case '2': cout<<"\n\n Enter roll number: ";
         cin>>num;
         display_sp(num); 
         break;
         case '3': display_all();
         break; 
         case '4': cout<<"\n\n Enter the roll no: ";
         cin>>num;
         delete_student(num);
         break;
         case '5': cout<<"\n\n Enter the roll no : ";
         cin>>num;
         change_student(num);
         break;
         case '6': cout<<"Exiting , Thank You!";
         exit (0); 

         }

     }while (ch!='6');
     return 0;     
 }
void create_student()   // write student details ino file
{
 student stud;
 ofstream oFile;
 oFile.open("student.dat", ios::binary|ios::app);
 stud.getdata();
 oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
 oFile.close();
 cout<<"\n record has been created";
 cin.ignore();
 cin.get();
}
 
void display_all() 
{
    student stud;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be opened !! press any key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\n\n Displaying all Records";
    while (inFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
    {
      stud.showdata();
      cout<<"\n\n_________________________________________________";
    }
    inFile.close();
    cin.ignore();
    cin.get();    
}

void display_sp(int n)

{
    student stud;
    ifstream iFile;
    iFile.open("student.dat",ios::binary);
    if (!iFile)
    {
        cout<<"\n File could not open";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag=false;
    while (iFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))

    {
       if (stud.return_rollno()==n)
       {
            stud.showdata();
            flag = true;
       }
       
    }
   iFile.close();
   if(flag==false)
   cout<<"\n Record does not exist...";
   cin.ignore();
   cin.get(); 
}


void change_student(int n)
{
    bool found = false;
    student stud;
    fstream f1;
    f1.open("student.dat",ios::binary|ios::in|ios::out);
 if(!f1)
{
cout<<"File could not be opened. Press any Key to exit...";
cin.ignore();
cin.get();
return;
}
     while(!f1.eof() && found==false)
{
f1.read(reinterpret_cast<char *> (&stud), sizeof(student));
if(stud.return_rollno()==n)
{
stud.showdata();
cout<<"\n\n Enter new student details:"<<endl;
stud.getdata();
    int pos=(-1)*static_cast<int>(sizeof(stud));
    f1.seekp(pos,ios::cur);
    f1.write(reinterpret_cast<char *> (&stud), sizeof(student));
    cout<<"\n\n\t Record Updated";
    found=true;
}
}
f1.close();
if(found==false)
cout<<"\n\n Record Not Found ";
cin.ignore();
cin.get();
}
//delete record with particular roll number
void delete_student(int n)
{
student stud;
ifstream iFile;
iFile.open("student.dat",ios::binary);
if(!iFile)
{
cout<<"File could not be opened... Press any Key to exit...";
cin.ignore();
cin.get();
return;
}
ofstream oFile;
oFile.open("Temp.dat",ios::out);
iFile.seekg(0,ios::beg);
while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(student)))
{
if(stud.return_rollno()!=n)
{
oFile.write(reinterpret_cast<char *> (&stud), sizeof(student));
}
}
oFile.close();
iFile.close();
remove("student.dat");
rename("Temp.dat","student.dat");
cout<<"\n\n\tRecord Deleted ..";
cin.ignore();
cin.get();
}