cmake_minimum_required(VERSION 3.5)
project(string_util C)

set(STRING_UTIL_VERSION 1.0.0)
add_library(${PROJECT_NAME} string_util.c)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "string_util.h")
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${STRING_UTIL_VERSION})