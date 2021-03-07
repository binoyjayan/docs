# Composite design pattern
ADD_EXECUTABLE(composite-geometric geometric.cc)
ADD_EXECUTABLE(composite-array-backed array-backed.cc)
ADD_EXECUTABLE(composite-integers integers.cc)
TARGET_LINK_LIBRARIES(composite-integers ${GTEST_LIBRARIES} pthread)
ADD_EXECUTABLE(composite-neurons composite-neurons.cc)
