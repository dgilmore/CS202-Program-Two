//David Gilmore Program # 2 CS202 WINTER 2017
//This is the implementation file for my rider
//history class, the history object class and
//it's node class. Also in this classare the 
//implementations for my controller class.  
#include "transportation.h"
#include <cctype>
#include <cstring>
#include <iostream>
using namespace std; 


//history obj default constructor
history::history()
{
   transpo_type = 0;
   rating = 0;
}

//history obj arg constructor
history::history(int type, int r)
{
    transpo_type = type;
    rating = r;
}

//history class default destructor
history::~history()
{
   transpo_type = 0;
   rating = 0; 
}

//returns current nodes next pointer
node*& node::get_next()
{
   return next;
}

//sets current node next to null
void node::set_next()
{
   next = NULL;
}

//creats a dynamic array which will
//hold history objects on the stack
void node::make_array()
{
   array = new history[MAX];
}

//sets the array at index type and status 
//from hist obj sent as an argument.
void node::array_data(int index, history &to_add)
{
    int r = to_add.get_rating();
    int t = to_add.get_type();
    array[index].set_type(t);
    array[index].set_rating(r);
}

//returns data by reference in history obj sent as arg
void node::receive_data(int index, history &to_copy)
{
	int r = array[index].get_rating();
	int t = array[index].get_type();
	to_copy.set_type(t);
	to_copy.set_rating(r);
}

//when a node and array are removed this
//sets the current nodes next to head
void node::set_top_next(node *& head)
{
	next = head;
}

//returns a pointer by ref. of the array
history *& node::get_array()
{
   return array;
}

//copies a history obj from obj sent as arg
void history::copy(history &to_copy)
{
	transpo_type = to_copy.transpo_type;
	rating = to_copy.rating;
}

//displays current history obj on top of stack
void node::display(int index)
{
   if(array[index].get_type() == 1)
      cout << "Transportation Type: Lyft " << endl;
   if(array[index].get_type() == 2)
      cout << "Transportation Type: Max " << endl; 
   if(array[index].get_type() == 3)
      cout << "Transportation Type: Bus " << endl;
  
   cout << "Your Rating: " << array[index].get_rating() << endl;
}

//wrapper to set rating data
void history::set_rating(int r)
{
    rating = r;
}

//wrapper to set type data
void history::set_type(int t)
{
    transpo_type = t;
}

//returns the type 
int history::get_type()
{
   return transpo_type;
}

//returns the rating
int history::get_rating()
{
   return rating;
}

//rider hist constructor
rider_history::rider_history()
{
   head = NULL;
   top_index = 0;
}

//rider history destructor
rider_history::~rider_history()
{
   if(head != NULL)
	delete head;
   top_index = 0;
}

//rider history copy function, recieves
//hist obj and saves its data into array
int rider_history::copy(history & to_add)
{
	head->array_data(top_index, to_add);
        return 1; 
}


//puts the history object added to the top of the
//stack. 
int rider_history::push(history & to_add)
{
    if(head == NULL)//if no stack creat node and array
    {
       head = new node;
       head->make_array();
       head->set_next(); 
       copy(to_add);
       ++top_index;
       return 1;
    }
    if(top_index == MAX)//if current stack is full creat new node and array
    {
       top_index = 0;
       node * temp = new node;
       temp->set_top_next(head);
       head = temp; 
       head->make_array();
       copy(to_add);
       ++top_index;
       return 1;
    }
    else//if room left in current array stack add at current index and move index
    {
      copy(to_add);
      ++top_index;
      return 1;
    }
    return 0;
}

//displays the stack
void rider_history::display()
{
    head->display(top_index - 1); 
}


//sends the data of the obj on top of the stack then moves index, in effect removing that obj
int rider_history::pop(history &to_switch) 
{
	if(!head)//if head is null nothing to pop, leave. 
	   return 0;
        
	if(head->get_next() == NULL)//if last obj in stack, remove node and array
	{
	   if(top_index == 1)
	   {
		   head->receive_data(top_index, to_switch);
		   delete [] head->get_array();
		   delete head;
		   head = NULL;
		   top_index = 0;
		   return 1;
	   }
	}

	if(top_index == 1)//if last obj in array of stack, remove array and move head to head next
	{
		node * temp = head->get_next();
		head->receive_data(top_index, to_switch);
                delete [] head->get_array();
		delete head;
		head = temp;
		top_index = MAX; 
		return 1; 
	}

	if(top_index > 1 && top_index < 5)// if not edge case just move index
	{
		head->receive_data(top_index, to_switch); 
		--top_index;
		return 1;
	}
        else return 0;
}

//sends info from obj at top of the stack to hist
//obj sent as arg
int rider_history::peek(history &to_see)
{
    if(head == NULL)
	    return 0;
    else
    {
	head->receive_data(top_index, to_see);
	return 1;
    }
}

//blows up the stack, needs to use wrapper
//functions such as get_next and set_next to
//gain access to the history obj
int rider_history::remove_all()
{
    if(head == NULL)
	return 1;

    if(head->get_next() == NULL)
    {
       if(head->get_array() != NULL)
       {
	  delete [] head->get_array();
       }
       delete head;
       head = NULL;
       return 1;
    }

    else
    {
       node * temp;
       while(head != NULL)
       {
	  temp = head->get_next();
	  delete [] head->get_array();
	  delete head;
	  head = temp;
       }
       return 1;
    }
}

//creates a rider history so we have something
//to work with
void controller::make_history()
{
  history my_his(1,5);
  my_history.push(my_his);
  history aa_his(3,5);
  my_history.push(aa_his);
  history bb_his(2,4);
  my_history.push(bb_his); 
}

//menu of options for the rider history
//data structure.
void controller::history_menu()
{
   char answer = 'Y';
   char menu;
   int rating, type;
   while(answer == 'Y')
   {
     cout << "This is your Rider History Menu: Enter the Option you'd like to use" << endl;
     cout << "A - add to rider history: " << endl;
     cout << "D - display your history: " << endl;
     cout << "R - remove last history: " << endl;
     cin >> menu;
     menu = toupper(menu);
     if(menu == 'A')
     {
       cout << "Enter the tranportation type: 1 - Lyft, 2 - Max, 3 - Bus" << endl; 
       cin >> type;
       cout << "Enter a star rating between 0 and 5 for this ride experience:" << endl;
       cin >> rating;
       history new_add(type,rating);
       my_history.push(new_add); 
     }
     
     if(menu == 'D')
         display_history();

     if(menu == 'R')
     {
         history trash;
	 my_history.pop(trash);
     }

     cout << "Would you like to see the menu again? " << endl;
     cin >> answer; 
     answer = toupper(answer); 
  }
}

// display the stack, basically a wrapper 
void controller::display_history()
{
   my_history.display();
}

//will call all of the remove all functions
//so our program will hopefully end with no
//memory leaks. 
void controller::end_program()
{
   int i = my_history.remove_all();
   int j = my_transpo.remove_all(); 
   if(i == 1 && j == 1) 
     cout << "Program End Successful: " << endl;
   else
     cout << "Program End Error: List Not terminated " << endl;
}

//creates the array of population pointers
//and dynamically binds them to the derived
//classes for the 3 types of transpo
void controller::make_pop()
{
   my_transpo.insert(); 
}


//population menu, gives options
//for the array of base class pointer ands 
//lets the user choose to display cost, status
//or display all the time descriptions
void controller::pop_menu()
{
   char answer = 'Y';
   char menu;
   int tt;


   while(answer == 'Y')
   {
     cout <<" Welcome to the Transit Assist: ";
     cout <<" What transit type would you like to look at?" << endl;
     cout <<" Type 1 for lyft, 2 for the Max and 3 for Busses" << endl;
     cin >> tt;

     if(tt == 1)//choose the lyft menu 
     {
        cout << "You have selected Lyft: " << endl;
	cout << "Would you like to:  A - See the Cost and Status of of current Lyft's" << endl;
	cout << "                    B - See the popularity of Lyft's at all times" << endl;
	cin >> menu;
	cin.ignore(100, '\n');

	menu = toupper(menu);

	if(menu == 'A')
	 {
	    my_transpo.display(0);
	 }

        else
         my_transpo.display_list(0); 
      }

      if(tt == 2)//choose Max menu
      {
        cout << "You have selected MAX: " << endl;
	cout << "Would you like to:  A - See the Cost and Status of of current MAX" << endl;
	cout << "                    B - See the popularity of MAX at all times" << endl;
	cin >> menu;
	cin.ignore(100, '\n');

        menu = toupper(menu);

	if(menu == 'A')
	 {
	    my_transpo.display(1);
	 }

        else
         my_transpo.display_list(1); 
      }

      
      if(tt == 3)//choose max menu 
      {
        cout << "You have selected BUS: " << endl;
	cout << "Would you like to:  A - See the Cost and Status of of current BUS" << endl;
	cout << "                    B - See the popularity of BUS at all times" << endl;
	cin >> menu;
	cin.ignore(100, '\n');

        menu = toupper(menu);

	if(menu == 'A')
	 {
	    my_transpo.display(2);
	 }

        else
         my_transpo.display_list(2); 
      }

      cout << "Would you like to see the menu Again? Y/N: " << endl; 
      cin >> answer;
      answer = toupper(answer);
    } 
} 

