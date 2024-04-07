#include <stdio.h>

int bocchiShutUp(int flag, int seq[], int size) {
    int count[6] = {0}; // 初始化计数数组，用于存储数字 1-6 的出现次数

    // 根据 flag 统计数字的出现次数
    for (int i = 0; i < size; ++i) {
        int tens_digit = seq[i] / 10;
        if ((flag == 1 && tens_digit == 1) || (flag == 2 && tens_digit == 2)) {
            int index = seq[i] % 10 - 1; // 将个位数字映射到数组索引
            count[index]++;
        }
    }

    // 寻找出现次数最多的数字
    int max_count = 0;
    for (int i = 0; i < 6; ++i) {
        if (count[i] > max_count) {
            max_count = count[i];
        }
    }

    // 寻找“👻幽灵”数字
    int ghost_count = 0;
    int ghost_number = 0;
    for (int i = 0; i < 6; ++i) {
        if (count[i] == max_count) {
            ghost_count++;
            ghost_number = i + 1; // 将索引映射回原始数字
        }
    }

    // 返回合适的结果
    if (ghost_count == 1) {
        return ghost_number + (flag * 10); // 包含 flag 以区分具有相同数字但不同 flag 的幽灵
    } else {
        return 10;
    }
}