/*
 * Singly Linked List Data Structure implemented in C
 *
*/

#include <stdlib.h>
#include <assert.h>

#include "singlyLinkedList.h"
#include "libTinyFS.h"

int InitLL(LinkedList **l, int (*cmp)(const void *, const int))
{
   assert(l);
   assert(cmp);

   *l = malloc(sizeof(LinkedList));
   if (!*l)
      return -1;

   (*l)->head = NULL;
   (*l)->tail = NULL;
   (*l)->count = 0;
   (*l)->cmp = cmp;

   return 0;
}

int DestroyLL(LinkedList **l)
{
   NodeEntry *cur;
   assert(l);
   assert(*l);

   while ((*l)->head) {
      cur = (*l)->head;
      (*l)->head = (*l)->head->next;
      free(cur);
      cur = NULL;
   }

   free(*l);
   *l = NULL;

   return 0;
}

int LLClear(LinkedList *l)
{
   NodeEntry *cur;
   assert(l);

   while (l->head) {
      cur = l->head;
      l->head = l->head->next;
      free(cur);
      cur = NULL;
   }

   l->head = NULL;
   l->tail = NULL;
   l->count = 0;

   return 0;
}

void *LLGet(LinkedList *l, int idx)
{
   int i = 0;
   NodeEntry *cur;
   void *ret = NULL;
   assert(l);
   assert(idx >= 0);

   cur = l->head;

   while (cur && i < idx) {
      cur = cur->next;
      i++;
   }

   if (cur)
      ret = cur->data;

   return ret;
}

int LLInsertTail(LinkedList *l, void *data)
{
   NodeEntry *newNode = NULL;
   assert(l);
   assert(data);

   newNode = malloc(sizeof(NodeEntry));
   if (!newNode)
      return -1;

   newNode->data = data;
   newNode->next = NULL;
   if (l->tail)
      l->tail->next = newNode;
   if (l->count == 0)
      l->head = newNode;
   l->tail = newNode;

   l->count++;

   return 0;
}

int LLIndexOf(LinkedList *l, int data)
{
   int idx = 0;
   NodeEntry *cur;
   assert(l);
   assert(data);

   cur = l->head;
   while (cur) {
      if (l->cmp(cur->data, data) == 0)
         return idx;
      cur = cur->next;
      idx++;
   }

   return -1;
}

int LLIsEmpty(LinkedList *l)
{
   assert(l);

   return l->count == 0;
}

void *LLRemove(LinkedList *l, int idx)
{
   int i = 0;
   void *ret = NULL;
   NodeEntry *cur, *prev = NULL;
   assert(l);
   assert(idx >= 0);

   if (idx == 0)
      return LLRemoveHead(l);
   if (idx == l->count)
      return LLRemoveTail(l);
   if (idx > l->count)
      return ret;

   cur = l->head;
   while (cur && i <= (idx - 1)) {
      prev = cur;
      cur = cur->next;
      i++;
   }

   ret = cur->data;
   prev->next = cur->next;
   free(cur);
   cur = NULL;
   l->count--;

   return ret;
}

void *LLRemoveHead(LinkedList *l)
{
   void *ret = NULL;
   NodeEntry *cur;
   assert(l);

   if (l->head) {
      ret = l->head->data;
      cur = l->head;
      l->head = l->head->next;
      l->count--;
      free(cur);
      cur = NULL;
   }

   return ret;
}

void *LLRemoveTail(LinkedList *l)
{
   void *ret = NULL;
   NodeEntry *cur, *prev = NULL;
   assert(l);

   cur = l->head;
   while (cur && cur->next) {
      prev = cur;
      cur = cur->next;
   }

   if (l->tail) {
      ret = l->tail->data;
      cur = l->tail;
      l->tail = prev;
      l->tail->next = NULL;
      l->count--;
      free(cur);
      cur = NULL;
   }

   return ret;
}

int LLSize(LinkedList *l)
{
   assert(l);

   return l->count;
}

int comparator(const void *data1, const int data2)
{
   if (((FileTableEntry *)data1)->fd == data2)
      return 0;
   else
      return 1;
}
