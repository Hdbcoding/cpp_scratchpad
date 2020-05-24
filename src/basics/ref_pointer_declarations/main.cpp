int main(){
    int x = 5;
    const int MAX = 12;
    int &ref_x1 = x;
    const int &ref_x2 = x;

    ref_x1 = 15;
    // ref_x2 = 25; // not a modifiable lvalue

    int y = 5;
    const int *ptr1 = &x;
    int *const ptr2 = &x;
    const int *const ptr3 = &x;

    ptr1 = &y; // not pointing to a constant memory location, so this is legal
    // *ptr1 = 10; // not a modifiable lvalue
    
    // ptr2 = &y; // pointing to a constant memory location, so this is illegal
    *ptr2 = 10;

    // ptr3 = &y; // memory location is const
    // *ptr3 = 10; // memory value is const

    const int *ptr4 = &MAX;
    // int *ptr5 = &MAX; // not legal because MAX is const

    const int &r1 = ref_x1;
    // int &r2 = ref_x2; // not legal because ref_x2 is const

    // int *&p_ref1 = ptr1; // not legal because ptr1 is const int
    const int *&p_ref1 = ptr1;

    // const int *&p_ref2 = ptr2; // not legal because ptr2 is *const
    int *const &p_ref2 = ptr2;
}