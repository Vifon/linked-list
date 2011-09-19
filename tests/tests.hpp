// File: tests.hpp
#ifndef _TESTS_H_
#define _TESTS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../src/list.h"

class ListTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(ListTest);
    CPPUNIT_TEST(initialization);
    CPPUNIT_TEST(movement);
    CPPUNIT_TEST(pushBack);
    CPPUNIT_TEST(pushFront);
    CPPUNIT_TEST(pushSort);
    CPPUNIT_TEST(getNthElement);
    CPPUNIT_TEST(removeByNumber);
    CPPUNIT_TEST(removeByValue);
    CPPUNIT_TEST(removeByNonExistentValue);
    CPPUNIT_TEST(length);
    CPPUNIT_TEST(pop);
    CPPUNIT_TEST(freeEmpty);
    CPPUNIT_TEST(empty);
    CPPUNIT_TEST(copy);
    CPPUNIT_TEST_SUITE_END();
  public:
    void setUp();
    void tearDown();

  protected:
    void initialization();
    void movement();
    void pushBack();
    void pushFront();
    void pushSort();
    void removeByNumber();
    void removeByValue();
    void removeByNonExistentValue();
    void getNthElement();
    void length();
    void pop();
    void freeEmpty();
    void empty();
    void copy();

  private:
    List l;
};

#endif
