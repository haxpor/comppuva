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
#include <unordered_map>
#include <queue>
#include <utility>
#include <set>
#include <cstring>
#include <algorithm>
#include <stack>
#include <tuple>

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

        std::unordered_map<int, Node*> lookup;
        cloneGraph_(node, lookup);
        return lookup[1];       // should be at least 1 node which always starts with 1
    }
private:
    void cloneGraph_(Node* node, std::unordered_map<int, Node*>& lookup) {
        if (node == nullptr)
            return;
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
    bool checkEqual(Node* a, Node* b) {
        std::set<int> checked;
        return checkEqual_(a, b, checked);
    }
private:
    bool checkEqual_(Node* a, Node* b, std::set<int>& checked) {
        if (a == nullptr || b != nullptr)
            return false;
        if (a != nullptr || b == nullptr)
            return false;

        const auto searchIt = checked.find(a->val);
        if (searchIt != checked.end())  // immediately return true, checked means checked & equal
            return true;
        
        if (a->val != b->val)
            return false;
        if (a->neighbors.size() != b->neighbors.size())
            return false;

        checked.insert(a->val);

        // optional: might not be necessary, but to make sure
        std::sort(a->neighbors.begin(), a->neighbors.end());
        std::sort(b->neighbors.begin(), b->neighbors.end());

        const int size = a->neighbors.size();
        for (int i=0; i<size; ++i) {
            return checkEqual_(a->neighbors[i], b->neighbors[i], checked);
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
