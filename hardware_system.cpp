#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
class dealer {
	public:
		void rewrite_line(int n,string rewrite) //function for rewriting a specific line in file
		{ 
		    ifstream filein("deal.txt"); //opening file in read mode
		    ofstream fileout("temp.txt"); //making a temp file in write mode
		    if(!filein || !fileout) //checking for all flags
			{
		        cout << "Error opening files!" << endl;
		    }
		    string strTemp; //temp string
		    int lineno=1; //line counter
		 	while(getline(filein,strTemp)) //reading file
		    {
		    	lineno++; //counting lines
		        if(lineno == n) //if line matches with desired line to change
				{
		            strTemp = rewrite; //then rewriting the data with new data
		        }
		        strTemp += "\n"; //going ahead
		        fileout << strTemp; //writing data 
		    }
		    filein.close(); //closing the files forcefully
		    fileout.close(); //closing the files forcefully
		    remove("deal.txt"); //removing previous file
		    rename("temp.txt","deal.txt"); //replacing with the new file
		} 
		bool search(string word) //search function for searching the name
		{
			ifstream dealf("deal.txt"); //opening the file in read mode
			if(!dealf) //checking for all types of flags
			{
				dealf.open("deal.txt"); //if file to open this will work
			}
			bool found=false; //default value
			string line; //temp string
			while(dealf >> line && found==false) //condition to read file and checking the name
			{
				if(line.compare(word)==0) //comparing the word with line from file
				{
					found = true; //if found this will break the while loop
				}
			}
			return found; //return search status
		}
		void additems() //adding items
		{
			fstream dealfile("deal.txt",ios::in | ios::out | ios::app); //opening file in append mode.
			if(!dealfile) //check for all flags
			{
				dealfile.open("deal.txt");
			}
			string name,price,stock; 
			cout<<"Enter Hardware name which is to be added"<<endl; 
			cin>>name; //taking input for name
			bool check = search(name); //checking if item is already present
			if(check)
			{
				cout<<"Hardware found already"<<endl; //returning error
			}
			else {
				string key;
				cout<<"Enter price"<<endl; //getting input for its price
				cin>>price;
				cout<<"Enter stock"<<endl; //getting input for its stock
				cin>>stock;
				key = name+" "+price+" "+stock; //generating key
				dealfile<<key<<endl; //output to file
				cout<<"Hardware added"<<endl;
			}
		}
		void stock()
		{
			string name,price,stock;
			cout<<"Enter hardware name"<<endl; //getting hardware name
			cin>>name;
			cout<<"Enter hardware price"<<endl; //getting current price value
			cin>>price;
			cout<<"Enter hardware available stock"<<endl; //getting current stock value
			cin>>stock;
			bool check = search(name); //checking for that hardware to be present
			string key = name+" "+price+" "+stock; //generating key
			if(!check)
			{
				cout<<"No such hardware found"<<endl; //if hardware not found, then output error
			}
			else {
			ifstream dealff("deal.txt"); //opening file in read mode
			if(!dealff)
			{
				dealff.open("deal.txt");
			}
			cout<<"Enter new hardware stock"<<endl; //taking new stock details
			string stocknew,newkey;
			cin>>stocknew; //input
			int count=1; //count lines
			string line="error",temp; //default value
			while(getline(dealff,line)) //getting line by line from file till eof
			{
				count++; //counting lines
				if(line.compare(key)==0) //if line compares to key then that line will be changed
				{
					stringstream ss(line); //generating a string stream to get tokens from that line by using delimeter space
					while(getline(ss,temp,' ')) //taking word by word as tokens
					{
						if(temp.compare(stock)!=0) //if word doesnt compare to stock value
						{
							newkey+=temp+" "; //then input same word to new key
						}
						else
						{
							newkey+=stocknew; //input new stock to new key
						}
					}
					dealff.close(); //closing file so that remove and rename functions work properly
					rewrite_line(count,newkey); //calling rewrite_line founction with that line number and new key value to be rewritten
					cout<<"Stocks changed"<<endl; //giving confirmation message
				}
			}
		}
		}
		void eraseFileLine(string eraseLine) {
			string line;
			ifstream fin;
			string path = "deal.txt";
			fin.open("deal.txt");
			ofstream temp; // contents of path must be copied to a temp file then renamed back to the path file
			temp.open("temp1.txt");
			
			while (getline(fin, line)) {
			    if (line != eraseLine) // write all lines to temp other than the line marked fro erasing
			        temp << line <<endl;
			}
			
			temp.close();
			fin.close();
			
			const char * p = path.c_str(); // required conversion for remove and rename functions
			remove(p);
			rename("temp1.txt", p);
		}
		void delitems()
		{
			ifstream dealfile("deal.txt",ios::in | ios::out | ios::app); //opening file in append mode.
			if(!dealfile) //check for all flags
			{
				dealfile.open("deal.txt");
			}
			string name;
			cout<<"Enter Hardware name which is to be deleted"<<endl;
			cin>>name; //taking input
			int count;
			bool found =false;
			bool check = search(name); //checking for hardware presence
			if(check)
			{
				while(!dealfile.eof()) //reading till end of file
				{
					
					string temp = "";
					getline(dealfile,temp); //getting line from file in temp
					count++;
					for(int i=0;i<name.size();i++)
					{
						if(temp[i]==name[i])
							found = true; //getting that line which is to be deleted
						else
						{
							found=false;
							break;
						}
					}
					if(found)
					{
						dealfile.close(); //closing file forcefully so that it doesnt interferes with remove and rename functions.
						eraseFileLine(temp); //calling erasefile function to delete the temp line which matches with hardware name
						cout<<"Deletion of item...done"<<endl;
					}
					else {
						continue; //else continuing the loop
					}
				}
			}
			else {
				cout<<"No such hardware found"<<endl;
			}
		}
		void availitems()
		{
			ifstream dealf("deal.txt"); //opening the file in read mode
			if(!dealf)
			{
				dealf.open("deal.txt");
			}
			cout<<"Available items List"<<endl; //reading the whole file
			cout<<"Name  - Price - Stock"<<endl;
			string line;
			while(!dealf.eof()) //reading till end of file
			{
				getline(dealf,line);
				cout<<line<<endl;
			}
		}
		void changeprice()
		{
			string name,price,stock;
			cout<<"Enter hardware name"<<endl; //taking inputs
			cin>>name;
			cout<<"Enter hardware stock"<<endl;
			cin>>stock;
			cout<<"Enter hardware price"<<endl;
			cin>>price;
			string key = name+" "+price+" "+stock;
			bool check = search(name); //checking for hardware presence
			if(!check)
			{
				cout<<"No such hardware found"<<endl;
			}
			else {
				ifstream dealff("deal.txt"); //opening file
				if(!dealff)
				{
					dealff.open("deal.txt");
				}
				cout<<"Enter new hardware price"<<endl; //getting new price
				string pricenew,newkey="";
				cin>>pricenew;
				int count=1; //setting counter for line
				string line="error",temp;
				while(getline(dealff,line)) //getting the line
				{
					count++;
					if(line.compare(key)==0) //comparing with the key
					{
						stringstream s(line); //making a stream to get token after each space
						int counttok=1; //counter for tokens
						while(getline(s,temp,' '))
						{
							if(counttok==1) //making new key 
							{
								newkey+=temp+" ";
							}
							if(counttok==2)
							{
								newkey+=pricenew+" ";
							}
							if(counttok==3)
							{
								newkey+=temp;
							}
							counttok++;
						}
						dealff.close(); //closing file forcefully
						rewrite_line(count,newkey); //rewriting line 
						cout<<"Prices changed"<<endl;
					}
				}
			}
		}
};


int main()
{
	cout<<"Hello there! Welcome to Neha's Hardware System Manager"<<endl;
	cout<<"Please select your option"<<endl;
	dealer d;
	int c,sc,pass=0;
	for(; ;)
	{
		cout<<"Enter 1 to add items or increase stock of any particular hardware"<<endl;
		cout<<"Enter 2 to delete items or reduce stock of any particular hardware"<<endl;
		cout<<"Enter 3 to Check available items"<<endl;
		cout<<"Enter 4 to change price of a particular hardware"<<endl;
		cout<<"Enter 5 to exit"<<endl;
		cin>>c;
		switch(c)
		{
			case 1: while(pass==0)
					{
						cout<<"Enter 1 to add items"<<endl;
						cout<<"Enter 2 to increase stock of particular hardware"<<endl;
						cout<<"Enter 3 to go back"<<endl;
						cin>>sc;
						switch(sc)
						{
							case 1:d.additems();
							break;
							case 2:d.stock();
							break;
							case 3:pass=1;
							break;
							default:cout<<"Enter correct choice"<<endl;
								}		
					}
			break;
			case 2: pass=0;
			 		while(pass==0)
					{
						cout<<"Enter 1 to delete items"<<endl;
						cout<<"Enter 2 to reduce stock of particular hardware"<<endl;
						cout<<"Enter 3 to go back"<<endl;
						cin>>sc;
						switch(sc)
						{
							case 1:d.delitems();
							break;
							case 2:d.stock();
							break;
							case 3:pass=1;
							break;
							default:cout<<"Enter correct choice"<<endl;
								}		
					}
			break;
			case 3:d.availitems();
			break;
			case 4:d.changeprice();
			break;
			case 5:exit(0);
			break;
			default: cout<<"Wrong choice, send again";
		}
	}
}
