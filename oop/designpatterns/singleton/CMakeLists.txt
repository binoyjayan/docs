# Singleton design pattern
ADD_EXECUTABLE(simple-singleton simple-singleton.cc)
ADD_EXECUTABLE(singleton-abstraction singleton-abstraction.cc)
TARGET_LINK_LIBRARIES(singleton-abstraction ${GTEST_LIBRARIES} pthread)
ADD_EXECUTABLE(singleton-lifetime singleton-lifetime.cc)
ADD_EXECUTABLE(multiton multiton.cc)