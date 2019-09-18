/**
 * Solution on interview coding session for problem I've faced myself.
 *
 * Given 2 sorted list; not necessary have the same element count.
 * Merge them and return reverse of sorted list.
 *
 * Compile with
 *  g++ -g -std=c++11 -I. Algorithm/Sort2SortedLists.cpp 
 *
 * Input:
 *  First line: number of numbers to be read, followed by numbers separated by a space for the first sorted list.
 *  Second line: number of numbers to be read, followed by numbers separted by a space for the second sorted list.
 *  PS: Use input testcases from testcases/Sort2SortedList.txt
 *
 * Output:
 *  Reverse of merged sorted list from those two sorted lists in a single line separated by a space.
 */

#include "Util.h"
#include <sstream>
#include <limits>
#include <stack>

using namespace std;

struct Node
{
    int value;
    Node* next;

    Node(): value(0), next(nullptr) {}
    Node(int v, Node* n): value(v), next(n) {}
};

/** pointer management section **/
/**
 * Print all elements inside linked-list.
 */
static void PrintAllElems(const Node* const r)
{
    Node* curr = const_cast<Node*>(r);
    while (curr)
    {
        if (!curr->next)
            cout << curr->value << endl;
        else
            cout << curr->value << " ";
        curr = curr->next;
    }
}

/**
 * Delete all elements inside linked-list.
 */
static void DeleteAllElems(Node* r)
{
    Node* curr = r;
    Node* tmp = nullptr;
    while (curr)
    {
        tmp = curr->next;
        delete curr;
        curr = tmp;
    }
}
/** end of pointer management section **/

/**
 * Accept input of linked-list.
 * Result linked-list is created on heap to input double pointer.
 */
static void InputLinkedList(Node** list)
{
    int n;
    cin >> n;

    if (n >= 1)
    {
        int v;
        cin >> v;
        *list = new Node(v, nullptr);
    }

    Node* curr = *list;

    for (int i=1; i<n; ++i)
    {
        int v;
        cin >> v;

        Node* nn = new Node(v, nullptr);
        curr->next = nn;
        curr = nn;
    }
}

/**
 * Recursively merge two sorted lists together into result of double-pointer result (which allocated
 * externally to this function).
 *
 * Note: Returned result will point to the first element of merged list.
 */
static void MergeRevRecurInternal(Node** result, const Node* const list1, const Node* const list2)
{
    if (list1 == nullptr)
    {
        if (*result == nullptr) *result = new Node(list2->value, nullptr);
        else
        {
            Node* nn = new Node(list2->value, nullptr);
            (*result)->next = nn;
            (*result) = nn;
            cout << nn->value << endl;
        }
    }
    else if (list2 == nullptr)
    {
        if (*result == nullptr) *result = new Node(list1->value, nullptr);
        else
        {
            Node* nn = new Node(list1->value, nullptr);
            (*result)->next = nn;
            (*result) = nn;
            cout << nn->value << endl;
        }
    }
    else if (list1->value <= list2->value)
    {
        if (*result == nullptr) *result = new Node(list1->value, nullptr);
        MergeRevRecurInternal(&(*result)->next, list1->next, list2);
    }
    else
    {
        if (*result == nullptr) *result = new Node(list2->value, nullptr);
        MergeRevRecurInternal(&(*result)->next, list1, list2->next);
    }
}

/**
 * Merge and reverse two sorted lists together then return result.
 * Returned result is created on heap, and need to be deleted by users.
 */
static Node* MergeRevRecur(const Node* const list1, const Node* const list2)
{
    Node* result = nullptr;
    MergeRevRecurInternal(&result, list1, list2);

    // reverse the result list
    // using stack
    stack<int> sk;
    Node* resultCurr = result;
    while (resultCurr)
    {
        sk.push(resultCurr->value);
        resultCurr = resultCurr->next;
    }

    resultCurr = result;
    while (!sk.empty())
    {
        resultCurr->value = sk.top();
        resultCurr = resultCurr->next;
        sk.pop();
    }

    return result;
}

/**
 * Merge two sorted linked-list together.
 * Result is reverse linked-list created on heap.
 */
static Node* MergeRev(const Node* const list1, const Node* const list2)
{
    Node* list1Curr = const_cast<Node*>(list1);
    Node* list2Curr = const_cast<Node*>(list2);

    Node* resultCurr = nullptr;
    bool first = true;

    // we will form reversed-linked-list later from this stack
    stack<Node*> sk;
    
    while (list1Curr && list2Curr)
    {
        if (list1Curr->value < list2Curr->value)
        {
            Node* nn = new Node(list1Curr->value, nullptr);
            if (first)
            {
                resultCurr = nn;
                first = false;
            }
            else
            {
                resultCurr->next = nn;
                resultCurr = nn;
            }

            list1Curr = list1Curr->next;
            sk.push(nn);
        }
        else
        {
            Node* nn = new Node(list2Curr->value, nullptr);
            if (first)
            {
                resultCurr = nn;
                first = false;
            }
            else
            {
                resultCurr->next = nn;
                resultCurr = nn;
            }

            list2Curr = list2Curr->next;
            sk.push(nn);
        }
    }

    while (list1Curr)
    {
        Node* nn = new Node(list1Curr->value, nullptr);
        sk.push(nn);
        resultCurr->next = nn;
        list1Curr = list1Curr->next;
    }

    while (list2Curr)
    {
        Node* nn = new Node(list2Curr->value, nullptr);
        sk.push(nn);
        resultCurr->next = nn;
        list2Curr = list2Curr->next;
    }

    Node* result = nullptr;
    resultCurr = nullptr;
    while (!sk.empty())
    {
        if (!result)
        {
            Node* nn = sk.top();
            result = nn;
            resultCurr = result;
            sk.pop();
        }
        else
        {
            Node* nn = sk.top();
            resultCurr->next = nn;
            resultCurr = resultCurr->next;
            sk.pop();
        }
    }
    // as we pop Node* from stack, its 'next' attribute doesn't end with nullptr, then
    // end it here
    resultCurr->next = nullptr;

    return result;
}

int main()
{
    PROFILE_DECLR

    // iterative version
    int num;
    Node *list1, *list2;

    InputLinkedList(&list1);
    InputLinkedList(&list2);

    cout << "list1: ";
    PrintAllElems(list1);
    cout << "list2: ";
    PrintAllElems(list2);

    PROFILE_START
    Node* result = MergeRev(list1, list2);
    PROFILE_END
    cout << "result (iterative): ";
    PrintAllElems(result);
    PROFILE_PRINT

    // recursive version
    PROFILE_START
    result = MergeRevRecur(list1, list2);
    PROFILE_END
    cout << "result (recursive): ";
    PrintAllElems(result);
    PROFILE_PRINT

    DeleteAllElems(list1);
    DeleteAllElems(list2);
    DeleteAllElems(result);

    return 0;
}
