#include <gtest/gtest.h>
#include "synthesis/envelopes/ienvelope.h"
#include "synthesis/envelopes/adsr_envelope.h"
#include "synthesis/envelopes/adsr_configuration.h"

TEST(ADSREnvelopeTests, ManipulatesAmplitude)
{
    using namespace BOSSCorp::Synthesis::Envelopes;

    ADSRConfiguration configuration;
    configuration.attack  = 0.1; // time
    configuration.decay   = 0.1; // time
    configuration.sustain = 0.5; // amplitude
    configuration.release = 0.1; // time

    auto envelope = ADSREnvelope(configuration);
    IEnvelope& ie = envelope;

    float last = 0;
    float deltaT = 0.01;

    // attacking for the first 100ms
    for(int i = 0; i < 10; i++)
    {
        float current = ie.next(deltaT); 
        ASSERT_GT(current, last);
        last = current;
    }

    // decaying for the next 100ms to the sustain level
    for(int i = 0; i < 10; i++)
    {
        float current = ie.next(deltaT);
        ASSERT_LT(current, last);
        last = current;
    }

    // making sure that we actually ended up on the sustain level
    ASSERT_EQ(last, configuration.sustain);

    // the value should stay the sustain level until we release
    for(int i = 0; i < 100; i++)
    {
        float current = ie.next(deltaT);
        ASSERT_EQ(last, configuration.sustain);
    }

    envelope.release();

    // the value should now release towards 0
    for(int i = 0; i < 11; i++)
    {
        float current = ie.next(deltaT);
        ASSERT_LT(current, last);
        last = current;
    }

    // the value should now be totaly dead
    ASSERT_EQ(0, last);

    ASSERT_TRUE(ie.finised());
}

TEST(ADSREnvelopeTests, SquareOutput)
{
     using namespace BOSSCorp::Synthesis::Envelopes;

    ADSRConfiguration configuration;
    configuration.attack  = 0.0; // time
    configuration.decay   = 0.0; // time
    configuration.sustain = 1.0; // amplitude
    configuration.release = 0.0; // time

    auto envelope = ADSREnvelope(configuration);
    IEnvelope& ie = envelope;  
    float deltaT = 0.01;

    for(int i = 0; i < 100; i++)
    {
        if(i == 50) envelope.release();

        float current = ie.next(deltaT);

        ASSERT_EQ(i < 50, current);
    }

}
