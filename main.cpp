#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;
ifstream fin("exam1.txt");//inputing data form this file

//enum for subjects
enum subject{math,biology,planet,geometry,physic};
//template to reurn the avarage
template <class T>
T avarage (T a,T b)
{
  return  a/b;
}

//structure for creating a linked list for all questions
struct questions
 {
  int question_id;
  int correct_alternative;
  subject category;
  string firstAlternative;
  string secondAlternative;
  string question;
  questions *nextt;
} *headd=NULL;

//structure for counting the number of questions is needed bellow i could have used global variable but i did like this from the begining and i didnt chanched that
struct total
{
  int total=20;
}tot;

//structure inputing admin info  i could have done something else but i let it like this because it can be created a linked list and can be many admis
struct admin
{
  string username="Admin";
  string password="Admin";
}admin1;

//structure inputing exam info and creating a linked list for all exams
struct exams{
string username;
int points;
int tot;
int id;
int day;
int month;
int year; 
exams *next;
}*head3=NULL;

//structure inputing user info and creating a linked list for all users
struct user{
int user_id;
string name;
string surename;
string username;
string password;
int age;
int total=0;
int nr_tests=0;
user *next1;
}*head2=NULL;

//structure inputing wrong question info needed to display users mistakes
struct wrong{
  int id_w;
  string question;
  string your_ans;
  string correct_ans;
  wrong *next2;
}*head4=NULL;

//functions prortotipe all their function will be explaind bellwo
void admin();
void login_admin();
void all_exams();
void serach_std();
int  gen(int n);
void edit_ques();
void past_exams(string *name);
void view_mistakes(string *name);

//function overloading
void input(string username,int points,int id,int day,int month,int year,int d);
void input(int id,string name,string lastname,int age,string username,string code);

void student_menu(string *name);
void login();
void register1();
void input_ques();
void main_menu();
void test(string *name);
void display();
void total_score(string *name);
void sort();
int show_arr(user *arr,int length);
void check_date(int day,int month,int year,string *name);

int main() 
{ 
  //staring the time becouse i have used a random function
  srand( time( 0 ) );
  //generating given guestions in the beggining form the file
  gen(20);
  //the main function that includes all the other functions
  main_menu();
}

//is the main function that includes all the other funcrions
void main_menu()
{
  while(1)
   {
     int a;
     //function options
     cout<<"Welcom into our system"<<endl<<"1 - Log in as Admin"<<endl<<"2 - Log in as Student"<<endl<<"3 - Registere"<<endl<<"4 - Close"<<endl<<endl;
     cin>>a; 
     if (a==1)
     {//first option to login as admin
       login_admin();    
     }
     else if(a==2)
     {//second option to login as student
       login();
     }
     else if(a==3)
     {//third option to register if he or she is not registered yet
       register1();
     }
     else if(a==4)
     {//the forth option to end ore shut down the system (break the infinite loop in the begining)
       cout<<"Goodbye"<<endl;
       break;
     }
   }
}

//testing the student 
void test(string *name)
{
  int id,d=0,correct=0,wrong_ans=0,n;
  int day,month,year;
   //inputing exam id
  cout<<"Enter exam Id"<<endl;
  cin>>id;
  //making sure that this exam id is unique for this user (because when he search for his mistakes he search by inputing exam id)
  exams *temp=head3;
  while(temp!=NULL)
  {
    if(temp->id==id&&temp->username==*name)
    {
      cout<<"This exam id is taken"<<endl;
      cout<<"Please try again"<<endl;
      test(name);
    }
    temp=temp->next;
  }
  //inputing exam date
  cout<<"Enter date seperated with space (dd/mm/yy)"<<endl;
  cin>>day;
  cin>>month;
  cin>>year;
  check_date(day,month,year,name);
  
   
  //creating a loop that displays 20 questions of an exam
  for(int i=0;i<20;i++)
  { 
    //geting a random number from the total number of questions 
    n=rand()%tot.total;
    questions *temp=headd;
    //generating a random question
    for(int j=0;j<n;j++)
    temp=temp->nextt;
    //printing out question
    cout<<"Question ID: "<<temp->question_id<<endl;   
    cout<<temp->question<<endl;
    cout<<"1 - "<<temp->firstAlternative<<"     "<<"2 - "<<temp->secondAlternative<<endl;
    int ans1;
    cin>>ans1;//geting the answer
    //if answer is correct print correct and count the correct answer for printing the total correct answer
    if(ans1==temp->correct_alternative)
    {
      cout<<"Correct"<<endl<<endl;
      correct++;   
    }
    //else if it is not correct it is wrong counting the wrong answer for displying it in his mistakes and print wrong
    else 
    {
      ++d;//total wrong answers
      cout<<"Wrong"<<endl<<endl;
      wrong_ans++;//wrong answers for this exam
      wrong *newNode= new wrong; //adding a item in wrong linked list
      newNode->id_w=id;  
      newNode->question=temp->question; 
      if(temp->correct_alternative==1)
      {
        newNode->correct_ans=temp->firstAlternative;newNode->your_ans=temp->secondAlternative;
      }      
      else if(temp->correct_alternative==2)
      {
        newNode->correct_ans=temp->secondAlternative;
        newNode->your_ans=temp->firstAlternative;      
      }   
      newNode->next2=head4;
      head4=newNode; 
    }  
  } 
  //declaring a tempory pointer type user thai is equal with the head of the user
  user *tempp=head2;
  //crating a loop for compearing the username until the end of the list and then if it finds the username then 
  while(tempp!=NULL)
  {
   if(*name==tempp->username)
   {
     tempp->total=tempp->total+correct;//add +1 the total correct points
     tempp->nr_tests=tempp->nr_tests+1;//add +1 the total number of tests
     //printing out the nr of correct answers / total points /and avarage points for exam     
      cout<<"You scored "<<correct<<"/20 points"<<endl<<"Total: "<<tempp->total<<endl<<"Avarage: "<<avarage(tempp->total,tempp->nr_tests)<<endl;//avarage function returns total/number of tests (avarage points for exam)
      
   }
   tempp=tempp->next1;//goes to the next part of the linked list
  }
  //this function add into the exam list exam information
  input(*name,correct,id,day,month,year,d);
  //here goes inside the student login
  student_menu(name);
}

//this function is for students to log in
void login()
{
  //gets the username and password compares them and if they are in the list than log them in
  bool loginn=true;
  user *temp=head2;
  string username1,password1;
  cout<<"Enter your username"<<endl;
  cin>>username1;
  cout<<"Enter the password"<<endl;
  cin>>password1;cout<<endl;
  while(temp!=NULL)
  {        
    if(username1==temp->username&&password1==temp->password)
    {
      string *name;
      name=&temp->username;
      student_menu(name); 
      loginn=false;
      break;
    } 
   temp=temp->next1;
  }
  //if this infos are not in the list then tell t
 if(loginn==true)
  {
    cout<<"Username or password is incorrect"<<endl<<"Please try again."<<endl;
    //goes back to main menu to try again
    main_menu();
  }
}

//this function has the student alternatives(student menu)
void student_menu(string *name)
{    
  cout<<"Welcom "<<*name<<endl<<"Type :"<<endl;
  cout<<"1 - Start a new test."<<endl;
  cout<<"2 - View your past testes."<<endl;
  cout<<"3 - Total scores."<<endl;
  cout<<"4 - Log out"<<endl;
  int choose1;
  cin>>choose1;        
  if(choose1==1)
  {
    // if he types 1 than he can take a test or exam
   test(name); 
   //after the exam he returns to the student menu
   student_menu(name);   
  }      
  else if(choose1==2)
  { //2 to view his past exams/testes
    cout<<"Your past testes"<<endl; 
    past_exams(name) ;
  }       
  else if(choose1==3)
  {//to display total points 
   total_score(name);          
  }    
  else if(choose1==4)
   main_menu();//to log out
  else
  {//if he dose not type any of this number then he should try again
    cout<<"Pleas write a valid number"<<endl<<endl;
    student_menu(name);//returns to the student menu
  }
}

//this function inputs user information into the user linked list
void input(int id,string name,string lastname,int age,string username,string code)
{
  user *newNode2= new user; 
  newNode2->user_id=id;  
  newNode2->name=name;
  newNode2->surename=lastname;
  newNode2->age=age;
  newNode2->username=username;
  newNode2->password=code;
  newNode2->next1=head2;
  head2=newNode2; 
}

//this function inputs a question from the admin from the keyboard
void input_ques()
{
  subject a;
  string category,question,first,second;
  int id,correct,b;
  cout<<"Input question id"<<endl;
  cin>>id;
  questions *temp=headd;
  while(temp!=NULL)
  {
   if(id==temp->question_id)//here makes sure that id and username are unique
    {
      cout<<"This Id is taken, Please write a different id"<<endl;
      input_ques();
    }
   temp=temp->nextt;
  }
  //inputs question info from the admin
  cout<<"Input question category({math,biology,planet,geometry,physic)"<<endl;
  cin>>category;
  category=a;
  cout<<"Input the first alternative"<<endl;
  cin>>first;
  cout<<"Input the second alternative"<<endl;
  cin>>second;
  cout<<"Input the corrrect alternative"<<endl;
  cin>>correct;
  cout<<"Input the question"<<endl;
  cin.ignore();
  getline(cin,question);
  //here puts them in the question linked list
  questions *newNode= new questions;
  newNode->question_id=id;
  newNode->category=a;
  newNode->question=question;
  newNode->firstAlternative=first;
  newNode->secondAlternative=second;
  newNode->correct_alternative=correct;
  newNode->nextt=headd;// 3 step
  headd=newNode;
  cout<<"Question was added sucessfully"<<endl;
  tot.total=tot.total+1;//the total number of question is added by one 
}

//this function is to register a student
void register1()
{
  string name,surename,username,password;
  int id,age;
  cout<<"Enter an Id"<<endl;
  cin>>id;
  cout<<"Create a username"<<endl;
  cin>>username;
  user *temp=head2;
  while(temp!=NULL)
  {//here makes sure that the username and id is unique
    if(id==temp->user_id)
    {
      cout<<"This Id is taken"<<endl;
      cout<<"Please try again"<<endl;
      register1();
    }
    else if(username==temp->username)
    {
      cout<<"This username is taken please try again"<<endl;
      cout<<"Please try again"<<endl;
      register1();
    }
    temp=temp->next1;
  }//enters the student info
  cout<<"Enter your name"<<endl;
  cin>>name;
  cout<<"Enter your surename"<<endl;
  cin>>surename;
  cout<<"Enter your age"<<endl;
  cin>>age;
  cout<<"Create a password"<<endl;
  cin>>password;
  //adding this infos int the user linked list
  input(id,name, surename,age, username, password);
  cout<<"You were registered sucessfully"<<endl<<endl;
  login();//get back to the student menu
}

//inputing exam info into the exam linked list
void input(string username,int points,int id,int day,int month,int year,int d)
{
  exams *newNode= new exams; 
  newNode->username=username;  
  newNode->points=points;
  newNode->id=id;
  newNode->day=day;
  newNode->month=month;
  newNode->year=year;
  newNode->tot=d;
  newNode->next=head3;
  head3=newNode; 
}

//displays all this user exams
void past_exams(string *name)
{
  exams *temp=head3;
  if(head3==NULL)
  {
   cout<<"List is empty\n";
   student_menu(name);
  }
  int a=0;
  
  while(temp!=NULL)
  { 
   if(*name==temp->username)
   {
     cout<<"Date: "<<temp->day<<"/"<<temp->month<<"/"<<temp->year<<"\t\t";
     cout<<temp->username<<"\t\t";
     cout<<"Exam Id: "<<temp->id<<"\t\t";
     cout<<temp->points<<"/20 points"<<endl;
     temp=temp->next;
    }
  } 
  int aaa;//another mini menu type one to view his mistakes or two to get back
  cout<<"Enter:"<<endl;
  cout<<"1- To view your mistakes"<<endl;
  cout<<"2- To get back"<<endl;
  cin>>aaa;
  if(aaa==1)
  {
   view_mistakes(name);
  }
  else if(aaa==2)
   student_menu(name);
   cout<<endl;
}

//views the user mistakes by entering the exam id
void view_mistakes(string*name)
{
  int id,d;
  cout<<"Enter exam id"<<endl;
  cin>>id;
  exams *temp=head3;
  cout<<endl<<"Your mistakes"<<endl<<endl;
  while(temp!=NULL)
  {   
   d=20-temp->points;
   cout<<d<<endl;
   if(id==temp->id)
   {
     wrong *temp=head4;
     for(int i=1;i<=d;i++)
     {
       cout<<"Id: "<<temp->id_w<<endl;
       cout<<temp->question<<endl; 
       cout<<"Correct answer: "<<temp->correct_ans<<endl;
       cout<<"Your answer: "<<temp->your_ans<<endl;  temp=temp->next2;
     }
   };
   temp=temp->next;
  }
  student_menu(name);//get back to the student menu
}

//here is the admin zone with his abilitys as shown below
void admin()
{
  int ans;
  cout<<"1 -Display all done exams"<<endl;
  cout<<"2 -Search for a student"<<endl;
  cout<<"3 -Sort the students(highest average points)"<<endl;
  cout<<"4 -Add a question"<<endl;
  cout<<"5 -Display all questions"<<endl;
  cout<<"6 -Edit a question"<<endl;
  cout<<"7 -Logout"<<endl;
  cin>>ans;
  if(ans==1)//1 to display all done exams
  all_exams();
  else if(ans==2)//2 to search for a student 
  serach_std();
  else if(ans==3)//3 to display a student in the sorted way from the student with highest points
  sort();
  else if(ans==4)//4 to add a new question
  input_ques();
  else if(ans==5)//5 to display all the questions
  display();
  else if(ans==6)//6 to edit a question by inputing its id
  edit_ques();
  else if(ans==7)//7 to log out
  main_menu();
  else
  {
    cout<<"Please write a valide number"<<endl;
    admin();
  }
  admin();
}

//this function displays all done exmas
void all_exams()
{
  if(head3==NULL)
  {
    cout<<"The list of exams is empty\n";
    return;
  }
  exams *temp=head3;
  while(temp!=NULL)
  { 
   cout<<"Date: "<<temp->day<<"/"<<temp->month<<"/"<<temp->year<<"\t\t";
   cout<<temp->username<<"\t\t";
   cout<<"Exam Id: "<<temp->id<<"\t\t";
   cout<<temp->points<<"/20 points"<<endl;
   temp=temp->next;
  }
}

//this function search for a student by his username and displays all his exams 
void serach_std()
{
  int a,b;
 
  exams *temp=head3;
   
  string user;
  cout<<"Enter the username of the student"<<endl;
  cin>>user; 

  cout<<"1- To display students last 5 exams"<<endl;
  cout<<"2- To display students all exams"<<endl;
  cin>>b;
  
  if(b==1)
  {
    while(temp!=NULL)
    {
      if(user==temp->username)
     a=a+1;
     temp=temp->next;
    }
   



   if(a>5)
   {
     exams *temp2=head3;
     for(int i=0;i<5;i++)
     {
      cout<<"Date: "<<temp2->day<<"/"<<temp2->month<<"/"<<temp2->year<<"\t\t";
      cout<<temp2->username<<"\t\t";
      cout<<"Exam Id: "<<temp2->id<<"\t\t";
      cout<<temp2->points<<"/20 points"<<endl;
      temp2=temp2->next;
     }
    }

   if(a>0&&a<5)
   {
      exams *tempp=head3;
    
     while(tempp!=NULL)  
     { 
      cout<<"Date: "<<tempp->day<<"/"<<tempp->month<<"/"<<tempp->year<<"\t\t";
      cout<<tempp->username<<"\t\t";
      cout<<"Exam Id: "<<tempp->id<<"\t\t";
      cout<<tempp->points<<"/20 points"<<endl;
      tempp=tempp->next;
     }
    } 
  }

  if(b==2)
  {
    exams *temppp=head3;
    while(temppp!=NULL)  
    { 
     cout<<"Date: "<<temppp->day<<"/"<<temppp->month<<"/"<<temppp->year<<"\t\t";
     cout<<temppp->username<<"\t\t";
     cout<<"Exam Id: "<<temppp->id<<"\t\t";
     cout<<temppp->points<<"/20 points"<<endl;
     temppp=temppp->next;
   }

  }
  
  
 
  admin();//returns to the admin menu
} 

//intputs admin info for login as admin
void login_admin()
{
  string a,b;
  cout<<"Enter username"<<endl;
  cin>>a;
  cout<<"Enter password"<<endl;
  cin>>b;
  if(a==admin1.username&&b==admin1.password)
  admin();
}

//this function generates the questions from the exam1.txt file its a recursion
int gen(int n)
{
  string a,first,second ,ques;
  subject ab;
  if(n==0)
  return 0;
  else 
  {
    //fin info from the file
    int id,correct;
    fin>>id;
    fin>>a;
    a=ab;
    fin>>correct;   
    getline(fin,ques);
    fin>>first;
    fin>>second;
    //inputing them into the linked list
    questions *newNode= new questions;
    newNode->question_id=id;
    newNode->category=ab;
    newNode->question=ques;
    newNode->firstAlternative=first;
    newNode->secondAlternative=second;
    newNode->correct_alternative=correct;
    newNode->nextt=headd;
    headd=newNode;
    gen(n-1);

  }
  
  
return 0;
}

//this function dislays all questions
void display()
{
  questions *temp=headd;
  while(temp!=NULL)
  {
    cout<<"ID: "<<temp->question_id<<endl;   
    cout<<" -> "<<temp->question<<endl;
    cout<<"1 - "<<temp->firstAlternative<<"     "<<"2 - "<<temp->secondAlternative<<endl;
   temp=temp->nextt;
  }
}

//this function eedit a question by inputing its id
void edit_ques()
{
  bool aa=false;
  int id,ans,correct;
  string category,first,second,question;
  subject a;
  cout<<"Enter the Id of the question you wanna change"<<endl;
  cin>>ans;
  questions *tempp=headd;
  while(tempp!=NULL)
  {
    if(tempp->question_id==ans)
    aa=true;
    
    tempp=tempp->nextt; 
  }
  if(aa==false)
  {
    cout<<"There is no question with that Id"<<endl<<"Please try again"<<endl;
    edit_ques();
  }
  else
  {//inputing the new question info
    cout<<"Input question category({math,biology,planet,geometry,physic)"<<endl;
    cin>>category;
    category=a;
    cout<<"Input the first alternative"<<endl;
    cin>>first;
    cout<<"Input the second alternative"<<endl;
    cin>>second;
    cout<<"Input the corrrect alternative"<<endl;
    cin>>correct;
    cout<<"Input the question"<<endl;
    cin.ignore();
    getline(cin,question);
    
    
    questions *temp=headd;
    while(temp!=NULL)
    {
      if(id==temp->question_id)//here finds the id and changes the question info
      { 
        
        temp->question=question;
        temp->question_id=id;
        temp->firstAlternative=first;
        temp->secondAlternative=second;
        temp->correct_alternative=correct;
        temp->category=a; 
      }
      temp=temp->nextt;
    }
    cout<<"Question was edit sucessfully"
<<endl;  }
}

//yhis function displays the totla points of a student
void total_score(string *name)
{
  user *tempp=head2;
  while(tempp!=NULL)
  {
   if(*name==tempp->username)
   {
      cout<<"Total: "<<tempp->total<<"/"<<20*tempp->nr_tests<<endl;
   }
   tempp=tempp->next1;
  }
  student_menu(name);
  
}

//this function sort and displays the students from the student with highest points 
void sort()
{
  int length=0,tempp;
  user *temp=head2;
  while(temp!=NULL)//here i have found the linked list length
  {
    length=length+1;
    temp=temp->next1;
  }
  user arr[length];
  user *temp2=head2;
  for(int i=0;i<length;i++)//here i have converted linked list into and array
  {
    arr[i].user_id=temp2->user_id;
    arr[i].total=temp2->total;
    arr[i].name=temp2->name;
    arr[i].surename=temp2->surename;
    arr[i].age=temp2->age;
    arr[i].nr_tests=temp2->nr_tests;
    temp2=temp2->next1;    
  }
  //here i have sorted the array
  for(int i=0;i>length;i++)
	{		
		for(int j=i+1;j>length;j++)
		{
			if(arr[i].total/arr[i].nr_tests<arr[j].total/arr[j].nr_tests)
			{
				tempp=arr[i].total;
				arr[i].total=arr[j].total;
				arr[j].total=tempp;
			}
		}
	}
  user *ptr=arr;
  //here i have display it using an arry
  show_arr(ptr,length-1);

}
//i have displayd the sorted arry using recursin and i have passed array into function
int show_arr(user *arr,int length)
{
  if(length<0)
  return 0;
  else 
  {
     cout<<"ID: "<<arr[length].user_id;
    cout<<"\t"<<arr[length].name;
    cout<<"\t"<<arr[length].surename;
    cout<<"\t"<<arr[length].age<<" Years old";
    cout<<"\t Total points: "<<arr[length].total;
    cout<<"\t Number of tests: "<<arr[length].nr_tests;
    cout<<"\t Avarage points/test: "<<avarage(arr[length].total,arr[length].nr_tests)<<endl;
    show_arr(arr,length-1);
  }
  return 0;
}


//this function checks the date if it is valide or not
void check_date(int day,int month,int year,string *name)
{
  if(1000 <= year&&year <= 3000)
   {
     if((month==1 || month==3 || month==5|| month==7|| month==8||month==10||month==12) && day>0 && day<=31)
       cout<<"Date is valid"<<endl;
     else 
       if((month==4 || month==6 || month==9|| month==11) && day>0 && day<=30)
           cout<<"Date is Valid"<<endl;
        else
           if(month==2)
            {
             if((year%400==0 || (year%100!=0 && year%4==0)) && day>0 && day<=29)
                 cout<<"Date is Valide"<<endl;
             else if(day>0 && day<=28)
              cout<<"Date is Valid"<<endl;
             else
             {
               cout<<"It is Invalid"<<endl;
               cout<<"Please try again"<<endl;
               test(name);
             }
            }
           else
           {
             cout<<"It is Invalid"<<endl;
             cout<<"Please try again"<<endl;
             test(name);
            }
    }
    else
      {
        cout<<"It is Invalid"<<endl;
        cout<<"Please try again"<<endl;
        test(name);
      }
}





  






