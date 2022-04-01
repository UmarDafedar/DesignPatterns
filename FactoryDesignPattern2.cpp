#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

#define Pi 3.142
#define CircleP 1
#define RectangleP 2

class Shape
{
 public:
  string Name;
  double area;
  string Operation;
  string color;
  
  Shape()
  {
   cout<<"Shape:: Constructor"<<endl;
  }
  
  ~Shape()
  {
   cout<<"Shape:: Destructor"<<endl;
  }
  
  virtual void CreateShape()=0;
  virtual void ColorShape()=0;
  virtual double GetArea()=0;
  static Shape* GetTheShape(int);
};

class Circle:public Shape
{
 public:
  float radius;
  float diameter;
  
  Circle();
  ~Circle();
  virtual void CreateShape();
  virtual void ColorShape();
  virtual double GetArea();
};

Circle::Circle()
{
 cout<<"Circle::Circle"<<endl;
 radius=10;diameter=20;
 area=0;
 Name="Circle";
 Operation="Draw a Circle";
 color="Red";
 cout<<"Initializing a Circle Parameters..."<<endl;
 this_thread::sleep_for(5s);
 cout<<Name<<" Initialization is completed!!"<<endl;
}

void Circle::CreateShape()
{
 cout<<"Constructing the "<<Name<<"..."<<endl;
 cout<<"[As per below Parameters]"<<endl;
 cout<<"Name     :"<<Name<<endl;
 cout<<"radius   :"<<radius<<endl;
 cout<<"diameter :"<<diameter<<endl;
 cout<<Operation<<endl;
 this_thread::sleep_for(5s);
 area=Pi*radius*radius;
 cout<<"Completed !!!"<<endl;
}

double Circle::GetArea()
{
 cout<<"Calculating the area"<<endl;
 return area;
}

void Circle::ColorShape()
{
 cout<<"Coloring the "<<Name<<"..."<<endl;
 cout<<"[As per below Parameters]"<<endl;
 cout<<"Color     :"<<color<<endl;
 this_thread::sleep_for(5s);
 cout<<"Completed !!!"<<endl;
}

/*Shape - Rectangle Start*/
class Rectangle:public Shape
{
 public:
  float Height;
  float Width;
  
  Rectangle();
  ~Rectangle();
  virtual void CreateShape();
  virtual void ColorShape();
  virtual double GetArea();
};

Rectangle::Rectangle()
{
 cout<<"Rectangle::Rectangle"<<endl;
 Height=10;Width=20;
 area=0;
 Name="Rectangle";
 Operation="Draw a Rectangle";
 color="Blue";
 cout<<"Initializing a Rectangle Parameters..."<<endl;
 this_thread::sleep_for(5s);
 cout<<Name<<" Initialization is completed!!"<<endl;
}

void Rectangle::CreateShape()
{
 cout<<"Constructing the "<<Name<<"..."<<endl;
 cout<<"[As per below Parameters]"<<endl;
 cout<<"Name     :"<<Name<<endl;
 cout<<"Width   :"<<Width<<endl;
 cout<<"Height :"<<Height<<endl;
 cout<<Operation<<endl;
 this_thread::sleep_for(5s);
 area=Height*Width;
 cout<<"Completed !!!"<<endl;
}

double Rectangle::GetArea()
{
 cout<<"Calculating the area"<<endl;
 return area;
}

void Rectangle::ColorShape()
{
 cout<<"Coloring the "<<Name<<"..."<<endl;
 cout<<"[As per below Parameters]"<<endl;
 cout<<"Color     :"<<color<<endl;
 this_thread::sleep_for(5s);
 cout<<"Completed !!!"<<endl;
}
/*Shape - Rectangle Finished*/


Shape* Shape::GetTheShape(int inp)
{
 cout<<"Generating the shape..."<<endl;
 Shape* ReturnObject=nullptr;
 
 switch(inp)
 {
  case CircleP:
   cout<<"Circle is being Generated"<<endl;
   ReturnObject=new Circle;
   ReturnObject->CreateShape();
   ReturnObject->ColorShape();
   break;
  case RectangleP:
   cout<<"Rectangle is being Generated"<<endl;
   ReturnObject=new Rectangle;
   ReturnObject->CreateShape();
   ReturnObject->ColorShape();
   break;
  default:
   break;
 }
 
 return ReturnObject;
}

int main()
{
 Shape* ptr=Shape::GetTheShape(RectangleP);
 cout<<"Area of RectangleP is "<<ptr->GetArea()<<endl;
 delete ptr;
 return 0;
}
