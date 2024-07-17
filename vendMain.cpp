#include <iostream>
#include <string>
#include<iomanip>
#include "Queue.h" 

using namespace std;
//Function Prototype
void displayMenu(); //display Main Menu Function
void showItems(int numStock,string stockName[],int stockPrice[],char itemSymbol[]);//show the available item in the vend Function
void adminMenu(int &numStock);//Admin Menu 
void changeStockHeader (string stockName[]);//Change stock header
void changeTitle(string &title);//Change Main Title
bool exchangeMoney(int stockNumber, int quantity, int &funds);//Payment Function
void changePrice (int stockIndex, int newPrice,int stockPrice[]);//Change price Function
void addFunds(int amount);//Add Funds Function
void displaySummary(int numStock);//Print Machine Summary Function
void addStock(string stockName[], char itemSymbol[],int stockPrice[], int &numStock);//Add Stock Function
void changePwd(string &correctPwd);//Change Password Function


//Declaration of Global Variable

//Declare Queue named stock1-stock5 
Queue<char> stock1(20);
Queue<char> stock2(20);
Queue<char> stock3(20);
Queue<char> stock4(20);
Queue<char> stock5(20);

int numStock = 3; //Initialise number of Stock=3

//Array to store Stock Name(Stock header)
//For the "Stock 4" and "Stock 5" are the initialise name for stock4 and stock5;
string stockName[5] = {"Stock 1", "Stock 2", "Stock 3","Stock 4","Stock 5"};

//Array to store Stock Name
//For the "A" and "B" are the initialise symbol for stock4 and stock5;
char itemSymbol[5] = {'P', 'C', 'M','A','B'};
bool flag2 = false;//control the looping for Restock Function

//Array to store Stock Price
//For the 0 at index 3 and index 4 are the initialise price for stock4 and stock5;
int stockPrice[5] = {2, 3, 1,0,0};

int restock = 0;  // Initialize stock Number that need to restock
int choice; //use to choose the Main Menu Function
int quantity; //Buying Quantity
bool status; //Transaction Status
int funds=200; //Initialise Vending Machine Funds to 200
string title = "INTI Vending Machine";  //Initialise Vending Machine title to [INTI Vending Machine]
string correctPwd="abcd";//Initialise Correct Password for Admin

int main(){
	//Enqueue the symbol store in itemSymbol array
	//intro stock1 to stock3 using for loop respectively
	for(int i=0;i<20;i++){
		stock1.enQueue(itemSymbol[0]);
		stock2.enQueue(itemSymbol[1]);
		stock3.enQueue(itemSymbol[2]);
	}
	
	string adPassword; //Variable for admin password
    // Main Program start
    do {
		cout <<"[ " << title << " ]" << endl; //print Vend Title
    	
        displayMenu(); // call the displaymenu function first, let the user to select what they want 
        cin >> choice;//User input number to select function
        
        //switch case for Main Function
        switch (choice) {
			case 1:
				{
				bool cancelBuy=false;	
    			showItems(numStock, stockName, stockPrice,itemSymbol); // show the item 
    			// enter which stock buyer want to buy 
    			cout << "Enter stock number to purchase: "; 
    			int stockNumber;
    			cin >> stockNumber;
    			while (stockNumber <=0 ||stockNumber>numStock ) {
        			cout << "Invalid Stock Number. Do you want to cancel the order? (y/n): ";
        			char choice;
        			cin >> choice;
		
				//if buyer wish to cancel their order, the system will back to main menu
        			if (choice == 'y' || choice == 'Y') {
            			cout << "Order cancelled." << endl<<endl;
            			cancelBuy=true;
						break;
        			//else system will prompt to let user continue pto choose the correct stock
        			} else {
            			cout << "Enter stock number to purchase: ";
            			cin >> stockNumber;
        			}
    			}

    			
    			//check whether the buyer have selected the selling stock
    			//if buyer have selected the selling stock
    			if(cancelBuy==false){
    				bool cancelBuy2=false;
    				if (stockNumber <= numStock) {
        			cout << "Please enter quantity of the item: "; // ask buyer how many items to buy 
        			cin >> quantity;
        			
        			//if buyer input the quantity which is less than or equal to 0,
        			//system will confirm with buyer whether they want to continue or not
        			while (quantity <=0) {
        				cout << "Invalid Quantity. Do you want to cancel the order? (y/n): ";
        				char choice;
        				cin >> choice;
		
						//if buyer wish to cancel their order, the system will back to main menu
        				if (choice == 'y' || choice == 'Y') {
            				cout << "Order cancelled." << endl<<endl;
            				cancelBuy2=true;
							break;
        				//else system will prompt to let user continue to enter the valid quantity
        				} else {
            				cout << "Please enter quantity of the item: ";
            				cin >> quantity;
        				}
    				}
        			if(cancelBuy2==false){
					
        				// Check if the stock is available before proceeding to payment
        				bool isSoldOut = false; //initialise the isSoldOut condition to false
        			
        				//switch case to determine the representing stock sold out or not
        				//if the number of item in stock is less than the quantity 
            			//of the buyer need, the isSoldOut will set to true
        				switch (stockNumber) {
            				case 1:
                				if (stock1.getNumItem() < quantity) {
                    				isSoldOut = true; 
               					}
                				break;
            				case 2:
                				if (stock2.getNumItem() < quantity) {
                    				isSoldOut = true;
                				}
                				break;
            				case 3:
                				if (stock3.getNumItem() < quantity) {
                    				isSoldOut = true;
                				}
                				break;
            				case 4:
                				if (stock4.getNumItem() < quantity) {
                   	 				isSoldOut = true;//set the isSoldOut to true
                				}
                				break;
            				case 5:
                				if (stock5.getNumItem() < quantity) {
                    				isSoldOut = true;//set the isSoldOut to true
                				}
                				break;
            				default:
                				cout << "Invalid Item." << endl<<endl;
                				break;
        				}
					
						//if the status of isSoldOut is true, system will print the error message
						//else system will proceed to payment function
        				if (isSoldOut) {
            				cout << "The selected stock is sold out or insufficient. Sorry!" << endl<<endl;
        				} 
						else {
            				// Proceed with payment if the stock is available
            				//The payment function will return the true to represent
            				//buyer have complete their payment and false to represent
            				//buyer do not complete their payment
            				status = exchangeMoney(stockNumber, quantity, funds);

            				// Transaction complete action
            				//When Payment is successful made, the stock that bought
							//by buyer will dequeue from its queue and sold to user
							//if payment unsuccessful, error message will pop out to buyer 
            				if (status) {
                				switch (stockNumber) {
                    				case 1:
                        				for (int quan = 0; quan < quantity; quan++) {
                            			stock1.deQueue(itemSymbol[0]);
                        				}
                        				break;
                    				case 2:
                        				for (int quan = 0; quan < quantity; quan++) {
                            				stock2.deQueue(itemSymbol[1]);
                       	 				}
                        				break;
                    				case 3:
                        				for (int quan = 0; quan < quantity; quan++) {
                            				stock3.deQueue(itemSymbol[2]);
                       	 				}
                        				break;
                    				case 4:
                        				for (int quan = 0; quan < quantity; quan++) {
                            				stock4.deQueue(itemSymbol[3]);
                        				}
                        				break;
                    				case 5:
                        				for (int quan = 0; quan < quantity; quan++) {
                            				stock5.deQueue(itemSymbol[4]);
                        				}
                        				break;
                    				default:
                        				cout << "Invalid Item." << endl<<endl;
                        				break;
                				}
            				} 
							else {
                				cout << "Transaction Error." << endl<<endl;//Error message for payment fail
           	 				}
        				}
        				
    				} 
				}
			}
    		break;
          }
            case 2:
            	//Inventory Admin Menu
            	
            	cout<<"Please Enter Admin's Password: "; //system prompt to inform user to enter admin password
            	cin>>adPassword;
            	//If the password is correct, grant access to user access to Inventory
    			//Admin Menu. Else, Password Error Message will prompt
            	if(adPassword==correctPwd){
            		cout<<"Access Granted! "<<endl<<endl;
            		adminMenu(numStock);
				}else{
					cout<<"Access Denied! Admin Password Error! "<<endl<<endl; //Error Message for invalid Password
				}
				break;
            case 3:
                cout << "Exiting..." << endl; //Message to show that user exit from the program
                break;
            default:
                cout << "Invalid option!" << endl<<endl;
                break;
        }
    } while (choice != 3); // loop when option not equal to 3
	
	return 0;
}
	
// Function to display the main menu
void displayMenu() {
    cout << "Vending Machine" << endl;
    cout << "1 [Show Items]" << endl; // to call the show item funtion 
    cout << "2 [Inventory-Admin]" << endl; // to call the inventory-admin function 
    cout << "3 [Exit]" << endl; // exit the program 
    cout << "Enter Option: ";
}
	
	
	
// Function to display the Item
void showItems(int numStock,string stockName[],int stockPrice[],char itemSymbol[]){
	//Finding the stock size, number of item and the empty slot
	//for the represented stock Queue
	int stock1Size = stock1.getStockSize();
    int stock1Item = stock1.getNumItem();
    int empty1 = stock1Size - stock1Item;

    int stock2Size = stock2.getStockSize();
    int stock2Item = stock2.getNumItem();
    int empty2 = stock2Size - stock2Item;

    int stock3Size = stock3.getStockSize();
    int stock3Item = stock3.getNumItem();
    int empty3 = stock3Size - stock3Item;

    int stock4Size = stock4.getStockSize();
    int stock4Item = stock4.getNumItem();
    int empty4 = stock4Size - stock4Item;

    int stock5Size = stock5.getStockSize();
    int stock5Item = stock5.getNumItem();
    int empty5 = stock5Size - stock5Item;
    
	//Printing out the price list and Stock list
	cout <<"----------Price List----------" << endl;
	
	for(int i=0 ; i<numStock ; i++){ // to print out the price list 
	cout << "Stock " << i+1 << " : " << "RM " << stockPrice[i] << endl;
	}
	
	cout << endl << endl;
	
	for(int i=0 ; i<numStock ; i++){//print header for the available stock only
		cout << setw(20)<<left<<("Stock " + to_string(i + 1) + " : " + stockName[i]); 
	}		
	cout<<endl;
	for(int j=0 ; j<numStock ; j++){ //print divider for the available stock only 
		cout <<setw(20)<<left<< "---------------------" ;
	
	}

    cout << endl;
	//print available stock using for loop
	//If the whole stock is already empty, <sold out> message will be prompted
	const int columnWidth = 20;//setw parameter
	
	//Printing Stock Start
    for (int i = 0; i < stock1Size || i < stock2Size || i < stock3Size || i < stock4Size || i < stock5Size; i++) {
        // Print stock 1
        if (stock1Item == 0 && i == 0) {
            cout << setw(columnWidth) << "<sold out>";
        } else if (i < empty1) {
            cout << setw(columnWidth) << "";
        } else {
            cout << setw(columnWidth) << stock1.getItem(i - empty1);
        }

        // Print stock 2
        if (stock2Item == 0 && i == 0) {
            cout << setw(columnWidth) << "<sold out>";
        } else if (i < empty2) {
            cout << setw(columnWidth) << "";
        } else {
            cout << setw(columnWidth) << stock2.getItem(i - empty2);
        }

        // Print stock 3
        if (stock3Item == 0 && i == 0) {
            cout << setw(columnWidth) << "<sold out>";
        } else if (i < empty3) {
            cout << setw(columnWidth) << "";
        } else {
            cout << setw(columnWidth) << stock3.getItem(i - empty3);
        }

        // Print stock 4
        if (numStock >= 4 && stock4Item == 0 && i == 0) {
            cout << setw(columnWidth) << "<sold out>";
        } else if (i < empty4) {
            cout << setw(columnWidth) << "";
        } else if (numStock >= 4) {
            cout << setw(columnWidth) << stock4.getItem(i - empty4);
        }

        // Print stock 5
        if (numStock >= 5 && stock5Item == 0 && i == 0) {
            cout << setw(columnWidth) << "<sold out>";
        } else if (i < empty5) {
            cout << setw(columnWidth) << "";
        } else if (numStock >= 5) {
            cout << setw(columnWidth) << stock5.getItem(i - empty5);
        }

        cout << endl;
	
	}

}

// Function to display the Admin menu
void adminMenu(int &numStock) {
	
	int options; //user optiom
	int restockQuan; //restock Quantity
	bool cancelRestock=false;
	
	do{
		cout << "-------------------------" << endl;
		cout << "Enter your option from 1 - 10 " << endl;
	
    	cout << "Inventory Admin Menu" << endl;
    	cout << "1 [Replenish Stock]" << endl;
    	cout << "2 [Display Machine Summary]" << endl;
    	cout << "3 [Reset Stock]" << endl;
    	cout << "4 [Change Price]" << endl;
    	cout << "5 [Add Funds]" << endl;
    	cout << "6 [Add Stock]"<<endl;
    	cout << "7 [Change Vend Title]"<<endl;
    	cout << "8 [Change Stock Header]"<<endl;
    	cout << "9 [Change Admin Password]"<<endl;
    	cout << "10 [Back to Main Menu]" << endl;
    	cout << "-------------------------" << endl;
    
    	cout << "Enter Option: ";
    	cin >> options;
	
		switch(options){
			case 1:
			{
				bool restockFail=false;
    			int empty1 = stock1.getStockSize() - stock1.getNumItem();
				int empty2 = stock2.getStockSize() - stock2.getNumItem();
				int empty3 = stock3.getStockSize() - stock3.getNumItem();
				int empty4 = stock4.getStockSize() - stock4.getNumItem();
				int empty5 = stock5.getStockSize() - stock5.getNumItem();
    
				//1 [Replenish Stock]
				//if admin enter the wrong stock number, the system will let admin enter again
				do {
        			cout << "Enter the stock number to restock: ";
        			cin >> restock;
        			
        			while (restock<=0||restock>numStock ) {
        				cout << "Invalid stock number. Do you want to cancel the restock process? (y/n): ";
        				char choiceR;
        				cin >> choiceR;
		
						//if admin wish to cancel the process, the system will back to admin main menu
        				if (choiceR == 'y' || choiceR == 'Y') {
            				cout << "Restock process cancelled." << endl<<endl;
            				restockFail=true;
							break;
        				//else system will prompt to let admin continue to enter the stock number
        				} else {
            				cout << "Enter the stock number to restock: ";
            				cin >> restock;
        				}
    				}
					
					if(restockFail==false){
						bool restockFail2=false;
						cout << "Enter the amount of item you want to restock: ";
        				cin>>restockQuan;
						
					        			
        				//If the admin enter 0 as  restock quantity, system will ask whether admin
        				//want to cancel the restock process or not
        				while (restockQuan <=0 ) {
        					cout << "Invalid Quantity. Do you want to cancel the restock process? (y/n): ";
        					char choice;
        					cin >> choice;
		
							//if admin wish to cancel the process, the system will back to admin main menu
        					if (choice == 'y' || choice == 'Y') {
            					cout << "Restock process cancelled." << endl<<endl;
            					restockFail2=true;
								break;
        					//else system will prompt to let admin continue to enter the restock Quantity
        					} else {
            					cout << "Enter the amount of item you want to restock: ";
            					cin >> restockQuan;
        					}
    					}
    					
        				if(restockFail2==false){
        				//if the stock number that enter by user is less than numStock
						//which mean existing in vending maxhine
						//admin able to restock the amount that being entered
						//if the restock quantity being insert by admin is more than the 
						//empty space available in stock, admin only able to restock based on
						//the quantity of the empty space
        					if (restock <= numStock) {
            					switch (restock) {
                					case 1:
                						if(empty1==0){
                							cout<<"The Stock Is Full! "<<endl<<endl;
                							break;
										}
										else if(restockQuan>empty1){
                							restockQuan=empty1;
                							cout<<"Only "<<restockQuan<<" stock able to refill"<<endl;
										}
                						for(int i=0;i<restockQuan;i++){
                							stock1.enQueue(itemSymbol[0]);
										}
										cout << "Stock successful refill."<<endl<<endl;
										break;

                					case 2:
                						if(empty2==0){
                							cout<<"The Stock Is Full! "<<endl<<endl;
                							break;
										}
                 						else if(restockQuan>empty2){
                							restockQuan=empty2;
                							cout<<"Only "<<restockQuan<<" stock able to refill"<<endl;
										}               				
                						for(int i=0;i<restockQuan;i++){
                							stock2.enQueue(itemSymbol[1]);
										}
										cout << "Stock successful refill."<<endl<<endl;
										break;
                					case 3:
                						if(empty3==0){
                							cout<<"The Stock Is Full! "<<endl<<endl;
                							break;
										}                						
                 						else if(restockQuan>empty3){
                							restockQuan=empty3;
                							cout<<"Only "<<restockQuan<<" stock able to refill"<<endl;
										}                 				
                						for(int i=0;i<restockQuan;i++){
                							stock3.enQueue(itemSymbol[2]);
										}
										cout << "Stock successful refill."<<endl<<endl;
										break;
                					case 4:
                						if(empty4==0){
                							cout<<"The Stock Is Full! "<<endl<<endl;
                							break;
										}                						
                 						else if(restockQuan>empty4){
                							restockQuan=empty4;
                							cout<<"Only "<<restockQuan<<" stock able to refill"<<endl;
										}                 				
                						for(int i=0;i<restockQuan;i++){
                							stock4.enQueue(itemSymbol[3]);
										}
										cout << "Stock successful refill."<<endl<<endl;
										break;
                					case 5:
                						if(empty5==0){
                							cout<<"The Stock Is Full! "<<endl<<endl;
                							break;
										}                						
                 						else if(restockQuan>empty5){
                							restockQuan=empty5;
                							cout<<"Only "<<restockQuan<<" stock able to refill"<<endl;
										}                 				
                						for(int i=0;i<restockQuan;i++){
                							stock5.enQueue(itemSymbol[4]);
										}
										cout << "Stock successful refill."<<endl<<endl;
										break;
                					default:
                    					cout << "Invalid Stock."<<endl<<endl;
                    					break;
            					}
            				}	flag2 = true;
        				} else {
            				
            				flag2=true;
        				}
					}else{
						flag2=true;
					}
					
    			} while (!flag2);
				break;
			}
			case 2:
				cout<<endl;
				displaySummary(numStock); //Called the function that use to Display Vend Summary
				break;
		
			case 3:
				//3 [Reset Stock]
				stock1.clear();
				stock2.clear();
				stock3.clear();
				stock4.clear();
				stock5.clear();
				cout<<"Stock successfully reset"<<endl<<endl;
				break;
		
			case 4:{
				//Change Price 
				int stockToChange;
				bool cancelCP=false;
				cout<<"What stock Price do you want to change? :";
    			cin>>stockToChange; // what stock to change 
    			//If the admin enter 0 as stock 0, system will ask whether admin
        			//want to cancel the change price process or not
        			while (stockToChange <=0 ||stockToChange>numStock) {
        				cout << "Invalid Stock. Do you want to cancel the change price process? (y/n): ";
        				char choice;
        				cin >> choice;
		
						//if admin wish to cancel the process, the system will back to admin main menu
        				if (choice == 'y' || choice == 'Y') {
            				cout << "Change Price process cancelled." << endl<<endl;
            				cancelCP=true;
							break;
        				//else system will prompt to let admin continue to enter the Stock Number
        				} else {
            				cout << "What stock Price do you want to change? : ";
            				cin >> stockToChange;
        				}
    				}
    				
					//Successfully Change price
					if(cancelCP==false){
						bool cancelChange2=false;
						int newPrice;
    					cout<<"What price you want to change for this Stock ? : ";
    					cin>>newPrice;
    				
    					//If the admin enter 0 as their new price, error message will 
						//prompt and system will ask whether admin want to cancel the 
						//restock change price process or not
        				while (newPrice <=0) {
        					cout << "Invalid Price. Do you want to cancel the change price process? (y/n): ";
        					char choice;
        					cin >> choice;
		
							//if admin wish to cancel the process, the system will back to admin main menu
        					if (choice == 'y' || choice == 'Y') {
            					cout << "Change Price process cancelled." << endl<<endl;
            					cancelChange2=true;
								break;
        					//else system will prompt to let admin continue to enter the Stock Number
        					} else {
            					cout << "What stock Price do you want to change? : ";
            					cin >> newPrice;
        					}
    					}
    					//if the user do not cancel the process and enter a valid price
    					if(cancelChange2==false){
    						changePrice (stockToChange, newPrice,stockPrice);
    						cout << "Successfuly Change the price for Stock " << stockToChange<<endl<<endl;    						
						}
					}	
				break;
			}

			case 5:
				//[Add Fund]			
				cout << "Enter the amount to add into the fund: ";
				int amount;
				cin >> amount;
				addFunds(amount);
	
				break;
			case 6:
				//Add Stock
				//if the numstock already reach 5, Message will prompt
				//to inform admin the stock is full and failed to added and return
				if(numStock>=5){
					cout<<"Sorry stock is Full! "<<endl<<endl;
				}else{
					addStock(stockName, itemSymbol, stockPrice,numStock );//call Add Stock Function
				}
				break;	
			case 7:
				//Change vend Title
				changeTitle(title);
				break;
			case 8:
				//change Stock Header
				changeStockHeader (stockName);
				break;
			case 9:
				//Change Password
				changePwd(correctPwd);
				break;		
			case 10:
				// Back to Main Menu
				break;
		
			default:
            	cout << "Invalid option!" << endl<<endl;
            	break;
		}	
		
	}while(options!=10);
	
}

//Change Stock Header Function
void changeStockHeader (string stockName[]){
	cin.ignore();// Ignore any remaining characters in the input buffer
	//Declare the variable for stockNum and newHeader
	bool failChange=false;
	int stockNum;
	string newHeader;
	cout<<"Which Stock title you want to change(Enter the Stock Number): ";
	cin>> stockNum;
	while (stockNum >numStock||stockNum<=0) {
        	cout << "Invalid stock Number. Do you want to cancel the change stock header process? (y/n): ";
        	char choice;
        	cin >> choice;
		
			//if admin wish to cancel the process, the system will back to admin main menu
        	if (choice == 'y' || choice == 'Y') {
            	cout << "Change stock header process cancelled." << endl<<endl;
            	failChange=true;
				break;
        	//else system will prompt to let admin continue to enter the stock Number
        	} else {
            	cout << "Which Stock title you want to change(Enter the Stock Number): ";
            	cin >> stockNum;
        	}
    }
    
	//If the stock number is existing, the header for the stock will change
    if(failChange==false){
    	cin.ignore(); // Ignore any remaining characters in the input buffer
		cout<<"Enter the new Header for Stock "<<stockNum<<":";
		getline(cin,newHeader);
		stockName[stockNum - 1] = newHeader;
		cout<<"Stock "<<stockNum<<" Header successfully changed"<<endl<<endl;
	}
}

//Change Vend Title Function
void changeTitle(string &title){
	cin.ignore();// Ignore any remaining characters in the input buffer
	
	//Admin enter new title
	cout<<"Enter the new title: ";
	getline(cin,title);
	cout<<"Title Successfully Change!"<<endl<<endl;
}

//Change Price Function
void changePrice (int stockIndex, int newPrice,int stockPrice[]){
    stockPrice[stockIndex-1] = newPrice;//replace the old price with the new price for the represented index
}

//Add funds Function
void addFunds(int amount) {
	bool cancelFund=false;
		//If the amount enter by admin is <0, Error Message will prompt
		// and system will ask whether admin want to cancel the 
		//restock change price process or not
        while (amount <=0) {
        	cout << "Invalid amount. Do you want to cancel the add fund process? (y/n): ";
        	char choice;
        	cin >> choice;
		
			//if admin wish to cancel the process, the system will back to admin main menu
        	if (choice == 'y' || choice == 'Y') {
            	cout << "Add fund process cancelled." << endl<<endl;
            	cancelFund=true;
				break;
        	//else system will prompt to let admin continue to enter the Stock Number
        	} else {
            	cout << "Enter the amount to add into the fund: ";
            	cin >> amount;
        	}
    	}
		//fund successful being added to the vending machine
		if(cancelFund==false){
			funds =funds+ amount;
        	cout << "Funds added." << endl<<endl;
		}	

}

//Payment function
bool exchangeMoney(int stockNumber, int quantity, int &funds) {
    bool flag; //initialise flag variable
    int insertAmount;
    //set the charge to the quantity of buyer buy mutiply
    //with the price for the represented stock
    int charge = quantity * stockPrice[stockNumber - 1];
    
    //User Input their paid amount
    cout << "Please enter RM " << charge << " : ";
    cin >> insertAmount;
	
	//If the amount that pay by user is insufficient
	//System will first ask user whether they want to cancel their payment
	//it will continue asking until buyer pay their charge or cancel 
	//their order
    while (insertAmount < charge) {
        cout << "Insufficient amount. Do you want to cancel the order? (y/n): ";
        char choice;
        cin >> choice;
		
		//if buyer wish to cancel their order, the money that paid will refund 
		//and the stock wont dequeue to them
        if (choice == 'y' || choice == 'Y') {
            cout << "Order cancelled." << endl<<endl;
            flag = false;
            return flag;
        //else system will prompt to let user continue paying the remaining amount
        } else {
            cout << "Please enter the remaining RM " << (charge - insertAmount) << " : ";
            int additionalAmount;
            cin >> additionalAmount;
            insertAmount += additionalAmount;
        }
    }
	//Formula to calculate the exchange that need to give to user
    int exchange = insertAmount - charge;
	
	//if the funds remaining in the machine is less the the amount of money that
	//need to exchange to user, system will promp error message refund to user and return the false flag 
	//for dequeuing item
    if (funds < exchange) {
        cout << "Sorry, machine insufficient of fund. Transaction failed. Please take the refund." << endl<<endl;
        flag = false;
        return flag;
        
    //else, the amount of money that paid by user will added to funds and a successful 
	//message will prompted and return the true flag for dequeuing item    
    } else {
        funds = funds + insertAmount - exchange; // Add the charge and deduct the exchange
        cout << "Transaction Successful. Your change is RM " << exchange << endl<<endl;
        flag = true;
        return flag;
    }
}

//Display Machine Summary Function 
void displaySummary(int numStock) {
	
    cout << "[Vending Machine Summary]" << endl;
    
    cout << "----------------------" << endl;
    cout << "Current Stock Count : " << endl;
    
    /*
	
	numstock = the amount of stock (not the items for it)
	stockName = stock's name
	stocksize = amount of items in the stock
	
	*/
    
    if(numStock >= 1 ){

		cout << stockName[0] << ": " << stock1.getNumItem() << " items left." << endl;
	
	}
	
	if(numStock >= 2){

	    cout << stockName[1] << ": " << stock2.getNumItem() << " items left." << endl;

	}
	
	if(numStock >= 3){

		cout << stockName[2] << ": " << stock3.getNumItem() << " items left." << endl;		
	
	}
	
	if(numStock >= 4){

		cout << stockName[3] << ": " << stock4.getNumItem() << " items left." << endl;
		
	}
	
	if(numStock >= 5){

		cout << stockName[4] << ": " << stock5.getNumItem() << " items left." << endl;
	
	}
    
    cout << "Total funds: RM " << funds << endl<<endl;
}


//Add Stock Function
void addStock(string stockName[], char itemSymbol[],int stockPrice[], int &numStock) {
    cin.ignore(); // Ignore any remaining characters in the input buffer
    string nameStock;
    char symb;
    int newPrice;
    bool cancelAdd=false;
	
	//Admin input Stock Name that they want to add
    cout << "What is the stock name you want to add: ";
    getline(cin, nameStock);
	
	//Admin input the Char symbol to represent the Stock
    cout << "What is the character you want for the stock: ";
    cin >> symb;
    
    //Admin set the price for this item
    cout<<"What is the price for this item: ";
    cin>>newPrice;
    
    //When the price is less than 0, system will prompt error message
    //and ask admin whether want to continue the add stock process
    //if admin wish to cancel, it will propmt a message to inform admin
    //process cancel and back to admin menu
    while (newPrice <=0) {
        	cout << "Invalid price. Do you want to cancel the add stock process? (y/n): ";
        	char choice;
        	cin >> choice;
		
			//if admin wish to cancel the process, the system will back to admin main menu
        	if (choice == 'y' || choice == 'Y') {
            	cout << "Add stock process cancelled." << endl;
            	cancelAdd=true;
				break;
        	//else system will prompt to let admin continue to enter the price
        	} else {
            	cout << "What is the price for this item: ";
            	cin >> newPrice;
        	}
    	}
	if(cancelAdd==false){
		stockName[numStock] = nameStock; // Update stockName array
    	itemSymbol[numStock] = symb; // Update itemSymbol array
    	stockPrice[numStock]=newPrice;//Update stockPrice array
    
    	//The item for the stock will automatically added to full (20 item) into the 
    	//Represented Queue based on the current numStock
    	if(numStock==3){
    		for(int x=0;x<stock4.getStockSize();x++){
    			stock4.enQueue(itemSymbol[3]);
			}
		}else if(numStock==4){
			for(int x=0;x<stock5.getStockSize();x++){
				stock5.enQueue(itemSymbol[4]);
			}	
		}
    	numStock++; // Increment numStock
    
		//successfull message prompt when stock success being added
    	cout << "Stock added successfully!" << endl<<endl;
	}
    
}

//Change Password Function
void changePwd(string &correctPwd){
	cin.ignore();// Ignore any remaining characters in the input buffer
	string newPass;
	
	//Admin Enter new Password
	cout<<"Please Enter your New Password: ";
	getline(cin,newPass);
	correctPwd=newPass;//current password set to the new password set by admin
	cout<<"Your Password Successfully Changed! "<<endl<<endl;//Message prompt to inform admin password changed successfully
}
