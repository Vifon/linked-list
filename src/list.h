/* File: list.h */
#ifndef _LIST_H_
#define _LIST_H_

 #ifdef __cplusplus
 extern "C"
 {
 #endif


typedef struct list
{
    void*        v;
    int          isRoot;        /* true only in the first one */
    struct list* n;
    struct list* p;
}
    *List;

#define NEXT(A)       (A = A->n)
#define PREV(A)       (A = A->p)
#define listBegin(A) A->n
#define listVal(A, T) *(T*) A->v
#define newListNode() (List) malloc(sizeof(struct list))

List listRbegin    (List root);
List listInit      ();
void listPushBack  (List root, void* val);
void listPushFront (List root, void* val);
void listPushSort  (List root, void* val, int (*compare)(const void*, const void*));
void listAddAfter  (List place, void* val);
void listFree      (List root);
List listGet       (List root, int n);
List listGetVal    (List root, void* val, int (*compare)(const void*, const void*));
void listRemove    (List root, List element);
int  listRemoveN   (List root, int n);
int  listRemoveVal (List root, void* val, int (*compare)(const void*, const void*));
int  listLength    (List root);
int  listIsEmpty   (List root);
void listEmpty     (List root);
int  listPopBack   (List root);
int  listPopFront  (List root);
List listCopy      (List source);
void listForeach   (List root, void (*fun)(void*, void*), void* arg);
int  listSwap      (List root, List place);
void listSort      (List root, int (*cmp)(const void*, const void*));


 #ifdef __cplusplus
 }
 #endif
#endif
