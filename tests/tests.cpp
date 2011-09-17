#include "tests.hpp"
#include <list>

CPPUNIT_TEST_SUITE_REGISTRATION(ListTest);

void ListTest::setUp()
{
    for (int i = 0; i < 1; ++i)
    {
        l[i] = listInit();
    }
}

void ListTest::tearDown()
{
    for (int i = 0; i < 1; ++i)
    {
        listFree(l[i]);
    }
}

void ListTest::initialization()
{
    for (int i = 0; i < 1; ++i)
    {
        CPPUNIT_ASSERT(l[i] != NULL);
        CPPUNIT_ASSERT(l[i]->n == NULL);
    }
}

void ListTest::movement()
{
    listPushBack(l[0], 5);
    listPushBack(l[0], 33);
    listPushBack(l[0], 9);
    listPushBack(l[0], 5);
    listPushBack(l[0], 99);

    List a = listBegin(l[0]);
    NEXT(a); NEXT(a); NEXT(a);
    CPPUNIT_ASSERT_EQUAL(l[0]->n->n->n->n, a);
    CPPUNIT_ASSERT_EQUAL(5, listVal(a));
    PREV(a);
    CPPUNIT_ASSERT_EQUAL(l[0]->n->n->n, a);
}

void ListTest::addingNewElements()
{
    std::list<int> sl;

    sl.push_back(5);
    listPushBack(l[0], 5);
    sl.push_back(33);
    listPushBack(l[0], 33);
    sl.push_back(9);
    listPushBack(l[0], 9);
    sl.push_back(5);
    listPushBack(l[0], 5);
    sl.push_back(99);
    listPushBack(l[0], 99);

    std::list<int>::iterator it1;
    List it2;

    for (it1 = sl.begin(), it2 = listBegin(l[0]);
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
void ListTest::addingNewSortedElements()
{
    std::list<int> sl;

    sl.push_back(5);
    listPushBackSort(l[0], 5, cmp);
    sl.push_back(33);
    listPushBackSort(l[0], 33, cmp);
    sl.push_back(9);
    listPushBackSort(l[0], 9, cmp);
    sl.push_back(5);
    listPushBackSort(l[0], 5, cmp);
    sl.push_back(99);
    listPushBackSort(l[0], 99, cmp);

    sl.sort();

    std::list<int>::iterator it1;
    List it2;

    for (it1 = sl.begin(), it2 = listBegin(l[0]);
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
    addingNewElements();

    listRemoveN(l[0], 3);

    List p = listBegin(l[0]);
    CPPUNIT_ASSERT_EQUAL(5, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(33, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(9, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(99, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);
}

void ListTest::removeByValue()
{
    addingNewElements();

    listRemoveVal(l[0], 33);

    List p = listBegin(l[0]);
    CPPUNIT_ASSERT_EQUAL(5, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(9, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(5, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT_EQUAL(99, listVal(p));
    NEXT(p);
    CPPUNIT_ASSERT(p == NULL);
}

void ListTest::removeByNonExistentValue()
{
    addingNewElements();

    CPPUNIT_ASSERT(listRemoveVal(l[0], 17) == false);

    List p = listBegin(l[0]);
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
    listPushBack(l[0], 5);
    listPushBack(l[0], 33);
    listPushBack(l[0], 9);
    listPushBack(l[0], 5);
    listPushBack(l[0], 99);

    CPPUNIT_ASSERT_EQUAL(l[0]->n->n->n, listGet(l[0], 2));
}
