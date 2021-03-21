# see https://cmake.org/cmake/help/v3.5/module/FindBoost.html
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(SOURCE_FILES main.cc headers.hpp observer.cc observer.hpp observable.cc observable.hpp saferobservable.cc saferobservable.hpp)
add_executable(observable ${SOURCE_FILES})


