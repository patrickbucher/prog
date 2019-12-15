#include <libowfat/buffer.h>
#include <libowfat/mmap.h>

int main()
{
    size_t filesize;
    const char *junk = mmap_read("./junk.txt", &filesize);
    buffer_puts(buffer_1, junk);
    buffer_flush(buffer_1);
    return 0;
}
