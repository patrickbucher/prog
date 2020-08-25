#include <stdlib.h>
#include <stdio.h>

#include "buffer.h"

buffer *new_buffer(FILE *source, int size, int lookahead)
{
    buffer *buf = (buffer *)malloc(sizeof(buffer));
    buf->source = source;
    buf->data = (int *)malloc(sizeof(int) * size);
    buf->size = size;
    buf->lookahead = lookahead;
    buf->lookback = size - lookahead - 1;
    buf->current = -1;
    buf->populated = -1;
    return buf;
}

void free_buffer(buffer *buf)
{
    free(buf->data);
    free(buf);
}

int get(buffer *buf, int offset)
{
    if ((offset < 0 && offset < buf->lookback * -1) ||
            (offset > 0 && offset > buf->lookahead)) {
        return EOF;
    }
    if (offset < 0) {
        if (buf->current + offset >= 0) {
            return buf->data[buf->current + offset];
        } else {
            return EOF;
        }
    }
    if (offset > 0) {
        while (buf->populated < buf->current + offset) {
            int c = getc(buf->source);
            if (c == EOF) {
                return EOF;
            }
            buf->populated++;
            buf->data[buf->populated] = c;
        }
        return buf->data[buf->populated];
    }
    if (buf->current == -1) {
        int c;
        if ((c = getc(buf->source)) == EOF) {
            return EOF;
        } else {
            buf->current++;
            buf->populated = buf->current;
            buf->data[buf->current] = c;
        }
    }
    return buf->data[buf->current];
}

int next(buffer *buf)
{
    int c = 0;
    if (buf->current >= buf->populated) {
        c = getc(buf->source);
        if (c == EOF) {
            return EOF;
        }
    }
    if (buf->current >= buf->lookback) {
        for (int i = 0; i < buf->size - 1; i++) {
            buf->data[i] = buf->data[i+1];
        }
        buf->populated--;
    } else {
        buf->current++;
    }
    if (c != 0) {
        buf->data[buf->current] = c;
        if (buf->populated < buf->current) {
            buf->populated = buf->current;
        }
    }
    return buf->data[buf->current];
}
