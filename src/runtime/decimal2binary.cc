#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

std::string decimalToBinary(const std::string& decimalStr) {
    std::string binaryResult;
    std::string currentValue = decimalStr;
    
    while (currentValue != "0") {
        std::string newValue;
        int carry = 0;
        int remainder = 0;

        for (char digit : currentValue) {
            int currentDigit = carry * 10 + (digit - '0');
            remainder = currentDigit % 2;
            newValue.push_back(currentDigit / 2 + '0');
            carry = (currentDigit % 2);
        }

        // 移除前导零
        while (newValue.size() > 1 && newValue.front() == '0') {
            newValue.erase(newValue.begin());
        }

        binaryResult.push_back(remainder + '0');
        currentValue = newValue;
    }

    std::reverse(binaryResult.begin(), binaryResult.end());
    return binaryResult;
}

