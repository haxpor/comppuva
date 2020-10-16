/**
 * Problem 2 : Add two numbers
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Array input for list A
 * TC#1 Array input for list B
 * TC#1 Expected result for A + B
 * TC#2 ... and so on
 *
 * Time complexity: N
 * Space complexity: N
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <queue>
#include "ArrayInputParser.h"

struct ListNode
{
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) { }
    ListNode(int x): val(x), next(nullptr) { }
    ListNode(int x, ListNode* next): val(x), next(next) {}
};

ListNode* formListNodeList(const std::vector<int>& nums)
{
    ListNode dummyHeadNode;
    ListNode* ptrNode = &dummyHeadNode;

    for (int i=0; i<nums.size(); ++i)
    {
        ListNode* newNode = new ListNode(nums[i]);
        ptrNode->next = newNode;
        ptrNode = newNode;
    }

    return dummyHeadNode.next;
}

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    { 
        ListNode* l1TmpPtr = l1;
        ListNode* l2TmpPtr = l2;

        // hold result
        std::vector<int> rr;        

        int carry = 0;
        while (l1TmpPtr != nullptr && l2TmpPtr != nullptr) {
            int sum = l1TmpPtr->val + l2TmpPtr->val + carry;
            carry = sum >= 10 ? 1 : 0;      // not for all generic case, but for this specific problem
            if (carry == 1) {
                rr.push_back(sum % 10);
            }
            else {
                rr.push_back(sum);
            }
            l1TmpPtr = l1TmpPtr->next;
            l2TmpPtr = l2TmpPtr->next;
        }

        if (l1TmpPtr == nullptr) {
            l1TmpPtr = l2TmpPtr;
        }

        while (l1TmpPtr != nullptr) {
            int sum = l1TmpPtr->val + carry;
            carry = sum >= 10 ? 1 : 0;
            if (carry == 1) {
                rr.push_back(sum % 10);
            }
            else {
                rr.push_back(sum);
            }
            l1TmpPtr = l1TmpPtr->next;
        }

        // handle last carry
        if (carry > 0) {
            rr.push_back(carry);
        }
        
        // form the result
        ListNode headDummy;
        ListNode* nodePtr = &headDummy;
        for (const auto& item : rr) {
            ListNode* nPtr = new ListNode(item);
            nodePtr->next = nPtr;
            nodePtr = nPtr;
        }
        
        return headDummy.next;
    }
};

int main()
{
    std::cout << "----" << std::endl;
    std::ifstream infile("testcases.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases
    infile.ignore();

    Solution sol;
    ArrayInputParser aparser;

    for (int i=0; i<N; ++i)
    {
        std::getline(infile, line);
        std::vector<int> nums = aparser.parse<int>(line);
        ListNode* listA = formListNodeList(nums);

#ifdef DEBUG
        std::cout << "list A:";
		ListNode* tmpNode = listA;
		while (tmpNode != nullptr)
		{
		    std::cout << tmpNode->val << " ";
            tmpNode = tmpNode->next;
		}
        std::cout << std::endl;
#endif

        std::getline(infile, line);
        nums = aparser.parse<int>(line);
        ListNode* listB = formListNodeList(nums);

#ifdef DEBUG
        std::cout << "list B:";
        tmpNode = listB;
		while (tmpNode != nullptr)
		{
		    std::cout << tmpNode->val << " ";
            tmpNode = tmpNode->next;
		}
        std::cout << std::endl;
#endif

        std::getline(infile, line);
        nums = aparser.parse<int>(line);
        ListNode* expectedList = formListNodeList(nums);

#ifdef DEBUG
        std::cout << "expected:";
        tmpNode = expectedList;
		while (tmpNode != nullptr)
		{
		    std::cout << tmpNode->val << " ";
            tmpNode = tmpNode->next;
		}
        std::cout << std::endl;
#endif

        // compute
        ListNode* out = sol.addTwoNumbers(listA, listB);

#ifdef DEBUG
        std::cout << "out:";
        tmpNode = out;
		while (tmpNode != nullptr)
		{
		    std::cout << tmpNode->val << " ";
            tmpNode = tmpNode->next;
		}
        std::cout << std::endl;
#endif

        ListNode* expectedListTmpPtr = expectedList;
        ListNode* outTmpPtr = out;
        bool isOk = true;
        while (outTmpPtr != nullptr && expectedListTmpPtr != nullptr)
        {
            if (outTmpPtr->val != expectedListTmpPtr->val)
            {
                std::printf("[Failed #%d] Output = %d, Expect = %d\n", i, outTmpPtr->val, expectedListTmpPtr->val);
                isOk = false;
            }

            outTmpPtr = outTmpPtr->next;
            expectedListTmpPtr = expectedListTmpPtr->next;

            if ((outTmpPtr == nullptr && expectedListTmpPtr != nullptr) ||
                (outTmpPtr != nullptr && expectedListTmpPtr == nullptr))
            {
                std::printf("[Failed #%d] Not equal list size\n", i);
                isOk = false;
            }
        }

        if (isOk)
        {
            std::printf("[Success #%d]\n", i);
        }
    }

    infile.close();

    return 0;
}
