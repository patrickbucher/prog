// buffer is a data structure that holds a source file from which a buffer with
// both lookahead and lookback is built up.
typedef struct {
    FILE *source;
    int *data;
    int size;
    int lookahead;
    int lookback;
    int current;
    int populated;
} buffer;

// new_buffer creates a new buffer of the given size reading from the source
// file handler. The size is divided into a lookahead buffer (third parameter),
// a current item, and a lookback buffer with (size-lookahead-1) elements.
buffer *new_buffer(FILE *source, int size, int lookahead);

// free_buffer unallocates the memory held by the buffer data structure. The
// source file must be closed by the caller.
void free_buffer(buffer *buf);

// get returns a single character from the buffer. The offset defines from
// which part of the buffer the character shall be read: negative offset for
// lookback, positive offset for lookahead, and zero for the current item.
// Reading outside of the lookahead/lookback buffer returns EOF.
int get(buffer *buf, int offset);

// next moves the buffer forward by one item and returns the underlying
// character. EOF is returned if the source file is exhausted.
int next(buffer *buf);
