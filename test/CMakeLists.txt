enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(chess_board_utest
    ${CMAKE_SOURCE_DIR}/src/ChessBoard.cpp
    ${CMAKE_SOURCE_DIR}/src/PieceAttributes.cpp
    ${CMAKE_SOURCE_DIR}/test/ChessBoardUtest.cpp
)
add_test(NAME chess_board_utest COMMAND chess_board_utest)


foreach(test_target chess_board_utest)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${test_target} PRIVATE -O0 -g)
    endif()
    if (MINGW)
        target_link_options(${test_target} PRIVATE -static)
    endif()
endforeach()