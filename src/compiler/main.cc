#include <reader.hh>

int main(int argc, char* argv[]) {
    std::cout << readSourceCodeIntoString(argv[1]) << std::endl;
    return 0;
}
