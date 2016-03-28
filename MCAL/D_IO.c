#include "..\MCAL\D_IO.h"


#define BIT_SET(REG,PIN) REG |=(1<<PIN)
#define BIT_CLEAR(REG,PIN) REG &=~(1<<PIN)

S8_t S8_DIO_init_port(const U8_t PortName, const U8_t value)
{
    S8_t state;
    state = 1;
    switch (PortName)
    {
    case 'A':
    case 'a':
        DDRA = value;
        break;
    case 'B':
    case 'b':
        DDRB = value;
        break;
    case 'C':
    case 'c':
        DDRC = value;
        break;
    case 'D':
    case 'd':
        DDRD = value;
        break;
    default:
        state = -1;
    }
    return (state);
}

S8_t S8_DIO_init_pin(const U8_t PortName, const U8_t PinNumber, const U8_t dir)
{
    U8_t state;
    state = 1;
    if (PinNumber > (REG_PINS - 1))
        state = -1;
    else
    {
        switch (PortName)
        {
        case 'A':
        case 'a':
            switch (dir)
            {
            case OUTPUT:
                BIT_SET(DDRA, PinNumber );
                break;
            case INPUT:
                BIT_CLEAR(DDRA, PinNumber );
                break;
            default:
                break;
            }
            break;

        case 'B':
        case 'b':
            switch (dir)
            {
            case OUTPUT:
                BIT_SET(DDRB, PinNumber) ;
                break;
            case INPUT :
                BIT_CLEAR(DDRB, PinNumber ) ;
                break;
            default:
                break;
            }
            break;

        case 'C':
        case 'c':
            switch (dir)
            {
            case OUTPUT:
                BIT_SET(DDRC, PinNumber );
                break;
            case INPUT:
                BIT_CLEAR(DDRC, PinNumber );
                break;
            default:
                break;
            }
            break;

        case 'D':
        case 'd':
            switch (dir)
            {
            case OUTPUT:
                BIT_SET(DDRD , PinNumber );
                break;
            case INPUT:
                BIT_CLEAR(DDRD , PinNumber );
                break;
            default:
                break;
            }
            break;
        default:
            state = -1;
        }
    }
    return (state);
}

volatile S16_t S16_DIO_read_port(const U8_t PortName)
{
    volatile S16_t state;
    switch (PortName)
    {
    case 'a':
    case 'A':
        state = PINA;
        break;
    case 'B':
    case 'b':
        state = PINB;
        break;
    case 'C':
    case 'c':
        state = PINC;
        break;
    case 'D':
    case 'd':
        state = PIND;
        break;
    default:
        state = -1;
    }
    return (state);
}

volatile S16_t S16_DIO_read_pin(const U8_t PortName, const U8_t pin)
{
    volatile S16_t state;
    if (pin > (REG_PINS - 1))
        state = -1;
    else
    {
        switch (PortName)
        {
        case 'A':
        case 'a':
            state = PINA & (1 << pin);
            break;
        case 'B':
        case 'b':
            state = PINB & (1 << pin);
            break;
        case 'C':
        case 'c':
            state = PINC & (1 << pin);
            break;
        case 'D':
        case 'd':
            state = PIND & (1 << pin);
            break;
        default:
            state = -1;
        }
    }
    return (state) ;
}

S8_t S8_DIO_set_port(const U8_t PortName)
{

    S8_t state;
    state = 1;
    switch (PortName)
    {
    case 'A':
    case 'a':
        PORTA = 0xFF;
        break;
    case 'B':
    case 'b':
        PORTB = 0xFF;
        break;
    case 'C':
    case 'c':
        PORTC = 0xFF;
        break;
    case 'D':
    case 'd':
        PORTD = 0xFF;
        break;
    default:
        state = -1;
    }
    return (state);
}

S8_t S8_DIO_set_pin(const U8_t PortName, const U8_t PinNumber)
{
    S8_t state;
    state = 1;
    if (PinNumber > (REG_PINS - 1))
        state = -1;
    else
    {

        switch (PortName)
        {
        case 'A':
        case 'a':
            BIT_SET(PORTA, PinNumber);
            break;
        case 'B':
        case 'b':
            BIT_SET(PORTB, PinNumber);
            break;
        case 'C':
        case 'c':
            BIT_SET(PORTC, PinNumber);
            break;
        case 'D':
        case 'd':
            PORTD |= (1<<PinNumber);
            break;
        default:
            state = -1;

        }

    }
    return (state);

}

S8_t S8_DIO_clear_port(const U8_t PortName)
{
    S8_t state;
    state = -1;
    switch (PortName)
    {
    case 'A':
    case 'a':
        PORTA = 0x00;
        break;
    case 'B':
    case 'b':
        PORTB = 0x00;
        break;
    case 'C':
    case 'c':
        PORTC = 0x00;
        break;
    case 'D':
    case 'd':
        PORTD = 0x00;
        break;
    default:
        state = -1;
    }
    return (state);
}

S8_t S8_DIO_clear_pin(const U8_t PortName, const U8_t PinNumber)
{

    S8_t state;
    state = -1;
    if (PinNumber > (REG_PINS - 1))
        state = -1;
    else
    {
        switch (PortName)
        {
        case 'A':
        case 'a':
            BIT_CLEAR(PORTA , PinNumber);
            break;
        case 'B':
        case 'b':
            BIT_CLEAR(PORTB , PinNumber);
            break;
        case 'C':
        case 'c':
            BIT_CLEAR(PORTC , PinNumber );
            break;
        case 'D':
        case 'd':
            BIT_CLEAR(PORTD , PinNumber);
            break;
        default:
            state = -1;
        }
    }
    return (state) ;
}

S8_t S8_DIO_write_port(const U8_t PortName, const U8_t value)
{
    S8_t state;
    state = 1;
    switch (PortName)
    {
    case 'A':
    case 'a':
        PORTA = value;
        break;
    case 'B':
    case 'b':
        PORTB = value;
        break;
    case 'C':
    case 'c':
        PORTC = value;
        break;
    case 'D':
    case 'd':
        PORTD = value;
        break;
    default:
        state = -1;
    }
    return (state) ;
}

S8_t S8_DIO_write_pin(const U8_t PortName, const U8_t PinNumber, const U8_t dir)
{
    U8_t state;
    state = 1;
    if (PinNumber > (REG_PINS - 1))
        state = -1;
    else
    {
        switch (PortName)
        {
        case 'A':
        case 'a':
            switch (dir)
            {
            case HIGH :
                BIT_SET(PORTA, PinNumber ) ;
                break;
            case LOW :
                BIT_CLEAR(PORTA, PinNumber ) ;
                break;

            default:
                break;
            }
            break;

        case 'B':
        case 'b':
            switch (dir)
            {
            case HIGH :
                BIT_SET(PORTB, PinNumber ) ;
                break;

            case LOW :
                BIT_CLEAR(PORTB, PinNumber ) ;
                break;
            default:
                break;
            }
            break;

        case 'C':
        case 'c':
            switch (dir)
            {
            case HIGH :
                BIT_SET(PORTC , PinNumber ) ;
                break;
            case LOW :
                BIT_CLEAR(PORTC , PinNumber ) ;
                break;
            default:
                break;
            }
            break;

        case 'D':
        case 'd':
            switch (dir)
            {
            case HIGH :
                BIT_SET( PORTD , PinNumber ) ;
                break;
            case LOW :
                BIT_CLEAR(PORTD , PinNumber );
                break;
            default:
                break;
            }
            break;
        default:
            state = -1;
        }
    }
    return (state) ;
}

S8_t S8_DIO_toggle_pin(const U8_t PortName, const U8_t PinNumber)
{
    S8_t state;
    state = -1;
    if (PinNumber > (REG_PINS - 1))
        state = -1;
    else
    {
        switch (PortName)
        {
        case 'A':
        case 'a':
            PORTA ^= (1 << PinNumber);
            break;
        case 'B':
        case 'b':
            PORTB ^= (1 << PinNumber);
            break;
        case 'C':
        case 'c':
            PORTC ^= (1<< PinNumber );
            break;
        case 'D':
        case 'd':
            PORTD ^= (1 << PinNumber);
            break;
        default:
            state = -1;
        }
    }
    return (state) ;
}

S8_t S8_DIO_init_output_port_mask(const U8_t PortName, const U8_t mask)
{
    S8_t state;
    state = 1;
    switch (PortName)
    {
    case 'A':
    case 'a':
        DDRA |= mask;
        break;
    case 'B':
    case 'b':
        DDRB |= mask;
        break;
    case 'C':
    case 'c':
        DDRC |= mask;
        break;
    case 'D':
    case 'd':
        DDRD |= mask;
        break;
    default:
        state = -1;
    }
    return (state);

}

S8_t S8_DIO_init_input_port_mask(const U8_t PortName, const U8_t mask)
{

    S8_t state;
    state = 1;
    switch (PortName)
    {
    case 'A':
    case 'a':
        DDRA &= mask;
        break;
    case 'B':
    case 'b':
        DDRB &= mask;
        break;
    case 'C':
    case 'c':
        DDRC &= mask;
        break;
    case 'D':
    case 'd':
        DDRD &= mask;
        break;
    default:
        state = -1;
    }
    return (state);
}

S8_t S8_DIO_set_port_mask(const U8_t PortName, const U8_t mask)
{
    S8_t state;
    state = 1;
    switch (PortName)
    {
    case 'A':
    case 'a':
        PORTA |= mask;
        break;
    case 'B':
    case 'b':
        PORTB |= mask;
        break;
    case 'C':
    case 'c':
        PORTC |= mask;
        break;
    case 'D':
    case 'd':
        PORTD |= mask;
        break;
    default:
        state = -1;
    }
    return (state);

}

S8_t S8_DIO_clear_port_mask(const U8_t PortName, const U8_t mask)
{
    S8_t state;
    state = 1;
    switch (PortName)
    {
    case 'A':
    case 'a':
        PORTA &= mask;
        break;
    case 'B':
    case 'b':
        PORTB &= mask;
        break;
    case 'C':
    case 'c':
        PORTC &= mask;
        break;
    case 'D':
    case 'd':
        PORTD &= mask;
        break;
    default:
        state = -1;
    }
    return (state);

}


S16_t S16_DIO_read_port_mask(const U8_t PortName, const S16_t mask)
{
	S16_t state;
	    switch (PortName)
	    {
	    case 'A':
	    case 'a':
	       state= PINA & mask;
	        break;
	    case 'B':
	    case 'b':
	    	state= PINB & mask;
	        break;
	    case 'C':
	    case 'c':
	    	state= PINC & mask;
	        break;
	    case 'D':
	    case 'd':
	    	state= PIND & mask;
	        break;
	    default:
	        state = -1;
	    }
	    return (state);

}

