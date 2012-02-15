cmake_minimum_required(VERSION 2.8)
project(list)
add_definitions(-pedantic -Wall -ansi)
set(CMAKE_C_FLAGS_DEBUG   "-g -O0")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS   "-O2")
set(CMAKE_CXX_FLAGS "-O2")
add_subdirectory(src)
if (${unittest})
  add_subdirectory(tests)
endif()

add_custom_command(
  OUTPUT  list.3.gz
  COMMAND pod2man --utf8 --name=list --section=3 ${CMAKE_CURRENT_SOURCE_DIR}/README.pod -o list.3
  COMMAND gzip -f list.3
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/README.pod
  COMMENT "Generating manpage"
  )

add_custom_target(
  manpage ALL
  DEPENDS list.3.gz
  )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/list.3.gz DESTINATION man/man3)
