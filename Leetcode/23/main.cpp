/**
 * Problem 23 - Merge k Sorted Lists https://leetcode.com/problems/merge-k-sorted-lists/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input array of array of numbers for sorted lists
 * TC#1 Expect array of numbers as one sorted list
 * TC#2 ... and so on
 *
 * Time complexity: O(K*N)
 * Space complexity: O(1)
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "ArrayInputParser.h"

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x)
        : val(x)
        , next(nullptr)
    {}
};

class Solution {
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        if (lists.size() == 0)
            return nullptr;

        if (lists.size() == 1)
            return lists[0];

        if (lists.size() == 2)
            return mergeTwoLists(lists[0], lists[1]);

        const int size = lists.size();
        int interval = 1;
        while (interval < size) {
            for (int i=0; i<size-interval; i+=(interval*2)) {
                lists[i] = mergeTwoLists(lists[i], lists[i+interval]);
            }
            interval *= 2;
        }
        return size > 0 ? lists[0] : nullptr;
    }
private:
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
    ArrayInputParser aparser;

    for (int i=0; i<N; ++i)
    {
        // read in array of array of numbers
        std::getline(infile, line);
        std::vector<std::vector<int>> nums = aparser.parse<std::vector<int>>(line);

        // form input array of lists
        std::vector<ListNode*> inputs;
        for (int i=0; i<nums.size(); ++i) {
            ListNode outList (-99);     // dummy node
            ListNode* nodeptr = &outList;
            for (int j=0; j<nums[i].size(); ++j) {
                nodeptr->next = new ListNode(nums[i][j]);
                nodeptr = nodeptr->next;
            }
            inputs.push_back(outList.next);
        }

        // read in output array of numbers
        std::getline(infile, line);
        std::vector<int> expectNumsOutput = aparser.parse<int>(line);
        // form output list
        ListNode expectList (-99);      // dummy node
        ListNode* expectListPtr = &expectList;
        for (const auto& n : expectNumsOutput) {
            expectListPtr->next = new ListNode(n);
            expectListPtr = expectListPtr->next;
        }
        expectListPtr = expectList.next;

        // compute
        ListNode* out = sol.mergeKLists(inputs);

        if (out == nullptr && expectListPtr == nullptr) {
            std::printf("[Success #%d]\n", i);
        }
        else if (out == nullptr && expectListPtr != nullptr) {
            std::printf("[Fail #%d] Mismatch\n", i);
        }
        else if (out != nullptr && expectListPtr == nullptr) {
            std::printf("[Fail #%d] Mismatch\n", i);
        }
        else {
            int index = 0;
            ListNode* outPtr = out;
            ListNode* expectPtr = expectListPtr;
            while (outPtr != nullptr && expectPtr != nullptr) {
                if (outPtr->val != expectPtr->val) {
                    std::printf("[Fail #%d] Element at %d for Output=%d, Expect=%d\n", i, index, outPtr->val, expectPtr->val);
                }
                outPtr = outPtr->next;
                expectPtr = expectPtr->next;
                ++index;
            }

            std::printf("[Success #%d]\n", i);
        }

    }

    infile.close();

    return 0;
}
