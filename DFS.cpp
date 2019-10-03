/**
 * Implementation of various type of Depth-First-Search (DFS) for binary tree.
 * Include
 *  - PreOrder
 *  - PostOrder
 *  - InOrder
 *  - Reverse PreOrder
 *  - Reverse PostOrder
 *  - Reverse InOrder
 *
 *  The binary tree is as follows
 *      1 is root
 *      1->left = 2
 *      1->right = 3
 *      2->left = 4
 *      2->right = 5
 *      4->left = 6
 *      4->right = 7
 *      5->left = 8
 *      5->right = 9
 */
#include <iostream>
#include <stack>

#define HEAD(t) std::cout << t;
#define END std::cout << std::endl;

struct Node
{
    int value;
    Node* left;
    Node* right;

    Node(int value): value(value), left(nullptr), right(nullptr) { }
};

// PreOrder => Root, Left, Right
static void PreOrder(const Node* root)
{
    if (root == nullptr)
       return; 

    std::cout << root->value << " ";
    PreOrder(root->left);
    PreOrder(root->right);
}

// PostOrder => Left, Right, Root
static void PostOrder(const Node* root)
{
    if (root == nullptr)
        return;

    PostOrder(root->left);
    PostOrder(root->right);
    std::cout << root->value << " ";
}

// InOrder => Left, Root, Right
static void InOrder(const Node* root)
{
    if (root == nullptr)
        return;

    InOrder(root->left);
    std::cout << root->value << " ";
    InOrder(root->right);
}

// note: sk is argument sent by reference, thus we have no need to clear all elements again after
// this call.
static void PrintStackElems(std::stack<int>& sk)
{
    while (!sk.empty())
    {
        std::cout << sk.top() << " ";
        sk.pop();
    }
}

// Rev-PreOrder => Right, Left, Root
static void RevPreOrder(const Node* root)
{
    if (root == nullptr)
        return;

    RevPreOrder(root->right);
    RevPreOrder(root->left);
    std::cout << root->value << " ";
}
// this is an underlying function called by its corresponding wrapper function call
static void RevPreOrderStack_(const Node* root, std::stack<int>& sk)
{
    if (root == nullptr)
        return;

    sk.emplace(root->value);
    RevPreOrderStack_(root->left, sk);
    RevPreOrderStack_(root->right, sk);
}
// this is a wrapper function call to underlying function, note its trailing _
static void RevPreOrderStack(const Node* root, std::stack<int>& sk)
{
    RevPreOrderStack_(root, sk);
    PrintStackElems(sk);
}

static void RevPostOrder(const Node* root)
{
    if (root == nullptr)
        return;

    std::cout << root->value << " ";
    RevPostOrder(root->right);
    RevPostOrder(root->left);
}
static void RevPostOrderStack_(const Node* root, std::stack<int>& sk)
{
    if (root == nullptr)
        return;

    RevPostOrderStack_(root->left, sk);
    RevPostOrderStack_(root->right, sk);
    sk.emplace(root->value);
}
static void RevPostOrderStack(const Node* root, std::stack<int>& sk)
{
    RevPostOrderStack_(root, sk);
    PrintStackElems(sk);
}

static void RevInOrder(const Node* root)
{
    if (root == nullptr)
        return;

    RevInOrder(root->right);
    std::cout << root->value << " ";
    RevInOrder(root->left);
}
static void RevInOrderStack_(const Node* root, std::stack<int>& sk)
{
    if (root == nullptr)
        return;

    RevInOrderStack_(root->left, sk);
    sk.emplace(root->value);
    RevInOrderStack_(root->right, sk);
}
static void RevInOrderStack(const Node* root, std::stack<int>& sk)
{
    RevInOrderStack_(root, sk);
    PrintStackElems(sk);
}

// delete uses PostOrder traversal to delete all leaf nodes first before parent
static void DeleteTree(Node* root)
{
    if (root == nullptr)
        return;

    DeleteTree(root->left);
    DeleteTree(root->right);

    std::cout << root->value << " ";
    delete root;
    root = nullptr;
}

int main()
{
    // form the input binary tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    
    Node* two = root->left;
    two->left = new Node(4);
    two->right = new Node(5);

    Node* four = two->left;
    four->left = new Node(6);
    four->right = new Node(7);

    Node* five = two->right;
    five->left = new Node(8);
    five->right = new Node(9);

    HEAD("PreOrder: ")
    PreOrder(root);
    END

    HEAD("PostOrder: ")
    PostOrder(root);
    END

    HEAD("InOrder: ")
    InOrder(root);
    END

    // shared stack to use for reverse algorithm variants
    // if Node struct has T as data type of its element value, use it here as type for std::stack
    std::stack<int> sk;

    HEAD("Rev-PreOrder: ")
    RevPreOrder(root);
    END
    // --
    HEAD("Rev-PreOrderStack: ")
    RevPreOrderStack(root, sk);
    END

    HEAD("Rev-PostOrder: ")
    RevPostOrder(root);
    END
    // --
    HEAD("Rev-PostOrderStack: ")
    RevPostOrderStack(root, sk);
    END

    HEAD("Rev-InOrder: ")
    RevInOrder(root);
    END
    // --
    HEAD("Rev-InOrderStack: ")
    RevInOrderStack(root, sk);
    END

    HEAD("Delete: ")
    DeleteTree(root);
    END

    return 0;
}
