#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct tree {
    int key;
    tree *left, *right, *parent;
};

tree* root = nullptr;

void insert(int k) {
    tree* y = nullptr;
    tree* x = root;
    
    tree* z = new tree;
    z->key = k;
    z->left = z->right = nullptr;

    while (x != nullptr) {
        y = x;
        if (z->key < x->key) x = x->left;
        else x = x->right;
    }

    z->parent = y;
    if (y == nullptr) {
        root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }
}

void inorder(tree* u) {
    if (u == nullptr) return;
    inorder(u->left);
    printf(" %d", u->key);
    inorder(u->right);
}

void preorder(tree* u) {
    if (u == nullptr) return;
    printf(" %d", u->key);
    preorder(u->left);
    preorder(u->right);
}

int main() {
    int n, val;
    string cmd;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> cmd;
        if (cmd == "insert") {
            cin >> val;
            insert(val);
        } else if (cmd == "print") {
            inorder(root);
            printf("\n");
            preorder(root);
            printf("\n");
        }
    }
    return 0;
}