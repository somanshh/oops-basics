#include <iostream>
using namespace std;

// class rectangle
// {
// private:
//     int length;
//     int breadth; // only these data members will occupy space in stack
// public:
//     rectangle()
//     {                             // Default CONSTRUCTOR
//         length = 1;
//         breadth =  1;
//     }
//     rectangle(int l = 0, int b = 0)
//     {                                // parameterized + default CONSTRUCTOR
//         setLength(l);
//         setBreadth(b);
//     }
//     rectangle(rectangle &rect)
//     {                                            // CoPY COnSTRUCOR
//         length = rect.length;
//         breadth = rect.breadth;
//     }
//     void setLength(int l)
//     {
//         if (l >= 0)
//             length = l;
//         else
//         {
//             cout << "length cannot be negative :-((" << endl;
//             length = 0;
//         }
//     }
//     void setBreadth(int l)
//     {
//         if (l >= 0)
//             breadth = l;
//         else
//         {
//             cout << "breadth cannot be negative :-((" << endl;
//             breadth = 0;
//         }
//     }
//     // int getLength(){
//     //     return length;
//     // }
//     // int getBreadth(){
//     //     return breadth;
//     // }
//     int area()
//     { //**functions in a class does not occupy any type space**
//         return length * breadth;
//     }
//     int perimeter()
//     {
//         return 2 * (length + breadth);
//     }
// };

// int main()
// {

//     // rectangle r1;
//     // rectangle *ptr = &r1; // object created in stack memory

//     // rectangle *ptr = new rectangle; // dynamic object allocation     (in heap)

//     // ptr->length = 10;
//     // ptr->breadth = -5;

//     rectangle r1(10,5);                  //calling parameterized  COnStruCtOR
//     rectangle r2(r1);               //calling CopY COnStruCtOR
//     cout << r1.area() << " = Area of rectangle" << endl;
//     cout << r2.area() << " = Perimeter of rectangle" << endl;

//     return 0;
// }


// .
// .
// .
// .

//

// class student
// {
// private:
//     int rollNo;
//     string name;
//     int marks1;
//     int marks2;
//     int marks3;

// public:
//     student(int r, string s, int m1, int m2, int m3);
//     int totalMarks();
//     char grade();
//     ~student();
// };

// student::student(int r, string s, int m1, int m2, int m3)
// {
//     int rollNo = r;
//     string name = s;
//     int marks1 = m1;
//     int marks2 = m2;
//     int marks3 = m3;
// }
// int student::totalMarks()
// {
//     return (marks1 + marks2 + marks3);
// }
// char student::grade()
// {
//     // int total = totalMarks();
//     if (totalMarks() >= 200)
//         return 'A';
//     else
//         return 'B';
// }

// student::~student()
// {
// }

// int main()
// {

//     int roll;
//     string name;
//     int m, p, c;
//     cout << "Enter Roll number of a Student: ";
//     cin >> roll;
//     cout << "Enter Name of a Student:";
//     cin >> name;
//     cout << "Enter marks in 3 subjects";
//     cin >> m >> p >> c;
//     student s(roll, name, m, p, c);
//     cout << "Total Marks:" << s.totalMarks() << endl;
//     cout << "Grade of Student:" << s.grade() << endl;

//     return 0;
// }


// .
// .
// .
// .


//OPERATOR OVERLOADING N FRND FUNC   (important)

class complex{
    int real;
    int img;

public:
    complex(int r=0,int i=0){
        int real = r;
        int img = i;
    }
    complex add(complex c);
    friend complex operator+(complex c1,complex c2);     //now it can access the private and public members of its parent class
};

complex complex::add(complex c){
    complex = temp;
    temp.real = real+c.real;
    temp.img = img+c.img;
}



/*******  virtual functions , base class pointer n polymorphism  ******/


class base
{
    public:
        virtual void print(){               //we made it virtual so that derived class function can be called,rather than this one 
            cout<<"print func. of base class"<<endl;
        }
        void show(){                        //we didn't made it virtual , so this func. will be executed
            cout<<"show func. of base class"<<endl;
        }
};

class derived:public base
{
    public:
        void print(){                   // function overiding
            cout<<"print func. of Derived class called"<<endl;
        }
        void show(){
            cout<<"show func. of derived class"<<endl;
        }
};

int main(){     //this is known as runtime polymorphism

    base *ptr;          //initializing a base class pointer

    derived d;          //a derived class object

    ptr = &d;           //base class pointer can point on derived class object but it can't be vice versa.

    ptr->print();       //now as we made the print()function of base class virtual , now print function of derived class will be called. else base class print func. would've been called

    ptr->show();        //as we did not made it virtual base class show func. will be called

    return 0;
}

