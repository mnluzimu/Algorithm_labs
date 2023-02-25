#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

typedef enum {
    red,
    black
} Color;

typedef struct Node {
    struct Node *p, *left, *right;
    Color color;
    int low;
    int high;
    int max_val;
} Node;

Node * NIL;

void left_rotate(Node * &root, Node * x) {
    Node * y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
        y->left->p = x;
    }
    y->p = x->p;
    if (x->p == NIL) {
        root = y;
    }
    else if (x == x->p->left) {
        x->p->left = y;
    }
    else {
        x->p->right = y;
    }
    y->left = x;
    x->p = y;
    y->max_val = x->max_val;
    x->max_val = max(x->high, max(x->left->max_val, x->right->max_val));
}

void right_rotate(Node * &root, Node * x) {
    Node * y = x->left;
    x->left = y->right;
    if (y->right != NIL) {
        y->right->p = x;
    }
    y->p = x->p;
    if (x->p == NIL) {
        root = y;
    }
    else if (x == x->p->left) {
        x->p->left = y;
    }
    else {
        x->p->right = y;
    }
    y->right = x;
    x->p = y;
    y->max_val = x->max_val;
    x->max_val = max(x->high, max(x->left->max_val, x->right->max_val));
}

void RB_insert_fixup(Node * &root, Node * &z) {
    while (z->p->color == red) {
        if (z->p == z->p->p->left) {
            Node * y = z->p->p->right;
            if (y->color == red) {
                z->p->color = black;
                y->color = black;
                z->p->p->color = red;
                z = z->p->p;
            }
            else{
                if (z == z->p->right) {
                    z = z->p;
                    left_rotate(root, z);
                }
                z->p->color = black;
                z->p->p->color = red;
                right_rotate(root, z->p->p);
            }
        }
        else {
            Node * y = z->p->p->left;
            if (y->color == red) {
                z->p->color = black;
                y->color = black;
                z->p->p->color = red;
                z = z->p->p;
            }
            else{
                if (z == z->p->left) {
                    z = z->p;
                    right_rotate(root, z);
                }
                z->p->color = black;
                z->p->p->color = red;
                left_rotate(root, z->p->p);
            }
        }
    }
    root->color = black;
}

void RB_insert(Node * &root, Node * z) {
    Node * y = NIL;
    Node * x = root;
    while (x != NIL) {
        y = x;
        x->max_val = max(x->max_val, z->max_val);
        if (z->low < x->low) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->p = y;
    if (y == NIL) {
        root = z;
    }
    else if(z->low < y->low) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = NIL;
    z->right = NIL;
    z->color = red;
    RB_insert_fixup(root, z);
}

void RB_transplant(Node * &root, Node *u, Node *v) {
    if (u->p == NIL) {
        root = v;
    }
    else if (u == u->p->left) {
        u->p->left = v;
    }
    else {
        u->p->right = v;
    }
    v->p = u->p;
}

Node * tree_minimum(Node * x) {
    while (x->left != NIL) {
        x = x->left;
    }
    return x;
}

void RB_delete_fixup(Node * &root, Node * x) {
    Node * w;
    while (x != root && x->color == black) {
        if (x == x->p->left) {
            w = x->p->right;
            if (w->color == red) {
                w->color = black;
                x->p->color = red;
                left_rotate(root, x->p);
                w = x->p->right;
            }
            if (w->left->color == black && w->right->color == black) {
                w->color = red;
                x = x->p;
            }
            else {
                if (w->right->color == black) {
                    w->left->color = black;
                    w->color = red;
                    right_rotate(root, w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = black;
                w->right->color = black;
                left_rotate(root, x->p);
                x = root;
            }
        }
        else {
            w = x->p->left;
            if (w->color == red) {
                w->color = black;
                x->p->color = red;
                right_rotate(root, x->p);
                w = x->p->left;
            }
            if (w->right->color == black && w->left->color == black) {
                w->color = red;
                x = x->p;
            }
            else {
                if (w->left->color == black) {
                    w->right->color = black;
                    w->color = red;
                    left_rotate(root, w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = black;
                w->left->color = black;
                right_rotate(root, x->p);
                x = root;
            }
        }
    }
    x->color = black;
}

void RB_delete(Node * &root, Node * z) {
    Node * y = z;
    Node * x;
    Node * g;
    Color y_original_color = y->color;
    if (z->left == NIL) {
        x = z->right;
        g = y->p;
        RB_transplant(root, y, y->right);
        g->max_val = max(max(g->high, g->left->max_val), g->right->max_val);
        g = g->p;
        while(g->max_val == y->max_val && g != NIL) {
            g->max_val = max(max(g->high, g->left->max_val), g->right->max_val);
            g = g->p;
        }
    }
    else if (z->right == NIL) {
        x = z->left;
        g = y->p;
        RB_transplant(root, y, y->left);
        g->max_val = max(max(g->high, g->left->max_val), g->right->max_val);
        g = g->p;
        while(g->max_val == y->max_val && g != NIL) {
            g->max_val = max(max(g->high, g->left->max_val), g->right->max_val);
            g = g->p;
        }
    }
    else {
        y = tree_minimum(z->right);
        z->low = y->low;
        z->high = y->high;
        x = y->right;
        y_original_color = y->color;
        g = y->p;
        RB_transplant(root, y, y->right);
        delete y;
        g->max_val = max(max(g->high, g->left->max_val), g->right->max_val);
        g = g->p;
        while(g->max_val == y->max_val && g != NIL) {
            g->max_val = max(max(g->high, g->left->max_val), g->right->max_val);
            g = g->p;
        }
    }
    if (y_original_color == black) {
        RB_delete_fixup(root, x);
    }
}

Node * interval_search(Node * &root, Node * i) {
    Node * x = root;
    while (x != NIL && (i->high < x->low || i->low > x->high)) {
        if (x->left != NIL && x->left->max_val >= i->low) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    if (x == NIL) return NULL;
    return x;
}

void get_interval(int &low, int &high, int a, int b) {
    low = a + (int)(b - a - 1) * rand() / (RAND_MAX + 1);
    high = low + (int)(b - low) * rand() / (RAND_MAX + 1);
    while (high == low) {
        high = low + (int)(b - low) * rand() / (RAND_MAX + 1);
    }
}

void print_tree(Node * root, ofstream & ofs) {
    if (root == NIL) return;
    print_tree(root->left, ofs);
    ofs << root->low << " " << root->high << " " << root->max_val << endl;
    print_tree(root->right, ofs);
}

int main() {
    FILE * fp;
    Node * root;
    ofstream inorder_ofs, search_ofs, delete_data_ofs;
    inorder_ofs.open("../output/inorder.txt", ios::out);
    search_ofs.open("../output/search.txt", ios::out);
    delete_data_ofs.open("../output/delete_data.txt", ios::out);
    NIL = new Node;
    NIL->color = black;
    NIL->high = 0;
    NIL->low = 0;
    NIL->right = 0;
    NIL->left = NULL;
    NIL->right = NULL;
    NIL->max_val = -1;
    NIL->p = NULL;
    root = NIL;
    if ((fp = fopen("../input/input.txt", "r")) == NULL) {
        printf("cannot open file!");
    }
    int lows[35];
    int hights[35];
    vector<Node*> vec;
    for(int i = 0; i < 30; i++){
        int h, l;
        fscanf(fp, "%d %d", & l, & h);
        lows[i] = l;
        hights[i] = h;
        Node * z = new Node;
        z->color = red;
        z->high = h;
        z->low = l;
        z->left = NIL;
        z->right = NIL;
        z->p = NIL;
        z->max_val = h;
        vec.push_back(z);
        RB_insert(root, z);
    }
    print_tree(root, inorder_ofs);
    inorder_ofs.close();
    int indx[3];
    for (int i = 0; i < 3; i++) {
        indx[i] = 0 + (int)30 * rand() / (RAND_MAX + 1);
        if (i == 1) {
            while (indx[i] == indx[0])
                indx[i] = 0 + (int)30 * rand() / (RAND_MAX + 1);
        }
        if (i == 2) {
            while (indx[i] == indx[0] || indx[i] == indx[1])
                indx[i] = 0 + (int)30 * rand() / (RAND_MAX + 1);
        }
        delete_data_ofs << vec[indx[i]]->low << " " << vec[indx[i]]->high << " " << vec[indx[i]]->max_val << endl;
        RB_delete(root, vec[indx[i]]);
    }
    delete_data_ofs << "the tree after delete:" << endl;
    print_tree(root, delete_data_ofs);
    delete_data_ofs.close();
    for (int i = 0; i < 3; i++) {
        int low, high;
        if (i == 0)
            get_interval(low, high, 0, 25);
        if (i == 1) 
            get_interval(low, high, 26, 29);
        if (i == 2)
            get_interval(low, high, 30, 50);
        Node * w = new Node;
        w->low = low;
        w->high = high;
        w->left = w->right = w->p = NIL;
        w->max_val = -1;
        Node * result = interval_search(root, w);
        search_ofs << "the interval:" << endl;
        search_ofs << w->low << " " << w->high << endl;
        search_ofs << "result:" << endl;
        if (result == NULL) {
            search_ofs << "not found" << endl;
        }
        else {
            search_ofs << result->low << " " << result->high << endl;
        }
    }
    search_ofs.close();

    return 0;
}