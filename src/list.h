/* File: list.h */
#ifndef _LIST_H_
#define _LIST_H_

 #ifdef __cplusplus
 extern "C"
 {
 #endif


/* MODIFY ME */
typedef char* T;
/* MODIFY ME */

typedef struct list
{
    T            v;
    int          isRoot;        /* true only in the first one */
    struct list* n;
    struct list* p;
}
    *List;

#define NEXT(A) A = A->n
#define PREV(A) A = A->p
#define listVal(A) A->v
#define listBegin(A) A->n
#define newListNode() (List) malloc(sizeof(struct list))
#define listFree(A) listFreeReal(&A)

List listRbegin(List root);
List listInit();
void listPushBack(List root, T val);
void listPushFront(List root, T val);
void listPushSort(List root, T val, int (*compare)(const T, const T));
void listAddAfter(List place, T val);
void listFreeReal(List* root);
List listGet(List root, int n);
void listRemove(List root, List element);
int  listRemoveN(List root, int n);
int  listRemoveVal(List root, T val);
int  listRemoveValCustom(List root, T val, int (*compare)(const T, const T));
int  listLength(List root);
int  listIsEmpty(List root);
void listEmpty(List root);
int  listPopBack(List root);
int  listPopFront(List root);
List listCopy(List source);
#ifdef _REGEX_H
List listGetRegex(List root, regex_t* re)
{
    List element = listBegin(root);
    for (; element != NULL && element->v != NULL && regexec(re, element->v, 0, NULL, 0); NEXT(element));
    return element;
}
void listRemoveRegexAll(List root, regex_t* re)
{
    List element = listBegin(root);
    while (element != NULL)
    {
        element = listBegin(root);
        for (; element != NULL && element->v != NULL && regexec(re, element->v, 0, NULL, 0); NEXT(element));
        if (element != NULL)
            listRemove(root, element);
    }
}
#endif


 #ifdef __cplusplus
 }
 #endif
#endif
