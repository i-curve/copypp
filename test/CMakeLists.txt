# find_package
find_package(GTest CONFIG REQUIRED)
find_package(fmt)
find_package(nlohmann_json CONFIG REQUIRED)
set(CMAKE_CXX_STANDARD 20)

message(STATUS "test")
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(copypp_test copypp_test.cpp)
target_link_libraries(copypp_test PRIVATE fmt::fmt-header-only GTest::gtest GTest::gtest_main)
target_link_directories(copypp_test PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_test(NAME copypp_test COMMAND copypp_test)

add_executable(copypp_test2 copypp_test2.cpp)
target_link_libraries(copypp_test2 PRIVATE fmt::fmt-header-only GTest::gtest GTest::gtest_main)
target_link_directories(copypp_test2 PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_test(NAME copypp_test2 COMMAND copypp_test2)

add_executable(copypp_only_test copypp_only_test.cpp)
target_link_libraries(copypp_only_test PRIVATE fmt::fmt-header-only GTest::gtest GTest::gtest_main)
target_link_directories(copypp_only_test PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_test(NAME copypp_only_test COMMAND copypp_only_test)


find_package(GTest CONFIG REQUIRED)

add_executable(copypp_test3 copypp_test3.cpp)
target_link_libraries(copypp_test3 PRIVATE GTest::gtest GTest::gtest_main)
target_link_directories(copypp_test3 PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_test(NAME copypp_test3 COMMAND copypp_test3)

add_executable(copypp_test4 copypp_test4.cpp)
target_link_libraries(copypp_test4 PRIVATE GTest::gtest GTest::gtest_main)
target_link_directories(copypp_test4 PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_test(NAME copypp_test4 COMMAND copypp_test4)

add_executable(copypp_array_test copypp_array_test.cpp)
target_link_libraries(copypp_array_test PRIVATE GTest::gtest GTest::gtest_main)
target_link_directories(copypp_array_test PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_test(NAME copypp_array_test COMMAND copypp_array_test)

add_executable(copypp_stl_test copypp_stl_test.cpp)
target_link_libraries(copypp_stl_test PRIVATE fmt::fmt-header-only GTest::gtest GTest::gtest_main)
target_link_directories(copypp_stl_test PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_test(NAME copypp_stl_test COMMAND copypp_stl_test)