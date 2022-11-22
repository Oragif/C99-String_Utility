cmake_minimum_required(VERSION 3.5)
project(string_util C)

set(STRING_UTIL_VERSION 1.0.0)
add_library(string_util string_util.c)

set_target_properties(string_util PROPERTIES PUBLIC_HEADER "string_util.h")
set_target_properties(string_util PROPERTIES VERSION ${STRING_UTIL_VERSION})