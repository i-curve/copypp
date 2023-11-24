# find_package
find_package(fmt)
# find_package(nlohmann_json CONFIG REQUIRED)

message(STATUS "test")
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(copypp_test copypp_test.cpp)
target_link_libraries(copypp_test PRIVATE fmt::fmt-header-only)
target_link_directories(copypp_test PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_test(NAME copypp_test COMMAND copypp_test)

add_executable(copypp_test2 copypp_test2.cpp)
target_link_libraries(copypp_test2 PRIVATE fmt::fmt-header-only)
target_link_directories(copypp_test2 PUBLIC ${PROJECT_SOURCE_DIR}/include)
add_test(NAME copypp_test2 COMMAND copypp_test2)