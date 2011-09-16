if (cfg STREQUAL "unittest")
  set(list_SOURCES
    testmain.cpp
    tests.cpp
    list.c
    )
  set(list_HEADERS
    list.h
    tests.hpp
    )
else()
  set(list_SOURCES
    list.c
    main.c
    )
  set(list_HEADERS
    list.h
    )
endif()

add_executable(list ${list_SOURCES})
if (cfg STREQUAL "unittest")
  target_link_libraries(list cppunit)
endif()
