/**
 * Problem 141 - Linked List Cycle https://leetcode.com/problems/linked-list-cycle/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Input array of numbers (can be positive or negative)
 * TC#1 Position (index-based) for tail of linked list points to representing the cycle of the whole list.
 * TC#1 Expect boolean output "true" or "false" that this linked list has cycle or not
 * TC#2 ... and so on
 *
 * Time complexity: O(N)
 * Space complexity: O(N) (for 1 auxiliary hashmap using std::unordered_set)
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <unordered_set>
#include <functional>
#include "ArrayInputParser.h"

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    bool hasCycle(ListNode* head) {
        std::unordered_set<const ListNode*> visited;

        return dfsCycle(head, visited);
    }
private:
    bool dfsCycle(const ListNode* node, std::unordered_set<const ListNode*>& visited) {
        if (node == nullptr)
            return false;

        // if found in visited, then found cycle
        // use memory address from pointer as the key which should be unique amongs even the same 'val' nodes
        if (visited.find(node) != visited.end())
            return true;

        // mark visited
        visited.insert(node);

        return dfsCycle(node->next, visited);
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
        // get input array of numbers
        std::getline(infile, line);
        std::vector<int> nums = aparser.parse<int>(line);

        // get target position that tail points to representing the cycle
        int cyclePosition;
        infile >> cyclePosition;

        // shared ListNode pointer
        ListNode* nodeptr = nullptr;

        // form linked list
        ListNode inputLinkedList (-9999);       // dummy node
        nodeptr = &inputLinkedList;
        int nodeIndex = 0;
        ListNode* targetCycleNode = nullptr;
        for (const auto& n : nums) {
            nodeptr->next = new ListNode(n);
            if (cyclePosition != -1 && nodeIndex == cyclePosition) {
                targetCycleNode = nodeptr->next;
            }

            if (cyclePosition != -1)
                ++nodeIndex;

            nodeptr = nodeptr->next;
        }
        nodeptr->next = targetCycleNode;        // link the cycle node

        // get expect boolean result
        bool expect;
        infile >> std::boolalpha >>  expect;
        infile.ignore();

        // compute
        bool out = sol.hasCycle(inputLinkedList.next);
        if (out == expect)
        {
            std::printf("[Success #%d] Output = %s, Expect = %s\n", i, out?"true":"false", expect?"true":"false");
        }
        else
        {
            std::printf("[Failed #%d] Output = %s, Expect = %s\n", i, out?"true":"false", expect?"true":"false");
        }
    }

    infile.close();

    return 0;
}
