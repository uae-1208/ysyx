#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>


int main(void)
{
    uint32_t result;
    int ret;
    char buff[40];

    FILE *fp = fopen("./uae", "r");
    assert(fp != NULL);

    for(int i = 0; i < 30; i++)
    {
        ret = fscanf(fp, "%u ", &result);  //fscanf读取字符串时无法读取空格
        assert(ret != 0);
        fgets(buff, 40, fp);               //fgets遇到\n时结束读取，但会读取进\n
        buff[strlen(buff) - 1] = '\0';     //删除\n
        printf("%u %s\n", result, buff);
    }


    return 0;
}