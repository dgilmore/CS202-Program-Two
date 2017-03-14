//David Gilmore Program#2 CS202 WINTER 2017
//This is my header file for all of my classes. It 
//seems really big but I found it easier to keep track
//of all of my classes in one place. I have a class for my
//base class and it's derived functions. I have classses to 
//build my stack, including a node and history class. I have a
//class for my array of base class pointers and it's neccesary
//classes including a list class for the popularity list. 
#ifndef TRANSPORTATION_H
#define TRANSPORTATION_H
const int MAX = 5;//max size of the rider_history stack array 
const int POP_MAX = 3;//the size of my base class pointer array 
class rider_history;//forward declartation
class popularity;//forward declartation

//node for a popularity list object
//holds the time of day and description
//for each of the types of transportation
class l_node
{
   public:
       l_node();
       ~l_node();
       l_node(int time, char * desc); 
       void set_null();//sets the current node to next ptr
       void set_next(l_node *& head);//set current node to arg
       void display();//display function
       l_node*& get_next();//return current node next ptr
       int get_time(); //returns time data member
   protected:
       int time_of_day;//int indicator for time of day
       char * description; //description of rider amount at time of day
       l_node * next; //next ptr
};


//list class will be how a user can see how busy a certain
//transpo type is at a given time. 
class list
{
   public:
        list();
	~list();
        int insert(int time, char * desc);
	int remove(int time); 
	void display();	
	int retrieve(int time);
	int remove_all(); 
    protected:
          int remove(int time, l_node *& head);
	  void display(l_node * head); 
          l_node * head; 
};

// My abstract base class, will have the data members 
//basic functions for the user to find info about which 
//transportation choice they want to use. 
class transportation
{
   public:
	transportation();
	transportation(int tran_status, int tran_cost);//arg constructor 
	virtual	~transportation();
	void display();
	int status();//return the transpo's current status(1 = perfect, 2 = slow, 3 = reroute etc)
	virtual float cost() = 0;//returns the transpo's cost per ride in float form. 
        virtual void create_pop_list(); 
	void display_pop_list(); 
   protected:
        int tran_status; //holds status
        float tran_cost;//holds cost per ride
	list my_pop;//head to the pop list  
};


//derived class for the lyft object
class lyft: public transportation
{
    public:
        lyft();
	~lyft();
	float cost();//overridden cost function
	void create_pop_list(); 
		
    protected:
};


//derived class for the max object
class max_st: public transportation
{
   public: 
       max_st();
       ~max_st();
       float cost();//overridden cost function 
       void create_pop_list();	
   protected:
};


//derived class for the bus object
class bus: public transportation
{
    public:
	bus();
	~bus();
        float cost();//overridden cost function 
        void create_pop_list(); 
    protected:

};

class history;//forward declaration 

//rider history is an linked list of arrays
//this class is basically a node and each node
//will have the pointer to a array of type 
//history, which is why I forward declared the history class. 
class node;
class rider_history
{
   public:
	rider_history();
	~rider_history(); 
	int push(history & to_add);//adds a history obj to top of the stack
	int copy(history & to_add);//copies the history obj sent as an arg 
	int pop(history & to_switch);//copies obj on top of stack and moves index past
	void display();//displays the top object on the stack
	int peek(history &to_see);//makes a copy of the obj on top of stack but does not remove
	int remove_all();//blows up the stack. 

   protected:
	node * head;//head pointer to the stacks nodes
	int top_index;//current index for the array on the top of stack 
};

//the history class is an object that holds the data for the
//user review of history. A node wraps around it but there is no
//derision
class history
{
   public:
	history();
        history(int type, int rating_s);
	// history(const &history copy);
	~history();
	void copy(history &to_copy); //makes a copy of a history obj
	void display();//displays one history object
	void set_rating(int r);//wrapper to set the rating data
	void set_type(int t);//wrapper to set the type data
	int get_type();//wrapper to return the type data
	int get_rating();//wrapper to return the rating data 

   protected:
	 int transpo_type;
	 int rating;
};

//node wraps a history obj and lets the rider_history class
//work with a history object. 
class node
{
   public:
	history *& get_index(int index);
	void make_array();//dynamic allocation of the stack array 
	void array_data(int index, history &to_add);//sets array data from history obj sent as arg
	void receive_data(int index, history &to_copy);//returns by reference the data at a index. 
	node *& get_next();//returns the current nodes next pointer by reference.
	void set_next();//sets the current nodes next to null
	void set_top_next(node *&head);//when the top node and array destroyed sets head to next node
	history *& get_array();//returns array pointer 
	void display(int index);//displays a node data 

   protected:
	node * next;
	history * array; 
};


class pop_info;//forward declaration
 
//this is the array of linked lists holding base class pointers
//this is where the dynamic binding will take place by making the 
//base reference pointer point to a derived class we then can access
//all the memeber functions and data for those classes to tell the user
//info about the ride they want to take. 
class popularity
{
   public:
	popularity();
	~popularity();
	int insert();//inserting new transpo types into array
	int remove(int index);//removing a transpo type from the array
	void display(int index);//displaying the transpo types
	int retrieve(int index, pop_info &to_get);//retrieving the transpo types
	int remove_all();//blowing up the structure for program shutdown 
        void display_list(int index);
   protected:
         pop_info * array;//array holding class pop info obj, which point to base class and head pointer
	 int info_index;//index of this array 
};

//this is the obj of the above array, holds pointer to a base
//class object. When a user says for what transpo type they want
//info for, we can search the array and then display all the class
//info using dynamic binding.
class pop_info
{
   public:
	pop_info();
	~pop_info();
        //wrapper functions to use 
	//the transpo class functions
	// and list class functions 
        transportation*& get_ptr(); //returns pointer to the base class obj
 
 protected:
	transportation * ptr;
}; 

//class controller just provides the client class with another level of 
//abstraction so really the client doesn't know about how our classes are 
//doing their work, the client can just call the given functions.
class controller
{
    public:
	void make_history();//creates the rider_history data structure
	void display_history();//displays stored rider_history 
	void history_menu();//gives user options about adding, removing history
	void end_program();// calls all of the remove_all functions for our 
	                   //data structures so there are no memory leaks.
        void make_pop();
	void pop_menu();
	//void options_menu(); 
    protected:
       rider_history my_history; //rider history object
       popularity my_transpo; 
}; 

#endif 


	   
