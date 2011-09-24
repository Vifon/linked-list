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
    listPushBack(l, "foo");
    listPushBack(l, "bar");
    listPushBack(l, "baz");
    listPushBack(l, "qux");

    List a = listBegin(l);
    NEXT(a); NEXT(a); NEXT(a);
    CPPUNIT_ASSERT_EQUAL(l->n->n->n->n, a);
    CPPUNIT_ASSERT(!strcmp("qux", listVal(a)));
    PREV(a);
    CPPUNIT_ASSERT_EQUAL(l->n->n->n, a);
}

void ListTest::pushBack()
{
    std::list<T> sl;

    sl.push_back("foo");
    listPushBack(l, "foo");
    sl.push_back("bar");
    listPushBack(l, "bar");
    sl.push_back("baz");
    listPushBack(l, "baz");
    sl.push_back("qux");
    listPushBack(l, "qux");

    std::list<T>::iterator it1;
    List it2;

    for (it1 = sl.begin(), it2 = listBegin(l);
         it1 != sl.end() && it2 != NULL;
         ++it1, NEXT(it2))
    {
        CPPUNIT_ASSERT_EQUAL(*it1, listVal(it2));
    }
    CPPUNIT_ASSERT(it1 == sl.end());
    CPPUNIT_ASSERT(it2 == NULL);
}

void ListTest::pushFront()
{
    std::list<T> sl;

    sl.push_front("foo");
    listPushFront(l, "foo");
    sl.push_front("bar");
    listPushFront(l, "bar");
    sl.push_front("baz");
    listPushFront(l, "baz");
    sl.push_front("qux");
    listPushFront(l, "qux");

    std::list<T>::iterator it1;
    List it2;

    for (it1 = sl.begin(), it2 = listBegin(l);
         it1 != sl.end() && it2 != NULL;
         ++it1, NEXT(it2))
    {
        CPPUNIT_ASSERT_EQUAL(*it1, listVal(it2));
    }
    CPPUNIT_ASSERT(it1 == sl.end());
    CPPUNIT_ASSERT(it2 == NULL);
}

int cmp(int a, int b)
{
    if      (a < b) return -1;
    else if (a > b) return 1;
    else            return 0;
}
int mystrcmp1(const T a, const T b)
{
    int n = strcmp(a, b);
    if      (n < 0) return -1;
    else if (n > 0) return 1;
    else            return 0;
}
bool mystrcmp2(const T a, const T b)
{
    int n = strcmp(a, b);
    if    (n < 0) return true;
    else          return false;
}
void ListTest::pushSort()
{
    std::list<T> sl;

    sl.push_back("foo");
    listPushSort(l, "foo", mystrcmp1);
    sl.push_back("bar");
    listPushSort(l, "bar", mystrcmp1);
    sl.push_back("baz");
    listPushSort(l, "baz", mystrcmp1);
    sl.push_back("qux");
    listPushSort(l, "qux", mystrcmp1);

    sl.sort(mystrcmp2);

    std::list<T>::iterator it1;
    List it2;

    for (it1 = sl.begin(), it2 = listBegin(l);
         it1 != sl.end() && it2 != NULL;
         ++it1, NEXT(it2))
    {
        CPPUNIT_ASSERT(!strcmp(*it1, listVal(it2)));
    }
    CPPUNIT_ASSERT(it1 == sl.end());
    CPPUNIT_ASSERT(it2 == NULL);
}

void ListTest::removeByNumber()
{
    listPushBack(l, "foo");
    listPushBack(l, "bar");
    listPushBack(l, "baz");
    listPushBack(l, "qux");

    CPPUNIT_ASSERT(listRemoveN(l, 2));

    List p = listBegin(l);
    CPPUNIT_ASSERT(!strcmp("foo", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("bar", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);

    CPPUNIT_ASSERT(listRemoveN(l, 0));

    CPPUNIT_ASSERT(l->n->p == NULL);
    CPPUNIT_ASSERT(!strcmp("bar", l->n->v));
}

void ListTest::removeByValue()
{
    listPushBack(l, "foo");
    listPushBack(l, "bar");
    listPushBack(l, "baz");
    listPushBack(l, "qux");

    CPPUNIT_ASSERT(listRemoveVal(l, "bar"));

    List p = listBegin(l);
    CPPUNIT_ASSERT(!strcmp("foo", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("baz", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);

    CPPUNIT_ASSERT(listRemoveVal(l, "foo"));

    CPPUNIT_ASSERT(l->n->p == NULL);
    CPPUNIT_ASSERT(!strcmp("baz", l->n->v));
}

void ListTest::removeByNonExistentValue()
{
    listPushBack(l, "foo");
    listPushBack(l, "bar");
    listPushBack(l, "baz");
    listPushBack(l, "qux");

    CPPUNIT_ASSERT(listRemoveVal(l, "cycki") == false);

    List p = listBegin(l);
    CPPUNIT_ASSERT(!strcmp("foo", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("bar", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("baz", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);
}

void ListTest::getNthElement()
{
    listPushBack(l, "foo");
    listPushBack(l, "bar");
    listPushBack(l, "baz");
    listPushBack(l, "qux");

    CPPUNIT_ASSERT_EQUAL(l->n->n->n, listGet(l, 2));
}

void ListTest::length()
{
    listPushBack(l, "foo");
    listPushBack(l, "bar");
    listPushBack(l, "baz");
    listPushBack(l, "qux");

    CPPUNIT_ASSERT_EQUAL(4, listLength(l));
}

void ListTest::pop()
{
    listPushBack(l, "foo");
    listPushBack(l, "bar");
    listPushBack(l, "baz");
    listPushBack(l, "qux");

    listPopBack(l);
    CPPUNIT_ASSERT(l->n->n->n->n == NULL);
    CPPUNIT_ASSERT(!strcmp("baz", l->n->n->n->v));
    listPopFront(l);
    CPPUNIT_ASSERT(!strcmp("bar", l->n->v));
    CPPUNIT_ASSERT(l->n->n->n == NULL);
    CPPUNIT_ASSERT(!strcmp("baz", l->n->n->v));
    listPopBack(l);
    CPPUNIT_ASSERT(l->n->n == NULL);
    CPPUNIT_ASSERT(!strcmp("bar", l->n->v));
    listPopBack(l);
    CPPUNIT_ASSERT(listIsEmpty(l));
    List c = listCopy(l);

    CPPUNIT_ASSERT(!listPopFront(l));
    CPPUNIT_ASSERT(!listPopBack(c));
    CPPUNIT_ASSERT(listIsEmpty(l));
    CPPUNIT_ASSERT(listIsEmpty(c));
    listFree(c);
}

void ListTest::freeEmpty()
{
    listFree(l);
}

void ListTest::empty()
{
    listPushBack(l, "foo");
    listPushBack(l, "bar");
    listPushBack(l, "baz");
    listPushBack(l, "qux");

    listEmpty(l);
    CPPUNIT_ASSERT(l != NULL);
    CPPUNIT_ASSERT(l->n == NULL);
}

void ListTest::copy()
{
    listPushBack(l, "foo");
    listPushBack(l, "bar");
    listPushBack(l, "baz");
    listPushBack(l, "qux");

    List c = listCopy(l);
    CPPUNIT_ASSERT(l != NULL);
    CPPUNIT_ASSERT(c != NULL);
    listFree(l);
    CPPUNIT_ASSERT(l == NULL);
    CPPUNIT_ASSERT(c != NULL);

    List p = listBegin(c);
    CPPUNIT_ASSERT(!strcmp("foo", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("bar", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("baz", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);
    listFree(c);
}

void ListTest::regex()
{
    listPushBack(l, "foo");
    listPushBack(l, "bar");
    listPushBack(l, "baz");
    listPushBack(l, "qux");

    regex_t regex;
    CPPUNIT_ASSERT(!regcomp(&regex, "^ba.$", 0));
    List match = listGetRegex(l, &regex);
    if (match != NULL)
        listRemove(l, match);


    List p = listBegin(l);

    CPPUNIT_ASSERT(!strcmp("foo", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("baz", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);

    listRemove(l, listGetRegex(l, &regex));

    p = listBegin(l);
    CPPUNIT_ASSERT(!strcmp("foo", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);
}

void ListTest::regexDelete()
{
    listPushBack(l, "foo");
    listPushBack(l, "bar");
    listPushBack(l, "baz");
    listPushBack(l, "qux");

    regex_t regex;
    CPPUNIT_ASSERT(!regcomp(&regex, "^ba.$", 0));
    listRemoveRegexAll(l, &regex);


    List p = listBegin(l);

    CPPUNIT_ASSERT(!strcmp("foo", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(!strcmp("qux", listVal(p)));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);


    CPPUNIT_ASSERT(!regcomp(&regex, "^f.*$", 0));
    listRemoveRegexAll(l, &regex);

    p = listRbegin(l);
    CPPUNIT_ASSERT(!strcmp("qux", listVal(p)));
    PREV(p);
    CPPUNIT_ASSERT(p == NULL);


    CPPUNIT_ASSERT(!regcomp(&regex, "x", 0));
    listRemoveRegexAll(l, &regex);

    p = listRbegin(l);
    CPPUNIT_ASSERT(p == NULL);
}
