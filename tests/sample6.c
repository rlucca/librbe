#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "ringbuffer.h"

int main()
{
	struct RingBuffer *h = NULL;
	int x = 10, y = INT_MAX, z = 2863311530, m = -3333;
	int offset_remove = 2;
	int offset_insert = 3;
	int offset_data = 4;

	assert(ringbuffer_init(&h, 3, sizeof(x)) == 0);
	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_SUCCESS);
	assert(ringbuffer_push(h, (unsigned char *)&y) == RBE_SUCCESS);
	assert(ringbuffer_full(h) != 0);
	assert(ringbuffer_pop(h) == RBE_SUCCESS);
	assert(ringbuffer_push(h, (unsigned char *)&z) == RBE_SUCCESS);
	assert(ringbuffer_full(h) != 0);

	assert(ringbuffer_resize(&h, 5) == RBE_SUCCESS);
	assert(ringbuffer_full(h) == 0);
	assert(ringbuffer_empty(h) == 0);
	assert(ringbuffer_push(h, (unsigned char *)&m) == RBE_SUCCESS);
	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_SUCCESS);
	assert(ringbuffer_full(h) != 0);

	{ /* checking the data: x y z m x  */
		unsigned *off = (unsigned *) h;
		int *values = (int *) off + offset_data;
		assert(*(off + offset_remove) == 1 * sizeof(x));
		assert(*(off + offset_insert) == 0);
		assert(values[0] == x);
		assert(values[1] == y);
		assert(values[2] == z);
		assert(values[3] == m);
		assert(values[4] == x);
	}

	ringbuffer_destroy(&h);

	return 0;
}
