/**
 * Problem 133 - Clone Graph - https://leetcode.com/problems/clone-graph/ 
 *
 * Format of testcase.txt is as follows
 *
 * Number of testcases
 * TC#1 Number of adjacency list (thus number of nodes)
 * TC#1 Adjacency for 1st node
 * TC#1 Adjacency for 2nd node
 * TC#1 ... (so on)
 * TC#1 Adjacency for n-nd node
 * TC#2 ... and so on
 *
 * Time complexity: O(N + E)
 * Space complexity: O(N) from 3 auxiliary data structure to keep track of operations
 */
#include <vector>
#include <cassert>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <queue>
#include <utility>
#include <set>
#include <cstring>
#include <algorithm>
#include <stack>
#include <tuple>
#include <unordered_set>

// Definition for a Node.
class Node {
public:
    int val;
    std::vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = std::vector<Node*>();
    }

    Node(int _val) {
        val = _val;
        neighbors = std::vector<Node*>();
    }

    Node(int _val, std::vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr)
            return nullptr;

        std::unordered_set<int> visited;
        std::unordered_map<int, Node*> lookup;
        std::queue<const Node*> processingNodes;

        processingNodes.push(node);

        while (!processingNodes.empty()) {
            const Node* toCloneNode = processingNodes.front();
            processingNodes.pop();

            if (visited.count(toCloneNode->val) == 0) {
                auto memoIt = lookup.find(toCloneNode->val);
                Node* clonedParentNode;
                if (memoIt == lookup.end()) {
                    clonedParentNode = new Node(toCloneNode->val);
                    lookup.insert(std::make_pair(clonedParentNode->val, clonedParentNode));
                }
                else
                    clonedParentNode = memoIt->second;

                visited.insert(clonedParentNode->val);

                for (auto it=toCloneNode->neighbors.begin(); it!=toCloneNode->neighbors.end(); ++it) {
                    processingNodes.push(*it);

                    auto memoChildIt = lookup.find((*it)->val);
                    if (memoChildIt == lookup.end()) {
                        Node* clonedNode = new Node((*it)->val);
                        lookup.insert(std::make_pair(clonedNode->val, clonedNode));
                        clonedParentNode->neighbors.push_back(clonedNode);
                    }
                    else {
                        clonedParentNode->neighbors.push_back(memoChildIt->second);
                    }
                }
            }
        }

        return lookup[1];
    }
};

// suitable for printing sequence of nodes
class TraversalDFS {
public:
    void traversePrint(const Node* node) {
        std::set<int> visited;
        traversePrint_(node, visited);
    }

    // optimized to use iterative instead of recursive
    void traversePrintStack(const Node* node) {
        if (node == nullptr)
            return;

        std::unordered_map<int, const Node*> visited;
        std::stack<std::pair<const Node*, bool>> depthNodes;    // true for parent node, false if not
        std::queue<const Node*> processingNodes;
        
        processingNodes.push(node);

        while (!processingNodes.empty()) {
            const Node* node = processingNodes.front();
            processingNodes.pop();

            const auto searchIt = visited.find(node->val);
            if (searchIt != visited.end())
                continue;
            else
                visited.insert(std::make_pair(node->val, node));

            depthNodes.push(std::make_pair(node, true));

            for (auto it=node->neighbors.begin(); it!=node->neighbors.end(); ++it) {
                processingNodes.push(*it);
                depthNodes.push(std::make_pair(*it, false));
            }
        }

        while (!depthNodes.empty()) {
            const Node* node;
            bool isParentNode;
            std::tie(node, isParentNode) = depthNodes.top();
            depthNodes.pop();

            if (isParentNode)
                std::cout << '(' << node->val << ") ";
            else
                std::cout << node->val << " ";
        }
    }
    std::vector<Node*> traverseGet(const Node* node) {
        std::set<int> visited;
        std::vector<Node*> nodesCollected;
        traverseGet_(node, visited, nodesCollected);
        return nodesCollected;
    }
    void deleteAll(Node* node) {
        if (node == nullptr)
            return;

        std::vector<Node*> nodes = traverseGet(node);
        for (int i=0; i<nodes.size(); ++i) {
            delete nodes[i];
        }
    }
private:
    void traversePrint_(const Node* node, std::set<int>& visited) {
        if (node == nullptr)
            return;

        std::cout << "(" << node->val << ") ";
        visited.insert(node->val);

        for (auto it=node->neighbors.begin(); it!=node->neighbors.end(); ++it) {
            auto searchIt = visited.find((*it)->val);
            if (searchIt != visited.end())
                continue;       // already visited
            else
                traversePrint_(*it, visited);
        }
    }
    void traverseGet_(const Node* node, std::set<int>& visited, std::vector<Node*>& nodesCollected) {
        if (node == nullptr)
            return;

        nodesCollected.push_back(const_cast<Node*>(node));
        visited.insert(node->val);

        for (auto it=node->neighbors.begin(); it!=node->neighbors.end(); ++it) {
            auto searchIt = visited.find((*it)->val);
            if (searchIt != visited.end())
                continue;       // already visited
            else
                traverseGet_(*it, visited, nodesCollected);
        }
    }
};

// suitable for printing neighbors of each node
// optimized: to use iterative, no recursive
class TraversalBFS {
public:
    void traversePrint(const Node* node) {
        if (node == nullptr)
            return;

        std::unordered_map<int, const Node*> visited;
        std::queue<const Node*> sameLevelNodes;
        sameLevelNodes.push(node);

        while (!sameLevelNodes.empty()) {
            const Node* node = sameLevelNodes.front();
            sameLevelNodes.pop();

            const auto searchIt = visited.find(node->val);
            if (searchIt != visited.end())
                continue;
            else
                visited.insert(std::make_pair(node->val, node));

            std::cout << '(' << node->val << ") ";
            for (auto it=node->neighbors.begin(); it!=node->neighbors.end(); ++it) {
                sameLevelNodes.push(*it);
                std::cout << (*it)->val << " ";
            }
        }
    }
};

class Checker {
public:
    // return true if both chain of nodes in a is equal to b
    bool checkEqual(const Node* a, const Node* b) {
        if (a == nullptr && b == nullptr)
            return true;
        if (a == nullptr && b != nullptr)
            return false;
        if (a != nullptr && b == nullptr)
            return false;

        std::unordered_set<int> checked;
        std::queue<std::pair<const Node*, const Node*>> processingNodes;
        processingNodes.push(std::make_pair(a, b));

        while (!processingNodes.empty()) {
            const Node* nodeA;
            const Node* nodeB;
            std::tie(nodeA, nodeB) = processingNodes.front();
            processingNodes.pop();

            if (checked.count(nodeA->val) > 0)
                continue;

            if (nodeA->val != nodeB->val)
                return false;
            if (nodeA->neighbors.size() != nodeB->neighbors.size())
                return false;
            
            const int size = nodeA->neighbors.size();
            const std::vector<Node*> nodeA_neighbors = nodeA->neighbors;
            const std::vector<Node*> nodeB_neighbors = nodeB->neighbors;
            for (int i=0; i<size; ++i) {
                if (nodeA_neighbors[i]->val != nodeB_neighbors[i]->val)
                    return false;

                processingNodes.push(std::make_pair(nodeA_neighbors[i], nodeB_neighbors[i]));
            }

            checked.insert(nodeA->val);
        }

        return true;
    }
};

int main()
{
    std::ifstream infile("testcases.txt");
    std::string line;

    int N;
    infile >> N;    // read number of testcases

    Solution sol;

    for (int i=0; i<N; ++i)
    {
        int n;      // number of adjacency list, thus number of nodes
        infile >> n;
        infile.ignore();

        Node* operateNode = nullptr;
        Node* startNode = nullptr;
        std::unordered_map<int, Node*> lookup;

        for (int j=0; j<n; ++j) {
            const int key = j+1;
            if (j == 0) {
                Node* newNode = new Node(key);
                lookup.insert(std::make_pair(key, newNode));
                operateNode = newNode;
                startNode = newNode;
            }
            else {
                auto searchIt = lookup.find(key);
                if (searchIt != lookup.end()) {
                    operateNode = searchIt->second;
                }
                else {
                    Node* newNode = new Node(key);
                    lookup.insert(std::make_pair(key, newNode));
                    operateNode = newNode;
                }
            }

            std::getline(infile, line);
            std::istringstream lineStream(line);

            // get list of input numbers
            int num;
            while (lineStream >> num)
            {
                auto searchIt = lookup.find(num);
                if (searchIt != lookup.end()) {
                    operateNode->neighbors.push_back(searchIt->second);
                }
                else {
                    Node* newNode = new Node(num);
                    lookup.insert(std::make_pair(num, newNode));
                    operateNode->neighbors.push_back(newNode);
                }
            }
        }

        // gather all nodes from the resultant cloneGraph() function
        std::unordered_map<int, Node*> lookupB (n);
        std::queue<Node*> queueB;

        Node* outResult = sol.cloneGraph(startNode);
        if (outResult) {
        }

        if (!outResult && !startNode) {
            std::printf("[Success #%d] Both starting node are empty\n", i);
        }
        else {
            if (Checker().checkEqual(startNode, outResult)) {
                std::printf("[Success #%d] Both chains of nodes matched\n", i);
            }
            else {
                std::printf("[Failed #%d] Mismatch\n", i);
            }
        }

        // clear heap memory from all nodes
        auto deleter = TraversalDFS();
        deleter.deleteAll(startNode);
        deleter.deleteAll(outResult);
    }

    infile.close();

    return 0;
}
