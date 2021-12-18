cmake_minimum_required(VERSION 3.12)

set(PACKAGE_NAME "logcabin")
set(PACKAGE_VERSION "1.2.0")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_TARNAME "${PACKAGE_NAME}-${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "https://github.com/logcabin/logcabin/issues")
set(PACKAGE_DESCRIPTION "LogCabin is a distributed system that provides a small amount of highly replicated, consistent storage.")
set(PACKAGE_URL "https://github.com/logcabin/logcabin")

project(${PACKAGE_NAME} VERSION ${PACKAGE_VERSION} LANGUAGES CXX)

include(cmake/CompileOptions.cmake)
include(cmake/ProtobufDependencies.cmake)