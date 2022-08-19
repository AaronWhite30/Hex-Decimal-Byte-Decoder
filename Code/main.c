#define F_CPU 1000000UL

#include <util/delay.h>
#include <avr/io.h>

#define firstDigitEnable PINC0
#define secondDigitEnable PINC1
#define thirdDigitEnable PINC2
#define displayModePin PINC5

/*uint8_t sevenSegmentBitCodesCommonAnode[16] =   
{
	0b01000000,
	0b11111001,
	0b00100100,
	0b00110000,
	0b00011001,
	0b00010010,
	0b00000010,
	0b11111000,
	0b00000000,
	0b00011000,
	0b00001000,
	0b00000011,
	0b01000110,
	0b00100001,
	0b00000110,
	0b00001110
};*/

uint8_t sevenSegmentBitCodesCommonCathode[16] =
{
	0b10111111,
	0b00000110,
	0b11011011,
	0b11001111,
	0b11100110,
	0b11101101,
	0b11111101,
	0b00000111,
	0b11111111,
	0b11100111,
	0b11110111,
	0b11111100,
	0b10111001,
	0b11011110,
	0b11111001,
	0b11110001
};
void display(uint8_t digit1, uint8_t digit2, uint8_t digit3){
	
	//PORTD = sevenSegmentBitCodesCommonAnode[digit1];
	PORTD = sevenSegmentBitCodesCommonCathode[digit1];
	
	//PORTC &= ~(1<<firstDigitEnable);
	PORTC |= (1<<firstDigitEnable);
	_delay_ms(1);
	//PORTC |= (1<<firstDigitEnable);
	PORTC &= ~(1<<firstDigitEnable);
		
	//PORTD = sevenSegmentBitCodesCommonAnode[digit2];	
	PORTD = sevenSegmentBitCodesCommonCathode[digit2];
	
	//PORTC &= ~(1<<secondDigitEnable);
	PORTC |= (1<<secondDigitEnable);
	_delay_ms(1);
	//PORTC |= (1<<secondDigitEnable);
	PORTC &= ~(1<<secondDigitEnable);
		
	//PORTD = sevenSegmentBitCodesCommonAnode[digit3];
	PORTD = sevenSegmentBitCodesCommonCathode[digit3];
	
	//PORTC &= ~(1<<thirdDigitEnable);
	PORTC |= (1<<thirdDigitEnable);
	_delay_ms(1);
	//PORTC |= (1<<thirdDigitEnable);
	PORTC &= ~(1<<thirdDigitEnable);	
}

int main(void){
	
	DDRD = 0xFF;
	DDRB = 0x00;
	
	DDRC |= (1<<firstDigitEnable) | (1<<secondDigitEnable) | (1<<thirdDigitEnable);	
	DDRC &= ~(1<<displayModePin);
	
	//PORTC |= (1<<firstDigitEnable) | (1<<secondDigitEnable) | (1<<thirdDigitEnable);
	PORTC &= ~(1<<firstDigitEnable);
	PORTC &= ~(1<<secondDigitEnable);
	PORTC &= ~(1<<thirdDigitEnable);
	
    while (1){
		
		//Mode = 1, display hex, Mode = 0, display decimal
		if(PINC & (1<<displayModePin)){
			
			uint8_t low = PINB & 0x0F;
			uint8_t high = PINB >> 4;	
					
			display(low, high, 0);
			
		}else{
			
			uint8_t hexNumber = PINB & 0xFF;
			uint8_t hexDividedByTen = hexNumber / 10;
			uint8_t d1 = hexNumber % 10;
			uint8_t d2 = hexDividedByTen % 10;
			uint8_t d3 = hexDividedByTen / 10;
			
			display(d1, d2, d3);			
		}
			
    }
}

