# synthesiser
A basic software synthesiser for use in other projects

# unit tests
The unit tests make use of Google test and cmake. The initial code is based on a script from hackwerken. 
https://github.com/hackwerken/cmake-googletest


The unit tests make use of a fast fourier transform to calculate and compare the output frequencies of the synth oscillators.
This is works thanks to d1vanov's Simple-FFT https://github.com/d1vanov/Simple-FFT
