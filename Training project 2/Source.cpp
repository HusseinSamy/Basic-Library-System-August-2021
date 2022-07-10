#include <iostream>
#include <vector> 


using namespace std; 

struct book
{
	string name, bookAuthor, field;
	int price, qty, id, duration;

	book(string name, string bookAuthor, string field, int price, int qty, int id)
		: name{ name }, bookAuthor{ bookAuthor }, field{ field }, price{ price }, qty{ qty }, id{ id }, duration{ NULL } {};
};

vector <book> allBooks; 

book searchInAllBooks(int id)
{
	for (int i = 0; i < allBooks.size(); i++)
	{
		if (id == allBooks[i].id)
		{
			return allBooks[i];
		}
	}
	book notFound(" ", " ", " ", NULL, NULL, NULL);
	return notFound;
}

void displayBook(book display)
{
	cout << "Name: " << display.name << endl;
	cout << "ID: " << display.id << endl;
	cout << "Author name:  " << display.bookAuthor << endl;
	cout << "Field: " << display.field << endl;
	cout << "Price: " << display.price << endl;
	cout << "Quantity:  " << display.qty << endl << endl;
}

void displayAllBooks()
{
	if (allBooks.size() > 0)
	{
		for (int i = 0; i < allBooks.size(); i++)
		{
			displayBook(allBooks[i]);
			cout << "=======================================================" << endl;
		}
	}
	else
	{
		cout << "There is no books in the library yet!" << endl;
	}
}

class admin
{
public:
	void createBook()
	{
		string name, bookAuthor, field;
		int price, qty, id;

		cout << "Name: ";
		cin >> name; 
		cout << "ID: ";
		cin >> id;
		cout << "Author name:  ";
		cin >> bookAuthor;
		cout << "Field: " ;
		cin >> field;
		cout << "Price: "; 
		cin >> price;
		cout << "Quantity:  "; 
		cin >> qty;

		book books(name, bookAuthor, field, price, qty, id); 
		allBooks.push_back(books);
	}

	void updateBook()
	{
		int id;
		int process; 
		bool loop = false; 
		cout << "Book ID: ";
		cin >> id;

		book result = searchInAllBooks(id);
		if (result.id != NULL)
		{
			while (!loop)
			{

				cout << "1- Update Name  |   2- Update Price  |  3- Update Author Name  |   4- Update field  |  5- Update Quantity  | 6- Quit Updating " << endl;
				cin >> process;

				if (process == 1)
				{
					string newName;
					cout << "New Name: ";
					cin >> newName;
					cout << endl;
					result.name = newName;

					displayBook(result);
				}
				else if (process == 2)
				{
					int newPrice;
					cout << "New Price: ";
					cin >> newPrice;
					cout << endl;
					result.price = newPrice;

					displayBook(result);
				}
				else if (process == 3)
				{
					string newAuthorName;
					cout << "New Author Name: ";
					cin >> newAuthorName;
					result.bookAuthor = newAuthorName;
					cout << endl;
					displayBook(result);
				}
				else if (process == 4)
				{
					string newField;
					cout << "New Field: ";
					cin >> newField;
					result.field = newField;
					cout << endl;
					displayBook(result);
				}
				else if (process == 5)
				{
					int newQty;
					cout << "New Quantity: ";
					cin >> newQty;
					result.qty = newQty;

					displayBook(result);
				}
				else if (process == 6)
				{
					loop = true;
				}
				else
				{
					cout << "Please enter a valid process code!" << endl;
				}
			} 
		}
		else
		{
			cout << "Please enter a valid ID!" << endl;
		}
	}

	void deleteBook()
	{
		int id; 

		cout << "Book ID: ";
		cin >> id;
		
		for (int i = 0; i < allBooks.size(); i++)
		{
			if (allBooks[i].id == id)
			{
				allBooks.erase(allBooks.begin() + i);
				cout << "Book deleted successfully! " << endl;
			}
			else
			{
				cout << "Invalid ID! " << endl;
			}
		}
	}

};

class student
{
	
	void displayBorrowedBook(book display)
	{
		
		cout << "Name: " << display.name << endl;
		cout << "ID: " << display.id << endl;
		cout << "Author name:  " << display.bookAuthor << endl;
		cout << "Field: " << display.field << endl;
		cout << "Price: " << display.price << endl;
		cout << "Quantity:  " << display.qty << endl;
		cout << "Duration: " << display.duration << " Days" << endl << endl;
	}

public:
	string name;
	int age, level,id,duration;
	vector<book> borrowedBooks;
	
	student(string name, int age, int level, int id, int duration)
		: name{ name }, age{ age }, level{ level }, id{ id }, duration{ duration } {};

	void displayBorrowedBooks()
	{
		if (borrowedBooks.size() > 0)
		{
			cout << "Your borrowed books: " << endl;
			cout << "=======================================================" << endl;
			for (int i = 0; i < borrowedBooks.size(); i++)
			{
				displayBorrowedBook(borrowedBooks[i]);
				cout << "=======================================================" << endl;
			}
		}
		else
		{
			cout << "You don't have any book in your borrwing list" << endl;
		}
	}

	book searchBorrowedBooks(int id, int *idx)
	{
		for (int i = 0; i < borrowedBooks.size(); i++)
		{
			if (borrowedBooks[i].id == id)
			{
				*idx = i;
				return borrowedBooks[i];
			}
		}
		book notFound("", "", "", NULL, NULL, NULL);
		return notFound;
	}

	void borrowBook()
	{
		int bookID, duration;
		cout << "Book ID: ";
		cin >> bookID;
		book res = searchInAllBooks(bookID);
		if (res.id == NULL)
		{
			cout << "There is no book with this ID!" << endl;
		}
		else
		{
			res.qty--;
			borrowedBooks.push_back(res);
			cout << endl;
			cout << "When will you return the book (in days): ";
			cin >> duration;
			int lastElement = borrowedBooks.size()-1;
			borrowedBooks[lastElement].duration = duration;
			cout << endl;
			displayBorrowedBooks();
		}
	}

	void returnBook()
	{
		int bookId;
		int bookIdx = -1;

		cout << "Book ID: ";
		cin >> bookId;
		cout << endl;

		book res = searchBorrowedBooks(bookId, &bookIdx);
		if (res.id == NULL)
		{
			cout << "Book not found in your borrowing list!" << endl;

		}
		else
		{
			res.qty++;
			borrowedBooks.erase(borrowedBooks.begin() + bookIdx);
			displayBorrowedBooks();
		}
	}

};

vector<student> students;

void createNewStudent()
{
	string name;
	int age, level,id, duration;

	cout << "Name: ";
	cin >> name; 
	cout << "Age: ";
	cin >> age; 
	cout << "Level: ";
	cin >> level; 
	cout << "ID: ";
	cin >> id;
	student a(name,age,level,id, NULL);
	students.push_back(a);
}

class libraryMenu
{
	int roleAns = 0;
	int admAns = 0;
	int studentAns = 0;
	int studentID = -1;
	bool studentFound = false;
	int idx = -1;
public:
	void roleMenuLoop()
	{

		cout << "1- Admin   |   2- Student   |    3- Quit" << endl;
		cin >> roleAns;

		if (roleAns == 1)
		{
			adminLoop();
		}

		else if (roleAns == 2)
		{
			if (students.size() == 0)
			{
				cout << "There is no students on our system now \nPlease enter your credentials" << endl;
				cout << "=======================================================" << endl;
				createNewStudent();
				cout << "=======================================================" << endl;
				roleMenuLoop();
			}
			studentLoop();
		}

		else if (roleAns == 3)
		{
			exit(0);
		}

		else
		{
			cout << "Enter a valid code!" << endl;
			roleMenuLoop();
		}
	}

	void adminLoop()
	{
		cout << "=======================================================" << endl;
		admin ad;
		cout << "Process:\n1- Create Book   |   2- Update Book   |   3- Delete Book   |   4- Display All Books   |   5- Role Menu   |   6- Quit" << endl;
		cin >> admAns;

		if (admAns == 1)
		{
			cout << "=======================================================" << endl;

			ad.createBook();
			adminLoop();
		}

		else if (admAns == 2)
		{
			cout << "=======================================================" << endl;

			ad.updateBook();
			adminLoop();
		}

		else if (admAns == 3)
		{
			cout << "=======================================================" << endl;

			ad.deleteBook();
			adminLoop();
		}

		else if (admAns == 4)
		{
			cout << "=======================================================" << endl;

			displayAllBooks();
			adminLoop();
		}

		else if (admAns == 5)
		{
			cout << "=======================================================" << endl;

			roleMenuLoop();
		}

		else if (admAns == 6)
		{
			exit(0);
		}

		else
		{
			cout << "Please enter a valid code!" << endl;
			adminLoop();
		}
	}

	void studentLoop()
	{
		if (studentFound == false)
		{
			cout << "=======================================================" << endl;
			cout << "Your Studenet ID: " ;
			cin >> studentID;
		}
		else if (studentFound == true)
		{
			cout << "=======================================================" << endl;
			cout << "Process:\n1- Borrow Book  |  2- Return Book  |  3- Display You Borrowed Books  |  4- Role Menu  |  5- Quit" << endl;
				cin >> studentAns;

				if (studentAns == 1)
				{
					cout << "=======================================================" << endl;
					students[idx].borrowBook();
					studentLoop();
				}

				else if (studentAns == 2)
				{
					cout << "=======================================================" << endl;
					students[idx].returnBook();
					studentLoop();
				}

				else if (studentAns == 3)
				{
					cout << "=======================================================" << endl;
					students[idx].displayBorrowedBooks();
					studentLoop();
				}

				else if (studentAns == 4)
				{
					cout << "=======================================================" << endl;
					studentFound = false;
					idx = -1;
					roleMenuLoop();
				}

				else if (studentAns == 5)
				{
					exit(0);
				}

				else
				{
					cout << "Please enter a valid code!" << endl;
					studentLoop();
				}
		}
		for (int i = 0; i < students.size(); i++)
		{
			if (students[i].id == studentID)
			{
				studentFound = true;
				idx = i;
				studentLoop();
				
			}
		}
		cout << "Please enter a valid student ID!" << endl;
		studentFound = false;
		studentLoop();
	}
};
void main()
{
	libraryMenu menu; 
	menu.roleMenuLoop();
	
}