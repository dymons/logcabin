cmake_minimum_required(VERSION 3.12)

set(PACKAGE_NAME "logcabin")
set(PACKAGE_VERSION "1.2.0")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_TARNAME "${PACKAGE_NAME}-${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "https://github.com/logcabin/logcabin/issues")
set(PACKAGE_DESCRIPTION "LogCabin is a distributed system that provides a small amount of highly replicated, consistent storage.")
set(PACKAGE_URL "https://github.com/logcabin/logcabin")

project(${PACKAGE_NAME} VERSION ${PACKAGE_VERSION} LANGUAGES CXX)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

include(cmake/CompileOptions.cmake)
include(cmake/Dependencies.cmake)
include(cmake/ProtobufDependencies.cmake)
include(cmake/Functions.cmake)

extract_source(FOLDER Core)
extract_source(FOLDER Client EXCLUDE ".ServerControl.cc" ".*Mock.cc")
extract_source(FOLDER RPC EXCLUDE ".*Mock.cc")
extract_source(FOLDER Event)
extract_source(FOLDER Server EXCLUDE ".Main.cc")
extract_source(FOLDER Storage EXCLUDE ".Tool.cc")
extract_source(FOLDER Tree)
extract_source(FOLDER Examples)

add_library(${PACKAGE_NAME} STATIC
            ${Core_SOURCE}
            ${Client_SOURCE}
            ${RPC_SOURCE}
            ${Event_SOURCE}
            ${Server_SOURCE}
            ${Storage_SOURCE}
            ${Tree_SOURCE})
target_link_libraries(${PACKAGE_NAME} PRIVATE ${PACKAGE_NAME}-proto)

add_executable(LogCabin Server/Main.cc)
add_executable(StorageTool Storage/Tool.cc)
add_executable(ServerControl Client/ServerControl.cc)

target_link_libraries(LogCabin ${PACKAGE_NAME} ${CABIN_COMMON_LIBRARIES})
target_link_libraries(StorageTool ${PACKAGE_NAME} ${CABIN_COMMON_LIBRARIES})
target_link_libraries(ServerControl ${PACKAGE_NAME} ${CABIN_COMMON_LIBRARIES})

foreach(Example ${Examples_SOURCE} ${Examples_SOURCE_TESTS})
    get_filename_component(EXAMPLE_NAME ${Example} NAME_WE)
    add_executable(${EXAMPLE_NAME} Examples/${EXAMPLE_NAME}.cc)
    target_link_libraries(${EXAMPLE_NAME} ${PACKAGE_NAME} ${CABIN_COMMON_LIBRARIES})
endforeach()

add_custom_target(check COMMAND scripts/cpplint.py)
add_custom_target(lint COMMAND scripts/cpplint.py)
add_custom_target(docs COMMAND doxygen docs/Doxyfile)
add_custom_target(tags COMMAND ctags -R --exclude=build --exclude=docs --exclude=CMakeFiles .)