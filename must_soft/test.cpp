#include <stdio.h>
int main(void)

{
    char buffer[200], s[] = "computer", c = 'l';
    int i = 35, j;
    float fp = 1.7320534f;
    // 格式化并打印各种数据到buffer
    sprintf(buffer, "   String:    %s\n", s); // C4996
    printf("Output:\n%s", buffer);
    sprintf(buffer, "   Character: %c\n", c); // C4996
    printf("Output:\n%s", buffer);
    sprintf(buffer, "   Integer:   %d\n", i); // C4996
    printf("Output:\n%s", buffer);
    sprintf(buffer, "   Real:      %f\n", fp); // C4996
    printf("Output:\n%s", buffer);

    return 0;
}