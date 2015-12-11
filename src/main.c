#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>

#define BLUE    0x01 
#define RED     0x02 
#define PURPLE  0x03 
#define GREEN   0x04 
#define CYAN    0x05 
#define YELLOW  0x06 
#define WHITE   0x07 
volatile unsigned int switchstate = 0;

void setup()
{
    char DDR_Switch = 0x20; 
    DDRB |= DDR_Switch;
    PORTB &= ~DDR_Switch; 
    GIMSK = 0b00100000;    // turns on pin change interrupts
    PCMSK = 0b00100000;    // turn on interrupts on pins PB0, PB1, &amp; PB4
    sei();                 // enables interrupts
    return;
}

ISR(PCINT0_vect)
{
        cli(); 
        _delay_loop_2(1000);
        if(switchstate > 8){
            switchstate = 0;
        }
        else
        {
            switchstate++;
        }
        sei();
        return;
}

int main (void)
{
    unsigned int i;
    char DDR_EYE = 0x7;
    char DDR_LEDS1 = 0x08;
    char DDR_LEDS0 = 0x10;
    char DDR_LEDS = 0x18;
    char DDR_Switch = 0x20; 
    setup(); 
    DDRB |= DDR_EYE | DDR_LEDS; 
    for (;;) {
        switch(switchstate)
        {
        case 0: 
            //flashy mode
                PORTB &= ~DDR_LEDS; 
                //DDRB &= ~DDR_LEDS;
                PORTB &= ~WHITE; 
                PORTB ^= GREEN; //turn on green 
                _delay_loop_2(40000);
                _delay_loop_2(40000);
                _delay_loop_2(40000);
                _delay_loop_2(40000);
                _delay_loop_2(40000);
                PORTB &= ~WHITE; 
                PORTB ^= RED; //turn on red
                _delay_loop_2(40000);
                _delay_loop_2(40000);
                _delay_loop_2(40000);
                _delay_loop_2(40000);
                _delay_loop_2(40000);
                PORTB |= DDR_LEDS; 
                PORTB &= ~WHITE; 
                PORTB ^= BLUE; //turn on blue
                _delay_loop_2(40000);
                _delay_loop_2(40000);
                _delay_loop_2(40000);
                _delay_loop_2(40000);
                _delay_loop_2(40000);
            break;
        case 1:
            PORTB |= DDR_LEDS;
            PORTB |= WHITE; 
            PORTB &= ~RED; 
            break;
        case 2:
            PORTB &= ~DDR_LEDS;
            PORTB |= WHITE; 
            PORTB &= ~GREEN;
            break;
        case 3:
            PORTB |= DDR_LEDS;
            PORTB |= WHITE; 
            PORTB &= ~BLUE;
            break;
        case 4:
            PORTB &= ~DDR_LEDS;
            PORTB |= WHITE; 
            PORTB &= ~PURPLE;
            break;
        case 5:
            PORTB |= DDR_LEDS;
            PORTB |= WHITE; 
            PORTB &= ~CYAN;
            break;
        case 6:
            PORTB &= ~DDR_LEDS;
            PORTB |= WHITE; 
            PORTB &= ~YELLOW;
            break;
        case 7:
            PORTB |= DDR_LEDS;
            PORTB |= WHITE; 
            PORTB &= ~WHITE;
            break;
        case 8:
                PORTB &= ~DDR_LEDS; 
                //DDRB &= ~DDR_LEDS;
                PORTB &= ~WHITE; 
                PORTB ^= GREEN; //turn on green 
                _delay_loop_2(65535);
                PORTB &= ~WHITE; 
                PORTB ^= RED; //turn on red
                _delay_loop_2(65535);
                PORTB |= DDR_LEDS; 
                PORTB &= ~WHITE; 
                PORTB ^= BLUE; //turn on blue
                _delay_loop_2(65535);
            break;
        default:
            PORTB |= DDR_LEDS;
            PORTB |= WHITE; 
            PORTB &= ~GREEN;
            break; 
        }
    } 
    return 0;
}
