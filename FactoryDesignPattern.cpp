/*
1. Factory Method is a creational design pattern that provides an interface for creating objects in a superclass, 
    but allows subclasses to alter the type of objects that will be created.
2. In the Factory pattern, we create an object without exposing the creation logic to the client and refer to newly created objects using a common interface.
3. The factory design pattern is used when we have a superclass with multiple sub-classes and based on input, we need to return one of the sub-class. 
    This pattern takes out the responsibility of the instantiation of a class from the client program to the factory class.

Benefits of Factory Pattern
---------------------------
1. Factory design pattern provides an approach to code for interface rather than implementation.
2. Factory pattern removes the instantiation of actual implementation classes from client code. Factory pattern makes our code more robust, 
    less coupled, and easy to extend. For example, we can easily change PC class implementation because the client program is unaware of this.
3. Factory pattern provides abstraction between implementation and client classes through inheritance.

Applicability
------------------------
1. Use the Factory Method when you don’t know beforehand the exact types and dependencies of the objects your code should work with.
    The Factory Method separates product construction code from the code that actually uses the product. 
    Therefore it’s easier to extend the product construction code independently from the rest of the code.

For example, to add a new product type to the app, you’ll only need to create a new creator subclass and override the factory method in it.

2. Use the Factory Method when you want to provide users of your library or framework with a way to extend its internal components.

  Inheritance is probably the easiest way to extend the default behavior of a library or framework. 
  But how would the framework recognize that your subclass should be used instead of a standard component?

  The solution is to reduce the code that constructs components across the framework into a single factory method and let anyone override this method in addition to 
  extending the component itself.

  Let’s see how that would work. Imagine that you write an app using an open source UI framework. Your app should have round buttons, 
  but the framework only provides square ones. You extend the standard Button class with a glorious RoundButton subclass. 
  But now you need to tell the main UIFramework class to use the new button subclass instead of a default one.

  To achieve this, you create a subclass UIWithRoundButtons from a base framework class and override its createButton method. 
  While this method returns Button objects in the base class, you make your subclass return RoundButton objects. 
  Now use the UIWithRoundButtons class instead of UIFramework. And that’s about it!

3. Use the Factory Method when you want to save system resources by reusing existing objects instead of rebuilding them each time.

 You often experience this need when dealing with large, resource-intensive objects such as database connections, file systems, and network resources.

Let’s think about what has to be done to reuse an existing object:

First, you need to create some storage to keep track of all of the created objects.
When someone requests an object, the program should look for a free object inside that pool.
… and then return it to the client code.
If there are no free objects, the program should create a new one (and add it to the pool).
That’s a lot of code! And it must all be put into a single place so that you don’t pollute the program with duplicate code.

Probably the most obvious and convenient place where this code could be placed is the constructor of the class whose objects we’re trying to reuse. 
However, a constructor must always return new objects by definition. It can’t return existing instances.

Therefore, you need to have a regular method capable of creating new objects as well as reusing existing ones. That sounds very much like a factory method.

How to Implement
----------------
1. Make all products follow the same interface. This interface should declare methods that make sense in every product.
2. Add an empty factory method inside the creator class. The return type of the method should match the common product interface.
3. In the creator’s code find all references to product constructors. One by one, replace them with calls to the factory method, 
    while extracting the product creation code into the factory method.

4. You might need to add a temporary parameter to the factory method to control the type of returned product.
  At this point, the code of the factory method may look pretty ugly. It may have a large switch operator that picks which product class to instantiate. 
  But don’t worry, we’ll fix it soon enough.

5. Now, create a set of creator subclasses for each type of product listed in the factory method. Override the factory method in the subclasses and extract the appropriate bits of construction code from the base method.
  If there are too many product types and it doesn’t make sense to create subclasses for all of them, 
  you can reuse the control parameter from the base class in subclasses.

6. For instance, imagine that you have the following hierarchy of classes: the base Mail class with a couple of subclasses: AirMail and GroundMail; the Transport classes are Plane, Truck and Train. While the AirMail class only uses Plane objects, GroundMail may work with both Truck and Train objects. You can create a new subclass (say TrainMail) to handle both cases, but there’s another option. The client code can pass an argument to the factory method of the GroundMail class to control which product it wants to receive.
  If, after all of the extractions, the base factory method has become empty, you can make it abstract. 
  If there’s something left, you can make it a default behavior of the method.

 Pros
 1. You avoid tight coupling between the creator and the concrete products.
 2. Single Responsibility Principle. You can move the product creation code into one place in the program, making the code easier to support.
 3. Open/Closed Principle. You can introduce new types of products into the program without breaking existing client code.
 
 Cons
 1. The code may become more complicated since you need to introduce a lot of new subclasses to implement the pattern. 
    The best case scenario is when you’re introducing the pattern into an existing hierarchy of creator classes.
*/

#include<iostream>
#include<chrono>
#include<thread>
using namespace std;


class RobotFactory
{
 public:
  string RobotName;
  string Operation;
  
  virtual void CreateItem()=0;
  virtual void DeliverItem()=0;
  
  static RobotFactory* DeliverRobot(int Type);
  
};

class DomesticRobot:public RobotFactory
{
 public:
  DomesticRobot();
  ~DomesticRobot();
  virtual void CreateItem();
  virtual void DeliverItem();
};

class MilitaryRobot:public RobotFactory
{
 public:
  MilitaryRobot();
  ~MilitaryRobot();
  virtual void CreateItem();
  virtual void DeliverItem();
};

RobotFactory* RobotFactory::DeliverRobot(int Type)
{
  cout<<"Robot Factory: Delivery Robot Function is called"<<endl;
  RobotFactory* Tmp=nullptr;
  switch(Type)
  {
   case 1:
    cout<<"Client has requested for Domestic Robot "<<endl;
    Tmp=new DomesticRobot;
    break;
   case 2:
    cout<<"Client has requested for Military Robot "<<endl;
    Tmp=new MilitaryRobot;
    break;
   default:
    cout<<"Invalid input"<<endl;
    break;
   
  }
  if(Tmp!=nullptr)
  {
   Tmp->CreateItem();
   Tmp->DeliverItem();
  } 
  return Tmp;
  }

DomesticRobot::DomesticRobot()
{
 cout<<"DomesticRobot:: Default Constructor"<<endl;
 cout<<"Constructing...."<<endl;
 this_thread::sleep_for(5s);
}

DomesticRobot::~DomesticRobot()
{
 cout<<"DomesticRobot:: Destructor"<<endl;
 cout<<"Destructing...."<<endl;
 this_thread::sleep_for(5s);
}

void DomesticRobot::CreateItem()
{
 cout<<"DomesticRobot:: CreateItem"<<endl;
 cout<<"Creating...."<<endl;
 RobotName="DomesticCharlie";
 this_thread::sleep_for(5s);
 cout<<"Constructing its parts and programming it..."<<endl;
 Operation="DomesticOperations";
 this_thread::sleep_for(5s);
}

void DomesticRobot::DeliverItem()
{
 cout<<"DomesticRobot:: DeliverItem"<<endl;
 cout<<"Gettin Ready For Delivery...."<<endl;
 this_thread::sleep_for(5s);
 cout<<"Its Ready and On the way..."<<endl;
 this_thread::sleep_for(5s);
 cout<<"Delivered"<<endl;
}


MilitaryRobot::MilitaryRobot()
{
 cout<<"MilitaryRobot:: Default Constructor"<<endl;
 cout<<"Constructing...."<<endl;
 this_thread::sleep_for(5s);
}

MilitaryRobot::~MilitaryRobot()
{
 cout<<"MilitaryRobot:: Destructor"<<endl;
 cout<<"Destructing...."<<endl;
 this_thread::sleep_for(5s);
}

void MilitaryRobot::CreateItem()
{
 cout<<"MilitaryRobot:: CreateItem"<<endl;
 cout<<"Creating...."<<endl;
 RobotName="MilitaryAlpha";
 this_thread::sleep_for(5s);
 cout<<"Constructing its parts and programming it..."<<endl;
 Operation="MilitaryOperations";
 this_thread::sleep_for(5s);
}

void MilitaryRobot::DeliverItem()
{
 cout<<"MilitaryRobot:: DeliverItem"<<endl;
 cout<<"Gettin Ready For Delivery...."<<endl;
 this_thread::sleep_for(5s);
 cout<<"Its Ready and On the way..."<<endl;
 this_thread::sleep_for(5s);
 cout<<"Delivered"<<endl;
}

int main()
{
 cout<<"Welcome to Factory of Robots"<<endl;
 cout<<"Press 1, for requesting Domestic Robot"<<endl;
 cout<<"Press 2, for requesting Military Robot"<<endl;
 cout<<"**************************************"<<endl;
 int i=3, inp=0;
 
 while(i>0)
 {
  cout<<"Provide your input"<<endl;
  cin>>inp; 
  RobotFactory* ptr=RobotFactory::DeliverRobot(inp);
  delete ptr;
  i--;
 }
 cout<<"Thank You for doing business with Robot Factory"<<endl;
 return 0;
}
