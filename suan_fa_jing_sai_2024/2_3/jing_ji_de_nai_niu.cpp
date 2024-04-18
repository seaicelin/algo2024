#include <stdio.h>
#include <iostream>
//#include <algorithm>

using namespace std;

int N,C;
int s[100000+5];
void initInput() {
    cin.clear();
    freopen("input.txt", "r", stdin); 
    cin >> N >> C;   
    for (int i = 0; i < N; i++) {
        cin >> s[i];
    }
    fclose(stdin);
}

int parent(int pos) {
    return (pos - 1) / 2;
}

void swap(int& a, int& b) {
    int c = a;
    a = b;
    b = c;
}

void shipdown(int arr[], int pos, int size) {
    int l, r, max;
    while(true) {
        max = pos;
        l = 2 * pos + 1;
        r = 2 * pos + 2;
        if (l < size && arr[max] < arr[l]) {
            max = l;
        }
        if (r < size && arr[max] < arr[r]) {
            max = r;
        }
        if (pos == max) break;

        swap(arr[pos], arr[max]);
        pos = max;
    }
}

void heap_sort(int arr[], int size) {
    for (int i = parent(size-1); i >= 0; i--) {
        shipdown(arr, i, size);
    }

    for (int i = size - 1; i > 0; i--) {
        swap(arr[i], arr[0]);
        shipdown(arr, 0, i-1);
    }
}

bool check(long long dis) {
    int i,j,cnt;
    i = 0;
    j = 0;
    cnt = 1;
    while(j < N) {
        if (s[j] - s[i] < dis) {
            j++;
        } else {
            cnt++;
            if(cnt >= C) return true;
            i = j;
            j++;
        }
    }
    if (cnt >= C ){
        return true;
    }
    return false;
}

int main() {

    initInput();
    //sort(s, s+N);
    //quick_sort(s, 0, N-1);
    heap_sort(s, N);

    int mid, left, right;
    left = 0;
    right = s[N-1] - s[0] + 1;
    int ans = 0;
    while(left < right) {
        mid = left + ((right - left) >> 1);
        if (check(mid) == true) {
            ans = std::max(ans, mid);
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    printf("%d\n", ans);

    return 0;
}