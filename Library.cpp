#include <iostream>
#include "Library.h"
#include<cstdlib>
#include<ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#include <fstream>
#pragma warning (disable:4996)
#define filename "libsys.bin"

using namespace std;
int main(int argc, char** argv)
{
	if (argc != 1)
	{
		string p = argv[1];
		if (p == "/?")
		{
			cout << "To Add a book:      " << setw(40) << "        libsys.exe add <bookname> <authorname> <isbn of book>" << endl;
			cout << "To search a book:   " << setw(40) << " libsys.exe search <isbn of book>" << endl;
			cout << "To delete a book:   " << setw(40) << " libsys.exe delete <isbn of book>" << endl;
			cout << "To update a book:   " << setw(72) << " libsys.exe update <isbn of book> <new bookname> <new authorname>" << endl;
			cout << "To list all books:  " << setw(40) << " libsys.exe list                 " << endl;
		}
		else if (p == "add")
		{
			if (argv[2] == "" && argv[3] == "" && argv[4] == "")
			{
				cout << "Incomplete Arguments" << endl;
			}
			addBook(argv[2], argv[3], argv[4]);
			cout << "add function called" << endl;
		}
		else if (p == "update")
		{
			updateBook(argv[3], argv[4], argv[2]);
		}
		else if (p == "list")
		{
			listOfAllBooks();
		}
		else if (p == "delete")
		{
			deleteBook(argv[2]);
		}
		else if (p == "search")
		{
			searchBook(argv[2]);
		}
		else {
			cout << "Invalid command " << endl;
			cout << "For help please type: libsys.exe /?" << endl;
		}

		return 0;
	}

	cout << "Welcome to Library Information System" << endl << endl;
	cout << "Following is the list of all available books" << endl;
	listOfAllBooks();
	int outerChoice = 0;
	while (outerChoice != 9)
	{
		int innerChoice = 0;
		while (innerChoice != 9)
		{
			cout << "Welcome to Library Information System" << endl;
			cout << "1. Add Book" << endl;
			cout << "2. Search Book" << endl;
			cout << "3. Update Book" << endl;
			cout << "4. Delete Book" << endl;
			cout << "5. List of All Books" << endl;
			cout << "0. Exit" << endl;
			cout << "\n Enter your choice : ";

			cin >> innerChoice;
			string bookname, bookauthor, bookisbn;

			switch (innerChoice)
			{
			case 1:
				cin.ignore();
				cout << "\n ---- Add a new Book ----";
				cout << "\n Enter book name : ";
				getline(cin, bookname);
				cout << "\n Enter book author : ";
				getline(cin, bookauthor);
				cout << "\n Enter SBN Number: ";
				getline(cin, bookisbn);
				addBook(bookname, bookauthor, bookisbn);
				break;
			case 2:
				searchBook("");
				break;
			case 3:
				cout << "Enter ISBN number of book to Update: ";
				cin >> bookisbn;
				updateBook("", "", bookisbn);
				break;
			case 4:
				cin.ignore();
				cout << "Enter ISBN number of book to delete: ";
				getline(cin, bookisbn);
				deleteBook(bookisbn);
				break;
			case 5: listOfAllBooks(); break;
			case 0: return 0;
			default: cout << "\n\n Invalid Choice. Press any key to continue..";
				getchar();
			}
		}
	}
}

int addBook(string bookname, string bookauthor, string bookisbn)
{

	int year, month, day;

	time_t t = time(NULL);
	struct tm tm= *localtime(&t);

	year = tm.tm_year + 1900;
	month = tm.tm_mon + 1;
	day = tm.tm_mday;




	ofstream file(filename, ios::out | ios::app);
	if (!file.is_open())
	{
		cout << "Error opening file" << endl;
		return 0;
	}

	file << bookname << ",";
	file << bookauthor << ",";
	file << bookisbn << ",";
	file << day << "-";
	file << month << "-";
	file << year;
	file << "\n";

	file.close();

	cout << "\n Data updated Successfully !!";
	cout << "\n Press Enter key to continue !!";
	getchar();
}

int deleteBook(string keyword)
{
	bool flag = false;

	fstream file(filename, ios::in);

	//Creating new file with name "libsyscopy"
	fstream newFile("libsyscopy.bin", ios::out | ios::app);


	if (!newFile.is_open())
	{
		cout << "Error opening new file" << endl;
		return 0;
	}
	if (!file.is_open())
	{
		cout << "Error opening file" << endl;
		return 0;
	}

	string line;
	string name;
	bool check = false;

	while (getline(file, line))
	{
		stringstream search(line);
		check = false;
		while (getline(search, name, ','))
		{
			if (name == keyword)
			{
				check = true;
				flag = true;
				break;
			}
		}

		if (!check)
		{
			newFile << line << "\n";
		}
	}

	if (!flag)
	{
		cout << "\n\nNo book found in record having ISBN ('" << keyword << "')" << endl;
	}
	else {
		cout << "Record Deleted successfuly" << endl;
	}
	file.close();
	newFile.close();

	if (remove(filename) != 0)
	{
		cout << "Error removing file" << endl;
	}

	if (rename("libsyscopy.bin", filename) != 0)
	{
		cout << "Error renaming new file" << endl;
	}

	cout << "\n\n\n";

}

int searchBook(string keyword)
{
	int choice;
	bool flag = false;
	int dsp = 0;
	string stype = "";

	if (keyword == "")
	{
		cout << "1- Search by name" << endl;
		cout << "2- Search by author" << endl;
		cout << "3- search by isbn" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
	}
	else {
		choice = 0;
	}

	switch (choice)
	{
	case 1:
		cin.ignore();
		cout << "Enter Book Name: ";
		stype = "Book Name";
		getline(cin, keyword);
		break;
	case 2:
		cin.ignore();
		cout << "Enter Author Name: ";
		stype = "Author Name";
		getline(cin, keyword);
		break;
	case 3:
		cin.ignore();
		cout << "Enter ISBN: ";
		stype = "ISBN Number";
		getline(cin, keyword);
		break;
	case 0:
		break;
	default:
		cout << "Invalid Input... Press any key to continue" << endl;
		getchar();
	}

	fstream file(filename, ios::in);
	if (!file.is_open())
	{
		cout << "Error opening file" << endl;
		return 0;
	}

	string line;
	string name;

	while (getline(file, line))
	{
		stringstream search(line);
		while (getline(search, name, ','))
		{
			if (name == keyword)
			{
				flag = true;
				if (dsp == 0)
				{
					cout << "\n\nfollowing are the books found with " << stype << " ('" << keyword << "'):\n" << endl;
					cout << setw(20) << "Book Name" << setw(20) << setw(20) << "Author Name"
						<< setw(20) << setw(20) << "ISBN Number" << setw(20) << setw(20) << "Date\n\n";
					dsp = 1;
				}
				displayLine(line);
				cout << "\n";
				break;
			}
		}
	}

	if (!flag)
	{
		cout << "\n\nNo book found in record having " << stype << " ('" << keyword << "')" << endl;
	}
	cout << "\n\n\n";
}

int updateBook(string bookname, string bookauthor, string keyword)
{

	int year, month, day;

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	year = tm.tm_year + 1900;
	month = tm.tm_mon + 1;
	day = tm.tm_mday;

	bool flag = false;
	fstream file(filename, ios::in);

	//Creating new file with name "libsyscopy"
	fstream newFile("libsyscopy.bin", ios::out | ios::app);


	if (!newFile.is_open())
	{
		cout << "Error opening new file" << endl;
		return 0;
	}
	if (!file.is_open())
	{
		cout << "Error opening file" << endl;
		return 0;
	}

	string line;
	string name;
	bool check = false;

	while (getline(file, line))
	{
		stringstream search(line);
		check = false;
		while (getline(search, name, ','))
		{
			if (name == keyword)
			{
				if (bookname == "" && bookauthor == "")
				{
					cin.ignore();
					cout << "Enter New Name: ";
					getline(cin, bookname);
					cout << "Enter New Author Name: ";
					getline(cin, bookauthor);
				}

				check = true;
				flag = true;

				//updating new info for book
				newFile << bookname << ",";
				newFile << bookauthor << ",";
				newFile << keyword << ",";
				newFile << day << "-";
				newFile << month << "-";
				newFile << year;
				newFile << "\n";
				break;
			}
		}

		if (!check)
		{
			newFile << line << "\n";
		}
	}

	if (!flag)
	{
		cout << "\n\nNo book found in record having ISBN ('" << keyword << "')" << endl;
	}
	else {
		cout << "Record Updated successfuly" << endl;
	}
	file.close();
	newFile.close();

	if (remove(filename) != 0)
	{
		cout << "Error removing file" << endl;
	}

	if (rename("libsyscopy.bin", filename) != 0)
	{
		cout << "Error renaming new file" << endl;
	}

	cout << "\n\n\n";
}

int listOfAllBooks()
{

	fstream file(filename, ios::in);
	if (!file.is_open())
	{
		cout << "Error opening file" << endl;
		return 0;
	}
	string line;
	cout << setw(20) << "Book Name" << setw(20) << setw(20) << "Author Name"
		<< setw(20) << setw(20) << "ISBN Number" << setw(20) << setw(20) << "Date\n\n";
	while (getline(file, line))
	{
		displayLine(line);
		cout << "\n";
	}
	file.close();
	cout << "\n\n";
}

void displayLine(string line)
{
	string word;
	stringstream ss(line);
	while (getline(ss, word, ','))
	{
		cout << setw(20) << word << setw(20);
	}
}
