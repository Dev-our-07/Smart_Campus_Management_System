/* Implementation of basic menu */

#include <iostream>
#include <string>
#include "Logger.h"
using namespace std;

int main(){
    // Logger start and log file set
    Logger logger("logs/events.log");
    //1. Welcome Message
    cout<<"==============O(n v n)O==============="<<endl<<endl;

    cout<<"Welcome to Smart Campus Management System"<<endl;
    cout<<"Kindly read the instructions and choose your option to interact further with the system."<<endl<<endl;

    //Break line
    cout<<"==============O(n v n)O==============="<<endl;

    //2. Main Menu
    cout<<endl<<"M A I N     M E N U"<<endl<<endl;

    cout<<"Select the corresponding number to access the feature:"<<endl;
    cout<<"1. Login"<<endl;
    cout<<"2. Register"<<endl;
    cout<<"3. Exit"<<endl;
    int choice;
    cout<<endl<<"Enter your choice: ";
    cin>>choice;

    //Switch-case structure to handle user choice
    switch(choice)
    {
        case 1:
            cout<<endl<<"You have chosen to Login."<<endl;
            //Login functionality would be implemented here
            //////////////////////////////  

            logger.log("INFO", "User attempted to log in.");
            break;

        case 2:
            cout<<endl<<"You have chosen to Register."<<endl;
            //Registration functionality would be implemented here
            /////////////////////////////

            logger.log("INFO", "User attempted to register.");
            break;

        case 3:
            cout<<endl<<"Exiting the system. Goodbye!"<<endl;
            //Ends the program
            logger.log("INFO", "User exited the system.");
            break;

        default:
            cout<<endl<<"Invalid choice. Please restart the program and select a valid option."<<endl; 
            //Handles invalid input and breaks out of the switch-case
            logger.log("WARNING", "User entered an invalid choice in the main menu.");
    }



    return 0;
}