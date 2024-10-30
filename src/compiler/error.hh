#ifndef _COMPILER_ERROR_HH_
#define _COMPILER_ERROR_HH_

#include <string.hh>
#include <unordered_map>

enum ERROR_TYPE
{
	INVALID_OR_UNEXPECTED_TOKEN,
};

std::unordered_map<ERROR_TYPE, String> error_map{
	{ INVALID_OR_UNEXPECTED_TOKEN, "Invalid or unexpected token" },
};

struct ErrorInfo {
	String info;
	ErrorInfo(ERROR_TYPE e, size_t x, size_t y, size_t length) {
		info = error_map[e];
	}
	size_t x, y, length;
};



#endif // !_COMPILER_ERROR_HH_
