ADD_EXECUTABLE(flyweight flyweight.cc)
TARGET_LINK_LIBRARIES(flyweight pthread)
ADD_EXECUTABLE(capitalize capitalize.cc)
ADD_EXECUTABLE(word-captitalize word-captitalize.cc)
TARGET_LINK_LIBRARIES(word-captitalize ${GTEST_LIBRARIES} pthread)

