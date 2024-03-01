# include <stdio.h>
# include <string.h>
int main(void)
{
    char str[] = "/bin/ls -l";
    char *s = strtok(str, " ");
    printf("This the original one : %s\n", str);
    printf("This is the token : %s\n", s);
    s = strtok(str, " ");
    printf("This is the token : %s\n", s);
}