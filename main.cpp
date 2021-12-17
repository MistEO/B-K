#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

constexpr int MaxDataSize = 16384;

using Iter = std::string::const_iterator;

bool brainfuck(const std::string& content);
Iter brainfuck(Iter begin, Iter end, char* ptr, char* head);

int main(int argc, char** argv)
{
    if (argc == 1) {
        std::cout << "Hello World" << std::endl;
        return 0;
    }
    for (int i = 1; i < argc; ++i) {
        std::stringstream iss;
        std::ifstream f(argv[i]);
        iss << f.rdbuf();
        f.close();
        std::string content = iss.str();

        bool ret = brainfuck(content);
        if (!ret) {
            return 1;
        }
    }
    return 0;
}

bool brainfuck(const std::string& content)
{
    std::vector<char> data(MaxDataSize);

    auto iter = content.cbegin();
    while (iter != content.cend()) {
        iter = brainfuck(iter, content.cend(), data.data(), data.data());
    }
    return true;
}

Iter brainfuck(Iter begin, Iter end, char* ptr, char* head)
{
    for (auto iter = begin; iter != end; ++iter) {
        switch (*iter) {
        case '>':
            if (ptr != head + MaxDataSize) {
                ++ptr;
            }
            break;
        case '<':
            if (ptr != head) {
                --ptr;
            }
            break;
        case '+':
            ++(*ptr);
            break;
        case '-':
            --(*ptr);
            break;
        case '.': {
            char tmp = *ptr;
            std::cout << tmp;
        } break;
        case ',': {
            char tmp = 0;
            std::cin >> tmp;
            *ptr = tmp;
        } break;
        case '[': {
            auto tmp = iter;
            while (*ptr) {
                tmp = brainfuck(iter + 1, end, ptr, head);
            }
            iter = tmp;
        } break;
        case ']': {
            return iter;
        } break;
        case ' ':
        case '\r':
        case '\n':
        case '\t':
            break;
        default:
            return end;
        }
    }
    return end;
}
