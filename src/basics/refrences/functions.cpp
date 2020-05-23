void add(int a, int b, int &result){
    result = a + b;
}

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}

void factorial(int a, int& result){
    result = 1;
    while (a > 1) result *= a--;
}