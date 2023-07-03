#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);

    // 禁用标准输入的缓冲区
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    // 读取字符
    char c;
    ssize_t bytesRead = read(STDIN_FILENO, &c, sizeof(c));
    if (bytesRead == -1) {
        // 读取错误，处理错误
        return 1;
    }

    // 恢复标准输入的缓冲区
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    // 处理读取到的字符
    // ...
    printf("%c\n",c);
    printf("end\n");
    printf("%c\n",c);

    return 0;
}

