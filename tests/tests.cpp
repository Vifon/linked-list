// File: tests.cpp
#include "tests.hpp"
#include <list>

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
    listPushBack(l, 5);
    listPushBack(l, 33);
    listPushBack(l, 9);
    listPushBack(l, 5);
    listPushBack(l, 99);

    List a = listBegin(l);
    NEXT(a); NEXT(a); NEXT(a);
    CPPUNIT_ASSERT_EQUAL(l->n->n->n->n, a);
    CPPUNIT_ASSERT_EQUAL(5, listVal(a));
    PREV(a);
    CPPUNIT_ASSERT_EQUAL(l->n->n->n, a);
}

void ListTest::pushBack()
{
    std::list<int> sl;

    sl.push_back(5);
    listPushBack(l, 5);
    sl.push_back(33);
    listPushBack(l, 33);
    sl.push_back(9);
    listPushBack(l, 9);
    sl.push_back(5);
    listPushBack(l, 5);
    sl.push_back(99);
    listPushBack(l, 99);

    std::list<int>::iterator it1;
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
    std::list<int> sl;

    sl.push_front(5);
    listPushFront(l, 5);
    sl.push_front(33);
    listPushFront(l, 33);
    sl.push_front(9);
    listPushFront(l, 9);
    sl.push_front(5);
    listPushFront(l, 5);
    sl.push_front(99);
    listPushFront(l, 99);

    std::list<int>::iterator it1;
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
void ListTest::pushSort()
{
    std::list<int> sl;

    sl.push_back(5);
    listPushSort(l, 5, cmp);
    sl.push_back(33);
    listPushSort(l, 33, cmp);
    sl.push_back(9);
    listPushSort(l, 9, cmp);
    sl.push_back(5);
    listPushSort(l, 5, cmp);
    sl.push_back(99);
    listPushSort(l, 99, cmp);

    sl.sort();

    std::list<int>::iterator it1;
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

void ListTest::removeByNumber()
{
    pushBack();

    CPPUNIT_ASSERT(listRemoveN(l, 3));

    List p = listBegin(l);
    CPPUNIT_ASSERT_EQUAL(5, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(33, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(9, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(99, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);

    CPPUNIT_ASSERT(listRemoveN(l, 0));

    CPPUNIT_ASSERT(l->n->p == NULL);
    CPPUNIT_ASSERT_EQUAL(33, l->n->v);
}

void ListTest::removeByValue()
{
    pushBack();

    CPPUNIT_ASSERT(listRemoveVal(l, 33));

    List p = listBegin(l);
    CPPUNIT_ASSERT_EQUAL(5, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(9, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(5, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(99, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);

    CPPUNIT_ASSERT(listRemoveVal(l, 5));

    CPPUNIT_ASSERT(l->n->p == NULL);
    CPPUNIT_ASSERT_EQUAL(9, l->n->v);
}

void ListTest::removeByNonExistentValue()
{
    pushBack();

    CPPUNIT_ASSERT(listRemoveVal(l, 17) == false);

    List p = listBegin(l);
    CPPUNIT_ASSERT_EQUAL(5, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(33, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(9, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(5, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(99, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);
}

void ListTest::getNthElement()
{
    listPushBack(l, 5);
    listPushBack(l, 33);
    listPushBack(l, 9);
    listPushBack(l, 5);
    listPushBack(l, 99);

    CPPUNIT_ASSERT_EQUAL(l->n->n->n, listGet(l, 2));
}

void ListTest::length()
{
    listPushBack(l, 5);
    listPushBack(l, 33);
    listPushBack(l, 9);
    listPushBack(l, 5);
    listPushBack(l, 99);

    CPPUNIT_ASSERT_EQUAL(5, listLength(l));
}

void ListTest::pop()
{
    listPushBack(l, 5);
    listPushBack(l, 33);
    listPushBack(l, 9);
    listPushBack(l, 5);
    listPushBack(l, 99);

    listPopBack(l);
    CPPUNIT_ASSERT(l->n->n->n->n->n == NULL);
    CPPUNIT_ASSERT_EQUAL(5, l->n->n->n->n->v);
    listPopFront(l);
    CPPUNIT_ASSERT_EQUAL(33, l->n->v);
    CPPUNIT_ASSERT(l->n->n->n->n == NULL);
    CPPUNIT_ASSERT_EQUAL(5, l->n->n->n->v);
    listPopBack(l);
    CPPUNIT_ASSERT(l->n->n->n == NULL);
    CPPUNIT_ASSERT_EQUAL(9, l->n->n->v);
    listPopBack(l);
    CPPUNIT_ASSERT(l->n->n == NULL);
    CPPUNIT_ASSERT_EQUAL(33, l->n->v);
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

void ListTest::copy()
{
    listPushBack(l, 5);
    listPushBack(l, 33);
    listPushBack(l, 9);
    listPushBack(l, 5);
    listPushBack(l, 99);

    List c = listCopy(l);
    CPPUNIT_ASSERT(l != NULL);
    CPPUNIT_ASSERT(c != NULL);
    listFree(l);
    CPPUNIT_ASSERT(l == NULL);
    CPPUNIT_ASSERT(c != NULL);

    List p = listBegin(c);
    CPPUNIT_ASSERT_EQUAL(5, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(33, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(9, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(5, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(99, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);
    listFree(c);
}
