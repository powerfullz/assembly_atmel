// AVR C code snippet with comments

#define F_CPU 16000000UL    // CPU frequency in Hz
#include <avr/io.h>         // AVR IO library
#include <util/delay.h>     // Delay library
#include <stdio.h>          // Standard IO library
#include <avr/interrupt.h>  // AVR interrupt library
#define BAUD 9600           // Baud rate
#include <util/setbaud.h>   // Set baud rate utility

void UARTinit();                    // Initialize UART
void USART_tx_string(char *data);   // Send a string over UART

void help();                        // Display help menu
void LED5on();                      // Turn on LED5
void LED5off();                     // Turn off LED5
void beginBlink();                  // Begin blinking LED
void stopBlink();                   // Stop blinking LED
void beginFade();                   // Begin fading LED intensity
void stopFade();                    // Stop fading LED intensity
void displayStatus();               // Display switch status

volatile int blinkBool;             // Blinking boolean variable
volatile int fadeBool;              // Fading boolean variable
volatile double dutyValue;          // Duty cycle value for fading

int main(void)
{
	DDRB = 0xFF;    // Set PORTB as output
	DDRC = 0x00;    // Set PORTC as input
	PORTC = 0xFF;   // Enable pull-up resistors on PORTC

	// Normal mode (default)
	// 1024 prescaler
	TCCR1B |= (1 << CS12) | (1 << CS10);

	// Normal mode (default)
	// 1024 prescaler
	TCCR0B |= (1 << CS12) | (1 << CS10);

	UARTinit();     // Initialize UART
	help();         // Display help menu
	sei();          // Enable interrupts
	while (1)
	{
		// Blink PB3 at 1 Hz if enabled
		if (TCNT1 == 7811)
		{
			if (blinkBool == 1)
			{
				PORTB ^= (1 << 5);  // Toggle PB5
			}
			TCNT1 = 0;
		}
		if (blinkBool == 0)
		{
			PORTB &= ~(1 << 5);     // Turn off PB5
		}

		// Blinks PB1 at 200 Hz if enabled with a duty cycle decreasing from 100% to 0% over 2 seconds
		// This turns off the LED and runs earlier the lower the duty cycle is
		if (TCNT0 == floor(77 * dutyValue))
		{
			PORTB &= ~(1 << 5);     // Turn off PB5
		}

		// This turns on the LED when enabled.
		// While debugging, I had to add the second term of the conditional, likely due to rounding issues
		if (TCNT0 == 77)
		{
			if ((fadeBool == 1) & (dutyValue > 0.0025))
			{
				PORTB |= (1 << 5);  // Turn on PB5
			}
			TCNT0 = 0;
			if (dutyValue != 0)
			{
				dutyValue = dutyValue - 0.0025;
			}
		}
	}
}

void UARTinit()
{
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	// Set 8 bit
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
	// Set 1 stop bit (default)
	// Disable parity (default)
	// Set asynchronous (default)
	// Enable RX interrupt
	UCSR0B |= (1 << RXCIE0);
	// Enable TX/RX
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
}

// Sends a string of characters over TX
void USART_tx_string(char *data)
{
	// Repeat until input string is empty
	while (*data != '\0')
	{
		// Wait for data register to be empty
		while ((UCSR0A & (1 << UDRE0)) != (1 << UDRE0))
		{
		}
		UDR0 = *data;
		data++;
	}
}

// UART RX interrupt service routine
ISR(USART_RX_vect)
{
	switch (UDR0)
	{
		case 'h':
		help();
		break;
		case 'o':
		LED5on();
		break;
		case 'O':
		LED5off();
		break;
		case 'p':
		beginBlink();
		break;
		case 'P':
		stopBlink();
		break;
		case 'f':
		beginFade();
		break;
		case 'F':
		stopFade();
		break;
		case 'b':
		displayStatus();
		break;
		default:
		break;
	}
}

void help()
{
	USART_tx_string("\n\n");
	USART_tx_string("'h' - help \n");
	USART_tx_string("'o' - turn on LED0\n");
	USART_tx_string("'O' - turn off LED0\n");
	USART_tx_string("'p' - blink LED1\n");
	USART_tx_string("'P' - stop blinking LED1\n");
	USART_tx_string("'f' - fade intensity of LED2\n");
	USART_tx_string("'F' - turn off LED2\n");
	USART_tx_string("'b' - display switch status\n");
}

void LED5on()
{
	PORTB |= (1 << 5);  // Turn on LED5 (PB5)
}

void LED5off()
{
	PORTB &= ~(1 << 5);  // Turn off LED5 (PB5)
}

void beginBlink()
{
	blinkBool = 1;  // Set blink boolean to enable blinking
}

void stopBlink()
{
	blinkBool = 0;  // Clear blink boolean to stop blinking
}

void beginFade()
{
	dutyValue = 1;  // Set initial duty cycle value to 100%
	fadeBool = 1;  // Set fade boolean to enable fading
}

void stopFade()
{
	fadeBool = 0;  // Clear fade boolean to stop fading
}

void displayStatus()
{
	USART_tx_string("\n\n");
	if ((PINC & (1 << 1)) == (1 << 1))
	{
		USART_tx_string("switch is on");
		while ((PINC & (1 << 1)) == (1 << 1))
		{
		}
	}
	else
	{
		USART_tx_string("switch is off");
		while ((PINC & (1 << 1)) == (0 << 1))
		{
		}
	}
}
