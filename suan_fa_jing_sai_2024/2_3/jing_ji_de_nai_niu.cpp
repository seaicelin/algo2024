#include <stdio.h>
#include <iostream>
#include <algorithm>

using namespace std;

int N,C;
int s[100000+5];
void initInput() {
    freopen("input.txt","r", stdin); 
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
            while(l < r && arr[r] >= x) r--;
            arr[l] = arr[r];
            while(l < r && arr[l] <= x) l++;
            arr[r] = arr[l];
        }
        arr[l] = x;
        quick_sort(arr, left, l - 1);
        quick_sort(arr, l+1, right);
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
    std::sort(s, s+N);
    //std::sort(s, 0, N);
    // for (int i = 0; i < N; i++) { 
    //     cout << s[i] << " ";
    // }
    // cout << endl;

    int mid, left, right;
    left = 0;
    right = s[N-1] - s[0];
    //cout << s[N-1] - s[0] << endl;
    int ans = 0;
    while(left <= right) {
        mid = left + right >> 1;
        if (check(mid) == true) {
            ans = std::max(ans, mid);
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    printf("%d\n", ans);

    return 0;
}