#include <iostream>
#include <string>
#include <vector>

using namespace std;

// InventoryItem class definition (base class)
class InventoryItem
{
private:
    string title;
    int stock;
    float sell_price;
    float buy_price;
    string genre;
    string age_group;

public:
    // Constructor
    InventoryItem(string t, int s, float sp, float bp, string g, string ag) : title(t), stock(s), sell_price(sp), buy_price(bp), age_group(ag) {}

    // Getters
    string getTitle() const { return title; }
    int getStock() const { return stock; }
    float getSellPrice() const { return sell_price; }
    float getBuyPrice() const { return buy_price; }
    string getGenre() const { return genre; }
    string getAgeGroup() const { return age_group; }

    // Setters
    void setTitle(string t) { title = t; }
    void setStock(int s) { stock = s; }
    void setSellPrice(float sp) { sell_price = sp; }
    void setBuyPrice(float bp) { sell_price = bp; }
    void setGenre(string g) { genre = g; }
    void setAgeGroup(string ag) { age_group = ag; }

    // Buy a publication
    void sell(int num)
    {
        if (stock > num)
        {
            stock -= num;
            cout << "Successfully sold " << num << " copies of " << title << "." << endl;
        }
        else
        {
            cout << "Sorry, we're out of stock for " << title << "." << endl;
        }
    }

    // Restock a publication
    void restock(int num)
    {
        stock += num;
        cout << "Successfully restocked " << title << " with " << num << " copies." << endl;
    }

    virtual void view() {}
};

// Book class definition (derived class)
class Book : public InventoryItem
{
private:
    string author;
    string publisher;

public:
    // Constructor
    Book(string t, int s, float sp, float bp, string g, string ag, string a, string pb) : InventoryItem(t, s, sp, bp, g, ag), author(a), publisher(pb) {}

    // Getters
    string getAuthor() const { return author; }
    string getPublisher() const { return publisher; }

    // Setters
    void setAuthor(string a) { author = a; }
    void setPublisher(string pb) { publisher = pb; }

    void view()
    {
        cout << "Title: " << this->getTitle() << endl;
        cout << "Author: " << this->getAuthor() << endl;
        cout << "Price: " << this->getSellPrice() << endl;
        cout << "Age Group: " << this->getAgeGroup() << endl;
        cout << "Publisher: " << this->getPublisher() << endl;
        cout << endl;
    }
};

// Magazine class definition (derived class)
class Magazine : public InventoryItem
{
private:
    string issue;

public:
    // Constructor
    Magazine(string t, int s, float sp, float bp, string g, string ag, string i) : InventoryItem(t, s, sp, bp, g, ag), issue(i) {}

    // Getters
    string getIssue() const { return issue; }

    // Setters
    void setIssue(string i) { issue = i; }
    void view()
    {
        cout << "Title: " << this->getTitle() << endl;
        cout << "Price: " << this->getSellPrice() << endl;
        cout << "Age Group: " << this->getAgeGroup() << endl;
        cout << "Issue: " << this->getIssue() << endl;
        cout << endl;
    }
};

class Cashier
{
public:
    int total_cash = 0;
};

class StoreManager
{
public:
    void menu(vector<InventoryItem *> &publications, vector<Book *> &books, vector<Magazine *> magazines, Cashier &cashier)
    {
        int instruction;
        while (1)
        {
            cout << "Press 1 to sell a book or magazine" << endl;
            cout << "Press 2 to add new copies of a publication" << endl;
            cout << "Press 3 if you are not store manager" << endl;
            cin >> instruction;

            if (instruction == 1)
            {
                cout << "Enter the title of the book or magazine you wish to sell: ";
                string n;
                cin.ignore();
                std::getline(std::cin >> std::ws, n);
                for (int i = 0; i < publications.size(); i++)
                {
                    if (publications[i]->getTitle() == n)
                    {
                        cout << "Enter the number of copies you wish to sell: ";
                        int num;
                        cin >> num;
                        publications[i]->sell(num);
                        cashier.total_cash += publications[i]->getSellPrice() * num;
                        return;
                    }
                }
                cout << "Sorry, we dont have that book." << endl
                     << endl;
            }
            if (instruction == 2)
            {
                cout << "Enter the title of the book or magazine you wish to restock: ";
                // char *sn;
                // cin.getline(sn, 50);
                string n;
                cin.ignore();
                std::getline(std::cin >> std::ws, n);
                for (int i = 0; i < publications.size(); i++)
                {
                    if (publications[i]->getTitle() == n)
                    {
                        cout << "Enter the number of copies you wish to restock: ";
                        int num;
                        cin >> num;
                        publications[i]->restock(num);
                        cashier.total_cash -= publications[i]->getBuyPrice() * num;
                        return;
                    }
                }
                cout << "We dont have that. Please enter all the details:" << endl;
                cout << "Enter the number of copies: ";
                int num;
                cin >> num;
                cout << "Enter the sell price: ";
                float sp;
                cin >> sp;
                cout << "Enter the buy price: ";
                float bp;
                cin >> bp;
                cout << "Enter the genre: ";
                string g;
                cin.ignore();
                std::getline(std::cin >> std::ws, g);
                cout << "Enter the age group of targeted audience: ";
                string ag;
                cin.ignore();
                std::getline(std::cin >> std::ws, ag);
                int b_or_m;
                cout << "Press 1 if it is a book, 2 if it is a magazine: ";
                cin >> b_or_m;
                if (b_or_m == 1)
                {
                    cout << "Enter the name of author: ";
                    string a;
                    cin.ignore();
                    std::getline(std::cin >> std::ws, a);
                    cout << "Enter the name of publisher: ";
                    string pb;
                    cin.ignore();
                    std::getline(std::cin >> std::ws, pb);
                    books.push_back(new Book(n, num, sp, bp, g, ag, a, pb));
                    publications.push_back(books[books.size() - 1]);
                }
                if (b_or_m == 2)
                {
                    cout << "Enter the issue month: ";
                    string is;
                    cin.ignore();
                    std::getline(std::cin >> std::ws, is);
                    magazines.push_back(new Magazine(n, num, sp, bp, g, ag, is));
                    publications.push_back(magazines[magazines.size() - 1]);
                }
                cashier.total_cash -= bp * num;
                cout << endl;
            }
            if (instruction == 3)
            {
                cout << endl;
                break;
            }
        }
    }
};

class Customer
{
public:
    void buy(vector<InventoryItem *> &publications, Cashier &cashier)
    {
        cout << "Enter the title of the book or magazine you wish to buy: ";
        string n;
        cin.ignore();
        std::getline(std::cin >> std::ws, n);
        for (int i = 0; i < publications.size(); i++)
        {
            if (publications[i]->getTitle() == n)
            {
                cout << "Enter the number of copies you wish to buy: ";
                int num;
                cin >> num;
                publications[i]->sell(num);
                cashier.total_cash += publications[i]->getSellPrice() * num;
                publications[i]->view();
                cout << endl;
                return;
            }
        }
        cout << "Sorry, we dont have that book." << endl
             << endl;
    }
};

void printInventory(vector<InventoryItem *> &publications)
{
    for (int i = 0; i < publications.size(); i++)
    {
        cout << "- " << publications[i]->getTitle() << ": " << publications[i]->getStock() << " copies" << endl;
    }
    cout << endl;
}

int main()
{
    // Create vectors to store our publications
    vector<InventoryItem *> publications;
    vector<Book *> books;
    vector<Magazine *> magazines;

    // Add some books and magazines to the inventory
    books.push_back(new Book("The Great Gatsby", 5, 499, 10, "Classics", "Adults", "F. Scott Fitzgerald", "Penguin"));
    books.push_back(new Book("Moby Dick", 5, 499, 10, "Classics", "Adults", "Herman Melville", "Penguin"));
    books.push_back(new Book("Pride and Prejudice", 5, 499, 10, "Classics", "Adults", "Jane Austen", "Penguin"));
    magazines.push_back(new Magazine("Time", 10, 299, 10, "Business", "Adults", "January 2021"));
    magazines.push_back(new Magazine("National Geographic", 15, 149, 10, "Nature", "All Ages", "February 2021"));
    magazines.push_back(new Magazine("Cosmopolitan", 15, 149, 10, "Novelty", "Women", "March 2021"));

    // Add all publications to the publications vector
    for (Book *book : books)
    {
        publications.push_back(book);
    }
    for (Magazine *magazine : magazines)
    {
        publications.push_back(magazine);
    }

    cout << "                   WELCOME!!" << endl;
    cout << "We have the following books and magazines available currently: " << endl;

    printInventory(publications);

    Cashier cashier;

    int instruction;
    while (1)
    {
        cout << "Press 1 if you are the store manager." << endl;
        cout << "Press 2 if you are a customer." << endl;
        cout << "Press 3 to see the available stock." << endl;
        cout << "Press 4 to see the cash balance." << endl;
        cout << "Press 5 to leave the bookstore." << endl;
        cin >> instruction;
        if (instruction == 1)
        {
            cout << "Hello, Store Manager, here you can manage the store." << endl;
            StoreManager sm;
            sm.menu(publications, books, magazines, cashier);
        }
        if (instruction == 2)
        {
            cout << "Hello, Customer, here you can buy books from the store." << endl;
            Customer c;
            c.buy(publications, cashier);
        }
        if (instruction == 3)
        {
            printInventory(publications);
        }
        if (instruction == 4)
        {
            cout << "Rs. " << cashier.total_cash << endl
                 << endl;
        }
        if (instruction == 5)
        {
            break;
        }
    }
}