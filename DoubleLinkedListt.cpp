#include <iostream>
using namespace std;

// Structure for doubly linked list node
struct Node {
    int noMhs;
    string name;
    Node *next;
    Node *prev;
};

// START pointer initialization
Node *START  = NULL;

// Function to check if list is empty
bool listEmpty() {
    return (START == NULL) ;
}

// Function to search for a node by roll number
bool search(int rollNo, Node **previous, Node **current)  {
    *previous = NULL;
    *current = START;
    while (*current != NULL && (*current)->noMhs != rollNo) {
        *previous = *current;
        *current = (*current)->next;
    }
    return (*current != NULL);
}

// Function to add a new node
void addNode() {
    Node *newNode = new Node();
    cout << "\nEnter the roll number of the student: ";
    cin >> newNode->noMhs;
    cout << "Enter the name of the student: ";
    cin >> newNode->name;

    // Duplicate check
    Node *prev, *curr;
    if (search(newNode->noMhs, &prev, &curr)) {
        cout << "\033[31mDuplicate roll numbers not allowed\033[0m" << endl;
        delete newNode;
        return;
    }

    // Insert at beginning if list is empty or new node is smallest
    if (START == NULL || newNode->noMhs <= START->noMhs) {
        newNode->next = START;
        newNode->prev = NULL;
        if (START != NULL)
            START->prev = newNode;
        START = newNode;
        return;
    }

    // Insert in the middle or end
    Node *current = START;
    Node *previous = NULL;
    while (current != NULL && current->noMhs < newNode->noMhs) {
        previous = current;
        current = current->next;
    }

    newNode->next = current;
    newNode->prev = previous;
    if (current != NULL)
        current->prev = newNode;
    if (previous != NULL)
        previous->next = newNode;
}

// Function to delete a node by roll number
void deleteNode() {
    if (listEmpty()) {
        cout << "List is empty" << endl;
        return;
    }

    int rollNo;
    cout << "\nEnter the roll number of the student whose record is to be deleted: ";
    cin >> rollNo;

    Node *previous, *current;
    if (!search(rollNo, &previous, &current)) {
        cout << "\033[31mThe record with roll number " << rollNo << " not found\033[0m" << endl;
        return;
    }

    if (current == START) {
        START = START->next;
        if (START != NULL)
            START->prev = NULL;
    } else {
        previous->next = current->next;
        if (current->next != NULL)
            current->next->prev = previous;
    }

    delete current;
    cout << "\x1b[32mRecord with roll number " << rollNo << " deleted\x1b[0m" << endl;
}

// Function to display all records in ascending order
void traverse() {
    if (listEmpty()) {
        cout << "\nList is empty" << endl;
        return;
    }

    cout << "\nRecords in ascending order of roll number are:\n";
    Node *current = START;
    while (current != NULL) {
        cout << current->noMhs << " " << current->name << endl;
        current = current->next;
    }
}

// Function to display all records in descending order
void revtraverse() {
    if (listEmpty()) {
        cout << "\nList is empty" << endl;
        return;
    }

    cout << "\nRecords in descending order of roll number are:\n";
    Node *current = START;
    while (current->next != NULL)
        current = current->next;

    while (current != NULL) {
        cout << current->noMhs << " " << current->name << endl;
        current = current->prev;
    }
}

// Function to search and display a record
void searchData() {
    if (listEmpty()) {
        cout << "\nList is empty" << endl;
        return;
    }

    int rollNo;
    cout << "\nEnter the roll number of the student whose record you want to search: ";
    cin >> rollNo;

    Node *previous, *current;
    if (!search(rollNo, &previous, &current)) {
        cout << "\nRecord not found" << endl;
    } else {
        cout << "\nRecord found" << endl;
        cout << "Roll number: " << current->noMhs << endl;
        cout << "Name: " << current->name << endl;
    }
}

// Main program loop
int main() 
{
    while (true) {
        try {
            cout << "\nMenu\n";
            cout << "1. Add a record to the list\n";
            cout << "2. Delete a record from the list\n";
            cout << "3. View all records in the ascending order of roll numbers\n";
            cout << "4. View all records in the descending order of roll numbers\n";
            cout << "5. Search for a record in the list\n";
            cout << "6. Exit\n";
            cout << "\nEnter your choice (1-6): ";
            char ch;
            cin >> ch;

            switch (ch) {
            case '1':
                addNode();
                break;
            case '2':
                deleteNode();
                break;
            case '3':
                traverse();
                break;
            case '4':
                revtraverse();
                break;
            case '5':
                searchData();
                break;
                searchData();
                break;
            case '6':
                return 0;
            default:
                   cout << "\nInvlid option" << endl;
                   break;
            }

        }
        catch (exception &e)
        {
            cout << "Check for the values entered." <<endl;
        }
    }
}