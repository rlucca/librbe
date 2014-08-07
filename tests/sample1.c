#include <stdio.h>
#include <assert.h>
#include "ringbuffer.h"

int main()
{
	struct RingBuffer *h = NULL;
	assert(ringbuffer_init(&h, 1, 100) == 0);
	assert(h != NULL);
	ringbuffer_destroy(&h);
	assert(h == NULL);
	return 0;
}
