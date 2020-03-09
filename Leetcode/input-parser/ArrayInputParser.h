#pragma once

#include <vector>
#include <string>
#include <stack>
#include <stdexcept>
#include <iostream>

/**
 * User still need to know which format to read and choose appropriately from either parse() or parse2()
 * function.
 */
class ArrayInputParser {
public:
    template <typename T>
    std::vector<T> parse(const std::string& str) const {
        throw std::logic_error("Not implemented");
    }
};

template <>
std::vector<int> ArrayInputParser::parse<int>(const std::string& str) const {
    if (str.size() == 0)
        return {};

    std::stack<char> st;
    std::vector<int> resVector;
    std::string tmpIntStr = "";

    for (const char& c : str) {
        if (c == '[')
            st.push(c);
        else if (c == '-' || c == '+' || (c  >= '0' && c <= '9'))
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
        throw std::runtime_error("stack size should be 0. Input string is '" + str + "'");

    return resVector;
}

template <>
std::vector<char> ArrayInputParser::parse<char>(const std::string& str) const {    
     if (str.size() == 0)
        return {};

    std::stack<char> st;
    std::vector<char> resVector;
    bool elemAddState = false;

    for (const char& c : str) {
        if (c == '[')
            st.push(c);
        else if (c == ']')
            st.pop();
        else if (!elemAddState && c == '"') {
            st.push(c);
            elemAddState = true;
        }
        else if (elemAddState && c == '"') {
            st.pop();
            elemAddState = false;
        }
        else if (elemAddState && c != '"')
            resVector.push_back(c);
    }

    // validate correctness
    if (st.size() != 0)
        throw std::runtime_error("stack size should be 0. Input string is '" + str + "'");

    return resVector;
}

template <>
std::vector<std::vector<int>> ArrayInputParser::parse<std::vector<int>>(const std::string& str) const {
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
        else if (c == '-' || c == '+' || (c  >= '0' && c <= '9' && leftParenCount >= 2)) {
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
        throw std::runtime_error("stack size should be 0. Input string is '" + str + "'");

    return resVector; 
}

template <>
std::vector<std::vector<char>> ArrayInputParser::parse<std::vector<char>>(const std::string& str) const {
    if (str.size() == 0)
        return {};      

    std::stack<char> st;
    std::vector<std::vector<char>> resVector;
    std::vector<char> tmpVector;
    bool elemAddState = false;
    int leftParenCount = 0;

    for (const char& c : str) {
        if (c == '[') {
            ++leftParenCount;
            if (leftParenCount >= 2)
                tmpVector.clear();
            st.push(c);
        }
        else if (!elemAddState && c == '"') {
            st.push(c);
            elemAddState = true;
        }
        else if (elemAddState && c == '"') {
            st.pop();
            elemAddState = false;
        }
        else if (elemAddState && c != '"') {
            tmpVector.push_back(c);
        }
        else if (c == ']') {
            if (leftParenCount >= 2) {
                resVector.emplace_back(std::move(tmpVector));
            } 
            --leftParenCount;
            st.pop();
        }
    }

    // validate correctness
    if (st.size() != 0)
        throw std::runtime_error("stack size should be 0. Input string is '" + str + "'");

    return resVector; 
}
