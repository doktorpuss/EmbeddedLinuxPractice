#include"my_strlib.h"

char* strsplit(char *input, const char *delim)
{
    static char *cursor = NULL;  // nhớ vị trí
    char *start;
    char *pos;

    if (input != NULL)
        cursor = input;  // bắt đầu mới

    if (cursor == NULL)
        return NULL;  // hết chuỗi

    // tìm delimiter trong cursor
    pos = strstr(cursor, delim);

    if (pos == NULL) {
        // không còn delimiter, trả phần cuối
        char *result = cursor;
        cursor = NULL;
        return result;
    }

    // cắt chuỗi
    *pos = '\0';
    start = cursor;

    // nhảy qua delimiter
    cursor = pos + strlen(delim);

    return start;
}


int main()
{
    char str[] = "Day la dong 1\nDay la dong thu 2\n\nDay la dong thu 4\n\nDay la dong thu 6";

    char *token = strsplit(str, "\n\n");

    int count = 0;
    while (token != NULL) {
        printf("Dong %d: '%s'\n", count, token);
        token = strsplit(NULL, "\n\n");
        count++;
    }

    return 0;
}