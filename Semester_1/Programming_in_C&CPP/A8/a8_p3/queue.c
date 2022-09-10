/*
CH-230-A
a8_p3.c
Faraz Ahmad
fahmad@jacobs.university.de
 */
/**
 * @file queue.c
 */
#include "queue.h"

void initialize_queue(Queue *pq)
{
    pq->front = pq->rear = NULL;
    pq->items = 0;
}
Node *newNode(Item k)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->item = k;
    temp->next = NULL;
    return temp;
}
int queue_is_full(const Queue *pq)
{
    return pq->items == MAXQUEUE;
}

int queue_is_empty(const Queue *pq)
{
    return pq->items == 0;
}

int queue_item_count(const Queue *pq)
{
    return pq->items;
}

int enqueue(Item item, Queue *pq)
{
    Node *temp = newNode(item);

    // If queue is empty, then new node is front and rear both
    if (pq->rear == NULL)
    {
        pq->items++;
        pq->front = pq->rear = temp;
        return 1;
    }

    // Add the new node at the end of queue and change rear
    pq->items++;
    pq->rear->next = temp;
    pq->rear = temp;
    return 1;
}

int dequeue(Item *pitem, Queue *pq)
{
    // If queue is empty, return NULL.
    if (pq->front == NULL)
    {
        return 0;
    }

    // Store previous front and move front one node ahead
    Node *temp = pq->front;

    pq->front = pq->front->next;

    // If front becomes NULL, then change rear also as NULL
    if (pq->front == NULL)
    {
        pq->rear = NULL;
    }
    int ret = temp->item;
    free(temp);
    pq->items--;
    return ret;
}

void empty_queue(Queue *pq)
{
    Item dummy;
    while (!queue_is_empty(pq))
    {
        dequeue(&dummy, pq);
    }
}
void printq(Queue *pq)
{
    int n = pq->items;
    Queue temp = *pq;
    printf("content of the queue: ");
    while (n > 0)
    {
        printf("%d ", temp.front->item);
        temp.front = temp.front->next;
        n--;
    }
    printf("\n");
}