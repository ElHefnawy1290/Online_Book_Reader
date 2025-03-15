#include <iostream>
#include <chrono>
#include <vector>
#include <map>
#include <iomanip>
#include <utility>
#include <sstream>
#include <ctime>
#include <set>
#include <limits.h>

using namespace std;

int toInt(string s)
{
    istringstream iss(s);
    int val;
    iss >> val;
    return val;
}

string GetCurrentTimeDate()
{ // src: https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
    auto now = chrono::system_clock::now();
    auto in_time_t = chrono::system_clock::to_time_t(now);
    ostringstream oss;
    oss << put_time(localtime(&in_time_t), "%Y-%m-%d %X");
    return oss.str();
}

class User
{
private:
    string name;
    string password;
    string user_name;
    string email;
    int id;

public:
    User() = default;

    User(string name, string password, string user_name, string email) : name(name), password(password), user_name(user_name), email(email) {}

    void setID(int id)
    {
        this->id = id;
    }

    int getID() const
    {
        return id;
    }

    const string &getName() const
    {
        return name;
    }

    void setName(const string &name)
    {
        this->name = name;
    }

    const string &getPassword() const
    {
        return password;
    }

    void setPassword(const string &password)
    {
        this->password = password;
    }

    const string &getUserName() const
    {
        return user_name;
    }

    void setUserName(const string &user_name)
    {
        this->user_name = user_name;
    }

    const string &getEmail() const
    {
        return email;
    }

    void setEmail(const string &email)
    {
        this->email = email;
    }

    void readUser()
    {
        string str;
        cout << "Enter user name (no spaces): ";
        cin >> str;
        setUserName(str);
        cout << "\nEnter Password (no spaces): ";
        cin >> str;
        setPassword(str);
        cout << "\nEnter name (no spaces): ";
        cin >> str;
        setName(str);
        cout << "\nEnter email (no spaces): ";
        cin >> str;
        setEmail(str);
    }

    void printUser()
    {
        cout << "Name: " << getName() << "\n";
        cout << "Email: " << getEmail() << "\n";
        cout << "User name: " << getUserName() << "\n";
    }
};

class Book
{
private:
    string ISBN;
    string title;
    string author_name;
    int number_of_pages;
    vector<string> book_content{};

public:
    Book() = default;

    const string &getISBN() const
    {
        return ISBN;
    }

    void setISBN(const string &ISBN)
    {
        this->ISBN = ISBN;
    }

    const string &getTitle() const
    {
        return title;
    }

    void setTitle(const string &title)
    {
        this->title = title;
    }

    const string &getAuthorName()
    {
        return author_name;
    }

    void setAuthorName(const string &author_name)
    {
        this->author_name = author_name;
    }

    int getNumberOfPages()
    {
        return number_of_pages;
    }

    void setNumberOfPages(int number_of_pages)
    {
        this->number_of_pages = number_of_pages;
    }

    void readBook()
    {
        string str;
        int num;
        cout << "Enter ISBN: ";
        cin >> str;
        setISBN(str);
        cout << "Enter title: ";
        cin >> str;
        setTitle(str);
        cout << "Enter Author name: ";
        cin >> str;
        setAuthorName(str);
        cout << "Enter how many pages: ";
        cin >> num;
        setNumberOfPages(num);
        cout << "\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        for (int i = 0; i < num; i++)
        {
            cout << "Enter page # " << i + 1 << ":";
            getline(cin, str);
            book_content.push_back(str);
        }
    }

    const string &getPageContent(int page) const
    {
        return book_content[page - 1];
    }
};

class BookReadingSession
{
private:
    Book book;
    int current_page;

public:
    BookReadingSession() = default;

    const Book &getBook() const
    {
        return book;
    }

    void setBook(const Book &book)
    {
        this->book = book;
    }

    int getCurrentPage()
    {
        return current_page;
    }

    void setCurrentPage(int current_page)
    {
        this->current_page = current_page;
    }

    bool hasNext()
    {
        return current_page < book.getNumberOfPages();
    }

    void getNext()
    {
        current_page++;
    }

    bool hasPrev()
    {
        return current_page > 1;
    }

    void getPrev()
    {
        current_page--;
    }

    pair<int, string> start(const Book &book, int current_page = 1)
    {
        setBook(book);
        setCurrentPage(current_page);
        int page = livePage();
        string time = GetCurrentTimeDate();
        pair<int, string> stat = {page, time};
        return stat;
    }

    int livePage()
    {
        cout << "Current page: " << current_page << "/" << book.getNumberOfPages() << "\n";
        cout << book.getPageContent(current_page) << "\n";
        cout << "Menu:\n";
        cout << "\t1: Next page\n";
        cout << "\t2: Previous Page\n";
        cout << "\t3: Stop reading\n";
        cout << "Enter a number in a range from 1 - 3: ";
        int num;
        cin >> num;
        if (num == 1)
        {
            if (hasNext())
                getNext();
        }
        else if (num == 2)
        {
            if (hasPrev())
                getPrev();
        }
        else
            return current_page;
        return livePage();
    }
};

class BooksManager
{
private:
    vector<Book> books;
    BookReadingSession session;

public:
    BooksManager() = default;

    pair<pair<int, string>, Book> selectBookToReadFromList()
    {
        pair<pair<int, string>, Book> result{};
        cout << "Which book to read?:\n";
        if (books.empty())
            cout << "There are no available books in the library right now\n";
        else
        {
            cout << "Select number in range from 1 - " << books.size() << ": ";
            int num;
            cin >> num;
            result = {session.start(books[num - 1]), books[num - 1]};
        }
        return result;
    }

    pair<pair<int, string>, Book> selectBookToReadFromHistory(Book &book, int current_page)
    {
        pair<pair<int, string>, Book> result = {session.start(book, current_page), book};
        return result;
    }

    void addBook()
    {
        Book b;
        b.readBook();
        books.push_back(b);
    }

    void listBooks()
    {
        for (int i = 0; i < int(books.size()); i++)
            cout << i + 1 << " " << books[i].getTitle() << "\n";
    }
};

class UsersManager
{
private:
    static int id;
    vector<User> users;
    map<int, vector<pair<pair<int, string>, Book>>> users_history;
    User *current_user{};
    BooksManager books_manager;

public:
    UsersManager() = default;

    BooksManager &getBooksManager()
    {
        return books_manager;
    }

    User &getCurrentUser()
    {
        return *current_user;
    }

    string login()
    {
        string user_name;
        string password;
        cout << "Menu:\n";
        cout << "\tEnter user name (no spaces): ";
        cin >> user_name;
        cout << "\tEnter password (no spaces): ";
        cin >> password;
        if (user_name == "Elhefnawy" && password == "amr123453mr")
            return "Admin";
        for (auto &user : users)
        {
            if (user.getPassword() == password && user.getUserName() == user_name)
            {
                current_user = &user;
                return "User";
            }
        }
        cout << "Invalid input, wrong user name or password\n";
        return "";
    }

    void signUp()
    {
        User u;
        u.readUser();
        u.setID(id++);
        users.push_back(u);
        current_user = &users.back();
    }

    void selectFromBookList(int id)
    {
        books_manager.listBooks();
        pair<pair<int, string>, Book> result = books_manager.selectBookToReadFromList();
        if (result.first.second != "")
            users_history[id].push_back(result);
    }

    void selectFromBookHistory(int id)
    {
        if (users_history[id].empty())
        {
            cout << "No history, the history is empty\n";
            return;
        }
        listHistory(id);
        cout << "Which session to open? \n";
        cout << "Enter number in range from 1 - " << (int)users_history[id].size() << ": ";
        int num;
        cin >> num;
        Book book = users_history[id][num - 1].second;
        int current_page = users_history[id][num - 1].first.first;
        pair<pair<int, string>, Book> result = books_manager.selectBookToReadFromHistory(book, current_page);
        users_history[id].push_back(result);
    }

    void listHistory(int id)
    {
        int cnt = 1;
        while (cnt <= (int)users_history[id].size())
        {
            cout << cnt << ": " << users_history[id][cnt - 1].second.getTitle() << ": " << users_history[id][cnt - 1].first.first << "/" << users_history[id][cnt - 1].second.getNumberOfPages() << " - " << users_history[id][cnt - 1].first.second << "\n";
            cnt++;
        }
    }
};

int UsersManager::id = 1;

class UserView
{
private:
    UsersManager user_manager;
    User *current_user{};

public:
    UserView() = default;

    UsersManager &getUsersManager()
    {
        return user_manager;
    }
    void menu()
    {
        current_user = &user_manager.getCurrentUser();
        cout << "Hello " << current_user->getName() << " | User View\n";
        cout << "menu:\n";
        cout << "\t1: View profile\n";
        cout << "\t2: List & Select from my reading history\n";
        cout << "\t3: List & Select from available books\n";
        cout << "\t4: Logout\n\n";
        cout << "Enter a number in range from 1 - 4: ";
        int choice;
        cin >> choice;
        if (choice == 1)
            current_user->printUser();
        else if (choice == 2)
            user_manager.selectFromBookHistory(current_user->getID());
        else if (choice == 3)
            user_manager.selectFromBookList(current_user->getID());
        else
            return;
        menu();
    }
};

class AdminView
{
private:
    UsersManager *user_manager;
    BooksManager *books_manager;
    UserView user_view;

public:
    AdminView() = default;
    UserView &getUserView()
    {
        return user_view;
    }
    void menu()
    {
        user_manager = &user_view.getUsersManager();
        books_manager = &user_manager->getBooksManager();
        cout << "Hello Amr Elhefnawy | Admin view\n\n";
        cout << "Menu:\n";
        cout << "\t1: View Profile\n";
        cout << "\t2: Add Book\n";
        cout << "\t3: Logout\n";
        int num;
        cin >> num;
        if (num == 1)
        {
            cout << "User name: Elhefnawy\n";
            cout << "Email: amr223489@gmail.com\n";
            cout << "Name: Amr\n";
        }
        else if (num == 2)
        {
            books_manager->addBook();
        }
        else
            return;
        menu();
    }
};

class BookReaderSystem
{
private:
    AdminView admin_view;
    UserView *user_view;

public:
    BookReaderSystem() = default;
    void run()
    {
        user_view = &admin_view.getUserView();
        cout << "Menu:\n";
        cout << "\t1: Login\n";
        cout << "\t2: Signup\n";
        cout << "Enter a number in a range from 1 - 2: ";
        int choice;
        cin >> choice;
        if (choice == 1)
        {
            string answer = user_view->getUsersManager().login();
            if (answer == "")
                run();
            else if (answer == "Admin")
                admin_view.menu();
            else
                user_view->menu();
        }
        if (choice == 2)
        {
            user_view->getUsersManager().signUp();
            user_view->menu();
        }
        run();
    }
};
int main()
{
    BookReaderSystem().run();
    return 0;
}