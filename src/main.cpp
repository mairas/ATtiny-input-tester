#include <Arduino.h>
#include <avr/io.h>

// ATtiny pin tester: toggle the output pin in a pattern
// depending on the state of the other PORTB pins

#define OUTPUT PB4 // pin 3 (output)

#define NOP __asm__ __volatile__ ("nop\n\t")  // alternate form is just("nop")

void set_isv_low() {
  PORTB &= ~_BV(OUTPUT);
}

void set_isv_high() {
  PORTB |= _BV(OUTPUT);
}

void setup() {
  // put your setup code here, to run once:

  // set all pins except INV_SENSE_VCC to input (high impedance)
  DDRB = _BV(OUTPUT);
  set_isv_low();
  }

void flash(uint8_t n, int dur=100) {
  for (uint8_t i=0 ; i<n ; i++) {
    set_isv_high();
    delay(dur);
    set_isv_low();
    delay(dur);
  }
}

void loop() {
  for (int i=0 ; i<=5 ; i++) {
    // indicate the current pin
    flash(i);
    // one long flash if the pin is on
    if (PINB & _BV(i)) {
      flash(1, 400);
    } else {
      delay(800);
    }
  }
}
