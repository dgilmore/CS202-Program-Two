//David Gilmore Program # 2 CS202 Winter 2017
//this is another implementation file. I eventually had
//to split my .cpp files because it because a real hassle 
//find certain functions when they need to be worked on. If I 
//had more time I would have tried to have the class functions grouped
//in files that maybe made a little more sense. In this file I have 
//the implementation of the popularity class and it's helper classes. 
//Also in this file are the implementations for my base class and it's 
//derived class, plus the list class and it's helper classes. 

#include "transportation.h"
#include <iostream>
#include <cctype>
#include <cstring>
using namespace std; 

//CONSTRUCTORS AND DESTRUCTORS FOR THE
//ARRAY OF LISTS DATA STRUCTURE
popularity::popularity()
{ 
   array = new pop_info[POP_MAX];
   info_index = 0;
}

//default destructor
popularity::~popularity()
{
  if(array != NULL)
      delete [] array;
      
  array = NULL;
  info_index = 0; 
}  

//default constructor
pop_info::pop_info()
{
  ptr = NULL;
}

//default destructor
pop_info::~pop_info()
{
   ptr = NULL;
}

//default constructor
list::list()
{
   head = NULL; 
}

//default destructor
list::~list()
{
   if(head != NULL)
      delete head;
}

//node constructor for the transpo
//class 
l_node::l_node()
{
  time_of_day = 0;
  description = NULL;
  next = NULL;
}

l_node::~l_node()
{
   time_of_day = 0;

   if(description != NULL)
       delete [] description;
   description = NULL;

   if(next != NULL)
       delete next;

   next = NULL;
}

l_node::l_node(int time, char * desc)
{
   time_of_day = time;
   description = new char[strlen(desc) + 1];
   strcpy(description, desc);
}
//default constructor for transpo class
transportation::transportation()
{
   tran_status = 0;
   tran_status = 0;
}

//constructor with args for transpo class
//need this constructor because when we create
//a derived class we need to send in the info given
//about transpo type.
transportation::transportation(int status, int cost)
{
   tran_status = status;
   tran_cost = cost;
}

//base class virtural destructor
transportation::~transportation() {} 

//returns cost of one rider for a lyft
float lyft::cost()
{
    return tran_cost * 5; 
}

//returns the const of one rider using the max
float max_st::cost()
{
   return tran_cost;
}

//returns the cost of one rider for the bus
float bus::cost()
{
   return tran_cost;
} 

//displays the transpo info
void transportation::display()
{
   if(tran_status == 0)
      cout << "Transportation Type Status: No Delays At This Time " << endl;
   if(tran_status == 1)
      cout << "Transportation Type Status: Slight Rain Delays" << endl;
   if(tran_status == 2)
      cout << "Transportation Type Status: Expect major Delays" << endl;
   cout << "Transportation Type Cost:   " << tran_cost << "  per rider " << endl; 
} 

//constructors and destructors for the derived classes
lyft::lyft(): transportation(0, 3.50) {}
lyft::~lyft(){}

max_st::max_st(): transportation(1, 2.50) {}
max_st::~max_st() {}

bus::bus(): transportation(0, 2.50) {}
bus::~bus() {} 

void transportation::create_pop_list() {} 
void lyft::create_pop_list()
{
  char temp[]  = "Morning Rush Hour Typically has a +50 percent surcharge, but drivers arrive in under 10 minutes"; 
  my_pop.insert(1, temp);
  char temp2[] = "At approx. noon is slowest time generally, will have no surcharge and drivers should arrive in 5 minutes or less";
  my_pop.insert(2, temp2);
  char temp3[] = "Evening rush hour is the busiest time, +100 percent surcharge many days, but drivers still arrive in approx 10 minutes";
  my_pop.insert(3, temp3); 
  char temp4[] = "Lat night on Friday and Saturday nights typically have a +50 - +100 surcharge depending on weather and local events";
  my_pop.insert(4, temp4);
} 


void max_st::create_pop_list()
{
  char temp[]  = "Morning Rush Hour Typically is the second busiest time, many trains are riding at 70-85 percent capacities and run 5-10 minutes slower than average"; 
  my_pop.insert(1, temp);
  char temp2[] = "At approx. noon is slowest time generally, trains are riding at 20-35 percent capacity and run at the average rate";
  my_pop.insert(2, temp2);
  char temp3[] = "Evening rush hour is the busiest time, trains are riding at over 90 percent capacity and can experience delays upward of 20 minutes to normal travel time";
  my_pop.insert(3, temp3); 
  char temp4[] = "Max trains stop running Friday and Saturday Nights at midnight except for New Years Eve, Halloween and Fourth of July, when trains run until 2:00am";
  my_pop.insert(4, temp4);
}


void bus::create_pop_list()
{
  char temp[]  = "Morning Rush Hour Typically the second busiest time, many busses are riding at 60-80 percent capacity and run 5 minutes slower than average"; 
  my_pop.insert(1, temp);
  char temp2[] = "At approx. noon is slowest time generally, busses run at about 20 percent capactiy and run at the average rate";
  my_pop.insert(2, temp2);
  char temp3[] = "Evening rush hour is the busiest time, busses are riding at over 90 percent capacity and can experience delays upward of 20 minutes to normal travel times";
  my_pop.insert(3, temp3); 
  char temp4[] = "Busses stop running Friday and Saturday nights at midnight expecpt for New Years Eve, Halloween and Fourth of July, when bussses run until 2:00 am";
  my_pop.insert(4, temp4);
}

//popularity class member functions
//insert, remove, display,remove_all, display

//returns the transpo base class pointer
//because protected, wrapper function
transportation *& pop_info::get_ptr()
{
  return ptr;
}

// creates the dynamic binding by upcasting
//the base class pointer to the derived types.
int popularity::insert()
{
   array[0].get_ptr()  = new lyft;
   array[0].get_ptr()->create_pop_list();
   array[1].get_ptr() = new max_st;
   array[1].get_ptr()->create_pop_list();
   array[2].get_ptr() = new bus;
   array[2].get_ptr()->create_pop_list();
   return 1; 
}

int popularity::remove(int index)
{
   if(array[index].get_ptr() != NULL)
       delete array[index].get_ptr();
   return 1;
}

void popularity::display(int index)
{
   array[index].get_ptr()->display();
}

int popularity::retrieve(int index, pop_info &to_copy)
{
    
    to_copy.get_ptr() = array[index].get_ptr();
    return 1; 
}

int popularity::remove_all()
{
   for(int i = 0; i < POP_MAX;  ++i)
   {
      if(array[i].get_ptr() != NULL)
      {
          delete array[i].get_ptr();
      }
   }
   if(array != NULL)
      delete [] array;

   array = NULL; 
   return 1; 
}

void popularity::display_list(int index)
{
   array[index].get_ptr()->display_pop_list();
}

void transportation::display_pop_list()
{
    my_pop.display();
}

void l_node::set_null()
{
    next = NULL;
}

void l_node::set_next(l_node *& head)
{
   next = head;
}

l_node*& l_node::get_next()
{
   return next;
}

int l_node::get_time()
{
  return time_of_day;
}

void l_node::display()
{
   if(time_of_day == 4)
     cout << "Travel Time: : Late Night Weekend: " << endl;  
   if(time_of_day == 3)
     cout << "Travel Time: Evening Rush Hour: " << endl;
   if(time_of_day == 2)
     cout << "Travel Time: Noon : " << endl;
   if(time_of_day == 1)
     cout << "Travel Time: Morning Rush Hour: " << endl; 
   cout << "What to Expect: " << description << endl;
}

int list::insert(int time, char * desc)
{
   if(head == NULL)
   {
      head = new l_node(time, desc);
      head->set_null(); 
      return 1;
   }
   else
   {
      l_node * temp = new l_node(time, desc);
      temp->set_next(head);
      head = temp;
      return 1;
   }
}

int list::remove(int time)
{
   return remove(time, head);
}

int list::remove(int time, l_node *& head)
{
   if(!head)
      return 0;

  if(head->get_next() == NULL)
  {
     if(head->get_time() == time)
     {
       delete head;
       head->set_null();
       return 1;
     }
  }
  remove(time, head->get_next()); 
  return 0; 
}

void list::display()
{
   display(head); 
}

void list::display(l_node * head)
{

   if(!head)
       return;

   head->display();
   display(head->get_next()); 
}

int list::remove_all()
{
    if(!head)
        return 0;
    l_node * temp;
    while(head != NULL)
    {
      temp = head;
      head = head->get_next();
      delete temp;
    }
    return 1; 
}

int list::retrieve(int time)
{
   if(!head)
      return 0;

   while(head != NULL)
   {
      if(head->get_time() == time)
      {
         head->display(); 
	 return 1;
      }
   }
   return 0; 
} 
