// File: tests.hpp
#ifndef _TESTS_H_
#define _TESTS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <regex.h>
#include "../src/list.h"

class ListTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(ListTest);
    CPPUNIT_TEST(initialization);
    CPPUNIT_TEST(movement);
    CPPUNIT_TEST(stringPushBack);
    CPPUNIT_TEST(stringPushFront);
    CPPUNIT_TEST(intPushSort);
    CPPUNIT_TEST(stringPushSort);
    CPPUNIT_TEST(stringGetNthElement);
    CPPUNIT_TEST(stringRemoveByNumber);
    CPPUNIT_TEST(stringRemoveByValue);
    CPPUNIT_TEST(stringRemoveByNonExistentValue);
    CPPUNIT_TEST(stringLength);
    CPPUNIT_TEST(stringPop);
    CPPUNIT_TEST(stringFreeEmpty);
    CPPUNIT_TEST(stringEmpty);
    CPPUNIT_TEST(stringCopy);
    CPPUNIT_TEST(foreach);
    CPPUNIT_TEST(swap);
    CPPUNIT_TEST(swapLast);
    CPPUNIT_TEST(swapFirst);
    CPPUNIT_TEST(swapFail);
    CPPUNIT_TEST(sort);
#ifdef _REGEX_H
    CPPUNIT_TEST(regex);
    CPPUNIT_TEST(regexDelete);
#endif
    CPPUNIT_TEST_SUITE_END();
  public:
    void setUp();
    void tearDown();

  protected:
    void initialization();
    void movement();
    void stringPushBack();
    void stringPushFront();
    void intPushSort();
    void stringPushSort();
    void stringRemoveByNumber();
    void stringRemoveByValue();
    void stringRemoveByNonExistentValue();
    void stringGetNthElement();
    void stringLength();
    void stringPop();
    void stringFreeEmpty();
    void stringEmpty();
    void stringCopy();
    void foreach();
    void swap();
    void swapLast();
    void swapFirst();
    void swapFail();
    void sort();
#ifdef _REGEX_H
    void regex();
    void regexDelete();
#endif

  private:
    List l;
};

#endif
