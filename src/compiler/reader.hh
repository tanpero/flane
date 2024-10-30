#ifndef _COMPILER_READER_HH_
#define _COMPILER_READER_HH_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string readSourceCodeIntoString(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    file.close();

    return buffer.str();
}

#endif // !_COMPILER_READER_HH_
