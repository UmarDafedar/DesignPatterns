#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

class Singleton
{
 private:
  static Singleton* SingleInstance;
  static int counter;
  string _value;
  //Default Constructor
  Singleton()
  {
   cout<<"Default constructor is called"<<endl;
   counter++;
  }
  
  Singleton(string value):_value(value)
  {
   cout<<"Parameterised constructor is called"<<endl;
   counter++;
  }
  
  //Copy constructor and Copy Assignment operator is deleted to avoid multiple object creation
  Singleton(const Singleton& other)=delete;
  Singleton& operator=(const Singleton& other)=delete;
  
  public:
   ~Singleton()
   {
    cout<<"Destructor is called"<<endl;
    SingleInstance=nullptr;
    // counter--;
   }
   
   static Singleton* GetInstance(string inp)
   {
    if(SingleInstance==nullptr)
    {
     SingleInstance=new Singleton(inp);
    }
     return SingleInstance;
   }
  
  int Getcount()
  {
   return counter;
  }
  
  string value()
  {
   return _value;
  }
};

Singleton* Singleton::SingleInstance=nullptr;
int Singleton::counter=0;


void Function1(string inp)
{
 this_thread::sleep_for(1000ms);
 Singleton* Ptr1=Singleton::GetInstance(inp);
 cout<<Ptr1->value()<<" "<<Ptr1->Getcount()<<endl;
 
}

void Function2(string inp)
{
 this_thread::sleep_for(1000ms);
 Singleton* Ptr1=Singleton::GetInstance(inp);
 cout<<Ptr1->value()<<" "<<Ptr1->Getcount()<<endl;
}

int main()
{
 thread t1(Function1,"Foo");
 thread t2(Function2,"BAR");
 t1.join();
 t2.join();
 return 0;
}

/*
Output:
Parameterised constructor is called
BAR 1
Parameterised constructor is called
Foo 2

*/
