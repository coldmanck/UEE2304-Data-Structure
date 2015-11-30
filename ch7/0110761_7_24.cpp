#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int key;
    Node *left, *right;
 
    // is this node need to be threaded?
    bool isThreaded;
};
 
void populateQueue(Node*, std::queue <Node *>*);
void createThreadedUtil(Node*, std::queue <Node *>*);
void createThreaded(Node*);
Node *leftMost(Node*);
void inOrder(Node*);
Node *newNode(int);
 
int main()
{
    cout << "create threaded binary tree: 1->2->4->8->9->5->3->6->7" << endl;
    Node *root = newNode(1);
    root->right = newNode(2);
    root->right->right = newNode(4);
    root->right->right->right = newNode(8);
    root->right->right->right->right = newNode(9);
    root->right->right->right->left = newNode(5);
    root->right->right->left = newNode(3);
    root->right->right->right->left->right = newNode(6);
    root->right->right->right->left->right->right = newNode(7);

    createThreaded(root);
    
    cout << "The threaded tree: ";
    inOrder(root);
    cout << endl;

    return 0;
}

// put the Nodes in inorder into queue
void populateQueue(Node *root, std::queue <Node *> *q)
{
    if (root == NULL) return;
    if (root->left)
        populateQueue(root->left, q);
    q->push(root);
    if (root->right)
        populateQueue(root->right, q);
}
 
// traverse queue, and make tree threaded
void createThreadedUtil(Node *root, std::queue <Node *> *q)
{
    if (root == NULL) return;
 
    if (root->left)
        createThreadedUtil(root->left, q);
    q->pop();
 
    if (root->right)
        createThreadedUtil(root->right, q);
 
    // If right pointer is NULL, link it to the
    // inorder successor and set 'isThreaded' bit.
    else{
        root->right = q->front();
        root->isThreaded = true;
    }
}
 
// uses populateQueue() and createThreadedUtil() to convert a 
// given binary tree to threaded tree.
void createThreaded(Node *root)
{
    // Create a queue to store inorder traversal
    std::queue <Node *> q;
 
    // Store inorder traversal in queue
    populateQueue(root, &q);
 
    // Link NULL right pointers to inorder successor
    createThreadedUtil(root, &q);
}
 
// find leftmost node in a binary
// tree rooted with 'root'. This function is used in inOrder()
Node *leftMost(Node *root)
{
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}
 
// do inorder traversal of a threadded binary tree
void inOrder(Node *root)
{
    if (root == NULL) return;
 
    // Find the leftmost node in Binary Tree
    Node *cur = leftMost(root);
 
    while (cur != NULL)
    {
        cout << cur->key << ((cur->right != NULL) ? "->" : "");
 
        // If this Node is a thread Node, then go to
        // inorder successor
        if (cur->isThreaded)
            cur = cur->right;
 
        else // Else go to the leftmost child in right subtree
            cur = leftMost(cur->right);
    }
}
 
// create a new node
Node *newNode(int key)
{
    Node *temp = new Node;
    temp->left = temp->right = NULL;
    temp->key = key;
    return temp;
}