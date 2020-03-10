/**
 * Problem 143 - Reorder List - https://leetcode.com/problems/reorder-list/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input array of numbers for input linked list
 * TC#1 Array of numbers for expected linked list
 * TC#2 ... and so on
 *
 * Time complexity: <to-be-filled>
 * Space complexity: <to-be-filled>
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include "ArrayInputParser.h"

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x): val(x), next(nullptr) {}
};

class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr)
            return;

        std::vector<ListNode*> list;

        ListNode* nodeptr = head;
        while (nodeptr) {
            list.push_back(nodeptr);
            nodeptr = nodeptr->next;
        }

        const int halfSize = std::floor(list.size()/2.0f);
        const int size = list.size();
        bool isOdd = size & 0x1;
        for (int i=0; i<halfSize; ++i) {
            list[i]->next = list[size-1-i];
            if ((!isOdd && i < halfSize-1) || isOdd)
                list[size-1-i]->next = list[i+1];
        }
        list[halfSize]->next = nullptr;
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
        // read in input linked list
        std::getline(infile, line);
        std::vector<int> nums = aparser.parse<int>(line);

        ListNode* nodeptr = nullptr;

        // form linked list
        ListNode dummyInputNode (-99);      // dummy node
        nodeptr = &dummyInputNode;
        for (const auto& n : nums) {
            nodeptr->next = new ListNode(n);
            nodeptr = nodeptr->next;
        }

        // read in output linked list
        std::getline(infile, line);
        std::vector<int> expectNums = aparser.parse<int>(line);

        // form linked list
        ListNode dummyOutputNode (-99);      // dummy node
        nodeptr = &dummyOutputNode;
        for (const auto& n : expectNums) {
            nodeptr->next = new ListNode(n);
            nodeptr = nodeptr->next;
        }

        // compute
        sol.reorderList(dummyInputNode.next);

        if (dummyInputNode.next == nullptr && dummyOutputNode.next == nullptr) {
            std::printf("[Success #%d]\n", i);
        }
        else if (dummyInputNode.next == nullptr && dummyOutputNode.next != nullptr) {
            std::printf("[Fail #%d] Mismatch\n", i);
        }
        else if (dummyInputNode.next != nullptr && dummyOutputNode.next == nullptr) {
            std::printf("[Fail #%d] Mismatch\n", i);
        }
        else {
            int index = 0;
            ListNode* outPtr = dummyInputNode.next;
            ListNode* expectPtr = dummyOutputNode.next;
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
