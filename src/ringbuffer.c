#include "ringbuffer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct RingBuffer {
	unsigned capacity;		/* how much elements */
	unsigned size;			/* size of each element */
	unsigned front;			/* index to where remove elements */
	unsigned back;			/* index to where insert elements */
	unsigned char data[0];	/* allocated data */
};

static unsigned
rb_advance(struct RingBuffer *handler, unsigned pos)
{
	return (pos + handler->size) % handler->capacity;
}

int
ringbuffer_init(struct RingBuffer **handler, unsigned n_elements, unsigned size)
{
	if (handler == NULL || size == 0)
		return RBE_WRONG_ARGS;

	*handler = realloc(*handler, sizeof(struct RingBuffer) + size * n_elements);
	if (*handler == NULL)
		return RBE_NO_MEMORY;

	handler[0]->front = handler[0]->back = 0;
	handler[0]->capacity = n_elements * size;
	handler[0]->size = size;
	return RBE_SUCCESS;
}

int
ringbuffer_empty(struct RingBuffer *handler)
{
	if (handler == NULL)
		return RBE_WRONG_ARGS;
	return (handler->front == handler->back
			&& handler->capacity > handler->size);
}

int
ringbuffer_full(struct RingBuffer *handler)
{
	if (handler == NULL)
		return RBE_WRONG_ARGS;
	return handler->capacity == 0
			|| handler->front == rb_advance(handler, handler->back);
}

int
ringbuffer_push(struct RingBuffer *handler, unsigned char *buffer)
{
	if (handler == NULL || buffer == NULL)
		return RBE_WRONG_ARGS;

	if (ringbuffer_full(handler) == 1)
		return RBE_NO_SPACE_OR_DATA;

	memcpy(&handler->data[handler->back], buffer, handler->size);
	handler->back = rb_advance(handler, handler->back);
	return RBE_SUCCESS;
}

int
ringbuffer_top(struct RingBuffer *handler, unsigned char *buffer)
{
	if (handler == NULL || buffer == NULL)
		return RBE_WRONG_ARGS;

	if (ringbuffer_empty(handler) == 1 || handler->capacity == 0)
		return RBE_NO_SPACE_OR_DATA;

	memcpy(buffer, &handler->data[handler->front], handler->size);
	return RBE_SUCCESS;
}

int
ringbuffer_pop(struct RingBuffer *handler)
{
	if (handler == NULL)
		return RBE_WRONG_ARGS;

	if (ringbuffer_empty(handler) == 1 || handler->capacity == 0)
		return RBE_NO_SPACE_OR_DATA;

	handler->front = rb_advance(handler, handler->front);
	return RBE_SUCCESS;
}

void
ringbuffer_destroy(struct RingBuffer **handler)
{
	free(*handler);
	*handler = NULL;
}

int
ringbuffer_resize(struct RingBuffer **handler, unsigned n_elements)
{
	struct RingBuffer *aux;
	struct RingBuffer *h;
	unsigned old_elements;
	unsigned new_capacity;

	if (handler == NULL || *handler == NULL || n_elements == 0)
		return RBE_WRONG_ARGS;

	h = *handler;
	old_elements = h->capacity / h->size;

	if (n_elements <= old_elements)
		return RBE_WRONG_ARGS;

	new_capacity = n_elements * h->size;
	aux = realloc(*handler, sizeof(struct RingBuffer) + new_capacity);

	if (aux == NULL)
		return RBE_NO_MEMORY;

	*handler = aux;
	h = aux;

	if (h->back < h->front)
	{
		memmove(&h->data[h->capacity], &h->data[0], h->back);
		h->back = h->capacity + h->back;
	}

	h->capacity = new_capacity;
	return RBE_SUCCESS;
}
