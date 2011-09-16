#ifndef _TESTS_H_
#define _TESTS_H_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "list.h"

class ListTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(ListTest);
    CPPUNIT_TEST(initialization);
    CPPUNIT_TEST(movement);
    CPPUNIT_TEST(addingNewElements);
    CPPUNIT_TEST(addingNewSortedElements);
    CPPUNIT_TEST(getNthElement);
    CPPUNIT_TEST(removeByNumber);
    CPPUNIT_TEST(removeByValue);
    CPPUNIT_TEST(removeByNonExistentValue);
    CPPUNIT_TEST_SUITE_END();
  public:
    void setUp();
    void tearDown();

  protected:
    void initialization();
    void movement();
    void addingNewElements();
    void addingNewSortedElements();
    void removeByNumber();
    void removeByValue();
    void removeByNonExistentValue();
    void getNthElement();

  private:
    List l[1];
};

#endif
