#include <iostream>

using namespace std;

#define maxn 30

struct NODE{
    char c;
    NODE* l;
    NODE* r;
    NODE():c(0),l(nullptr),r(nullptr){}
};

NODE node_list[maxn];

char a[30];

void initNodeList() {
    for (int i = 0; i < maxn; i++) {
        node_list[i].c = 'a'+i;
    }
}

void dfs(NODE* node) {
    if (!node) return;
    cout << node->c;
    dfs(node->l);
    dfs(node->r);
}

int main() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    initNodeList();
    int n;
    cin >> n;
    //getchar();
    NODE* root, *root2;
    for(int i = 0; i < n; i++) {
        cin>>a[0]>>a[1]>>a[2];
        //cin.getline(a, maxn);
        root = &node_list[a[0]-'a'];
        if (a[1] != '*'){
            root->l = &node_list[a[1]-'a'];
        }
        if (a[2] != '*'){
            root->r = &node_list[a[2]-'a'];
        }
        if (i==0) root2 = root;
    }

    dfs(root2);
    cout<<endl;
    return 0;
}