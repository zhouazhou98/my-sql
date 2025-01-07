# 源代码构建
set(SRC_FILES 
    lexer.cc
    parser.cc
)

add_library(sql_parser ${SRC_FILES})
target_include_directories(sql_parser PUBLIC ${CMAKE_SOURCE_DIR}/src)

