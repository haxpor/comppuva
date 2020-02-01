/**
 * Implementation of BFS for binary tree.
 *
 * Two algorithms
 * 1. Use stack
 * 2. Use print level to print at specific level
 *
 * With the following binary tree setup
 *  1 is root
 *  1->left is 2
 *  1->right is 3
 *  2->left is 4
 *  2->right is 5
 */

#include <iostream>
#include <queue>

struct Node
{
    int value;
    Node* left;
    Node* right;

    Node(int value): value(value), left(nullptr), right(nullptr) { }
};

// 1. Stack-based version
// This will print elements' value starting from input `root`.
static void PrintLevelOrder(const Node* root)
{
    if (root == nullptr) return;

    std::queue<Node*> q;
    // we send in pointer by value, it's safe to do const_cast<> here
    // as we want to ensure users of this function that root pointer won't be changed
    q.push(const_cast<Node*>(root));

    while (!q.empty())
    {
        Node* n = q.front();
        std::cout << n->value << " ";
        q.pop();

        if (n->left != nullptr)
            q.push(n->left);
        if (n->right != nullptr)
            q.push(n->right);
    }
}

// 2. Print level version
// This will print elements' value starting from input `root`.
static void PrintAtLevel(const Node* root, int level)
{
    if (root == nullptr)
        return;
    else if (level == 1)
        std::cout << root->value << " ";
    else if (level > 1)
    {
        PrintAtLevel(root->left, level-1);
        PrintAtLevel(root->right, level-1);
    }
}

// compute height of tree
static int Height(const Node* root)
{
    if (root == nullptr)
        return 0;
    else
    {
        // compute height from left and right node of root
        int leftHeight = Height(root->left);
        int rightHeight = Height(root->right);

        if (leftHeight > rightHeight)
            return leftHeight + 1;
        else
            return rightHeight + 1;
    }
}

// delete uses PostOrder traversal to delete all leaf nodes first before parent
static void DeleteTree(Node* root)
{
    if (root == nullptr)
        return;

    DeleteTree(root->left);
    DeleteTree(root->right);

    delete root;
    root = nullptr;
}

int main()
{
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);

    Node* two = root->left;
    two->left = new Node(4);
    two->right = new Node(5);

    std::cout << "Level order (via stack): ";
    PrintLevelOrder(root);
    std::cout << std::endl;

    int height = Height(root);
    for (int i=1; i<=height; ++i)
    {
        std::cout << "level " << i << ": ";
        PrintAtLevel(root, i);
        std::cout << std::endl;
    }

    DeleteTree(root);
    return 0;
}
