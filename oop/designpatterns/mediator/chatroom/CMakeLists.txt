#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std:c++latest")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

find_package(Boost REQUIRED)

link_directories("c:/boost/stage/lib32")
include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES main.cc person.cc person.hpp chatroom.cc chatroom.hpp)
add_executable(chatroom ${SOURCE_FILES})
# target_link_libraries(chatroom "c:/gtest/lib32/gtestd.lib")


