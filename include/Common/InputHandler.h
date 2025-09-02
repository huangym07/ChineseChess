#ifndef CHINESECHESS_COMMON_INPUTHANDLER_H
#define CHINESECHESS_COMMON_INPUTHANDLER_H

class InputHandler {
  public:
    // 读取 [min, max] 区间内的一个整数
    // 从标准输入读取一个整数，并确保其在 [min, max] 范围内
    // 若输入无效，会持续提示并等待正确输入
    // 参数：
    //      min - 允许的最小整数值
    //      max - 允许的最大整数值
    // 返回值：有效范围内的整数
    static int read_int_range(int min, int max);
};

#endif // CHINESECHESS_COMMON_INPUTHANDLER_H