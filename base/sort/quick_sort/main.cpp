#include "main.h"

extern void quick_sort(int arr[], int left, int right);

const int max_size = 10000;
int N;
int a[max_size];

void init() {
    cin.clear();
    freopen("input.txt", "r", stdin);
    cin >> N;
    cout << "input ";
    for (int i = 0; i < N; i++) {
        cin>>a[i];
        cout << " " << a[i];
    }
    cout << endl;
    fclose(stdin);
}

int main() {
    init();
    quick_sort(a, 0, N-1);
    cout << "output: ";
    for (int i = 0; i < N; i++) {
        cout<<" " << a[i];
    }    
}