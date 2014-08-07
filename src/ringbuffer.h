#pragma once

struct RingBuffer;

enum {
	RBE_SUCCESS = 0,
	RBE_RESERVED = 1, /* Reserved to not missinterpretate pop/empty */
	RBE_WRONG_ARGS = 2,
	RBE_NO_MEMORY,
	RBE_NO_SPACE_OR_DATA,
	RBE_LAST
};

int
ringbuffer_init(struct RingBuffer **handler, unsigned count, unsigned size);

int
ringbuffer_push(struct RingBuffer *handler, unsigned char *buffer);

int
ringbuffer_top(struct RingBuffer *handler, unsigned char *buffer);

int
ringbuffer_pop(struct RingBuffer *handler);

int
ringbuffer_empty(struct RingBuffer *handler);

int
ringbuffer_full(struct RingBuffer *handler);

/* It will return error if count is not greater than the old count.
Also, it will move the pointers of the elements to inside of the new block. */
int
ringbuffer_resize(struct RingBuffer **handler, unsigned count);

void
ringbuffer_destroy(struct RingBuffer **handler);
