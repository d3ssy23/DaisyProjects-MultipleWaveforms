#include "daisy_seed.h"
#include "daisysp.h"

using namespace daisy;
using namespace daisysp;

DaisySeed hw;
Oscillator osc;
Switch button1, button2;

float knob_value_amp, knob_value_freq;
bool is_muted = false;

void AudioCallback(float *in, float *out, size_t size)
{
	for(size_t i{0}; i< size; i+=2)
	{
		if(!is_muted)
		{
				float sig = osc.Process();
		out[i] = sig; //left
		out[i+1] = sig; //right
		}
		else{

			// float amp = knob_value_amp;
			// osc.SetAmp(amp);
				out[i] = 0.0f; //left
				out[i+1] = 0.0f; //right
		}

	
	}
}



int main(void)
{
   
    hw.Configure();
    hw.Init();

	osc.Init(hw.AudioSampleRate());
	osc.SetFreq(440.0f);
	AdcChannelConfig adc_cfg[2];
	//osc.SetAmp(0.5f);
	osc.SetWaveform(Oscillator::WAVE_SIN);
	adc_cfg[0].InitSingle(hw.GetPin(15)); // knob pin
	adc_cfg[1].InitSingle(hw.GetPin(21));
	hw.adc.Init(adc_cfg,2);
	hw.adc.Start();

    button1.Init(hw.GetPin(28), 100); // buttons pins
	button2.Init(hw.GetPin(27), 100);
	hw.StartAudio(AudioHandle::InterleavingAudioCallback(AudioCallback));


    for(;;)
    {
        button1.Debounce();
		button2.Debounce();
        hw.SetLed(button1.Pressed()||button2.Pressed());

		knob_value_amp = hw.adc.GetFloat(0);
		knob_value_freq = hw.adc.GetFloat(1);
		 osc.SetAmp(knob_value_amp);
        osc.SetFreq(knob_value_freq * 1000.0f + 100.0f);

		if (button1.RisingEdge())
        {
            is_muted = !is_muted;
        }

		  if (button2.RisingEdge())
        {
            static int waveform = 0;
            waveform = (waveform + 1) % 3;
            switch (waveform)
            {
                case 0:
                    osc.SetWaveform(Oscillator::WAVE_SIN);
                    break;
                case 1:
                    osc.SetWaveform(Oscillator::WAVE_SQUARE);
                    break;
                case 2:
                    osc.SetWaveform(Oscillator::WAVE_TRI);
                    break;
            }
        }
        //wait 1 ms
        System::Delay(1);
		__WFI();
    }
	return 0;
}

