#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "ringbuffer.h"

int main()
{
	struct RingBuffer *h = NULL;
	int x;
	assert(ringbuffer_init(&h, 3, sizeof(x)) == 0);
	assert(ringbuffer_pop(h) == RBE_NO_SPACE_OR_DATA);
	x = 10;
	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_SUCCESS);
	x = -1;
	assert(ringbuffer_top(h, (unsigned char *)&x) == RBE_SUCCESS);
	assert(x == 10);
	x = 666;
	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_SUCCESS);
	x = -1;
	assert(ringbuffer_top(h, (unsigned char *)&x) == RBE_SUCCESS);
	assert(x == 10);
	assert(ringbuffer_pop(h) == RBE_SUCCESS);
	x = -1;
	assert(ringbuffer_top(h, (unsigned char *)&x) == RBE_SUCCESS);
	assert(x == 666);
	assert(ringbuffer_pop(h) == RBE_SUCCESS);
	assert(ringbuffer_pop(h) == RBE_NO_SPACE_OR_DATA);
	assert(ringbuffer_empty(h) != 0);
	ringbuffer_destroy(&h);

	assert(ringbuffer_init(&h, 3, sizeof(x)) == 0);
	x = INT_MIN;
	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_SUCCESS);
	x = INT_MAX;
	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_SUCCESS);
	x = -1;
	assert(ringbuffer_top(h, (unsigned char *)&x) == RBE_SUCCESS);
	assert(x == INT_MIN);
	assert(ringbuffer_pop(h) == RBE_SUCCESS);
	assert(ringbuffer_top(h, (unsigned char *)&x) == RBE_SUCCESS);
	assert(x == INT_MAX);
	ringbuffer_destroy(&h);
	return 0;
}
