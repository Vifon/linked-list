file(GLOB list_SOURCES *.cpp *.c)
file(GLOB list_HEADERS *.hpp *.h)

add_executable(list ${list_SOURCES})
