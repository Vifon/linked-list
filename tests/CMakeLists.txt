set(unittests_SOURCES
  ../src/list.c
  testmain.cpp
  tests.cpp
  )

set(unittests_HEADERS
  ../src/list.h
  tests.hpp
  )

add_executable(unittests ${unittests_SOURCES})
target_link_libraries(unittests cppunit)
