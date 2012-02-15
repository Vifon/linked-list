set(list_SOURCES
  list.c
  )

set(list_HEADERS
  list.h
  )

add_library(list       SHARED ${list_SOURCES})
add_library(listStatic STATIC ${list_SOURCES})

set_target_properties(listStatic PROPERTIES OUTPUT_NAME list)

install(FILES list.h DESTINATION include)
install(
  TARGETS list listStatic
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
