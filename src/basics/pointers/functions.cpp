
int add(int *a, int *b){
    return *a + *b;
}

void add(int *a, int *b, int *result){
    *result = *a + *b;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void factorial(int *a, int *result){
    int b = *a;
    *result = 1;
    while (b > 1){
        *result *= b--;
    }
}