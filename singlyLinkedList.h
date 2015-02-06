
#ifndef __SinglyLinkedList_H_
#define __SinglyLinkedList_H_

struct NodeEntry {
   void *data;
   struct NodeEntry *next;
};

typedef struct NodeEntry NodeEntry;

struct LinkedList {
   NodeEntry *head;
   NodeEntry *tail;
   int count;
   int (*cmp)(const void *, const int);
};

typedef struct LinkedList LinkedList;

int InitLL(LinkedList **l, int (*cmp)(const void *, const int));
int DestroyLL(LinkedList **l);

int LLClear(LinkedList *l);
void *LLGet(LinkedList *l, int idx);
int LLInsertTail(LinkedList *l, void *data);
int LLIndexOf(LinkedList *l, int data);
int LLIsEmpty(LinkedList *l);
void *LLRemove(LinkedList *l, int idx);
void *LLRemoveHead(LinkedList *l);
void *LLRemoveTail(LinkedList *l);
int LLSize(LinkedList *l);

int comparator(const void *data1, const int data2);

#endif // __SinglyLinkedList_H_
