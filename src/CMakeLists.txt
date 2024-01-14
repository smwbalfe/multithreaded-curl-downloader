find_library(cp curlpp)
find_package(fmt)

add_executable(downloadTest main.cpp ThreadPool.cpp ../include/CurlRequest.h ../include/curl.h CurlRequest.cpp ProgressWrapper.cpp ../include/ProgressWrapper.h ../include/HeaderWrapper.h HeaderWrapper.cpp)

target_link_libraries(downloadTest ${cp} fmt::fmt curl)
target_include_directories(downloadTest PRIVATE ../include)