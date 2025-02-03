#include <iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<algorithm>


using namespace std;

struct person
{
	string 	Id_no,
			person_name,
			item_name;
};

struct InventoryItem
{
	string  name,
			item_ID;
	string  category;
	int		item_count = 0;
	person	allocated_to;
};
//new
void add_inventory(InventoryItem [100], int );
void view_inventory(InventoryItem[100], int);
void search_inventory(InventoryItem array[100], person arr[100], int index, int index1);
void edit_inventory(InventoryItem array[100], int);
void delete_inventory(InventoryItem array[100], int index);
void assign_item(InventoryItem array[100], int);
void retrieve_item(InventoryItem array[100], person[100], int, int);
void list_of_faculty_members(person ary[100], int loc);
void Search_list(person arr[100], string name, int index);
void list_of_items(InventoryItem array[100], int index);

void read_file(InventoryItem arr1[100], int& i)//i mainatins location in array
{

	string sname, scategory, id;  int  count=0;
	ifstream in("inventory_item_data.txt");
	string line, mystring;
	i = 0;

	while (in.good() && !in.eof())											
	{
		in.ignore();
		getline(in, sname, '\t');
	    in >> id>>scategory>>count;							
		in.ignore();
		if (in.eof())									//eofbit is a flag that is true when the last character of the file is encountered
			break;
		arr1[i].name = sname;
		arr1[i].item_ID = id;
		arr1[i].category = scategory;
		arr1[i].item_count = count;
		in.ignore();
		i++;

	}
	in.close();
}
void read_person_file(person ary[100], int& loc)		//loc(location)  variable maintains the index of this array
{
	string item_name, p_name , p_ID;
	string line, mystring;
	ifstream fp("allocated_item_data.txt");
	loc = 0;																	
	while (fp.good() && !fp.eof())
	{
		fp.ignore();
		getline(fp,item_name, '\t');
		getline(fp, p_name, '\t');
    	fp >>  p_ID;
		fp.ignore();
		if (fp.eof())
			break;
		ary[loc].item_name = item_name;
		ary[loc].person_name = p_name;
		ary[loc].Id_no = p_ID;
		fp.ignore();
		loc++;


	}
	
	fp.close();
}


int main()
{
	
	InventoryItem arr1[100]; person ary[100];
	int i = 0, loc = 0;		
	read_file(arr1, i);
	read_person_file(ary, loc);
	int choice, flag = 1;

	while (flag == 1)
	{
		cout << endl;
		cout << "-------Welcome To Our Inventory Management System-------\n\n";
		cout << "Enter 1 To Add inventory items \n";
		cout << "Enter 2 To View inventory items \n";
		cout << "Enter 3 To Search inventory item \n";
		cout << "Enter 4 To Edit inventory item \n";
		cout << "Enter 5 To Delete inventory item \n";
		cout << "Enter 6 To Assign inventory items \n";
		cout << "Enter 7 To Retrieve inventory items \n";
		cout << "Enter 8 To View faculty members who have borrowed an inventory item\n";
		cout << "Enter 9 To EXIT \n";
		cout << endl << "===========================================================" << endl<<endl;
		cout << "Enter Your Choice: \n";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			char ch='y';
			while (ch == 'y'||ch=='Y')
			{
				add_inventory(arr1,i);
				read_file(arr1, i);
				cout << "Do you want to add more items ? (y/n)\n";
				cin >> ch;
				if (ch == 'n' || ch == 'N')
					break;
			}
			break;

		}

		case 2:
		{
			ifstream file("inventory_item_data.txt");
			bool isEmpty = file.peek() == EOF;
			file.close();
			if (!isEmpty)
			{
				view_inventory(arr1, i);
			}
			else
				cout << "File is empty!\n ";
			break;
		}
		case 3:
		{
			search_inventory(arr1,ary ,i,loc);
			break;
		}
		case 4:
		{
			edit_inventory(arr1, i);
			read_file(arr1, i);
			break;
		}
		case 5:
		{
			delete_inventory(arr1, i);
			read_file(arr1, i);
			break;
		}
		case 6:
		{	char ch;
			cout << "Do you want to see the list of items available ? (y/n)\n";
			cin >>ch;
			if (ch == 'y' || ch == 'Y')
			{
				list_of_items(arr1, i);
			}
			cout << endl;
			assign_item(arr1, i);
			read_person_file(ary, loc);
			read_file(arr1, i);
			break;
		}
		case 7:
		{


			retrieve_item(arr1, ary, i, loc);
			read_person_file(ary, loc);

			break;
		}
		case 8:
		{  
			ifstream file("allocated_item_data.txt");
			bool isEmpty = file.peek() == EOF;
			
			file.close();
			if (!isEmpty)
			{
				list_of_faculty_members(ary, loc);
			}
			else
				cout << "File is empty! No item is assigned!\n ";
			break;
		}
		case 9:
		{
			flag = 0;
			break;

		}

		}
	}



	return 0;

}


void search_inventory(InventoryItem array[100],person arr[100],int index,int index1)
{
	string name; int flag = 0; char ch;
	cout << endl;
	while (flag == 0)
	{
		cout << "Enter the name of item  you want to search: \n";
		getline(cin >> ws,name);
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		for (int j = 0; j < index; j++)
		{
			if (array[j].name == name)
			{
				flag = 1;
				cout << "\nName of item: " << array[j].name << endl;
				cout << "Item ID: " << array[j].item_ID << endl;
				cout << "Category of item: " << array[j].category << endl;
				cout << "Count of item: " << array[j].item_count << endl;
				cout << "\nDo you wish to see the list of person having it ? (y/n)\n";
				cin >> ch;
				if (ch == 'Y' || ch == 'y')
				{
					Search_list(arr, name, index1);
				}
				else
					break;


			}

		}
		if (flag == 0)
		{
			cout << "You entered wrong name! No match found \n";

		}
		if (flag == 1)
			break;

	}
}

void Search_list(person arr[100],string name, int index)
{
	int flag = 0;
	for (int x = 0; x < index; x++)
	{
		if (arr[x].item_name == name)
		{
			flag = 1;
			cout << "\nName of Person: " << arr[x].person_name << " and ID NO. is " << arr[x].Id_no << endl;
		}
	}
	if (flag == 0)
	{
		cout << "This item is assigned to no one! \n";
	}
}

void edit_inventory(InventoryItem array[100], int index)
{
	string name; int flag = 0;
	cout << endl;
	while (flag == 0)
	{
		cout << "Enter the name of item you want to edit: \n";
		getline(cin >> ws, name);
		transform(name.begin(), name.end(), name.begin(), ::tolower);
		for (int j = 0; j < index; j++)
		{
			if (array[j].name == name)
			{
				flag = 1;
				cout << "Enter the updated name: \n";
				getline(cin >> ws, array[j].name);
				transform(array[j].name.begin(), array[j].name.end(), array[j].name.begin(), ::tolower);
				cout << "Enter the new Item ID: \n";
				cin >> array[j].item_ID;
				cout << "Enter the updated Category of item: \n";
				cin >> array[j].category;
				cout << "Enter the Count of item: \n";
				cin >> array[j].item_count;
				cout << endl;
				break;
			}
		}
		if (flag == 0)
		{
			cout << "You entered wrong name !No match found \n";
		}
		if (flag == 1)
			break;
	}
	if (flag == 1)
	{
		ofstream out;
		out.open("inventory_item_data.txt", ios::out);
		for (int i = 0; i < index; i++)
		{
			
			out << endl 
				<< array[i].name << "\t"
				 << array[i].item_ID << "\t"
				<< array[i].category << "\t"
				 << array[i].item_count <<"\t"<<endl;

		}
		cout << "Data has been updated successfully! \n";
	}
}

void add_inventory(InventoryItem array[100],int index)
{
	InventoryItem arr[1];
	int flag = 0;
	cout << endl;
	cout << "Enter the name of item: \n";
	getline(cin >> ws, arr[0].name);
	transform(arr[0].name.begin(), arr[0].name.end(), arr[0].name.begin(), ::tolower);								
	cout << "Enter the Item ID : \n";
	cin >> arr[0].item_ID;												
	cout << "Enter the category of item: \n";
	cin >> arr[0].category;
	cout << "Enter the item count : \n";
	cin >> arr[0].item_count;
	for (int i = 0; i < index; i++)
	{
		if (array[i].name == arr[0].name && array[i].item_ID == arr[0].item_ID)
		{
			flag = 1;
			cout << "This item is already added in the inventory.\nYou may edit data by pressing 4!\n";
			break;
		}
	}
	if (flag == 0)
	{
		ofstream out;
		out.open("inventory_item_data.txt", ios::out | ios::app);
		for (int i = 0; i < 1; i++)
		{

			out << endl << arr[0].name << "\t" << arr[0].item_ID << "\t" << arr[0].category
				<< "\t" << arr[0].item_count << "\t" << endl;

		}
		cout << "\nData has been added successfully!\n";
	}
}

void view_inventory(InventoryItem arr1[100], int index)
{
	for (int j = 0; j < index; j++)
	{
		cout << endl << "Name of item: " << arr1[j].name << endl
			<< "Item ID: " <<
			arr1[j].item_ID << endl << "Item Category: " <<
			arr1[j].category << endl << "Item count: " <<
			arr1[j].item_count << endl;

	}
}

void delete_inventory(InventoryItem array[100], int index)
{
	string name; int flag = 0;
	cout << endl;
	cout << "Enter the name of item you want to delete: \n";
	getline(cin >> ws, name);
	
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	for (int j = 0; j < index; j++)
	{
		if (array[j].name == name)
		{
			for (int x = j; x < index - 1; x++)
			{
				array[x].name = array[x + 1].name;
				array[x].item_ID = array[x + 1].item_ID;
				array[x].category = array[x + 1].category;
				array[x].item_count = array[x + 1].item_count;
			}
			flag = 1;
		}
	}
	if (flag == 0)
	{
		cout << "No item matched! \n";
	}
	if (flag == 1)
	{
		ofstream out;
		out.open("inventory_item_data.txt", ios::out);
		for (int i = 0; i < index - 1; i++)
		{
			
			out <<endl<< array[i].name << "\t" << array[i].item_ID <<
				"\t" << array[i].category << "\t" << array[i].item_count << "\t"<<endl;


		}
		cout << "Data has been deleted successfully! \n";
	}
}
void assign_item(InventoryItem array[100], int index)
{
	string name; int flag = 0; string pname, PID ;
	cout << "Enter the name of item you want : \n";
	getline(cin >> ws, name);
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	for (int j = 0; j < index; j++)
	{
		if (array[j].name == name && array[j].item_count!=0)
		{
			
			
				flag = 1;
				cout << "Enter your full name: \n";
				getline(cin >> ws, pname);
				transform(pname.begin(), pname.end(), pname.begin(), ::tolower);
				cout << "Enter your ID: \n";
				getline(cin >> ws, PID);

				array[j].item_count -= 1;
				break;
			
		}

	}
	if (flag == 0)
	{
		cout << "Either Item name is wrong or item not available!\n ";
	}
	if (flag == 1)
	{

		ofstream out;
		out.open("allocated_item_data.txt", ios::out | ios::app);
		out << name << "\t" << pname << "\t" << PID <<"\t"<< endl;
		cout << "Item has been assigned successfully! \n";
	}
	
	if (flag == 1)
	{
		ofstream fout;
		fout.open("inventory_item_data.txt", ios::out);
		for (int i = 0; i < index; i++)
		{
			
			fout<<endl<< array[i].name << "\t" << array[i].item_ID <<
				"\t" << array[i].category << "\t" << array[i].item_count <<"\t" << endl;


		}

	}
}
void retrieve_item(InventoryItem array[100], person ary[100], int index, int loc)

{
	string name; int flag = 0; string pname,  PID; int check = 0;
	cout << "Enter the name of item you are returning : \n";
	getline(cin >> ws, name);
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	for (int j = 0; j < index; j++)
	{

		if (array[j].name == name)
		{
			check = 1;
			cout << "Enter your full name : \n";
			getline(cin >> ws, pname);
			cout << "Enter your ID no. : \n";
			cin>> PID;
			transform(pname.begin(), pname.end(), pname.begin(), ::tolower);
			for (int b = 0; b < loc; b++)			
			{

				if (ary[b].item_name == name && ary[b].person_name == pname && ary[b].Id_no == PID)
				{
					flag = 1;
					for (int x = b; x < loc - 1; x++)			//loc is no. of records that are read by alloacted array
					{

						ary[x].item_name = ary[x + 1].item_name;
						ary[x].person_name = ary[x + 1].person_name;
						ary[x].Id_no = ary[x + 1].Id_no;

					}

					break;
				}


			}
			if (flag == 0)
			{
				cout << " No match found! You entered either wrong Name or ID. \n ";
				break;
			}
			if (flag == 1)
			{
				array[j].item_count += 1;

				cout << "Item has been retrieved! \n";
				break;
			}
		}

	}
	if (check == 0)
	{
		cout << "No match found! You entered wrong item name. \n";
	}
	if (flag == 1)
	{
		ofstream fout;
		fout.open("allocated_item_data.txt", ios::out);
		for (int i = 0; i < loc - 1; i++)
		{
			fout << ary[i].item_name << "\t"
				<< ary[i].person_name << "\t"
				<< ary[i].Id_no << "\t" << endl;
		}
		fout.close();
	}
}

void list_of_faculty_members(person ary[100], int loc)
{
	cout << "======= List of Faculty Members who have borrowed an Item =======\n\n";
	cout << setw(25) << "Name of item: " << setw(25) << "Person name: " << setw(25) << "Person ID: \t\n";
	for (int i = 0; i < loc; i++)
	{
		cout << setw(25) << ary[i].item_name << setw(25) << ary[i].person_name << setw(15) << ary[i].Id_no << "\t\n";
	}
}
void list_of_items(InventoryItem array[100], int index)
{
	cout <<"Following items are available: \n\n";
	for (int i = 0; i < index; i++)
	{
		cout << array[i].name << endl;
	}
}