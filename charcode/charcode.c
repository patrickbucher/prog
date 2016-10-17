#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

int main()
{
    wint_t c;

    while ((c = getwchar()) != WEOF) {
        if (c != '\n') {
            wprintf(L"%lc\t0x%04x\t%5d\n", c, c, c);
        }
    }
    return 0;
}
