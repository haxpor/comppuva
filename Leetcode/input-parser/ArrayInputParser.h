#pragma once

#include <vector>
#include <string>

/**
 * User still need to know which format to read and choose appropriately from either parse() or parse2()
 * function.
 */
class ArrayInputParser {
public:
    std::vector<int> parse(const std::string& str) const;
    std::vector<std::vector<int>> parse2(const std::string& str) const;
};
