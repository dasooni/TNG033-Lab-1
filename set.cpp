#include "set.hpp"
using namespace std;

// std::size_t is defined in the C++ standard library
// std::size_t is an unsigned integer type that can store the maximum size of any possible object
// sizes are non-negative integers -- i.e. unsigned integer type

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

void Set::insert(Node* p, int value) const
{
    Node* newNode = new Node(value, nullptr);
    newNode->next = p->next;
    p->next = newNode;
}


/* ******************************************************** */

// Default constructor
Set::Set() {

    //Head is an identifier for a dummy node?
    // Constructor node expects two inputs, a value and a pointer.
    //So a dummy node is made with value 0 and nullptr as pointer to the next node. 
    head = new Node(0, nullptr);
}

// Constructor for creating a set from an int
Set::Set(int v) {
    // Create a element v in the set, point to the next node
    //Example (IGNORE): head = new node();, head -> data = 1, head -> next = second
    head = new Node(0, nullptr);
    insert(head, v);
}

// Constructor: create a set with the elements in V
// V is not sorted and may contain repeated elements
Set::Set(const std::vector<int>& V) {
    // Create a set with nodes in vector V

    head = new Node(0, nullptr);

    Node* p = head;
    
    for (unsigned int i = 0; i < V.size(); i++) 
    {
        if (V.at(i) )  {

            p = p->next;
        }
        insert(p, V.at(i));
        
            
    }
   
}

// copy constructor
Set::Set(const Set& source) {
    // ADD CODE
}

// Assignment operator: copy-and-swap idiom
// Uses the copy constructor and the destructor
Set& Set::operator=(Set s) {
    // ADD CODE

    return *this;
}

// Destructor: deallocate all nodes
Set::~Set() {
    Node* p = head;

    while (p != nullptr) {
        head = head->next;
        delete p;
        p = head;
    }

    head = nullptr;
}


// Return number of elements in the set
std::size_t Set::cardinality() const {
    
    int counter = 0;

    Node* p = head->next;

    while (p != nullptr) {
        counter++;
        p = p->next;
    }
    return counter;  // delete if needed
}

// Test if set is empty
bool Set::empty() const {
   
    if (head->next != nullptr) {
        return false;
    }
    else {
        return true;
    }
}

// Test if x is an element of the set
bool Set::member(int x) const {
    // ADD CODE

    return false;  // delete if needed
}

bool Set::operator<=(const Set& b) const {
    // ADD CODE

    return false;  // delete if needed
}

bool Set::operator==(const Set& b) const {
    // ADD CODE

    return false;  // delete if needed
}

bool Set::operator!=(const Set& b) const {
    // ADD CODE

    return false;  // delete if needed
}

bool Set::operator<(const Set& b) const {
    // ADD CODE

    return false;  // delete if needed
}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const {
    // ADD CODE

    return Set{};  // delete if needed
}

// Set intersection
Set Set::operator*(const Set& b) const {
    // ADD CODE

    return Set{};  // delete if needed
}

// Set difference
Set Set::operator-(const Set& b) const {
    // ADD CODE

    return Set{};  // delete if needed
}

// set difference with set {x}
Set Set::operator-(int x) const {
    // ADD CODE

    return Set{};  // delete if needed
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Set& theSet) {
    if (theSet.empty()) {
        os << "Set is empty!";
    } else {
        Set::Node* temp = theSet.head->next;
        os << "{ ";

        while (temp != nullptr) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
    return os;
}

/********** Private member functions ************/


