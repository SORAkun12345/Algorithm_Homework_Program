/*
Reconstruction of a Tree
ある二分木に対して、それぞれ先行順巡回 (preorder tree walk) と中間順巡回 (inorder tree walk) を行って得られる節点の列が与えられるので、その二分木の後行順巡回 (postorder tree walk) で得られる節点の列を出力するプログラムを作成してください。

入力
１行目に二分木の節点の数 
 が与えられます。
２行目に先行順巡回で得られる節点の番号の列が空白区切りで与えられます。
３行目に中間順巡回で得られる節点の番号の列が空白区切りで与えられます。

節点には 
 から 
 までの整数が割り当てられています。
 が根とは限らないことに注意してください。

出力
後行順巡回で得られる節点の番号の列を１行に出力してください。節点の番号の間に１つの空白を入れてください。

制約
入力例 1
5
1 2 3 4 5
3 2 4 1 5
出力例 1
3 4 2 5 1
入力例 2
4
1 2 3 4
1 2 3 4
出力例 2
4 3 2 1
*/

#include <stdio.h>

#define MAX_N 40

int n;
int preorder[MAX_N];
int inorder[MAX_N];
int postorder[MAX_N];
int post_index = 0;

// inorder配列の中でvalueの位置を探す
int search(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// preorderとinorderから木を再構築し、postorderを生成
void reconstruct(int pre_start, int pre_end, int in_start, int in_end) {
    if (pre_start > pre_end || in_start > in_end) {
        return;
    }
    
    // preorderの最初の要素がルート
    int root = preorder[pre_start];
    
    // inorder配列でルートの位置を探す
    int root_index = search(inorder, in_start, in_end, root);
    
    // 左部分木のサイズ
    int left_size = root_index - in_start;
    
    // 左部分木を再帰的に処理
    reconstruct(pre_start + 1, pre_start + left_size, in_start, root_index - 1);
    
    // 右部分木を再帰的に処理
    reconstruct(pre_start + left_size + 1, pre_end, root_index + 1, in_end);
    
    // 後行順なので、左→右→ルートの順で処理
    postorder[post_index++] = root;
}

/*
// 【inorder + postorder から preorder を生成】
// 使う場合は pre_index を用意して、preorder 配列に書き込みます。
void reconstruct_in_post_to_pre(int in_start, int in_end, int post_start, int post_end) {
    if (in_start > in_end || post_start > post_end) {
        return;
    }

    // postorderの最後の要素がルート
    int root = postorder[post_end];

    // inorder配列でルートの位置を探す
    int root_index = search(inorder, in_start, in_end, root);

    // 左部分木のサイズ
    int left_size = root_index - in_start;

    // preorderはルート→左→右
    preorder[pre_index++] = root;

    // 左部分木を再帰的に処理
    reconstruct_in_post_to_pre(in_start, root_index - 1, post_start, post_start + left_size - 1);

    // 右部分木を再帰的に処理
    reconstruct_in_post_to_pre(root_index + 1, in_end, post_start + left_size, post_end - 1);
}
*/

/*
// 【preorder + postorder から inorder を生成】
// 注意: 一意に決まるのは「完全二分木」が前提の場合のみ
// 使う場合は in_index を用意して、inorder 配列に書き込みます。
void reconstruct_pre_post_to_in(int pre_start, int pre_end, int post_start, int post_end) {
    if (pre_start > pre_end || post_start > post_end) {
        return;
    }

    if (pre_start == pre_end) {
        inorder[in_index++] = preorder[pre_start];
        return;
    }

    int root = preorder[pre_start];
    int left_root = preorder[pre_start + 1];

    // postorderで左部分木の根の位置を探す
    int left_root_index = search(postorder, post_start, post_end, left_root);

    int left_size = left_root_index - post_start + 1;

    // 左部分木
    reconstruct_pre_post_to_in(pre_start + 1, pre_start + left_size, post_start, left_root_index);

    // ルート
    inorder[in_index++] = root;

    // 右部分木
    reconstruct_pre_post_to_in(pre_start + left_size + 1, pre_end, left_root_index + 1, post_end - 1);
}
*/

int main() {
    scanf("%d", &n);
    // preorder読み込み
    for (int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }

    // inorder読み込み
    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }

    // 木を再構築してpostorderを生成
    post_index = 0;
    reconstruct(0, n - 1, 0, n - 1);

    // postorder出力
    for (int i = 0; i < n; i++) {
        if (i > 0) printf(" ");
        printf("%d", postorder[i]);
    }
    printf("\n");
    return 0;
}
