# Builder design pattern
ADD_EXECUTABLE(fluent-builder fluent-builder.cc)
ADD_EXECUTABLE(code-builder codebuilder.cc)
TARGET_LINK_LIBRARIES(code-builder ${GTEST_LIBRARIES} pthread)
ADD_EXECUTABLE(groovy-style groovy-style.cc)
ADD_EXECUTABLE(builder-facets builder-facets.cc)
