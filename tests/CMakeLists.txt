cmake_minimum_required(VERSION 3.13)
project(cmake-googletest-example)

include(CTest)
include(../GoogleTest.cmake)

function(add_test_executable testname testfile) # add source files after test file, they will be added automatically
    
    add_executable(${testname} ${testfile})
    
    foreach(sourcefile ${ARGN})
        target_sources(${testname} PRIVATE ../src/${sourcefile})
    endforeach()

    target_include_directories(${testname} PRIVATE "../src")
    target_link_libraries(${testname}  PRIVATE ${GMOCK_MAIN_PATH})
    target_link_googletest(${testname})
    
    add_test(NAME ${testname} COMMAND ${testname})
endfunction()   

# The tests

add_test_executable(midi-converter-tests "midi-converter-tests.cpp" "midi/converter.cpp")
add_test_executable(observer-tests "observer-tests.cpp")