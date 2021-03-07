# Bridge design pattern
ADD_EXECUTABLE(pimpl-idiom pimpl-idiom/person.cc)
ADD_EXECUTABLE(pimpl-wrap pimpl-wrap/foo.cc pimpl-wrap/pimpl.cc)
ADD_EXECUTABLE(bridge-impl bridge-impl.cc)
ADD_EXECUTABLE(bridge-original refactor/original.cc)
TARGET_LINK_LIBRARIES(bridge-original ${GTEST_LIBRARIES} pthread)
ADD_EXECUTABLE(bridge-refactored refactor/refactored.cc)
TARGET_LINK_LIBRARIES(bridge-refactored ${GTEST_LIBRARIES} pthread)

