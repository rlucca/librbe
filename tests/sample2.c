#include <stdio.h>
#include <assert.h>
#include "ringbuffer.h"

int main()
{
	struct RingBuffer *h = NULL;
	int x;
	assert(ringbuffer_init(&h, 1, sizeof(x)) == 0);
	assert(h != NULL);
	assert(ringbuffer_empty(h) == 0);
	assert(ringbuffer_full(h) != 0);
	ringbuffer_destroy(&h);
	assert(h == NULL);

	assert(ringbuffer_init(&h, 3, sizeof(x)) == 0);
	assert(h != NULL);
	assert(ringbuffer_empty(h) != 0);
	assert(ringbuffer_full(h) == 0);

	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_SUCCESS);
	assert(ringbuffer_empty(h) == 0);
	assert(ringbuffer_full(h) == 0);
	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_SUCCESS);
	assert(ringbuffer_empty(h) == 0);
	assert(ringbuffer_full(h) != 0);
	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_NO_SPACE_OR_DATA);
	ringbuffer_destroy(&h);
	assert(h == NULL);
	return 0;
}
