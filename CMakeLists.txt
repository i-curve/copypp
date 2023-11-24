cmake_minimum_required(VERSION 3.10)

project(copypp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(COPYPP_MASTER_PROJECT OFF)
# option(COPYPP_TEST "build copypp tests" OFF) # 是否开启 test 开关

# message(STATUS "CMAKE_CURRENT_SOURCE_DIR" ${CMAKE_CURRENT_SOURCE_DIR})
# message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  # message(STATUS "CMAKE_CURRENT_SOURCE_DIR = CMAKE_SOURCE_DIR")
  set(COPYPP_MASTER_PROJECT ON)
  if (NOT DEFINED COPYPP_TEST)
    set(COPYPP_TEST "build mathpp tests" ON)
  endif()
  # message(STATUS "CMake version: ${CMAKE_VERSION}")
# else()
#   message(STATUS "CMAKE_CURRENT_SOURCE_DIR != CMAKE_SOURCE_DIR")
endif()

include(GNUInstallDirs)

add_library(copypp INTERFACE)
add_library(icurve::copypp ALIAS copypp)

set_target_properties(
  copypp PROPERTIES VERSION ${${PROJECT_NAME}_VERSION}
                    SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR})
target_include_directories(copypp INTERFACE
                $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                $<INSTALL_INTERFACE:include>)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
      DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# 进行库安装
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
install(
  TARGETS copypp
  EXPORT ${TARGETS_EXPORT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION include
  FRAMEWORK DESTINATION ".")

# 添加后续使用 cmake 导入的相关配置
include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake
  ${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION lib/cmake/${PROJECT_NAME})

install(FILES "${PROJECT_BINARY_DIR}/cmake/${PROJECT_NAME}Config.cmake"
  DESTINATION lib/cmake/${PROJECT_NAME})

install(EXPORT ${TARGETS_EXPORT_NAME}
  NAMESPACE icurve::
  DESTINATION "lib/cmake/${PROJECT_NAME}")

if (COPYPP_TEST)
    message(STATUS "copypp tests...")
    enable_testing()
    add_subdirectory(test)
endif()