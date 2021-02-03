
class integer
{
    int *v;

public:
    // rule of 3 -> { destructor, copy constructor, copy assignment operator }
    //      e.g., if you need custom implementation for one of those three, you need all three

    // rule of 5 -> { destructor, copy constructor, copy assignment operator, move constructor, move assignment operator }
    //      same as rule of 3, just more to implement

    // default constructor
    integer();

    // destructor
    ~integer();

    // parameterized constructor
    integer(int value);

    // copy constructor - takes a const lvalue reference
    integer(const integer &obj);

    // move constructor - takes an rvalue reference
    integer(integer &&obj);

    // copy assignment operator
    integer &operator=(const integer &a);

    // move assignment operator
    integer &operator=(integer &&a);

    int getValue() const;
    void setValue(int value);
};