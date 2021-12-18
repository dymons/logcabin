cmake_minimum_required(VERSION 3.12)

set(PACKAGE_NAME "logcabin")
set(PACKAGE_VERSION "1.2.0")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_TARNAME "${PACKAGE_NAME}-${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "https://github.com/logcabin/logcabin/issues")
set(PACKAGE_DESCRIPTION "LogCabin is a distributed system that provides a small amount of highly replicated, consistent storage.")
set(PACKAGE_URL "https://github.com/logcabin/logcabin")

project(${PACKAGE_NAME} VERSION ${PACKAGE_VERSION} LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

include(cmake/CompileOptions.cmake)
include(cmake/ProtobufDependencies.cmake)
include(cmake/Functions.cmake)

extract_source(FOLDER Core)
extract_source(FOLDER Client EXCLUDE ".ServerControl.cc" ".*Mock.cc")
extract_source(FOLDER RPC EXCLUDE ".*Mock.cc")
extract_source(FOLDER Event)
extract_source(FOLDER Server EXCLUDE ".Main.cc")
extract_source(FOLDER Storage EXCLUDE ".Tool.cc")
extract_source(FOLDER Tree)

add_library(${PACKAGE_NAME} STATIC
            ${Core_SOURCE}
            ${Client_SOURCE}
            ${RPC_SOURCE}
            ${Event_SOURCE}
            ${Server_SOURCE}
            ${Storage_SOURCE}
            ${Tree_SOURCE})
target_link_libraries(${PACKAGE_NAME} PRIVATE ${PACKAGE_NAME}-proto)