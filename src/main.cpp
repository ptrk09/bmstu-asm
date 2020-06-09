#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#define MAX_LEN_STR 80

#define SUCCESS 0

extern "C" {
    void strcopy(char *dest, const char *src, int32_t size);
}


int32_t asmstrlen(const char *bufStr) {
    int32_t count;

    __asm__(".intel_syntax noprefix\n"
        "lea rdi, [%1]\n"
        "mov ecx, 1024\n"
        "mov eax, 1024\n"

        "repnz scasb\n"
        "sub eax, ecx\n"
        "dec eax\n"

        "mov %0, eax \n"

        : "=r" (count)
        : "r" (bufStr)
        : "eax", "rdi", "ecx"
    );
    return count;
}


void test_asmstrlen() {
    int32_t count = 0;
    char bufInput[MAX_LEN_STR];
    count = asmstrlen(bufInput);

    printf("Введите строку для определения её длины: ");
    scanf("%s", bufInput);
    puts("\n");

    printf("TEST 1 (strlen):\n\tasmstrlen            : %"PRId32"\n\tstrlen(from string.h): %"PRId32, asmstrlen(bufInput), strlen(bufInput));
    puts("\n\n");
}

int32_t main(void) {
    test_asmstrlen();
    
    return SUCCESS;
}
