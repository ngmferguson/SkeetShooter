#include "queue.h"

void init_queue(queue_t *buf) {
  int i;
  buf->head = 0;
  buf->tail = 0;
  for (i = 0; i < QUEUE_SIZE; i++)
     buf->buffer[i] = 0;
}

int enqueue (queue_t *buf, int data) {
  if (((buf->tail + 1) % QUEUE_SIZE) == buf->head)
    return 0;
  else{
    buf->buffer[buf->tail] = data;
    buf->tail = (buf->tail + 1) % QUEUE_SIZE;
    return 1;
  }
}

int dequeue (queue_t *buf) {
  int rtn;
  if (queue_empty(buf)) //buffer is empty
    return 0;
  rtn = buf->buffer[buf->head];
  buf->head = (buf->head+1) % QUEUE_SIZE;
  return rtn;
  
}

int queue_empty(queue_t *buf) {
  return (buf->tail == buf->head);
}


/* queue.c ends here */
