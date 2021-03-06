#include "Talkthrough.h"
#include <math.h>

#include "distortion.h"
#include "wah_wah.h"
#include "flanger.h"
#include "delay.h"
#include "ringMode.h"
#include "tremolo.h"
#include "compressor.h"
#include "noisegate.h"

//--------------------------------------------------------------------------//
// Function:	Process_Data()												//
//																			//
// Description: This function is called from inside the SPORT0 ISR every 	//
//				time a complete audio frame has been received. The new 		//
//				input samples can be found in the variables iChannel0LeftIn,//
//				iChannel0RightIn, iChannel1LeftIn and iChannel1RightIn 		//
//				respectively. The processed	data should be stored in 		//
//				iChannel0LeftOut, iChannel0RightOut, iChannel1LeftOut,		//
//				iChannel1RightOut, iChannel2LeftOut and	iChannel2RightOut	//
//				respectively.												//
//--------------------------------------------------------------------------//
void Process_Data(void)
{
	short tst = 100;
	
	if(FlagAMode != PASS_THROUGH)
	{
		// Delay-line
		// the input signal is an int so we shift it to get the 16th most significant
		// bit into the delay-line which is short
		x[x_pos] = (short) (iChannel0LeftIn >> 16);	
	}

	// FlagAMode �ndres ved at trykke p� pushbutton	
	switch (FlagAMode) {
		case PASS_THROUGH : 
		
			iChannel0LeftOut = iChannel0LeftIn;
			
			iChannel0RightOut = iChannel0RightIn;
			iChannel0RightOut = iChannel0LeftIn; // left ind ud p� begge udgange..
			
			iChannel1LeftOut = iChannel1LeftIn;
			iChannel1RightOut = iChannel1RightIn;
			break;
			
		case DISTORTION_ACTIVE :
			yn = applyDistortion(x, SIZE_DELAY_LINE_X);
			break;

			
		case WAH_WAH_ACTIVE :
			yn = applyWahWah(x, SIZE_DELAY_LINE_X);
			break;
			
		case FLANGER_ACTIVE :
			yn = applyFlanger(x, SIZE_DELAY_LINE_X);
			break;
		
		case DELAY_ACTIVE :
			yn = applyDelay(x, SIZE_DELAY_LINE_X);
			break;
			
		case RING_MODE_ACTIVE :
			yn = applyRingMode(x, SIZE_DELAY_LINE_X);
			break;
	
		case TREMOLOT_ACTIVE :
			yn = applyTremolo(x, SIZE_DELAY_LINE_X);
			break;
			
		case COMPRESSOR_ACTIVE :
			yn = applyComp(x);
			break;
			
		case NOISE_GATE_ACTIVE :
			yn = applyNoise(x);
			break;
	
	}	// end switch
	
	
	if(FlagAMode != PASS_THROUGH)
	{
		if(++x_pos >= SIZE_DELAY_LINE_X)
		{
			x_pos = 0;
		}
		if(++y_pos >= SIZE_DELAY_LINE_Y)
		{
			y_pos = 0;
		}
	
		// Update y delay-line
		y[y_pos] = (short) (yn >> 16);
	
		// Set the output
		iChannel0LeftOut = yn;
		iChannel0RightOut = yn;
	
	
		//=========== Debug ===========
		if(tst == 100)
		{
			if(myCounter < 2000)
			{
				yPlot[myCounter] = yn;
				xPlot[myCounter] = x[x_pos];
				myCounter++;
			}
			tst = 0;
		}
		else
		{
			tst++;
		}
		//========= End debug =========
	}
	
	
}
