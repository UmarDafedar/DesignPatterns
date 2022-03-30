/*
1. Singleton is a creational design pattern that lets you ensure that a class has only one instance, while providing a global access point to this instance.
2. Violates the Single Responsibility Principle
    a. Ensure that a class has just a single instance.
    b. Provide a global access point to that Single instance.
3. Make the default constructor private, to prevent other objects from using the new operator with the Singleton class.
4. Create a static creation method that acts as a constructor. Under the hood, this method calls the private constructor to create an object and saves it in a static 
    field. All following calls to this method return the cached object.
5. If your code has access to the Singleton class, then it’s able to call the Singleton’s static method. So whenever that method is called, the same object is always returned.
6. Note that you can always adjust this limitation and allow creating any number of Singleton instances. The only piece of code that needs changing is the body 
    of the getInstance method.
    
How to implement
----------------
1. Add a private static field to the class for storing the singleton instance.
2. Declare a public static creation method for getting the singleton instance.
3. Implement “lazy initialization” inside the static method. It should create a new object on its first call and put it into the static field. 
    The method should always return that instance on all subsequent calls.
4. Make the constructor of the class private. The static method of the class will still be able to call the constructor, but not the other objects.
5. Go over the client code and replace all direct calls to the singleton’s constructor with calls to its static creation method.
6. Copy Constructor is deleted

Pro's
-----
1. You can be sure that a class has only a single instance.
2. You gain a global access point to that instance.
3. The singleton object is initialized only when it’s requested for the first time.

Con's
-----
1. Violates the Single Responsibility Principle. The pattern solves two problems at the time.
2. The Singleton pattern can mask bad design, for instance, when the components of the program know too much about each other.
3. The pattern requires special treatment in a multithreaded environment so that multiple threads won’t create a singleton object several times.
4. It may be difficult to unit test the client code of the Singleton because many test frameworks rely on inheritance when producing mock objects.
    Since the constructor of the singleton class is private and overriding static methods is impossible in most languages, 
    you will need to think of a creative way to mock the singleton. Or just don’t write the tests. Or don’t use the Singleton pattern.

Applicability
-------------
1. Use the Singleton pattern when a class in your program should have just a single instance available to all clients; for example, 
    a single database object shared by different parts of the program.
    The Singleton pattern disables all other means of creating objects of a class except for the special creation method. 
    This method either creates a new object or returns an existing one if it has already been created.

 2. Use the Singleton pattern when you need stricter control over global variables.
    Unlike global variables, the Singleton pattern guarantees that there’s just one instance of a class. 
    Nothing, except for the Singleton class itself, can replace the cached instance.
*/

#include<iostream>

using namespace std;

class Singleton
{
 private:
  static Singleton* SingleInstance;
  static int counter;
  //Default Constructor
  Singleton()
  {
   cout<<"Default constructor is called"<<endl;
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
   
   static Singleton* GetInstance()
   {
    if(SingleInstance==nullptr)
    {
     SingleInstance=new Singleton;
    }
     return SingleInstance;
   }
  
  int Getcount()
  {
   return counter;
  }
};

Singleton* Singleton::SingleInstance=nullptr;
int Singleton::counter=0;

int main()
{
 Singleton* Instance=Singleton::GetInstance();
 cout<<Instance->Getcount()<<endl;
 delete Instance;
 Singleton* Instance2=Singleton::GetInstance();
 cout<<Instance2->Getcount()<<endl;
 Singleton* Instance3=Singleton::GetInstance();
 cout<<Instance3->Getcount()<<endl;
 if(Instance2==Instance3)
  delete Instance3;
  else
  {
    delete Instance3;
    delete Instance2;
  }
 return 0;
}
