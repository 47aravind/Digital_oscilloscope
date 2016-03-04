#include <platform.h>
#include <stdint.h>

#define N 12								// Choosing 12 bit ADC

#define		AN0  0x0001						// For choosing channels
#define		AN1  0x0002
#define		AN2  0x0004
#define		AN3  0x0008

void adcInit(void); 						// This function initializes the ADC
void adcRead(int); 							// This function will read an analog value from the specified channel 
float convertADC(int);						// This function converts the ADC value to Vref value