#include "set.hpp"



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
    //Node* newNode = new Node(value, nullptr);
    //newNode->next = p->next;
    //p->next = newNode;

    p->next = new Node(value, p->next);
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
Set::Set(const std::vector<int>& V){

    //create a dummy
    head = new Node(0, nullptr);
    
    for (int i : V) {

        Node* p = head; //node p points to dummy

        //sorting: while value of element i is greater than value of next node
        while (p->next != nullptr && (i > (p->next->value))) {
            p = p->next; //move to next node
        }
        //otherwise, if value of next node is not equal to a value in i, meaning the value
        //already exists in the set
        //insert it
        if (p->next == nullptr || p->next->value != i) {
            insert(p, i);
        }

    }
   
}

// copy constructor
Set::Set(const Set& source) :Set{}{ //create default constructor
    
    Node* p = source.head -> next; //point to dummy
    Node* p2 = head; //2nd node point to dummy
    
    while (p!= nullptr) { //while p still points to a existing node
        p2->next = new Node(p->value, nullptr); //COPY: set p2 to the value of node which p points to

        p = p->next; // p1 point to next node
        p2 = p2->next; // p2 point to next node until p has no more nodes to point to
    }
}

// Assignment operator: copy-and-swap idiom
// Uses the copy constructor and the destructor
Set& Set::operator=(Set s) {
    std::swap(head, s.head);
    
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
    return counter;  
}

// Test if set is empty
bool Set::empty() const {
  
    return (head->next == nullptr);


}

// Test if x is an element of the set
bool Set::member(int x) const {
    
    Node* p = head -> next; //skip the dummy

    while ( (p != nullptr) && (p -> value != x) ) {
        p = p->next;
    }
    if (p == nullptr) {
        return false;
    }
    else {
        return true;
    }

}

bool Set::operator<=(const Set& b) const {
    
    // left = "this"
    // right = arguement

    Node* rhs = head -> next;
   

    while (rhs != nullptr) { //while not null
        //if lhs (b) does not contain rhs value then it cant be a subset by definition
        if ( (b.member(rhs -> value)) == false) {
           
            return false;
        }
        //check all rhs values
        rhs = rhs->next;
    }
    //if statement is not called and all rhs values have been checked, so lhs has all the values 
    //that rhs has, meaning it is a subset
    return true;
        
  
}

bool Set::operator==(const Set& b) const {

    return  *this <= b && b <= *this; // == gives stackoverflow
}

bool Set::operator!=(const Set& b) const {

    return !(*this <= b);
}

bool Set::operator<(const Set& b) const {
    Node* rhs = head->next;

    while (rhs != nullptr) { 
        if ((b.member(rhs->value)) == false) {

            return false;
        }

        if (*this == b) {
            return false;
        }
        rhs = rhs->next;
    }
    return true;

}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const {
    
    Node* rhs = head -> next; //skip dummy?

    Set Union{ b }; //create copy of lhs using copy constructor
    //creating copy of b is easier because we only need to add elements from rhs

    while (rhs != nullptr) {
        if (Union.member(rhs->value) == false) { //if new set doesn't already contain value
           
            Union.insert(Union.head, rhs->value); //insert node with rhs value
        }

        rhs = rhs->next; // move to next
    }

    return Union; //return new set

}

// Set intersection
Set Set::operator*(const Set& b) const {

    Set intersect{};
    Node* rhs = head->next;

    while (rhs != nullptr) {

        if (b.member(rhs->value) == true) {
            intersect.insert(intersect.head, rhs->value);

        }
        rhs = rhs->next;

    }
    return intersect;  
}

// Set difference
Set Set::operator-(const Set& b) const {
    Set difference{};

    Node* rhs = head->next; //skip dummy
    Node* lhs = b.head;

    while (rhs != nullptr) {
        if (!(b.member(rhs->value))) {
            difference.insert(difference.head,rhs->value);
            
            
        }
        rhs = rhs->next;
    }

    return difference; 
}

// set difference with set {x}
//new set should be 3,1,8,1?
Set Set::operator-(int x) const {
    
    Set r = *this;
    Set dummy{ x };

    r = r - dummy;

    return r;
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


