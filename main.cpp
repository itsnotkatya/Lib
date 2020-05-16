/*Предметная область: Библиотека
Информационные объекты: Библиотека, Библиотекарь, Книги, Авторы, Посетитель
У книги может быть только один автор.
Посетитель посещает библиотеку с целью найти книгу по имени автора И/ИЛИ по названию книги.
Необходимо реализовать данный функционал, придерживаясь принципов DRY, KISS, YAGNI и Single Responsibility Principle*/

#include <iostream>
#include <vector>
using namespace std;

class Book {
private:
    string name;
    string author;
public:
    Book(const std::string name, const std::string author) {
        this->name = name;
        this->author = author;
    }
    const std::string &getName() const {
        return name;
    }
    const std::string &getAuthor() const {
        return author;
    }
    Book& operator= (const Book &book) {       // Перегрузка оператора присваивания
        name = book.name;                      // Выполняем копирование значений
        author = book.author;
        return *this;                          // Возвращаем текущий объект, чтобы иметь возможность связать в цепочку выполнение нескольких операций присваивания
    }
    friend std::ostream& operator<<(std::ostream& out, const Book &book);
};

class Library {
private:
    string NameofLibrary;
    int size;
public:
    static vector<Book> VectorBook;                             //вектор экземпляров класса Book

    Library(string _NameofLibrary, int _size) {
        NameofLibrary = _NameofLibrary;
        size = _size;
    }

    Library(vector<Book> &vectorBook) {
        VectorBook = vectorBook;
    }

    ~Library() {
        VectorBook.clear();
    }

    virtual void SearchBookByName(const Book &book) {
        string name = book.getName();
        for (int i = 0; i < size; i++) {
            if (name == VectorBook[i].getName()) {
                cout << "Book is found by name:" << name << endl;
            } else {
                cout << "Not found";
            }
        }
    }

    virtual void SearchBookByAuthor(const Book &book) {
        string author = book.getAuthor();
        for (int i = 0; i < size; i++) {
            if (author == VectorBook[i].getAuthor()) {
                cout << "Book is found by author:" << author << endl;
            } else {
                cout << "Not found";
            }
        }
    }

};

class Visitor {
public:
    Visitor();
    ~Visitor();
    string requestByName;
    string requestByAuthor;
    string request;


    std::string tellName(string requestByName) {
        return requestByName;
    }

    std::string tellAuthor(string requestByAuthor) {
        return requestByAuthor;
    }
};

class Librarian : public Library, Visitor {
public:
    Librarian();
    ~Librarian();

    std::string sayHello() {
        cout << "Hello!" << endl;
    }

    virtual void getBook (string request) {
        if (Visitor::tellName(requestByName) == requestByName) {
            Library::SearchBookByName(const Book &book);
        }
        if (Visitor::tellAuthor(requestByAuthor) == requestByAuthor) {
            Library::SearchBookByAuthor(const Book &book);
        }
    }
};

int main() {

    Library ("LondonLib",5);
    Book A1 = {"The Lord of the Rings", "J.R. Tolkien"};
    Book A2 = { "The Alchemist", "P. Coehlo"};
    Book A3 = {"Harry Potter and Deathly Hallows", "J.K. Rowling"};
    Book A4 = {"The Master and Margarita", "M. Bulgakov"};
    Book A5 = {"Dream of the Red Chamber", "C. Xueqin"};
    Library::VectorBook = {A1, A2, A3, A4, A5};

    Visitor V1;
    V1.tellName("Dream of the Red Chamber");

    Librarian L1;
    L1.getBook("Dream of the Red Chamber");


    return 0;
}