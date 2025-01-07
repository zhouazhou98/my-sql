# 声明测试文件
set(TEST_FILES test_lexer.cc)

# 构建测试可执行文件
add_executable(test_lexer ${TEST_FILES})

# 链接 sql_parser 静态库
target_link_libraries(test_lexer sql_parser)

# 设置头文件路径
target_include_directories(test_lexer PRIVATE ${CMAKE_SOURCE_DIR}/include)



add_executable(test_parser test_parser.cc)
target_link_libraries(test_parser sql_parser)
