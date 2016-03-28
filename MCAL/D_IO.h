#ifndef MCAL_D_IO_H_
#define MCAL_D_IO_H_
#include "..\ServiceLayer\stdTypes.h"
#include <avr/io.h>
S8_t S8_DIO_init_port(const U8_t PortName , const U8_t value) ;
S8_t S8_DIO_init_pin(const U8_t PortName,const U8_t  PinNumber, const U8_t dir) ;
volatile S16_t S16_DIO_read_port(const U8_t PortName) ;
volatile S16_t S16_DIO_read_pin(const U8_t   PortName,const U8_t pin) ;
S8_t S8_DIO_set_port( const U8_t  PortName) ;
S8_t S8_DIO_set_pin (const U8_t  PortName , const U8_t PinNumber) ;
S8_t S8_DIO_clear_port (const U8_t PortName ) ;
S8_t S8_DIO_clear_pin (const U8_t PortName , const U8_t PinNumber) ;
S8_t S8_DIO_write_port(const U8_t PortName , const U8_t value) ;
S8_t S8_DIO_write_pin(const U8_t PortName,const U8_t  PinNumber, const U8_t dir) ;
S8_t S8_DIO_toggle_pin(const U8_t PortName , const U8_t PinNumber) ;
S8_t S8_DIO_init_output_port_mask(const U8_t PortName , const U8_t mask );
S8_t S8_DIO_init_input_port_mask(const U8_t PortName , const U8_t mask );
S8_t S8_DIO_set_port_mask(const U8_t PortName ,const U8_t mask );
S8_t S8_DIO_clear_port_mask(const U8_t  PortName , const U8_t mask );
S16_t S16_DIO_read_port_mask(const U8_t PortName, const S16_t mask);
#endif // D_IO_H
