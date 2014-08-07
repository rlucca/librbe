#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "ringbuffer.h"

int main()
{
	struct RingBuffer *h = NULL;
	int x = 10, y = INT_MAX, z = 2863311530, k;
	assert(ringbuffer_init(&h, 0, sizeof(x)) == 0);
	assert(ringbuffer_pop(h) == RBE_NO_SPACE_OR_DATA);
	assert(ringbuffer_push(h, (unsigned char *)&k) == RBE_NO_SPACE_OR_DATA);
	assert(ringbuffer_top(h, (unsigned char *)&k) == RBE_NO_SPACE_OR_DATA);
	assert(ringbuffer_empty(h) == 0);
	assert(ringbuffer_full(h) != 0);

	assert(ringbuffer_resize(NULL, 4) == RBE_WRONG_ARGS);
	assert(ringbuffer_resize(&h, 0) == RBE_WRONG_ARGS);
	assert(ringbuffer_resize(&h, 4) == RBE_SUCCESS);
	assert(ringbuffer_empty(h) != 0);
	assert(ringbuffer_full(h) == 0);
	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_SUCCESS);
	assert(ringbuffer_push(h, (unsigned char *)&y) == RBE_SUCCESS);
	assert(ringbuffer_pop(h) == RBE_SUCCESS);
	assert(ringbuffer_empty(h) == 0);
	assert(ringbuffer_full(h) == 0);
	assert(ringbuffer_top(h, (unsigned char *)&k) == RBE_SUCCESS);
	assert(k == y);
	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_SUCCESS);
	assert(ringbuffer_push(h, (unsigned char *)&z) == RBE_SUCCESS);
	assert(ringbuffer_empty(h) == 0);
	assert(ringbuffer_full(h) != 0);
	k = -1;
	assert(ringbuffer_top(h, (unsigned char *)&k) == RBE_SUCCESS);
	assert(k == y);
	assert(ringbuffer_pop(h) == RBE_SUCCESS);
	assert(ringbuffer_top(h, (unsigned char *)&k) == RBE_SUCCESS);
	assert(k == x);
	assert(ringbuffer_pop(h) == RBE_SUCCESS);
	assert(ringbuffer_top(h, (unsigned char *)&k) == RBE_SUCCESS);
	assert(k == z);

	// It only expands, for secure reasons
	assert(ringbuffer_resize(&h, 2) == RBE_WRONG_ARGS);
	assert(ringbuffer_pop(h) == RBE_SUCCESS);
	assert(ringbuffer_pop(h) == RBE_NO_SPACE_OR_DATA);
	ringbuffer_destroy(&h);

	return 0;
}
