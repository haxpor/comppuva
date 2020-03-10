/**
 * Problem 19 - Remove Nth Node From End of List https://leetcode.com/problems/remove-nth-node-from-end-of-list/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input array of numbers for linked list
 * TC#1 Input node number to remove from the end
 * TC#1 Array of numbers for expect linked list
 * TC#2 ... and so on
 *
 * Time complexity: precisely O(N * (n+1)) =~ O(N)
 * Space complexity: O(1) (2 auxiliary pointers, and 1 on-stack dummy node)
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include "ArrayInputParser.h"

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head == nullptr)
            return nullptr;

        ListNode dummyHead (-99);        // dummy node
        dummyHead.next = head;
        ListNode* sentinel = &dummyHead;
        ListNode* curr = &dummyHead;

        while (curr && sentinel) {
            for (int i=0; i<=n; ++i) {
                sentinel = sentinel->next;

                if (!sentinel && i < n)
                    return nullptr;

                // found a node to remove
                if (!sentinel && i == n) {
                    curr->next = curr->next->next;
                    goto DONE;
                }
            }
            curr = curr->next;
            sentinel = curr;
        }

DONE:
        return dummyHead.next;
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
        // read in numbers for linked list
        std::getline(infile, line);
        std::vector<int> nums = aparser.parse<int>(line);

        ListNode* nodeptr = nullptr;

        // form input linked list
        ListNode inputLinkedList (-99);     // dummy node
        nodeptr = &inputLinkedList;
        for (const auto& n : nums) {
            nodeptr->next = new ListNode(n);
            nodeptr = nodeptr->next;
        }

        // read in index to be removed from the end
        int removeNoNodeFromEnd;
        infile >> removeNoNodeFromEnd;
        infile.ignore();

        // read in expect numbers for expect linked list
        std::getline(infile, line);
        std::vector<int> expectNums = aparser.parse<int>(line);
        // form expect linked list
        ListNode expectOutputLinkedList (-99);
        nodeptr = &expectOutputLinkedList;
        for (const auto& n : expectNums) {
            nodeptr->next = new ListNode(n);
            nodeptr = nodeptr->next;
        }

        // compute
        ListNode* out = sol.removeNthFromEnd(inputLinkedList.next, removeNoNodeFromEnd);
        if (out == nullptr && expectOutputLinkedList.next == nullptr) {
            std::printf("[Success #%d]\n", i);
        }
        else if (out == nullptr && expectOutputLinkedList.next != nullptr) {
            std::printf("[Fail #%d] Mismatch. Output is null. Expect is not null.\n", i);
        }
        else if (out != nullptr && expectOutputLinkedList.next == nullptr) {
            std::printf("[Fail #%d] Mismatch. Output is not null. Expect is null.\n", i);
        }
        else {
            int index = 0;
            ListNode* outPtr = out;
            ListNode* expectPtr = expectOutputLinkedList.next;
            bool isFail = false;
            while (outPtr != nullptr && expectPtr != nullptr) {
                if (outPtr->val != expectPtr->val) {
                    std::printf("[Fail #%d] Element at %d for Output=%d, Expect=%d\n", i, index, outPtr->val, expectPtr->val);
                    isFail = true;
                    break;
                }
                outPtr = outPtr->next;
                expectPtr = expectPtr->next;
                ++index;
            }

            if (!isFail)
                std::printf("[Success #%d]\n", i);
        }

    }

    infile.close();

    return 0;
}
