cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g")

project(cmake-googletest-synthesizer)

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

# pattern tests
add_test_executable(observer-tests "observer-tests.cpp")

# midi tests
add_test_executable(midi-converter-tests "midi-converter-tests.cpp" "midi/converter.cpp")


# envelope tests
add_test_executable(adsr-envelope-tests "adsr-envelope-tests.cpp" "synthesis/envelopes/adsr_envelope.cpp")

# oscillator tests
add_test_executable(sawtooth-oscillator-tests "sawtooth-oscillator-tests.cpp" "synthesis/oscillators/sawtooth_oscillator.cpp" "synthesis/oscillators/reverse_sawtooth_oscillator.cpp")
add_test_executable(reverse-sawtooth-oscillator-tests "reverse-sawtooth-oscillator-tests.cpp" "synthesis/oscillators/reverse_sawtooth_oscillator.cpp" "synthesis/oscillators/sawtooth_oscillator.cpp")
add_test_executable(triangle-oscillator-tests "triangle-oscillator-tests.cpp" "synthesis/oscillators/triangle_oscillator.cpp" "synthesis/oscillators/sawtooth_oscillator.cpp")
add_test_executable(pwm-oscillator-tests "pwm-oscillator-tests.cpp" "synthesis/oscillators/pwm_oscillator.cpp")
add_test_executable(sine-oscillator-tests "sine-oscillator-tests.cpp" "synthesis/oscillators/sine_oscillator.cpp")