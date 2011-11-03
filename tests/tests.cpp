// File: tests.cpp
#include "tests.hpp"
#include <list>
#include <string.h>

CPPUNIT_TEST_SUITE_REGISTRATION(ListTest);

void ListTest::setUp()
{
    l = listInit();
}

void ListTest::tearDown()
{
    listFree(l);
}

void ListTest::initialization()
{
    CPPUNIT_ASSERT(l != NULL);
    CPPUNIT_ASSERT(l->n == NULL);
}

void ListTest::movement()
{
    listPushBack(l, (void*) "foo");
    listPushBack(l, (void*) "bar");
    listPushBack(l, (void*) "baz");
    listPushBack(l, (void*) "qux");

    List a = listBegin(l);
    NEXT(a); NEXT(a); NEXT(a);
    CPPUNIT_ASSERT_EQUAL(l->n->n->n->n, a);
    CPPUNIT_ASSERT(!strcmp("qux", &listVal(a, char)));
    PREV(a);
    CPPUNIT_ASSERT_EQUAL(l->n->n->n, a);
}

void ListTest::stringPushBack()
{
    std::list<char*> sl;

    sl.push_back("foo");
    listPushBack(l, (void*) "foo");
    sl.push_back("bar");
    listPushBack(l, (void*) "bar");
    sl.push_back("baz");
    listPushBack(l, (void*) "baz");
    sl.push_back("qux");
    listPushBack(l, (void*) "qux");

    std::list<char*>::iterator it1;
    List it2;

    for (it1 = sl.begin(), it2 = listBegin(l);
         it1 != sl.end() && it2 != NULL;
         ++it1, NEXT(it2))
    {
        CPPUNIT_ASSERT_EQUAL(*it1, &listVal(it2, char));
    }
    CPPUNIT_ASSERT(it1 == sl.end());
    CPPUNIT_ASSERT(it2 == NULL);
}

void ListTest::stringPushFront()
{
    std::list<char*> sl;

    sl.push_front("foo");
    listPushFront(l, (void*) "foo");
    sl.push_front("bar");
    listPushFront(l, (void*) "bar");
    sl.push_front("baz");
    listPushFront(l, (void*) "baz");
    sl.push_front("qux");
    listPushFront(l, (void*) "qux");

    std::list<char*>::iterator it1;
    List it2;

    for (it1 = sl.begin(), it2 = listBegin(l);
         it1 != sl.end() && it2 != NULL;
         ++it1, NEXT(it2))
    {
        CPPUNIT_ASSERT_EQUAL(*it1, &listVal(it2, char));
    }
    CPPUNIT_ASSERT(it1 == sl.end());
    CPPUNIT_ASSERT(it2 == NULL);
}

int cmp(const void* a, const void* b)
{
    if      (*(int*) a < *(int*) b) return -1;
    else if (*(int*) a > *(int*) b) return 1;
    else            return 0;
}
void freeint(void* a, void*)
{
    delete (int*) a;
}
void ListTest::intPushSort()
{
    std::list<int> sl;

    sl.push_back(5);
    listPushSort(l, (void*) new int(5), cmp);
    sl.push_back(33);
    listPushSort(l, (void*) new int(33), cmp);
    sl.push_back(8);
    listPushSort(l, (void*) new int(8), cmp);
    sl.push_back(1);
    listPushSort(l, (void*) new int(1), cmp);
    sl.push_back(17);
    listPushSort(l, (void*) new int(17), cmp);
    sl.push_back(102);
    listPushSort(l, (void*) new int(102), cmp);
    sl.push_back(38);
    listPushSort(l, (void*) new int(38), cmp);

    sl.sort();

    std::list<int>::iterator it1;
    List it2;

    for (it1 = sl.begin(), it2 = listBegin(l);
         it1 != sl.end() && it2 != NULL;
         ++it1, NEXT(it2))
    {
        CPPUNIT_ASSERT(*it1 == listVal(it2, int));
    }
    CPPUNIT_ASSERT(it1 == sl.end());
    CPPUNIT_ASSERT(it2 == NULL);

    listForeach(l, freeint, NULL);
}

int mystrcmp1(const void* a, const void* b)
{
    int n = strcmp((char*) a, (char*) b);
    if      (n < 0) return -1;
    else if (n > 0) return 1;
    else            return 0;
}
bool mystrcmp2(const void* a, const void* b)
{
    int n = strcmp((char*) a, (char*) b);
    if    (n < 0) return true;
    else          return false;
}
void ListTest::stringPushSort()
{
    std::list<char*> sl;

    sl.push_back("foo");
    listPushSort(l, (void*) "foo", mystrcmp1);
    sl.push_back("bar");
    listPushSort(l, (void*) "bar", mystrcmp1);
    sl.push_back("baz");
    listPushSort(l, (void*) "baz", mystrcmp1);
    sl.push_back("qux");
    listPushSort(l, (void*) "qux", mystrcmp1);

    sl.sort(mystrcmp2);

    std::list<char*>::iterator it1;
    List it2;

    for (it1 = sl.begin(), it2 = listBegin(l);
         it1 != sl.end() && it2 != NULL;
         ++it1, NEXT(it2))
    {
        CPPUNIT_ASSERT(!strcmp(*it1, &listVal(it2, char)));
    }
    CPPUNIT_ASSERT(it1 == sl.end());
    CPPUNIT_ASSERT(it2 == NULL);
}

void ListTest::stringRemoveByNumber()
{
    listPushBack(l, (void*) "foo");
    listPushBack(l, (void*) "bar");
    listPushBack(l, (void*) "baz");
    listPushBack(l, (void*) "qux");

    CPPUNIT_ASSERT(listRemoveN(l, 2));

    List p = listBegin(l);
    CPPUNIT_ASSERT(!strcmp("foo", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("bar", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);

    CPPUNIT_ASSERT(listRemoveN(l, 0));

    CPPUNIT_ASSERT(l->n->p == NULL);
    CPPUNIT_ASSERT(!strcmp("bar", (char*) l->n->v));
}

void ListTest::stringRemoveByValue()
{
    listPushBack(l, (void*) "foo");
    listPushBack(l, (void*) "bar");
    listPushBack(l, (void*) "baz");
    listPushBack(l, (void*) "qux");

    CPPUNIT_ASSERT(listRemoveVal(l, (void*) "bar", mystrcmp1));

    List p = listBegin(l);
    CPPUNIT_ASSERT(!strcmp("foo", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("baz", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);

    CPPUNIT_ASSERT(listRemoveVal(l, (void*) "foo", mystrcmp1));

    CPPUNIT_ASSERT(l->n->p == NULL);
    CPPUNIT_ASSERT(!strcmp("baz", (char*) l->n->v));
}

void ListTest::stringRemoveByNonExistentValue()
{
    listPushBack(l, (void*) "foo");
    listPushBack(l, (void*) "bar");
    listPushBack(l, (void*) "baz");
    listPushBack(l, (void*) "qux");

    CPPUNIT_ASSERT(listRemoveVal(l, (void*) "cycki", mystrcmp1) == false);

    List p = listBegin(l);
    CPPUNIT_ASSERT(!strcmp("foo", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("bar", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("baz", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);
}

void ListTest::stringGetNthElement()
{
    listPushBack(l, (void*) "foo");
    listPushBack(l, (void*) "bar");
    listPushBack(l, (void*) "baz");
    listPushBack(l, (void*) "qux");

    CPPUNIT_ASSERT_EQUAL(l->n->n->n, listGet(l, 2));
}

void ListTest::stringLength()
{
    listPushBack(l, (void*) "foo");
    listPushBack(l, (void*) "bar");
    listPushBack(l, (void*) "baz");
    listPushBack(l, (void*) "qux");

    CPPUNIT_ASSERT_EQUAL(4, listLength(l));
}

void ListTest::stringPop()
{
    listPushBack(l, (void*) "foo");
    listPushBack(l, (void*) "bar");
    listPushBack(l, (void*) "baz");
    listPushBack(l, (void*) "qux");

    listPopBack(l);
    CPPUNIT_ASSERT(l->n->n->n->n == NULL);
    CPPUNIT_ASSERT(!strcmp("baz", (char*) l->n->n->n->v));
    listPopFront(l);
    CPPUNIT_ASSERT(!strcmp("bar", (char*) l->n->v));
    CPPUNIT_ASSERT(l->n->n->n == NULL);
    CPPUNIT_ASSERT(!strcmp("baz", (char*) l->n->n->v));
    listPopBack(l);
    CPPUNIT_ASSERT(l->n->n == NULL);
    CPPUNIT_ASSERT(!strcmp("bar", (char*) l->n->v));
    listPopBack(l);
    CPPUNIT_ASSERT(listIsEmpty(l));
    List c = listCopy(l);

    CPPUNIT_ASSERT(!listPopFront(l));
    CPPUNIT_ASSERT(!listPopBack(c));
    CPPUNIT_ASSERT(listIsEmpty(l));
    CPPUNIT_ASSERT(listIsEmpty(c));
    listFree(c);
}

void ListTest::stringFreeEmpty()
{
    listFree(l);
    l = NULL;
}

void ListTest::stringEmpty()
{
    listPushBack(l, (void*) "foo");
    listPushBack(l, (void*) "bar");
    listPushBack(l, (void*) "baz");
    listPushBack(l, (void*) "qux");

    listEmpty(l);
    CPPUNIT_ASSERT(l != NULL);
    CPPUNIT_ASSERT(l->n == NULL);
}

void ListTest::stringCopy()
{
    listPushBack(l, (void*) "foo");
    listPushBack(l, (void*) "bar");
    listPushBack(l, (void*) "baz");
    listPushBack(l, (void*) "qux");

    List c = listCopy(l);
    CPPUNIT_ASSERT(l != NULL);
    CPPUNIT_ASSERT(c != NULL);
    listFree(l);
    l = NULL;
    CPPUNIT_ASSERT(l == NULL);
    CPPUNIT_ASSERT(c != NULL);

    List p = listBegin(c);
    CPPUNIT_ASSERT(!strcmp("foo", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("bar", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("baz", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);
    listFree(c);
}

void divide2(void* a, void* b)
{
    *(int*) a = *(int*) a / (long) b ;
}
void ListTest::foreach()
{
    int a = 8;
    int b = 18;
    int c = 106;
    int d = 200;

    listPushBack(l, (void*) &a);
    listPushBack(l, (void*) &b);
    listPushBack(l, (void*) &c);
    listPushBack(l, (void*) &d);

    listForeach(l, divide2, (void*) 2);

    List p = listBegin(l);
    CPPUNIT_ASSERT_EQUAL(4, listVal(p, int));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(9, listVal(p, int));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(53, listVal(p, int));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(100, listVal(p, int));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);

}

void ListTest::swap()
{
    int a = 8;
    int b = 18;
    int c = 106;
    int d = 200;

    listPushBack(l, (void*) &a);
    listPushBack(l, (void*) &b);
    listPushBack(l, (void*) &c);
    listPushBack(l, (void*) &d);

    List cp = listCopy(l);
    List ptr = listBegin(l);
    NEXT(ptr);
    listSwap(l, ptr);
    ptr = listBegin(l);
    NEXT(ptr);
    CPPUNIT_ASSERT_EQUAL(cp->n->v          , ptr->p->v);
    CPPUNIT_ASSERT_EQUAL(cp->n->n->n->v    , ptr->v);
    CPPUNIT_ASSERT_EQUAL(cp->n->n->v       , ptr->n->n->p->v);
    CPPUNIT_ASSERT_EQUAL(ptr->v            , ptr->n->p->v);
    listFree(cp);
}

void ListTest::swapLast()
{
    int a = 8;
    int b = 18;
    int c = 106;
    int d = 200;

    listPushBack(l, (void*) &a);
    listPushBack(l, (void*) &b);
    listPushBack(l, (void*) &c);
    listPushBack(l, (void*) &d);

    List cp = listCopy(l);
    List ptr = listRbegin(l);
    listSwap(l, ptr);
    ptr = listBegin(l);
    NEXT(ptr); NEXT(ptr);
    CPPUNIT_ASSERT_EQUAL(cp->n->n->n->v    , ptr->v);
    CPPUNIT_ASSERT_EQUAL(cp->n->n->n->n->v , ptr->n->v);
    CPPUNIT_ASSERT(ptr->n->n == NULL);
    listFree(cp);
}

void ListTest::swapFirst()
{
    int a = 8;
    int b = 18;
    int c = 106;
    int d = 200;

    listPushBack(l, (void*) &a);
    listPushBack(l, (void*) &b);
    listPushBack(l, (void*) &c);
    listPushBack(l, (void*) &d);

    List cp = listCopy(l);
    List ptr = listBegin(l);
    listSwap(l, ptr);
    ptr = listBegin(l);
    CPPUNIT_ASSERT_EQUAL(cp->n->v       , ptr->n->v);
    CPPUNIT_ASSERT_EQUAL(cp->n->n->v    , ptr->v);
    CPPUNIT_ASSERT_EQUAL(cp->n->n->n->v , ptr->n->n->v);
    CPPUNIT_ASSERT(ptr->p == NULL);
    listFree(cp);
}

void ListTest::swapFail()
{
    int a = 8;

    listPushBack(l, (void*) &a);

    List cp = listCopy(l);
    List ptr = listBegin(l);
    CPPUNIT_ASSERT(!listSwap(l, ptr));
    ptr = listBegin(l);
    CPPUNIT_ASSERT_EQUAL(cp->n->v, ptr->v);
    CPPUNIT_ASSERT(ptr->p == NULL);
    CPPUNIT_ASSERT(ptr->n == NULL);
    listFree(cp);
}

void ListTest::sort()
{
    int a = 80;
    int b = 18;
    int c = 306;
    int d = 20;

    listPushBack(l, (void*) &a);
    listPushBack(l, (void*) &b);
    listPushBack(l, (void*) &c);
    listPushBack(l, (void*) &d);

    listSort(l, cmp);

    List p = listBegin(l);
    CPPUNIT_ASSERT_EQUAL(18, listVal(p, int));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(20, listVal(p, int));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(80, listVal(p, int));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(306, listVal(p, int));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);
}

#ifdef _REGEX_H
int regexMatch(const void* a, const void* re)
{
    return regexec((regex_t*) re, (char*) a, 0, NULL, 0);
}
void ListTest::regex()
{
    listPushBack(l, (void*) "foo");
    listPushBack(l, (void*) "bar");
    listPushBack(l, (void*) "baz");
    listPushBack(l, (void*) "qux");

    regex_t regex;
    CPPUNIT_ASSERT(!regcomp(&regex, "^ba.$", 0));
    List match = listGetVal(l, (void*) &regex, regexMatch);
    if (match != NULL)
        listRemove(l, match);


    List p = listBegin(l);

    CPPUNIT_ASSERT(!strcmp("foo", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("baz", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);

    listRemove(l, listGetVal(l, (void*) &regex, regexMatch));

    p = listBegin(l);
    CPPUNIT_ASSERT(!strcmp("foo", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);
    regfree(&regex);
}

void ListTest::regexDelete()
{
    listPushBack(l, (void*) "foo");
    listPushBack(l, (void*) "bar");
    listPushBack(l, (void*) "baz");
    listPushBack(l, (void*) "qux");

    regex_t regex;
    List match;
    CPPUNIT_ASSERT(!regcomp(&regex, "^ba.$", 0));
    while((match = listGetVal(l, (void*) &regex, regexMatch)) != NULL)
        listRemove(l, match);


    List p = listBegin(l);

    CPPUNIT_ASSERT(!strcmp("foo", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", &listVal(p, char)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);

    regfree(&regex);

    CPPUNIT_ASSERT(!regcomp(&regex, "^f.*$", 0));
    while((match = listGetVal(l, (void*) &regex, regexMatch)) != NULL)
        listRemove(l, match);

    p = listRbegin(l);
    CPPUNIT_ASSERT(!strcmp("qux", &listVal(p, char)));
    PREV(p);
    CPPUNIT_ASSERT(p == NULL);

    regfree(&regex);

    CPPUNIT_ASSERT(!regcomp(&regex, "x", 0));
    while((match = listGetVal(l, (void*) &regex, regexMatch)) != NULL)
        listRemove(l, match);

    p = listRbegin(l);
    CPPUNIT_ASSERT(p == NULL);
    regfree(&regex);
}
#endif
