/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int MAX_CONTACTS = 100;

class Contact {
private:
    string name;
    string phoneNumber;
    string address;

public:
    void setContact(string n, string num, string a) {
        name = n;
        phoneNumber = num;
        address = a;
    }

    string getName() const {
        return name;
    }

    void display() const {
        cout << "Name: " << name << ", Phone Number: " << phoneNumber << ", Address: " << address << endl;
    }

    // Save contact to file
    void saveToFile(ofstream &file) const {
        file << name << "\n" << phoneNumber << "\n" << address << "\n";
    }

    // Load contact from file
    static Contact loadFromFile(ifstream &file) {
        string n, num, a;
        getline(file, n);
        getline(file, num);
        getline(file, a);
        Contact c;
        c.setContact(n, num, a);
        return c;
    }
};

class ContactManager {
private:
    Contact contacts[MAX_CONTACTS];
    int contactCount;

public:
    ContactManager() : contactCount(0) {}

    void addContact() {
        if (contactCount >= MAX_CONTACTS) {
            cout << "Contact list is full!" << endl;
            return;
        }

        string name, phoneNumber, address;
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter phone number: ";
        getline(cin, phoneNumber);
        cout << "Enter address: ";
        getline(cin, address);

        contacts[contactCount].setContact(name, phoneNumber, address);
        contactCount++;
        cout << "Contact added successfully!" << endl;
    }

    void viewContacts() const {
        if (contactCount == 0) {
            cout << "No contacts available." << endl;
            return;
        }
        cout << "Contacts List:" << endl;
        for (int i = 0; i < contactCount; i++) {
            contacts[i].display();
        }
    }

    void deleteContact() {
        string name;
        cout << "Enter the name of the contact to delete: ";
        getline(cin, name);

        for (int i = 0; i < contactCount; i++) {
            if (contacts[i].getName() == name) {
                contacts[i] = contacts[contactCount - 1]; // Replace with last contact
                contactCount--;
                cout << "Contact deleted successfully!" << endl;
                return;
            }
        }
        cout << "Contact not found." << endl;
    }

    void searchContact() const {
        string name;
        cout << "Enter the name of the contact to search: ";
        getline(cin, name);

        for (int i = 0; i < contactCount; i++) {
            if (contacts[i].getName() == name) {
                contacts[i].display();
                return;
            }
        }
        cout << "Contact not found." << endl;
    }

    void saveContactsToFile(const string &filename) const {
        ofstream file(filename);
        if (!file) {
            cout << "Unable to open file for writing." << endl;
            return;
        }

        for (int i = 0; i < contactCount; i++) {
            contacts[i].saveToFile(file);
        }
        file.close();
        cout << "Contacts saved to file successfully!" << endl;
    }

    void loadContactsFromFile(const string &filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Unable to open file for reading." << endl;
            return;
        }

        contactCount = 0; // Reset contact count
        while (file.peek() != EOF && contactCount < MAX_CONTACTS) {
            contacts[contactCount] = Contact::loadFromFile(file);
            contactCount++;
        }
        file.close();
        cout << "Contacts loaded from file successfully!" << endl;
    }

    void menu() {
        int choice;
        do {
            cout << "\nContact Management System" << endl;
            cout << "1. Add Contact" << endl;
            cout << "2. View Contacts" << endl;
            cout << "3. Delete Contact" << endl;
            cout << "4. Search Contact" << endl;
            cout << "5. Save Contacts to File" << endl;
            cout << "6. Load Contacts from File" << endl;
            cout << "7. Exit" << endl;
            cout << "Choose an option: ";
            cin >> choice;
            cin.ignore(); // Clear the newline character from the input buffer

            switch (choice) {
                case 1:
                    addContact();
                    break;
                case 2:
                    viewContacts();
                    break;
                case 3:
                    deleteContact();
                    break;
                case 4:
                    searchContact();
                    break;
                case 5: {
                    string filename;
                    cout << "Enter filename to save contacts: ";
                    getline(cin, filename);
                    saveContactsToFile(filename);
                    break;
                }
                case 6: {
                    string filename;
                    cout << "Enter filename to load contacts: ";
                    getline(cin, filename);
                    loadContactsFromFile(filename);
                    break;
                }
                case 7:
                    cout << "Exiting the program." << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 7);
    }
};

int main() {
    ContactManager cm;
    cm.menu();
    return 0;
}
