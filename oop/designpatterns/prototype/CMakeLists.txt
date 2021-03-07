# Prototype design pattern
ADD_EXECUTABLE(prototype prototype.cc)
ADD_EXECUTABLE(deep-copy deep-copy.cc)
TARGET_LINK_LIBRARIES(deep-copy ${GTEST_LIBRARIES} pthread)
