//David Gilmore Program # 2 CS202 Winter 2017
//this is my client file for the program. This just
//creates my controller class and then calls it's member
//functions to do everything. This lets all of my classes
//have one last level of abstration so the client really
//doesn't need to know how my program works only how to kick off
//each task.

#include "transportation.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std; 

int main() {

  controller my_controller;//creates controller class
  my_controller.make_history();//makes the history data structure
  my_controller.make_pop();//makes the population array of base class pointers
                           //and creates the LLL of population lists

  int menu;
  char ans = 'Y';
  
  cout << "Welcome to Transit Assist: " << endl;
  while(ans == 'Y')
  {
    cout << "*************TRANSIT MENU*******************************" << endl; 
    cout << "Press 1 to see information about our three transit types: " << endl;
    cout << "Press 2 to see your previous rider history" << endl;
    cin >> menu;
    cin.ignore(100, '\n');

    if(menu == 1)
    {
      my_controller.pop_menu();//controls the menu for our population array
    }

    if(menu == 2)
    {
      my_controller.history_menu();//controls the menu for rider history menu 
    }

    cout << "Would you like to see the transit menu again?" << endl;
    cin >> ans;
    cin.ignore(100, '\n'); 
    ans = toupper(ans);
  }

  my_controller.end_program();//calls the data strucutes remove_all functions 
  return 0;
}
	
