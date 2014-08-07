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
	/* - - - */
	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_SUCCESS);
	/* x - - */
	assert(ringbuffer_push(h, (unsigned char *)&y) == RBE_SUCCESS);
	/* x y - */
	assert(ringbuffer_pop(h) == RBE_SUCCESS);
	assert(ringbuffer_push(h, (unsigned char *)&z) == RBE_SUCCESS);
	/* x y z */
	assert(ringbuffer_full(h) != 0);
	assert(ringbuffer_pop(h) == RBE_SUCCESS);
	assert(ringbuffer_push(h, (unsigned char *)&x) == RBE_SUCCESS);

	{ /* checking the erased data: x y z  */
		unsigned *off = (unsigned *) h;
		int *values = (int *) off + offset_data;
		assert(*(off + offset_remove) == 2 * sizeof(x));
		assert(*(off + offset_insert) == 1 * sizeof(x));
		assert(values[0] == x);
		assert(values[1] == y);
		assert(values[2] == z);
	}

	/* x y z */
	assert(ringbuffer_push(h, (unsigned char *)&y) == RBE_NO_SPACE_OR_DATA);
	/* x y z */
	assert(ringbuffer_resize(&h, 5) == RBE_SUCCESS);

	{ /* checking the data: x y z x - */
		unsigned *off = (unsigned *) h;
		int *values = (int *) off + offset_data;
		assert(*(off + offset_remove) == 2 * sizeof(x));
		assert(*(off + offset_insert) == 4 * sizeof(x));
		assert(values[0] == x);
		assert(values[1] == y);
		assert(values[2] == z);
		assert(values[3] == x);
	}
	/* x y z x - */
	assert(ringbuffer_full(h) == 0);
	assert(ringbuffer_empty(h) == 0);
	assert(ringbuffer_push(h, (unsigned char *)&m) == RBE_SUCCESS);
	/* x y z x m */
	assert(ringbuffer_push(h, (unsigned char *)&y) == RBE_SUCCESS);
	/* y y z x m */
	assert(ringbuffer_full(h) != 0);

	{ /* checking the data: y y z x m  */
		unsigned *off = (unsigned *) h;
		int *values = (int *) off + offset_data;
		assert(*(off + offset_remove) == 2 * sizeof(x));
		assert(*(off + offset_insert) == 1 * sizeof(x));
		assert(values[0] == y);
		assert(values[1] == y);
		assert(values[2] == z);
		assert(values[3] == x);
		assert(values[4] == m);
	}

	ringbuffer_destroy(&h);

	return 0;
}
