#ifndef  __Talkthrough_DEFINED
	#define __Talkthrough_DEFINED

//--------------------------------------------------------------------------//
// Header files																//
//--------------------------------------------------------------------------//
#include <sys\exception.h>
#include <cdefBF533.h>
#include <ccblkfn.h>
#include <sysreg.h>
#include <sys/05000311.h>

//--------------------------------------------------------------------------//
// Symbolic constants														//
//--------------------------------------------------------------------------//
// addresses for Port A in Flash A
#define pFlashA_PortA_Dir	(volatile unsigned char *)0x20270006
#define pFlashA_PortA_Data	(volatile unsigned char *)0x20270004

// addresses in Flash for the LED's
#define pFlashA_PortB_Dir	(volatile unsigned char *)0x20270007
#define pFlashA_PortB_Data	(volatile unsigned char *)0x20270005

// names for codec registers, used for iCodec1836TxRegs[]
#define DAC_CONTROL_1		0x0000
#define DAC_CONTROL_2		0x1000
#define DAC_VOLUME_0		0x2000
#define DAC_VOLUME_1		0x3000
#define DAC_VOLUME_2		0x4000
#define DAC_VOLUME_3		0x5000
#define DAC_VOLUME_4		0x6000
#define DAC_VOLUME_5		0x7000
#define ADC_0_PEAK_LEVEL	0x8000
#define ADC_1_PEAK_LEVEL	0x9000
#define ADC_2_PEAK_LEVEL	0xA000
#define ADC_3_PEAK_LEVEL	0xB000
#define ADC_CONTROL_1		0xC000
#define ADC_CONTROL_2		0xD000
#define ADC_CONTROL_3		0xE000

// names for slots in ad1836 audio frame
#define INTERNAL_ADC_L0			0
#define INTERNAL_ADC_L1			1
#define INTERNAL_ADC_R0			4
#define INTERNAL_ADC_R1			5
#define INTERNAL_DAC_L0			0
#define INTERNAL_DAC_L1			1
#define INTERNAL_DAC_L2			2
#define INTERNAL_DAC_R0			4
#define INTERNAL_DAC_R1			5
#define INTERNAL_DAC_R2			6

// size of array iCodec1836TxRegs and iCodec1836RxRegs
#define CODEC_1836_REGS_LENGTH	11

// SPI transfer mode
#define TIMOD_DMA_TX 0x0003

// SPORT0 word length
#define SLEN_32	0x001f

// DMA flow mode
#define FLOW_1	0x1000


// FlagA - defines
#define PASS_THROUGH		0
#define DISTORTION_ACTIVE	1
#define WAH_WAH_ACTIVE		2
#define FLANGER_ACTIVE		3
#define DELAY_ACTIVE		4
#define RING_MODE_ACTIVE	5
#define TREMOLOT_ACTIVE		6
#define COMPRESSOR_ACTIVE   7
#define NOISE_GATE_ACTIVE   8
#define NUMBER_FLAGA_STATES	9

#define ANTAL_FILTKOEF 3

#define PI (3.141592653589793F)
#define FS (48000.0F)

#define SIZE_DELAY_LINE_X   1024
#define SIZE_DELAY_LINE_Y   20

//--------------------------------------------------------------------------//
// Global variables															//
//--------------------------------------------------------------------------//
extern int iChannel0LeftIn;
extern int iChannel0RightIn;
extern int iChannel0LeftOut;
extern int iChannel0RightOut;
extern int iChannel1LeftIn;
extern int iChannel1RightIn;
extern int iChannel1LeftOut;
extern int iChannel1RightOut;
extern volatile short sCodec1836TxRegs[];
extern volatile int iRxBuffer1[];
extern volatile int iTxBuffer1[];

extern short FlagAMode;
extern short x[];
extern short x_pos;
extern short y[];
extern short y_pos;
extern int yn; 

extern int yPlot[];
extern short xPlot[];
extern int myCounter;

// distortion parameters
extern short dist_a, dist_b;
extern int dist_threshold;

// wah-wah parameters
extern short wah_f1;
extern int wah_f1Length;
extern int wah_f1Count;
extern short wah_minfn;
extern short wah_maxfn;
extern short wah_a;
extern short wah_q1;

extern short wah_yh;
extern short wah_yb;
extern short wah_yb1;
extern short wah_yl;
extern short wah_yl1;

// flanger parameters
extern short flanger_a;
extern short flanger_D;
extern short flanger_pos;
extern short flanger_count;
extern short flanger_delay[];

// delay parameters
extern short delay;
extern short gain;
extern short delay_pos;

// RingMode
extern short ring_a1;
extern short ring_a2;
extern short ring_b0;
extern short c1,c2;
extern int cn;

// TwoSin
extern short ring_modulated;

// Tremolo
extern short trem_a1;
extern short trem_a2;
extern short trem_b0;
extern short t1,t2;
extern int tn;
//--------------------------------------------------------------------------//
// Prototypes																//
//--------------------------------------------------------------------------//
// in file Initialisation.c
void Init_EBIU(void);
void Init_Flash(void);
void Init1836(void);
void Init_Sport0(void);
void Init_DMA(void);
void Init_Interrupts(void);
void Enable_DMA_Sport0(void);
void Init_Flags(void);

// file InitFilterCoefs.c
void InitFilterCoefs(void);

// in file Process_data.c
void Process_Data(void);

// in file ISRs.c
EX_INTERRUPT_HANDLER(Sport0_RX_ISR);
EX_INTERRUPT_HANDLER(FlagA_ISR);

#endif //__Talkthrough_DEFINED
