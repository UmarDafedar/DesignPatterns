#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>

using namespace std;

class Singleton
{
 private:
  static Singleton* SingleInstance;
  static int counter;
  string _value;
  static mutex m1;
  static int Max_instance;
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
    lock_guard<mutex> lock(m1);
    Singleton* ReturnInstance;
    if(SingleInstance==nullptr && counter==0)
    {
     SingleInstance=new Singleton(inp);
     ReturnInstance=SingleInstance;
    }
    else if(counter<Max_instance)
    {
     ReturnInstance=new Singleton(inp);
    }
    else
     ReturnInstance=SingleInstance;
    
    return ReturnInstance;
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
std::mutex Singleton::m1;
int Singleton::Max_instance=5;


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
 thread t3(Function2,"Hello");
 thread t4(Function1,"World");
 thread t5(Function2,"Car");
 thread t6(Function2,"Dog");
 t1.join();
 t2.join();
 t3.join();
 t4.join();
 t5.join();
 t6.join();
 
 return 0;
}
