#ifndef CHINESECHESS_TESTFRAMEWORK_H
#define CHINESECHESS_TESTFRAMEWORK_H

#include <cstdlib>
#include <iostream>

#if __WIN32
#include <Windows.h>
#endif

#define ASSERT_TRUE(condition, message)                                                            \
    do {                                                                                           \
        if (!(condition)) {                                                                        \
            std::cerr << "断言失败: " << #condition << " 于 " << __FILE__ << ":" << __LINE__       \
                      << std::endl;                                                                \
            std::cerr << "错误信息: " << message << std::endl;                                     \
            std::exit(1);                                                                          \
        }                                                                                          \
    } while (0)

#define ASSERT_FALSE(condition, message) ASSERT_TRUE(!(condition), message)
#define ASSERT_EQ(a, b, message)                                                                   \
    ASSERT_TRUE((a == b), #a " == " #b " 不成立，实际值: " #a " = " << (a) << ", " #b " = " << (b) \
                                                                    << "。" << message)

#ifdef __WIN32
#define SetOutputCharset SetConsoleOutputCP(CP_UTF8)
#else
#define SetOutputCharset                                                                           \
    do {                                                                                           \
    } while (0)
#endif

#define TEST_MAIN(...)                                                                             \
    int main() {                                                                                   \
        SetOutputCharset;                                                                          \
        std::cout << "开始执行测试..." << std::endl;                                               \
        __VA_ARGS__                                                                                \
        std::cout << "全部测试通过！" << std::endl;                                                \
        return 0;                                                                                  \
    }

#define TEST_CASE(name) void test_##name()

#define RUN_TEST(name)                                                                             \
    do {                                                                                           \
        std::cout << "运行测试: " << #name << std::endl;                                           \
        test_##name();                                                                             \
        std::cout << "测试通过" << std::endl;                                                      \
    } while (0)

#endif // CHINESECHESS_TESTFRAMEWORK_H