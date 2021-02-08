#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "simple_fft/fft_settings.h"
#include "simple_fft/fft.h"
#include "synthesis/oscillators/ioscillator.h"
#include <gtest/gtest.h>

bool plot(const std::string& name, BOSSCorp::Synthesis::Oscillators::IOscillator& oscillator, int size, float samplerate)
{
    std::vector<real_type>    input;
    std::vector<complex_type> output;
    output.reserve(size);


    for(int i = 0; i < size; i++)
    {
        input.emplace_back(oscillator.next(1.0 / samplerate));
    }

    const char* error = nullptr;
    bool success = simple_fft::FFT(input, output, size, error);
    if(!success)
    {
        return false;
    }

    std::ofstream fftcsv;
    std::ofstream wavcsv;
    fftcsv.open(name + ".fft.gnuplot.csv");
    wavcsv.open(name + ".wav.gnuplot.csv");

    for(int i = 0; i < size; i++)
    {
        auto& v = output[i];
        
        wavcsv << std::fixed << input[i] << std::endl;

        if (i < size/2) fftcsv << std::fixed << sqrt(pow(v.real(), 2) + pow(v.imag(), 2)) << std::endl;
    }

    fftcsv.close();
    wavcsv.close();

    auto genPlotfile = [&](std::string gnuplot, std::string csv) {
        std::ofstream file;
        file.open(gnuplot);

        file << "set datafile separator ','" << std::endl;
        file << "set xtics " << std::fixed << size * (1.0 / oscillator.frequency()) << std::endl;
        file << "set xlabel 'frequency'" << std::endl;
        file << "set ylabel 'amplitude'" << std::endl;
        //file << "set mxtics " << 500 << std::endl;
        //file << "show mxtics" << std::endl;
        file <<  " " <<  std::endl;
        file << "plot '" << csv << "' using 0:1 with lines" << std::endl;
        file.close();
    };

    genPlotfile(name + ".wav.gnuplot", name + ".wav.gnuplot.csv");
    genPlotfile(name + ".fft.gnuplot", name + ".fft.gnuplot.csv");

    return true;
}

void dataplot(std::string filename, std::vector<float>& plotData)
{
    std::ofstream csv;
    csv.open(filename + ".gnuplot.csv");

    for(auto point : plotData)
    {
        csv << std::setprecision(10) << std::fixed <<  point << std::endl;
    }
    csv.close();

    std::ofstream gnuplot;
    gnuplot.open(filename + ".gnuplot");

    gnuplot << "set datafile separator ','" << std::endl;
    //gnuplot << "set xtics " << std::fixed << size * (1.0 / oscillator.frequency()) << std::endl;
    gnuplot << "set xlabel 'time'" << std::endl;
    gnuplot << "set ylabel 'amplitude'" << std::endl;
    //gnuplot << "set mxtics " << 500 << std::endl;
    //gnuplot << "show mxtics" << std::endl;
    gnuplot <<  " "     <<  std::endl;
    gnuplot << "plot '" << filename << ".gnuplot.csv" << "' using 0:1 with lines" << std::endl;
    gnuplot.close();
}

void autoplot(std::string waveform, BOSSCorp::Synthesis::Oscillators::IOscillator& oscillator)
{
    int frequencies[] {20, 440, 3000};

    for(auto frequency : frequencies)
    {
        std::stringstream ss;
        ss << waveform << "-" << frequency << "hz";

        oscillator.reset();
        oscillator.configure(frequency);
        
        plot(ss.str(), oscillator, 8192, 44100);
    }
}

float detectFrequency(BOSSCorp::Synthesis::Oscillators::IOscillator& oscillator, int samplerate, int size)
{
    std::vector<real_type>    input;
    std::vector<complex_type> output;
    output.reserve(size);


    for(int i = 0; i < size; i++)
    {
        input.emplace_back(oscillator.next(1.0 / samplerate));
    }

    const char* error = nullptr;
    bool success = simple_fft::FFT(input, output, size, error);
    if(!success)
    {
        return 0.0;
    }

    int   peakIndex     = 0;
    float peakAmplitude = 0;

    for(int i = 1; i < size/2; i++)
    {
        auto v = output[i];
        float amplitude = sqrt(pow(v.real(), 2) + pow(v.imag(), 2));
        if(amplitude > peakAmplitude) 
        {
            peakIndex = i;
            peakAmplitude = amplitude;
        }
    }

    return samplerate * peakIndex / size; // calculate the highest peak's frequency
}

void doGlobalFrequencyTest(BOSSCorp::Synthesis::Oscillators::IOscillator& oscillator, int frequencies[], int numFrequencies, int maxDeviation)
{
    int samplerate = 44100;
    int sampleSize = 8192;

    for(int i = 0; i < numFrequencies; i++)
    {
        int frequency = frequencies[i];

        oscillator.reset();
        oscillator.configure(frequency);
        float detectedFrequency = detectFrequency(oscillator,samplerate, sampleSize);

        EXPECT_TRUE(detectedFrequency > (frequency - maxDeviation) && detectedFrequency < (frequency + maxDeviation));
        std::cout << "expected: " << frequency << " actual: " << std::fixed << detectedFrequency << std::endl;
    }
}