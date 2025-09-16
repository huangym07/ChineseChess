include_directories(
    ${CMAKE_SOURCE_DIR}/include 
    ${CMAKE_SOURCE_DIR}/test
)


############################################ start 单元测试 target ############################################
set(ALL_UTEST_TARGETS "")

################################# 棋盘单元测试 #################################
add_executable(chess_board_utest
    ${CMAKE_SOURCE_DIR}/src/ChessBoard.cpp
    ${CMAKE_SOURCE_DIR}/src/PieceAttributes.cpp
    ${CMAKE_SOURCE_DIR}/test/ChessBoardUtest.cpp
)
list(APPEND ALL_UTEST_TARGETS chess_board_utest)
################################# 棋子单元测试 #################################
set(COMMON_CHESSPIECE_UTEST_SRC 
    ${CMAKE_SOURCE_DIR}/src/ChessBoard.cpp
    ${CMAKE_SOURCE_DIR}/src/PieceAttributes.cpp
)
set(CHESSPIECE_UTEST_SRC_LIST
    advisor_utest:::::${CMAKE_SOURCE_DIR}/src/ChessPiece/Advisor.cpp:::::${CMAKE_SOURCE_DIR}/test/ChessPiece/AdvisorUtest.cpp
    cannon_utest:::::${CMAKE_SOURCE_DIR}/src/ChessPiece/Cannon.cpp:::::${CMAKE_SOURCE_DIR}/test/ChessPiece/CannonUtest.cpp
    chariot_utest:::::${CMAKE_SOURCE_DIR}/src/ChessPiece/Chariot.cpp:::::${CMAKE_SOURCE_DIR}/test/ChessPiece/ChariotUtest.cpp
    elephant_utest:::::${CMAKE_SOURCE_DIR}/src/ChessPiece/Elephant.cpp:::::${CMAKE_SOURCE_DIR}/test/ChessPiece/ElephantUtest.cpp
    general_utest:::::${CMAKE_SOURCE_DIR}/src/ChessPiece/General.cpp:::::${CMAKE_SOURCE_DIR}/test/ChessPiece/GeneralUtest.cpp
)

# message(STATUS "棋子测试")
foreach(utest_info IN LISTS CHESSPIECE_UTEST_SRC_LIST)
    # message(STATUS "utest_info = ${utest_info}")

    string(REPLACE ":::::" ";" info_parts ${utest_info})
    list(GET info_parts 0 target_name)
    list(GET info_parts 1 piece_src)
    list(GET info_parts 2 utest_src)

    # message(STATUS "target_name = ${target_name}")
    # message(STATUS "piece_src = ${piece_src}")
    # message(STATUS "utest_src = ${utest_src}")
    # message("\n")

    add_executable(${target_name} ${COMMON_CHESSPIECE_UTEST_SRC} ${piece_src} ${utest_src})
    list(APPEND ALL_UTEST_TARGETS ${target_name})
endforeach()
################################# 单元测试设置 #################################
foreach(test_target IN LISTS ALL_UTEST_TARGETS)
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${test_target} PRIVATE -O0 -g)
    endif()
    if (MINGW)
        target_link_options(${test_target} PRIVATE -static)
    endif()

    message(STATUS "测试 ${test_target} 注册")
    add_test(NAME ${test_target} COMMAND ${test_target})
endforeach()
############################################ end 单元测试 target ############################################

add_custom_target(all_utests DEPENDS ${ALL_UTEST_TARGETS})