#include "ArrayInputParser.h"
#include <stack>
#include <stdexcept>
#include <iostream>

std::vector<int> ArrayInputParser::parse(const std::string& str) const {
    if (str.size() == 0)
        return {};

    std::stack<char> st;
    std::vector<int> resVector;
    std::string tmpIntStr = "";

    for (const char& c : str) {
        if (c == '[')
            st.push(c);
        else if (c  >= '0' && c <= '9')
            tmpIntStr += c;
        else if (c == ',') {
            resVector.push_back(std::stoi(tmpIntStr));
            tmpIntStr = ""; 
        }
        else if (c == ']') {
            if (tmpIntStr != "") {
                resVector.push_back(std::stoi(tmpIntStr));
                tmpIntStr = "";
            }
            st.pop();
        }
    }

    // validate correctness
    if (st.size() != 0)
        throw std::runtime_error("stack size should be 0");

    return resVector;
}

std::vector<std::vector<int>> ArrayInputParser::parse2(const std::string& str) const {
    if (str.size() == 0)
        return {};      

    std::stack<char> st;
    std::vector<std::vector<int>> resVector;
    std::vector<int> tmpVector;
    std::string tmpIntStr = "";

    int leftParenCount = 0;

    for (const char& c : str) {
        if (c == '[') {
            ++leftParenCount;
            if (leftParenCount >= 2)
                tmpVector.clear();
            st.push(c);
        }
        else if (c  >= '0' && c <= '9' && leftParenCount >= 2) {
            tmpIntStr += c;
        }
        else if (c == ',' && leftParenCount >= 2) {
            tmpVector.push_back(std::stoi(tmpIntStr));
            tmpIntStr = ""; 
        }
        else if (c == ']') {
            if (leftParenCount >= 2) {
                if (tmpIntStr != "") {
                    tmpVector.push_back(std::stoi(tmpIntStr));
                }
                resVector.emplace_back(std::move(tmpVector));
                tmpIntStr = "";
            } 
            --leftParenCount;
            st.pop();
        }
    }

    // validate correctness
    if (st.size() != 0)
        throw std::runtime_error("stack size should be 0");

    return resVector;
    
}
