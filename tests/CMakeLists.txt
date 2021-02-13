cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -pg")

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
add_test_executable(noise-oscillator-tests "noise-oscillator-tests.cpp" "synthesis/oscillators/noise_oscillator.cpp")

# sound sources
add_test_executable(poly-sound-source-tests "poly-sound-source-tests.cpp" 
                   "midi/converter.cpp"
                   "synthesis/sound_sources/poly_sound_source.cpp" 
                   "synthesis/envelopes/adsr_envelope.cpp" 
                   "synthesis/oscillators/sine_oscillator.cpp"
                   "synthesis/oscillators/sawtooth_oscillator.cpp"
                   "synthesis/oscillators/reverse_sawtooth_oscillator.cpp"
                   "synthesis/oscillators/noise_oscillator.cpp"
                   "synthesis/oscillators/pwm_oscillator.cpp"
                   "synthesis/oscillators/triangle_oscillator.cpp")

# midi sources and sinks
add_test_executable(synth-midi-sink-tests "synth-midi-sink-tests.cpp" 
                   "midi/synthesizer_midi_sink.cpp"
                   "midi/converter.cpp")

# synthesizer tests
add_test_executable(synth-tests "synth-tests.cpp"
                   "midi/converter.cpp"
                   "synthesis/synthesizers/synthesizer.cpp"
                   "synthesis/sound_sources/poly_sound_source.cpp" 
                   "synthesis/sound_sources/max_sound_source.cpp" 
                   "synthesis/envelopes/adsr_envelope.cpp" 
                   "synthesis/oscillators/sine_oscillator.cpp"
                   "synthesis/oscillators/sawtooth_oscillator.cpp"
                   "synthesis/oscillators/reverse_sawtooth_oscillator.cpp"
                   "synthesis/oscillators/noise_oscillator.cpp"
                   "synthesis/oscillators/pwm_oscillator.cpp"
                   "synthesis/oscillators/triangle_oscillator.cpp")