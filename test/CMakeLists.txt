include_directories(
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/test
)



# 1 ChessBoard
add_executable(chess_board_utest
    ${CMAKE_SOURCE_DIR}/src/ChessBoard.cpp
    ${CMAKE_SOURCE_DIR}/src/PieceAttributes.cpp

    ${CMAKE_SOURCE_DIR}/test/ChessBoardUtest.cpp
)
add_test(NAME chess_board_utest COMMAND chess_board_utest)

# 2 Advisor
add_executable(advisor_utest
    ${CMAKE_SOURCE_DIR}/src/ChessBoard.cpp
    ${CMAKE_SOURCE_DIR}/src/PieceAttributes.cpp
    ${CMAKE_SOURCE_DIR}/src/ChessPiece/Advisor.cpp

    ${CMAKE_SOURCE_DIR}/test/ChessPiece/AdvisorUtest.cpp
)
add_test(NAME advisor_utest COMMAND advisor_utest)

# 3 Cannon
add_executable(cannon_utest
    ${CMAKE_SOURCE_DIR}/src/ChessBoard.cpp
    ${CMAKE_SOURCE_DIR}/src/PieceAttributes.cpp
    ${CMAKE_SOURCE_DIR}/src/ChessPiece/Cannon.cpp

    ${CMAKE_SOURCE_DIR}/test/ChessPiece/CannonUtest.cpp
)
add_test(NAME cannon_utest COMMAND cannon_utest)



foreach(test_target chess_board_utest advisor_utest cannon_utest)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${test_target} PRIVATE -O0 -g)
    endif()
    if (MINGW)
        target_link_options(${test_target} PRIVATE -static)
    endif()
endforeach()

add_custom_target(all_utests DEPENDS chess_board_utest advisor_utest cannon_utest)