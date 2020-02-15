/**
 * Problem 21 - Merge Two Sorted Lists 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 A singly linked-list's elements for list 1 - elemeny by element separated by white space
 * TC#1 A singly linked-list's elements for list 2 - elemeny by element separated by white space
 * TC#1 A singly linked-list's elements for expect output - elemeny by element separated by white space
 *
 * Time complexity: O(N + M)
 * Space complexity: O(1) 
 *
 * Note:
 * Use the following for quick print out for all elements in the linked-list
 *
 *       ListNode* tt = listExpectStart.next;
 *       while (tt != nullptr)
 *       {
 *           std::cout << tt->val << std::endl;
 *           tt = tt->next;
 *       }
 */
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x)
        : val(x)
        , next(nullptr)
    {}
};

class Solution
{
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
    {
        ListNode dummy(-1);
        ListNode* last = &dummy;

        while (l1 != nullptr && l2 != nullptr)
        {
            if (l1->val < l2->val)
            {
                last->next = l1;
                last = l1;
                l1 = l1->next;
            }
            else
            {
                last->next = l2;
                last = l2;
                l2 = l2->next;
            }
        }

        if (l1 != nullptr)
        {
            last->next = l1;
        }
        else if (l2 != nullptr)
        {
            last->next = l2;
        }

        return dummy.next;
    }
};

int main()
{
    std::ifstream infile("testcases.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases
    infile.ignore();

    Solution sol;

    for (int i=0; i<N; ++i)
    {
        std::getline(infile, line);
        std::istringstream lineStream(line);

        int num;

        // get list 1
        ListNode list1Start(-1);
        ListNode* list1End = &list1Start;
        while (lineStream >> num)
        {
            list1End->next = new ListNode(num);
            list1End = list1End->next;
        }

        // get list 2
        std::getline(infile, line);
        lineStream.str(line);
        lineStream.clear();

        ListNode list2Start(-1);
        ListNode* list2End = &list2Start;
        while (lineStream >> num)
        {
            list2End->next = new ListNode(num);
            list2End = list2End->next;
        }

        // get expect list
        std::getline(infile, line);
        lineStream.str(line);
        lineStream.clear();

        ListNode listExpectStart(-1);
        ListNode* listExpectEnd = &listExpectStart;
        while (lineStream >> num)
        {
            listExpectEnd->next = new ListNode(num);
            listExpectEnd = listExpectEnd->next;
        }

        // compute
        ListNode* listExpectPtr = listExpectStart.next;
        ListNode* out = sol.mergeTwoLists(list1Start.next, list2Start.next);
        bool isCorrect = out != nullptr;
        while (out != nullptr && listExpectPtr != nullptr)
        {
            if (out->val != listExpectPtr->val)
            {
                std::printf("[Failed #%d] Output = %d, Expect = %d\n", i, out->val, listExpectPtr->val);
                isCorrect = false;
                break;
            }

            out = out->next;
            listExpectPtr = listExpectPtr->next;
        }

        if (isCorrect)
            std::printf("[Success #%d]\n", i);
        else
            std::printf("[Failed #%d] Mismatch output\n", i);

        // clear memory allocated for this test case
        ListNode* tmpPtr = list1Start.next;
        while (tmpPtr != nullptr)
        {
            ListNode* nextPtr = tmpPtr->next;
            delete tmpPtr;
            tmpPtr = nextPtr;
        }
        tmpPtr = list2Start.next;
        while (tmpPtr != nullptr)
        {
            ListNode* nextPtr = tmpPtr->next;
            delete tmpPtr;
            tmpPtr = nextPtr;
        }
        tmpPtr = list2Start.next;
        while (tmpPtr != nullptr)
        {
            ListNode* nextPtr = tmpPtr->next;
            delete tmpPtr;
            tmpPtr = nextPtr;
        }
    }

    infile.close();

    return 0;
}
