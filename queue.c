/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /*No effect if q is NULL*/
    if (q == NULL)
        return;
    /* How about freeing the list elements and the strings? */
    list_ele_t *delete;
    while (q->head) {
        delete = q->head;
        q->head = q->head->next;
        free(delete->value);
        free(delete);
        // q->head = q->head->next;
    }

    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (q == NULL)
        return false;

    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    char *add = malloc((strlen(s) + 1) * sizeof(char));

    /* What if either call to malloc returns NULL? */
    if (newh == NULL || add == NULL) {
        free(newh);
        free(add);
        return false;
    }
    strcpy(add, s);
    newh->value = add;
    newh->next = q->head;
    q->size = q->size + 1;
    if (q->head == NULL)  // first insert
        q->tail = newh;
    q->head = newh;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Reme mber: It should operate in O(1) time */
    if (q == NULL)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    char *add = malloc((strlen(s) + 1) * sizeof(char));
    if (newh == NULL || add == NULL) {
        free(newh);
        free(add);
        return false;
    }



    strcpy(add, s);
    newh->value = add;
    newh->next = NULL;
    q->size = q->size + 1;
    if (q->tail == NULL) {  // first insert
        q->head = newh;
        q->tail = newh;
    } else {
        q->tail->next = newh;
        q->tail = newh;
    }
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q == NULL || q->size == 0)
        return false;

    if (sp) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
        // strcat(sp,'\0');
    }

    list_ele_t *replace;

    replace = q->head;
    q->head = q->head->next;
    free(replace->value);
    free(replace);
    q->size = q->size - 1;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL || q->size == 0 || q->size == 1)
        return;
    list_ele_t *cur = q->head->next;
    q->head->next = NULL;
    list_ele_t *temp;

    q->tail = q->head;
    while (cur != NULL) {
        temp = cur->next;
        cur->next = q->head;
        q->head = cur;
        cur = temp;
    }
}
