#include <stdio.h>
#include <iostream>
#include <algorithm>

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

void quick_sort(int arr[], int left, int right) {
    if (left < right) {
        int x = arr[left];
        int l = left;
        int r = right;
        while(l < r) {
            while(l < r && arr[r] > x) r--;
            if (l < r) {
                arr[l++] = arr[r];
            }
            while(l < r && arr[l] < x) l++;
            if (l < r){
                arr[r--] = arr[l];
            }
        }
        arr[l] = x;
        quick_sort(arr, left, l - 1);
        quick_sort(arr, l + 1, right);
    }
}

void sort(int a[], int size) {
    quick_sort(a, 0, size-1);
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
    quick_sort(s, 0, N-1);

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