/********************************
 ** File: proj1.cpp
 ** Project: CMSC 202 Project 1, Fall 2017
 ** Author: Enzo Walker
 ** Date: 9/17/2017
 ** Section: 1093, Discussion: 1095
 ** Email: enzow1@umbc.edu
 **
 ** This file is the driver program for Project 1. 
 ** The program creates a kiosk menu for True Grits with items and prices.
 ** Then the program computes an order with a max of 3 items with a subtotal, total and tax.
 ** This is done through a file which holds the menu items and corrosponding item prices.
 **
********************************/
#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>

using namespace std;
const int TOTAL_AMOUNT_FILE_ITEMS = 10; //Max amount of items in the file being read
const double SALES_TAX = .06; //Sales tax on purchases
const int MAX_AMOUNT_ORDER_ITEMS = 3; //Max amount of items per order

//Function Prototype

//-------------------------------------------------------------------------------------------
//Name: loadArrays
//PreCondition: The user decides to create a new order. "1" was entered at the main menu
//PostCondition: The menu will be loaded into the two array parameters
//-------------------------------------------------------------------------------------------
void loadArrays(string itemNames[], double itemPrices[]);

//-------------------------------------------------------------------------------------------
//Name: manageOrder
//PreCondition: The user decides to create a new order. "1" was entered at the main menu
//PostCondition: The order was entered with the information being stored in the 2D Array
//-------------------------------------------------------------------------------------------
void manageOrder(string itemNames[], double itemPrices[], int loadedOrder[3][2]);

//-------------------------------------------------------------------------------------------
//Name: printReceipt
//PreCondition: The user is done ordering
//PostCondition: Order is displayed on terminal w/ subtotal, total, and tax.
//-------------------------------------------------------------------------------------------
void printReceipt(int loadedOrder[3][2], string itemNames[], double itemPrices[]);

//-------------------------------------------------------------------------------------------
//Name: saveReceipt
//PreCondition: The order is completed and displayed on the screen
//PostCondition: Order is saved in a file called "proj1_old_receipt.txt" with the same format as the receipt
//-------------------------------------------------------------------------------------------
void saveReceipt(int loadedOrder[3][2], string itemNames[], double itemPrices[]);

//-------------------------------------------------------------------------------------------
//Name: loadOldReceipt
//PreCondition: Option #2 was pressed at the main menue. The user wants to load their old receipt
//PostCondition: The previous order stored in the "proj1_old_receipt.txt" file is printed on the screen
//-------------------------------------------------------------------------------------------
void loadOldReceipt();

int main(){

  //Variables
  double itemPrices[TOTAL_AMOUNT_FILE_ITEMS] = {}; //Holds the prices
  string itemNames[TOTAL_AMOUNT_FILE_ITEMS] = {}; //Holds the item names
  int loadedOrder[MAX_AMOUNT_ORDER_ITEMS][2] = {{0}}; //Will hold the item number and quantity for a max of three orders
  int choice = 0;
  
  //Will always loop until the user decides to exit
  do{

    do{
      cout << "------------------------------------------------------------" << endl;
      cout << "Welcome to True Grit Snack Bar \nWhat would you like to do?:" 
	   << "\n1. New Order\n2. Load Recepit\n3. Exit"
	   <<"\n------------------------------------------------------------" << endl;
  
      cin >> choice;

     //Validates input to be between 1 and 3
    }while(choice < 1 || choice > 3); //Loops until the choice inputted is between 1 & 3

    //Switches based on the choice selected
    switch(choice){

    case 1:

      loadArrays(itemNames, itemPrices);
      manageOrder(itemNames, itemPrices, loadedOrder);
      printReceipt(loadedOrder, itemNames, itemPrices);
      saveReceipt(loadedOrder, itemNames, itemPrices);
      break;

    case 2:

      loadOldReceipt();
      break;

    case 3:

      cout << "Thank you for choosing True Grit Snack Bar" << endl;
      break;

    }
    //Loops until the user decides to exit

  }while(choice != 3);


  return 0;

}


//loadArrays
//Given the arrays for names and prices. Loads the values into the corrosponding names and prices arrays.
void loadArrays(string itemNames[], double itemPrices[]){

  //Sets the precision to 2 decimal places
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);
  
  //Opens the input stream
  ifstream inputStream;
  inputStream.open("proj1_items.txt");
  
  //Used for formatting
  cout << setw(5) << "Number" << setw(20) << "Item" << setw(12) << "Price" <<  endl;



  //Iterates through the indexes of the parallel arrays
  for(int i = 0; i < TOTAL_AMOUNT_FILE_ITEMS; i++){
    
    //Reads up until the , delimiter
    getline(inputStream, itemNames[i], ',');
    //Reads the rest of the line into the itemPrices array
    inputStream >> itemPrices[i];
    //Ignores the new line character
    inputStream.ignore(10, '\n');
    
    //Used for formatting
    cout << setw(5) << i+1 << "." << setw(20) << itemNames[i ] << setw(10) <<"$" << itemPrices[i] << endl;
  }

  cout << "------------------------------------------------------------" << endl;
  inputStream.close();


}


//manageOrder
//Given item names and prices array and a 2D Array to store the item number and quantity
void manageOrder(string itemNames[], double itemPrices[], int loadedOrder[3][2]){

  //Variables
  int orderNumber;
  int currAmountOfItems = 0; //Holds the current amount of items as the order continues
  double orderQuantity = 0;
  char yesOrNo;
  int arrayRowCount = 0, arrayColumnCount = 0;


  //Runs once, then runs again based on if we're at max order or if 'n' is entered
  do{
    
    //Order number input validation
    do{	
      cout << "What would you like to buy?: ";
      cin >> orderNumber;
      //Validates input is between 1 and 10
    }while(orderNumber < 1 || orderNumber > 10);
    
    //Quantity input validation
    do{
      cout << "How many would you like to buy?: ";
      cin >> orderQuantity;
      //Makes sure a positive order quantity is entered
    }while(orderQuantity < 0);

    currAmountOfItems++;

    
    //Used for constant looping after all operations are completed
    //If there is an item in the array index, set the value to 0
    if(loadedOrder[arrayRowCount][arrayColumnCount] > 0 ){

      for(int i = 0; i < 3; i++)
        for(int j = 0; j < 2; j++)
          loadedOrder[i][j] = 0;

    } 

    
    //Checks to see if the array index is empty and also iterates through the rows and columns
    if(loadedOrder[arrayRowCount][arrayColumnCount] == 0){
      //Order number is in column index 0 and order quantity is in column index 1
      arrayColumnCount = 0;

      loadedOrder[arrayRowCount][arrayColumnCount] = orderNumber;
      arrayColumnCount++;
      loadedOrder[arrayRowCount][arrayColumnCount] = orderQuantity;

      arrayRowCount++;
    }
    


    //Operates only if we aren't at the max amount of items
    if(currAmountOfItems != MAX_AMOUNT_ORDER_ITEMS){
      
      //y or n input validation
      do{
	cout << "Do you want to add more items? (y/n): ";
 	cin >> yesOrNo;
	//loops unti y or n is entered
      }while(yesOrNo != 'y' && yesOrNo != 'n');
      cout << endl;

    }

    //Loops as long as Y is entered and we aren't at the max amount of orders
  }while((currAmountOfItems != MAX_AMOUNT_ORDER_ITEMS ) && (yesOrNo == 'y'));

}

//printReceipt
//Given item names and prices array and loadedOrder array. Outputs user's order and subtotal, total and tax.
void printReceipt(int loadedOrder[3][2], string itemNames[], double itemPrices[]){

  //Variables
  int itemNumber = 0;
  int itemQuantity = 0;
  int col = 0;
  double subTotal= 0;
  double total = 0;


  //Formatting
  cout << "------------------------------------------------------------"
       << "\nYour Order: \n" << endl;
  cout << "Qnty" << setw(20) << "Item" << setw(10) << "Price" << endl;




  //Loops through the 2D Array
  for(int row = 0; row < 3; row++){
    col = 0;
    //Only adds non 0 values to the output of the receipt
    if(loadedOrder[row][col] != 0){
      //Column 0 holds the Item Number
      itemNumber = loadedOrder[row][col];
      col++;
      //Column 1 holds the Item Quantity
      itemQuantity = loadedOrder[row][col];
      subTotal += itemPrices[itemNumber-1] * itemQuantity;
      cout << setw(5) << itemQuantity << setw(20) << itemNames[itemNumber-1] << setw(10) <<"$"<< itemPrices[itemNumber-1] << endl;
    }
  }


  
  //Calculates the total
  total = (subTotal + (subTotal * SALES_TAX));
  //Formatts the output
  cout << "\nSubtotal: $" << subTotal << "\n" << "Tax: $" << subTotal*SALES_TAX << "\n" << "Total: $" << total << endl;
  cout << "\nThank you for choosing True Grit" << endl;



}

//saveReceipt
//Given item names and prices array and a parallel 2D array. Stores the order in the same format as the receipt
void saveReceipt(int loadedOrder[3][2], string itemNames[], double itemPrices[]){

  int itemNumber = 0;
  int itemQuantity = 0;
  int col = 0;
  int total = 0;
  int subTotal = 0;

  
  //Opens the "proj1_old_receipt.txt" file for writing
  ofstream outputStream;
  outputStream.open ("proj1_old_receipt.txt");
  outputStream.precision(3);


  //Used for formatting
  outputStream << "Qnty" << setw(20) << "Item" << setw(10) << "Price" << endl;




  //Iterates through 2D Array, storing only non 0 values in the same format as the receipt
  for(int row = 0; row < 3; row++){
    col = 0;
    //Only adds non 0 values to the output of the receipt
    if(loadedOrder[row][col] != 0){
      itemNumber = loadedOrder[row][col];
      col++;
      //Column 1 holds the Item Quantity
      itemQuantity = loadedOrder[row][col];
      subTotal += itemPrices[itemNumber-1] * itemQuantity;
      outputStream << setw(5) << itemQuantity << setw(20) 
		   << itemNames[itemNumber-1] << setw(10) << "$" << itemPrices[itemNumber-1] << endl;
    }
  }



  //Used to calculate the total
  total = (subTotal + (subTotal * SALES_TAX));
  //Used for formatting
  outputStream << "\nSubtotal: $" << subTotal << "\n" << "Tax: $" << subTotal*SALES_TAX << "\n" << "Total: $" << total << endl;
  
  outputStream.close();

}

//loadOldReceipt
//Has no parameters and is used to print the contents of the "proj1_old_receipt.txt"
void loadOldReceipt(){


  //Opens the file and prints out the stream buffer.
  ifstream inputStream;
  inputStream.open("proj1_old_receipt.txt");
  inputStream.precision(3);
  //The project was saved formatted
  cout << inputStream.rdbuf();


}
