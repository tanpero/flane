#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdint>

std::string decimalToBinary(const std::string& decimalStr) {
    std::string binaryResult;
    std::string currentValue = decimalStr;
    
    while (currentValue != "0") {
        std::string newValue; // 记录除以2后的值
        int carry = 0; // 记录进位
        int remainder = 0; // 余数

        for (char digit : currentValue) {
            int currentDigit = carry * 10 + (digit - '0'); // 处理进位
            remainder = currentDigit % 2; // 余数
            newValue.push_back(currentDigit / 2 + '0'); // 更新当前值
            carry = (currentDigit % 2); // 进位
        }

        // 移除前导零
        while (newValue.size() > 1 && newValue.front() == '0') {
            newValue.erase(newValue.begin());
        }

        binaryResult.push_back(remainder + '0'); // 将余数（当前二进制位）加入结果
        currentValue = newValue; // 更新当前值
    }

    // 反转结果
    std::reverse(binaryResult.begin(), binaryResult.end());
    return binaryResult;
}

