#ifndef MiDefinicion
#define MiDefinicion
// Ports to manipulate the pins(B,C,D) to in/out are DDRx, to set High/low is PORTx, and to read is PINx
//default states on reset or power on.
//DDRB  =B0000,0000   DDRC =B0000,0000  DDRD =B0000,0000 
//PORTB =B0000,0000   PORTC=B0000,0000  PORTD=B0000,0000
//PIND  =B0000,0000   PIND =B0000,0000  PIND =B0000,0000
//(uint8_t) is a variable size 8 bits example PORTB is one by thi is =B00000000; 
// turn something on: |= (1<<bit) is the same as PORTB |=(1<<PB5) = B00000000 | B00010000
// turn something of: &= ~(1<<bit) is the same as PORTB &= ~(1<<PB5) = B00010000 & B11101111
// read state (PINB & (1<<PB5)) gives true any number not 0 or false the bit is not set so 0.
//Map in arduino and the actual bare metal name
//Digital 0  = PD0
//Digital 1  = PD1
//Digital 2  = PD2
//Digital 3  = PD3
//Digital 4  = PD4
//Digital 5  = PD5
//Digital 6  = PD6
//Digital 7  = PD7
//Digital 8  = PB0
//Digital 9  = PB1
//Digital 10 = PB2
//Digital 11 = PB3
//Digital 12 = PB4
//Digital 13 = PB5
//A0 PC0
//A1 PC1
//A2 PC2
//A3 PC3
//A4 PC4
//A5 PC5

/*Address,Name,Bit 7,Bit 6,Bit 5,Bit 4,Bit 3,Bit 2,Bit 1,Bit 0,Page
(0xC6),UDR0,USART I/O Data Register,,,,,,,,200
(0xC5),UBRR0H,USART Baud Rate Register High,,,,,,,,204
(0xC4),UBRR0L,USART Baud Rate Register Low,,,,,,,,204
(0xC2),UCSR0C,UMSEL01,UMSEL00,UPM01,UPM00,USBS0,UCSZ01 /UDORD0,UCSZ00 / UCPHA0,UCPOL0,202/213
(0xC1),UCSR0B,RXCIE0,TXCIE0,UDRIE0,RXEN0,TXEN0,UCSZ02,RXB80,TXB80,201
(0xC0),UCSR0A,RXC0,TXC0,UDRE0,FE0,DOR0,UPE0,U2X0,MPCM0,200
(0xBD),TWAMR,TWAM6,TWAM5,TWAM4,TWAM3,TWAM2,TWAM1,TWAM0,–,242
(0xBC),TWCR,TWINT,TWEA,TWSTA,TWSTO,TWWC,TWEN,–,TWIE,239
(0xBB),TWDR,2-wire Serial Interface Data Register,,,,,,,,241
(0xBA),TWAR,TWA6,TWA5,TWA4,TWA3,TWA2,TWA1,TWA0,TWGCE,241
(0xB9),TWSR,TWS7,TWS6,TWS5,TWS4,TWS3,–,TWPS1,TWPS0,240
(0xB8),TWBR,2-wire Serial Interface Bit Rate Register,,,,,,,,239
(0xB6),ASSR,–,EXCLK,AS2,TCN2UB,OCR2AUB,OCR2BUB,TCR2AUB,TCR2BUB,167
(0xB4),OCR2B,Timer/Counter2 Output Compare Register B,,,,,,,,166
(0xB3),OCR2A,Timer/Counter2 Output Compare Register A,,,,,,,,166
(0xB2),TCNT2,Timer/Counter2 (8-bit),,,,,,,,166
(0xB1),TCCR2B,FOC2A,FOC2B,–,–,WGM22,CS22,CS21,CS20,165
(0xB0),TCCR2A,COM2A1,COM2A0,COM2B1,COM2B0,–,–,WGM21,WGM20,162
(0x8B),OCR1BH,Timer/Counter1 - Output Compare Register B High Byte,,,,,,,,144
(0x8A),OCR1BL,Timer/Counter1 - Output Compare Register B Low Byte,,,,,,,,144
(0x89),OCR1AH,Timer/Counter1 - Output Compare Register A High Byte,,,,,,,,144
(0x88),OCR1AL,Timer/Counter1 - Output Compare Register A Low Byte,,,,,,,,144
(0x87),ICR1H,Timer/Counter1 - Input Capture Register High Byte,,,,,,,,144
(0x86),ICR1L,Timer/Counter1 - Input Capture Register Low Byte,,,,,,,,144
(0x85),TCNT1H,Timer/Counter1 - Counter Register High Byte,,,,,,,,143
(0x84),TCNT1L,Timer/Counter1 - Counter Register Low Byte,,,,,,,,143
(0x82),TCCR1C,FOC1A,FOC1B,–,–,–,–,–,–,143
(0x81),TCCR1B,ICNC1,ICES1,–,WGM13,WGM12,CS12,CS11,CS10,142
(0x80),TCCR1A,COM1A1,COM1A0,COM1B1,COM1B0,–,–,WGM11,WGM10,140
(0x7F),DIDR1,–,–,–,–,–,–,AIN1D,AIN0D,245
(0x7E),DIDR0,–,–,ADC5D,ADC4D,ADC3D,ADC2D,ADC1D,ADC0D,260
(0x7C),ADMUX,REFS1,REFS0,ADLAR,–,MUX3,MUX2,MUX1,MUX0,257
(0x7B),ADCSRB,–,ACME,–,–,–,ADTS2,ADTS1,ADTS0,260
(0x7A),ADCSRA,ADEN,ADSC,ADATE,ADIF,ADIE,ADPS2,ADPS1,ADPS0,258
(0x79),ADCH,ADC Data Register High byte,,,,,,,,259
(0x78),ADCL,ADC Data Register Low byte,,,,,,,,259
(0x70),TIMSK2,–,–,–,–,–,OCIE2B,OCIE2A,TOIE2,166
(0x6F),TIMSK1,–,–,ICIE1,–,–,OCIE1B,OCIE1A,TOIE1,144
(0x6E),TIMSK0,–,–,–,–,–,OCIE0B,OCIE0A,TOIE0,118
(0x6D),PCMSK2,PCINT23,PCINT22,PCINT21,PCINT20,PCINT19,PCINT18,PCINT17,PCINT16,83
(0x6C),PCMSK1,–,PCINT14,PCINT13,PCINT12,PCINT11,PCINT10,PCINT9,PCINT8,83
(0x6B),PCMSK0,PCINT7,PCINT6,PCINT5,PCINT4,PCINT3,PCINT2,PCINT1,PCINT0,83
(0x69),EICRA,–,–,–,–,ISC11,ISC10,ISC01,ISC00,80
(0x68),PCICR,–,–,–,–,–,PCIE2,PCIE1,PCIE0,
(0x66),OSCCAL,Oscillator Calibration Register,,,,,,,,46
(0x64),PRR,PRTWI,PRTIM2,PRTIM0,–,PRTIM1,PRSPI,PRUSART0,PRADC,51
(0x61),CLKPR,CLKPCE,–,–,–,CLKPS3,CLKPS2,CLKPS1,CLKPS0,46
(0x60),WDTCSR,WDIF,WDIE,WDP3,WDCE,WDE,WDP2,WDP1,WDP0,63
0x3F (0x5F),SREG,I,T,H,S,V,N,Z,C,19
0x3E (0x5E),SPH,–,–,–,–,–,(SP10) 5.,SP9,SP8,22
0x3D (0x5D),SPL,SP7,SP6,SP5,SP4,SP3,SP2,SP1,SP0,22
0x37 (0x57),SPMCSR,SPMIE,(RWWSB)5.,SIGRD,(RWWSRE)5.,BLBSET,PGWRT,PGERS,SPMEN,287
0x35 (0x55),MCUCR,–,BODS(6),BODSE(6),PUD,–,–,IVSEL,IVCE,54/77/100
0x34 (0x54),MCUSR,–,–,–,–,WDRF,BORF,EXTRF,PORF,63
0x33 (0x53),SMCR,–,–,–,–,SM2,SM1,SM0,SE,49
0x30 (0x50),ACSR,ACD,ACBG,ACO,ACI,ACIE,ACIC,ACIS1,ACIS0,244
0x2E (0x4E),SPDR,SPI Data Register,,,,,,,,178
0x2D (0x4D),SPSR,SPIF,WCOL,–,–,–,–,–,SPI2X,177
0x2C (0x4C),SPCR,SPIE,SPE,DORD,MSTR,CPOL,CPHA,SPR1,SPR0,176
0x2B (0x4B),GPIOR2,General Purpose I/O Register 2,,,,,,,,35
0x2A (0x4A),GPIOR1,General Purpose I/O Register 1,,,,,,,,35
0x28 (0x48),OCR0B,Timer/Counter0 Output Compare Register B,,,,,,,,
0x27 (0x47),OCR0A,Timer/Counter0 Output Compare Register A,,,,,,,,
0x26 (0x46),TCNT0,Timer/Counter0 (8-bit),,,,,,,,
0x25 (0x45),TCCR0B,FOC0A,FOC0B,–,–,WGM02,CS02,CS01,CS00,
0x24 (0x44),TCCR0A,COM0A1,COM0A0,COM0B1,COM0B0,–,–,WGM01,WGM00,
0x23 (0x43),GTCCR,TSM,–,–,–,–,–,PSRASY,PSRSYNC,149/168
0x22 (0x42),EEARH,(EEPROM Address Register High Byte) 5.,,,,,,,,31
0x21 (0x41),EEARL,EEPROM Address Register Low Byte,,,,,,,,31
0x20 (0x40),EEDR,EEPROM Data Register,,,,,,,,31
0x1F (0x3F),EECR,–,–,EEPM1,EEPM0,EERIE,EEMPE,EEPE,EERE,31
0x1E (0x3E),GPIOR0,General Purpose I/O Register 0,,,,,,,,35
0x1D (0x3D),EIMSK,–,–,–,–,–,–,INT1,INT0,81
0x1C (0x3C),EIFR,–,–,–,–,–,–,INTF1,INTF0,81
0x1B (0x3B),PCIFR,–,–,–,–,–,PCIF2,PCIF1,PCIF0,
0x17 (0x37),TIFR2,–,–,–,–,–,OCF2B,OCF2A,TOV2,167
0x16 (0x36),TIFR1,–,–,ICF1,–,–,OCF1B,OCF1A,TOV1,145
0x15 (0x35),TIFR0,–,–,–,–,–,OCF0B,OCF0A,TOV0,
0x0B (0x2B),PORTD,PORTD7,PORTD6,PORTD5,PORTD4,PORTD3,PORTD2,PORTD1,PORTD0,101
0x0A (0x2A),DDRD,DDD7,DDD6,DDD5,DDD4,DDD3,DDD2,DDD1,DDD0,101
0x09 (0x29),PIND,PIND7,PIND6,PIND5,PIND4,PIND3,PIND2,PIND1,PIND0,101
0x08 (0x28),PORTC,–,PORTC6,PORTC5,PORTC4,PORTC3,PORTC2,PORTC1,PORTC0,100
0x07 (0x27),DDRC,–,DDC6,DDC5,DDC4,DDC3,DDC2,DDC1,DDC0,100
0x06 (0x26),PINC,–,PINC6,PINC5,PINC4,PINC3,PINC2,PINC1,PINC0,101
0x05 (0x25),PORTB,PORTB7,PORTB6,PORTB5,PORTB4,PORTB3,PORTB2,PORTB1,PORTB0,100
0x04 (0x24),DDRB,DDB7,DDB6,DDB5,DDB4,DDB3,DDB2,DDB1,DDB0,100
0x03 (0x23),PINB,PINB7,PINB6,PINB5,PINB4,PINB3,PINB2,PINB1,PINB0,100.          

Register Relationship Graph (Hierarchical Tree)
EEPROM (Non-volatile memory management)
├── EEARH/EEARL (Address registers - set EEPROM address)
├── EEDR (Data register - read/write data)
└── EECR (Control register - mode, enable read/write)
Clock (System clock configuration)
├── OSCCAL (Calibration for internal RC oscillator)
└── CLKPR (Prescaler for system clock division)
Power (Sleep and power reduction modes)
├── SMCR (Sleep mode control)
├── MCUCR (BOD sleep, pull-up disable)
└── PRR (Power reduction for peripherals)
System Control (Reset and watchdog)
├── MCUSR (Reset status flags)
└── WDTCSR (Watchdog control and prescaler)
Interrupts (Global and external/pin change interrupts)
├── MCUCR (Interrupt vector select)
├── EICRA (External interrupt sense control)
├── EIMSK (External interrupt mask)
├── EIFR (External interrupt flags)
├── PCICR (Pin change interrupt control)
├── PCIFR (Pin change interrupt flags)
└── PCMSK0/PCMSK1/PCMSK2 (Pin change masks for ports)
I/O Ports (Digital pin control)
├── MCUCR (Pull-up disable)
├── PORTB/DDRB/PINB (Port B data/direction/input)
├── PORTC/DDRC/PINC (Port C data/direction/input)
└── PORTD/DDRD/PIND (Port D data/direction/input)
Timer0 (8-bit timer with PWM)
├── TCCR0A/TCCR0B (Control - mode, prescaler, compare output)
├── TCNT0 (Counter value)
├── OCR0A/OCR0B (Output compare values)
├── TIMSK0 (Interrupt mask)
└── TIFR0 (Interrupt flags)
Timer1 (16-bit timer with PWM and input capture)
├── TCCR1A/TCCR1B/TCCR1C (Control - mode, prescaler, force compare)
├── TCNT1H/TCNT1L (Counter value)
├── OCR1AH/OCR1AL/OCR1BH/OCR1BL (Output compare values)
├── ICR1H/ICR1L (Input capture value)
├── TIMSK1 (Interrupt mask)
└── TIFR1 (Interrupt flags)
Timer2 (8-bit timer with PWM, async operation)
├── TCCR2A/TCCR2B (Control - mode, prescaler)
├── TCNT2 (Counter value)
├── OCR2A/OCR2B (Output compare values)
├── ASSR (Async status and control)
├── TIMSK2 (Interrupt mask)
└── TIFR2 (Interrupt flags)
Prescalers (Shared timer prescaler reset)
└── GTCCR (Synchronization and reset for Timer0/1/2)
SPI (Serial peripheral interface)
├── SPCR (Control - enable, mode, clock rate)
├── SPSR (Status - interrupt flag, double speed)
└── SPDR (Data register)
USART (Serial communication)
├── UDR0 (Data register)
├── UCSR0A (Status - flags for complete, empty)
├── UCSR0B (Control - enable RX/TX, interrupts)
├── UCSR0C (Control - mode, parity, stop bits)
└── UBRR0H/UBRR0L (Baud rate)
TWI (I2C/Two-wire interface)
├── TWBR (Bit rate)
├── TWCR (Control - enable, start/stop, interrupt)
├── TWSR (Status and prescaler)
├── TWDR (Data register)
├── TWAR (Slave address)
└── TWAMR (Address mask)
Analog Comparator (Compare analog inputs)
├── ACSR (Control - enable, bandgap, interrupt mode)
└── DIDR1 (Digital input disable for AIN0/1)
ADC (Analog-to-digital converter)
├── ADMUX (Multiplexer - channel, reference)
├── ADCSRA (Control - enable, start, prescaler)
├── ADCSRB (Trigger source)
├── ADCH/ADCL (Data result)
└── DIDR0 (Digital input disable for ADC pins)
debugWIRE (On-chip debugging)
└── DWDR (Data register for communication)
Self Programming (Flash self-programming)
└── SPMCSR (Control - enable SPM, page erase/write)
General Purpose (User-defined I/O registers)
├── GPIOR0
├── GPIOR1
└── GPIOR2.      

Vector No.,Program Address,Source,Interrupt Definition,Enable Register and Bit(s)
1,0x0000,RESET,"External Pin, Power-on Reset, Brown-out Reset and Watchdog System Reset",N/A (always active)
2,0x0002,INT0,External Interrupt Request 0,             EIMSK.INT0
3,0x0004,INT1,External Interrupt Request 1,             EIMSK.INT1
4,0x0006,PCINT0,Pin Change Interrupt Request 0,         PCICR.PCIE0 (and PCMSK0 bits for specific pins)
5,0x0008,PCINT1,Pin Change Interrupt Request 1,         PCICR.PCIE1 (and PCMSK1 bits for specific pins)
6,0x000A,PCINT2,Pin Change Interrupt Request 2,         PCICR.PCIE2 (and PCMSK2 bits for specific pins)
7,0x000C,WDT,Watchdog Time-out Interrupt,               WDTCSR.WDIE
8,0x000E,TIMER2 COMPA,Timer/Counter2 Compare Match A,   TIMSK2.OCIE2A
9,0x0010,TIMER2 COMPB,Timer/Counter2 Compare Match B,   TIMSK2.OCIE2B
10,0x0012,TIMER2 OVF,Timer/Counter2 Overflow,           TIMSK2.TOIE2
11,0x0014,TIMER1 CAPT,Timer/Counter1 Capture Event,     TIMSK1.ICIE1
12,0x0016,TIMER1 COMPA,Timer/Counter1 Compare Match A,  TIMSK1.OCIE1A
13,0x0018,TIMER1 COMPB,Timer/Counter1 Compare Match B,  TIMSK1.OCIE1B
14,0x001A,TIMER1 OVF,Timer/Counter1 Overflow,           TIMSK1.TOIE1
15,0x001C,TIMER0 COMPA,Timer/Counter0 Compare Match A,  TIMSK0.OCIE0A
16,0x001E,TIMER0 COMPB,Timer/Counter0 Compare Match B,  TIMSK0.OCIE0B
17,0x0020,TIMER0 OVF,Timer/Counter0 Overflow,           TIMSK0.TOIE0
18,0x0022,"SPI, STC",SPI Serial Transfer Complete,      SPCR.SPIE
19,0x0024,"USART, RX",USART Rx Complete,                UCSR0B.RXCIE0
20,0x0026,"USART, UDRE","USART, Data Register Empty",   UCSR0B.UDRIE0
21,0x0028,"USART, TX","USART, Tx Complete",             UCSR0B.TXCIE0
22,0x002A,ADC,ADC Conversion Complete,                  ADCSRA.ADIE
23,0x002C,EE READY,EEPROM Ready,                        EECR.EERIE
24,0x002E,ANALOG COMP,Analog Comparator,                ACSR.ACIE
25,0x0030,TWI,2-wire Serial Interface,                  TWCR.TWIE
26,0x0032,SPM READY,Store Program Memory Ready,         SPMCSR.SPMIE  */
#endif