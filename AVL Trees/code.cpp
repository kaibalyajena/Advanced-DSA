#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    Node *left;
    Node *right;
    int val;
    int height;

    Node(int v)
    {
        val = v;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

int getHeight(Node *root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

int getBalance(Node *root) // the ideal value for balanced tree will be {-1,0,1}
{
    if (root == NULL)
        return 0;

    return getHeight(root->left) - getHeight(root->right);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left),
                    getHeight(y->right)) +
                1;
    x->height = max(getHeight(x->left),
                    getHeight(x->right)) +
                1;
    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left),
                    getHeight(x->right)) +
                1;
    y->height = max(getHeight(y->left),
                    getHeight(y->right)) +
                1;

    return y;
}

Node *insert(Node *root, int key)
{
    if (root == NULL)
        return (new Node(key));

    if (key < root->val)
        root->left = insert(root->left, key);
    else if (key > root->val)
        root->right = insert(root->right, key);
    else
        return root;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && key < root->left->val)
        return rightRotate(root);

    if (balance < -1 && key > root->right->val)
        return leftRotate(root);

    if (balance > 1 && key > root->left->val)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->val)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node *minValueNode(Node *root)
{
    Node *pointer = NULL;

    while (root->left)
    {
        pointer = root->left;
    }

    return pointer;
}

Node *deleteNode(Node *root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->val)
        root->left = deleteNode(root->left, key);
    else if (key > root->val)
        root->right = deleteNode(root->right, key);
    else
    {
        if (!root->left || !root->right) // if atleast one of them is NULL
        {
            Node *temp = root->left ? root->left : root->right;
            if (!temp) // if it is a leaf node
            {
                temp = root;
                root = NULL;
            }
            else
            {
                *root = *temp;
                delete temp;
            }
        }
        else
        {
            Node *temp = minValueNode(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right,
                                     temp->val);
        }
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preOrder(Node *root, vector<int> &v)
{
    if (root == NULL)
        return;
    v.push_back(root->val);
    preOrder(root->left, v);
    preOrder(root->right, v);
}

void inOrder(Node *root, vector<int> &v)
{
    if (root == NULL)
        return;

    inOrder(root->left, v);
    v.push_back(root->val);
    inOrder(root->right, v);
}

int main()
{
    Node *root = NULL;
    return 0;
}