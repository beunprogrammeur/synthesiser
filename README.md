# synthesiser
A basic software synthesiser for use in other projects

# unit tests
The unit tests make use of Google test and cmake. The initial code is based on a script from hackwerken. 
https://github.com/hackwerken/cmake-googletest


The unit tests make use of a fast fourier transform to calculate and compare the output frequencies of the synth oscillators.
This is works thanks to d1vanov's Simple-FFT https://github.com/d1vanov/Simple-FFT

The tests now also create wav files to hear if the output is correct. This works thanks to https://github.com/aazpitarte/sound-maker


# midi
when using the midi source and synthesizer midi sink, a predefined set of midi codes are bound to the synthesizers functinality.
You can always change this by changing midi/synthesizer_midi_sink.h|cpp

codes:
    CC sustain -> ADSR sustain # I don't know if this is industry standard
    CC Controller 1 (32) pwm volume
    CC Controller 2 (33) pwm duty cycle
    CC Controller 3 (34) sawtooth volume
    CC Controller 4 (35) reverse sawtooth volume
    CC Controller 5 (36) triangle volume
    CC controller 6 (37) noise volume
    CC controller 7 (38) sine volume