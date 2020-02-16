/**
   Nano LFO
   2 Channel LFO with multiple waveforms
   - One channel fixed (Sine, triangle.... you pick and hard code it)
   - Other channel Selectable
     - Sine
     - Triangle
     - Ramp up
     - Ramp Down
     - Psycho 1 and 2

   Improvements to do
   Add decaying wave
   https://daycounter.com/Calculators/Decaying-Wave-Generator-Calculator.phtml

   fast pwm
   fast read of analog pin
   http://yaab-arduino.blogspot.com/2015/02/fast-sampling-from-analog-input.html
   This would ont be important if you had a modulation going to this.

   Sync might be nice


   This is set up for two LFOs because I have the room for it, but you could build
   a fine LFO with just one.

   Rob Stave (Rob the fiddler) ccby 2020
*/



uint8_t  triangle_wave[256] = {
  0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10,
  0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20,
  0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30,
  0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40,
  0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50,
  0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60,
  0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70,
  0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e, 0x80,
  0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d, 0x8f,
  0x91, 0x93, 0x95, 0x97, 0x99, 0x9b, 0x9d, 0x9f,
  0xa1, 0xa3, 0xa5, 0xa7, 0xa9, 0xab, 0xad, 0xaf,
  0xb1, 0xb3, 0xb5, 0xb7, 0xb9, 0xbb, 0xbd, 0xbf,
  0xc1, 0xc3, 0xc5, 0xc7, 0xc9, 0xcb, 0xcd, 0xcf,
  0xd1, 0xd3, 0xd5, 0xd7, 0xd9, 0xdb, 0xdd, 0xdf,
  0xe1, 0xe3, 0xe5, 0xe7, 0xe9, 0xeb, 0xed, 0xef,
  0xf1, 0xf3, 0xf5, 0xf7, 0xf9, 0xfb, 0xfd, 0xff,
  0xfd, 0xfb, 0xf9, 0xf7, 0xf5, 0xf3, 0xf1, 0xef,
  0xed, 0xeb, 0xe9, 0xe7, 0xe5, 0xe3, 0xe1, 0xdf,
  0xdd, 0xdb, 0xd9, 0xd7, 0xd5, 0xd3, 0xd1, 0xcf,
  0xcd, 0xcb, 0xc9, 0xc7, 0xc5, 0xc3, 0xc1, 0xbf,
  0xbd, 0xbb, 0xb9, 0xb7, 0xb5, 0xb3, 0xb1, 0xaf,
  0xad, 0xab, 0xa9, 0xa7, 0xa5, 0xa3, 0xa1, 0x9f,
  0x9d, 0x9b, 0x99, 0x97, 0x95, 0x93, 0x91, 0x8f,
  0x8d, 0x8b, 0x89, 0x87, 0x85, 0x83, 0x81, 0x80,
  0x7e, 0x7c, 0x7a, 0x78, 0x76, 0x74, 0x72, 0x70,
  0x6e, 0x6c, 0x6a, 0x68, 0x66, 0x64, 0x62, 0x60,
  0x5e, 0x5c, 0x5a, 0x58, 0x56, 0x54, 0x52, 0x50,
  0x4e, 0x4c, 0x4a, 0x48, 0x46, 0x44, 0x42, 0x40,
  0x3e, 0x3c, 0x3a, 0x38, 0x36, 0x34, 0x32, 0x30,
  0x2e, 0x2c, 0x2a, 0x28, 0x26, 0x24, 0x22, 0x20,
  0x1e, 0x1c, 0x1a, 0x18, 0x16, 0x14, 0x12, 0x10,
  0x0e, 0x0c, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x00
};


uint8_t  sine_wave[256] = {
  0x80, 0x83, 0x86, 0x89, 0x8C, 0x90, 0x93, 0x96,
  0x99, 0x9C, 0x9F, 0xA2, 0xA5, 0xA8, 0xAB, 0xAE,
  0xB1, 0xB3, 0xB6, 0xB9, 0xBC, 0xBF, 0xC1, 0xC4,
  0xC7, 0xC9, 0xCC, 0xCE, 0xD1, 0xD3, 0xD5, 0xD8,
  0xDA, 0xDC, 0xDE, 0xE0, 0xE2, 0xE4, 0xE6, 0xE8,
  0xEA, 0xEB, 0xED, 0xEF, 0xF0, 0xF1, 0xF3, 0xF4,
  0xF5, 0xF6, 0xF8, 0xF9, 0xFA, 0xFA, 0xFB, 0xFC,
  0xFD, 0xFD, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFE, 0xFD,
  0xFD, 0xFC, 0xFB, 0xFA, 0xFA, 0xF9, 0xF8, 0xF6,
  0xF5, 0xF4, 0xF3, 0xF1, 0xF0, 0xEF, 0xED, 0xEB,
  0xEA, 0xE8, 0xE6, 0xE4, 0xE2, 0xE0, 0xDE, 0xDC,
  0xDA, 0xD8, 0xD5, 0xD3, 0xD1, 0xCE, 0xCC, 0xC9,
  0xC7, 0xC4, 0xC1, 0xBF, 0xBC, 0xB9, 0xB6, 0xB3,
  0xB1, 0xAE, 0xAB, 0xA8, 0xA5, 0xA2, 0x9F, 0x9C,
  0x99, 0x96, 0x93, 0x90, 0x8C, 0x89, 0x86, 0x83,
  0x80, 0x7D, 0x7A, 0x77, 0x74, 0x70, 0x6D, 0x6A,
  0x67, 0x64, 0x61, 0x5E, 0x5B, 0x58, 0x55, 0x52,
  0x4F, 0x4D, 0x4A, 0x47, 0x44, 0x41, 0x3F, 0x3C,
  0x39, 0x37, 0x34, 0x32, 0x2F, 0x2D, 0x2B, 0x28,
  0x26, 0x24, 0x22, 0x20, 0x1E, 0x1C, 0x1A, 0x18,
  0x16, 0x15, 0x13, 0x11, 0x10, 0x0F, 0x0D, 0x0C,
  0x0B, 0x0A, 0x08, 0x07, 0x06, 0x06, 0x05, 0x04,
  0x03, 0x03, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03,
  0x03, 0x04, 0x05, 0x06, 0x06, 0x07, 0x08, 0x0A,
  0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x13, 0x15,
  0x16, 0x18, 0x1A, 0x1C, 0x1E, 0x20, 0x22, 0x24,
  0x26, 0x28, 0x2B, 0x2D, 0x2F, 0x32, 0x34, 0x37,
  0x39, 0x3C, 0x3F, 0x41, 0x44, 0x47, 0x4A, 0x4D,
  0x4F, 0x52, 0x55, 0x58, 0x5B, 0x5E, 0x61, 0x64,
  0x67, 0x6A, 0x6D, 0x70, 0x74, 0x77, 0x7A, 0x7D
};

#define LFO1_LOW 230
#define LFO1_HIGH 20

#define LFO2_LOW 230
#define LFO2_HIGH 20

#define SINE 0
#define TRIANGLE 1
#define RAMP_UP 2
#define RAMP_DOWN 3
#define PSYCHO1 4
#define PSYCHO2 5

#define LFO1 1
#define LFO2 2

#define VERBOSE_LOGS 0

//wavetable pointer
volatile uint8_t loop1Count = 255;
volatile uint8_t loop2Count = 255;
//speed
volatile int oscFreq1 = 50;
volatile int oscCounter1 = 0;

volatile int oscFreq2 = 50;
volatile int oscCounter2 = 0;

volatile uint8_t lfo_1a_state = SINE;
volatile uint8_t lfo_1b_state = RAMP_DOWN;
volatile uint8_t lfo_2a_state = RAMP_DOWN;
volatile uint8_t lfo_2b_state = TRIANGLE;

volatile uint8_t lfo_1a_value = 0;
volatile uint8_t lfo_1b_value = 0;
volatile uint8_t lfo_2a_value = 0;
volatile uint8_t lfo_2b_value = 0;

volatile unsigned int lfsr1  = 1;
volatile  unsigned int lfsr2 = 55;


// the setup function runs once when you press reset or power the board
void setup() {


  Serial.begin(9600);
  Serial.println("Hello world");

  pinMode(3, OUTPUT); // lfo1 a  PWM
  pinMode(4, OUTPUT); // digital square
  pinMode(5, OUTPUT); // lfo1 b  PWM

  pinMode(6, OUTPUT); //lfo2 a  PWM
  pinMode(7, OUTPUT);  // digital out sqaure LFO2
  pinMode(11, OUTPUT); //   lfo2 b  PWM

  pinMode(A0, INPUT); // LFO 1 input
  pinMode(A1, INPUT); // LFO 2 input
  pinMode(A2, INPUT); //button1  chose waveform lfo 1
  pinMode(A3, INPUT); //button2  chose waveform lfo 2



  noInterrupts();           // disable all interrupts

  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 1560;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |=  (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

// Juice up 3 and 11 (Nano specific) to nano
TCCR2B = TCCR2B & 0b11111000 | 0x01;
// Juice up 5 and 6  Timer 0
TCCR0B = TCCR0B & 0b11111000 |  0x01;


  interrupts();             // enable all interrupts
}

uint8_t doTriangle (uint8_t value) {
  return triangle_wave[value];
}

uint8_t rampUp (uint8_t value) {
  return value;
}

uint8_t rampDown (uint8_t value) {
  return 255 - value;
}

uint8_t doSine(uint8_t value) {
  return sine_wave[value];
}

void clockLfsr1 () {

  //calculate new state
  boolean outputBit = bitRead(lfsr1, 10) ^ bitRead(lfsr1, 12)
                      ^ bitRead(lfsr1, 13) ^ bitRead(lfsr1, 15);
  lfsr1 = lfsr1 << 1;
  lfsr1 |= outputBit;
}

void clockLfsr2 () {

  //calculate new state
  boolean outputBit = bitRead(lfsr2, 10) ^ bitRead(lfsr2, 12)
                      ^ bitRead(lfsr2, 13) ^ bitRead(lfsr2, 15);
  lfsr2 = lfsr2 << 1;
  lfsr2 |= outputBit;
}

uint8_t psycho1 (int steps, uint8_t value) {
  if (steps == 2) {
    if ( value == 0 ||   value == 127  ) {
      clockLfsr1();
    }
  }
  if (steps == 4) {
    if ( value == 0 || value == 63 || value == 127 || value == 192) {
      clockLfsr1();
    }
  }

  uint8_t low8bits = lfsr1 & 0xFF;

  return low8bits;
}

uint8_t psycho2 (int steps, uint8_t value) {
  if (steps == 2) {
    if ( value == 0 ||   value == 127  ) {
      clockLfsr2();
    }
  }
  if (steps == 4) {
    if ( value == 0 || value == 63 || value == 127 || value == 192) {
      clockLfsr2();
    }
  }

  uint8_t low8bits = lfsr2 & 0xFF;

  return low8bits;
}



ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{

  //Count up and toggle portB bits
  if (oscCounter1 > oscFreq1) {
    oscCounter1 = 0;

    loop1Count++;
    if (loop1Count > 255) {
      loop1Count = 0;
    }

    //Squarewave output
    if (loop1Count == 127) {
      PORTD |= B00010000;
    } else if (loop1Count == 0) {
      PORTD &= B11101111;
    }


    //Figure out what the state is and display the
    //LFO output

    lfo_1a_value = calculateValue(LFO1, lfo_1a_state, loop1Count);
    lfo_1b_value = calculateValue(LFO1, lfo_1b_state, loop1Count);

  }

  oscCounter1++;


  //Count up and toggle portB bits
  if (oscCounter2 > oscFreq2) {
    oscCounter2 = 0;

    loop2Count++;
    if (loop2Count > 255) {
      loop2Count = 0;
    }

    //Squarewave output
    if (loop2Count == 127) {
      PORTD |= B10000000;
    } else if (loop2Count == 0) {
      PORTD &= B01111111;
    }




    //Figure out what the state is and display the
    //LFO output
    lfo_2a_value = calculateValue(LFO2, lfo_2a_state, loop2Count);
    lfo_2b_value = calculateValue(LFO2, lfo_2b_state, loop2Count);

  }

  oscCounter2++;

}

String getState( uint8_t state ) {

  switch (state) {
    case SINE:
      return "Sine";
      break;
    case TRIANGLE:
      return "Trng";
      break;
    case RAMP_UP:
      return "RmpU";
      break;
    case RAMP_DOWN:
      return "RmpD";
      break;
    case PSYCHO1:
      return "Psy1";
      break;
    case PSYCHO2:
      return "Psy2";
      break;
    default:
      return "Other";
      break;
  }


}

void printStates() {

  Serial.println("--- States ---");

  Serial.println("1-A:" + getState(lfo_1a_state));
  Serial.println("1-B:" + getState(lfo_1b_state));
  Serial.println(oscFreq1);
  Serial.println("2-A:" + getState(lfo_2a_state));
  Serial.println("2-B:" + getState(lfo_2b_state));
  Serial.println(oscFreq1);

}

uint8_t calculateValue(int lfo, uint8_t state, uint8_t value) {

  if (state == SINE ) {
    return doSine(value);
  }
  if (state == TRIANGLE ) {
    return doSine(value);
  }

  if (state == RAMP_UP) {
    return rampUp(value);
  }

  if (state == RAMP_DOWN) {
    return rampDown(value);
  }

  if (state == PSYCHO1) {
    if (lfo == LFO1) {
      return psycho1(4, value);
    } else {
      return psycho2(4, value);
    }
  }

  if (state == PSYCHO2) {
    if (lfo == LFO1) {
      return psycho1(2, value);
    } else {
      return psycho2(2, value);
    }
  }


}

uint8_t toggleState(uint8_t state) {
  if (state == SINE ) {
    return RAMP_UP;
  }
  if (state == RAMP_UP ) {
    return RAMP_DOWN;
  }

  if (state == RAMP_DOWN) {
    return TRIANGLE;
  }
  if (state == TRIANGLE) {
    return PSYCHO1;
  }

  if (state == PSYCHO1) {
    return PSYCHO2;
  }

  if (state == PSYCHO2) {
    return SINE;
  }


  return SINE;
}



void loop() {

 
  byte counter = 0;

  byte counter2 = 0;

  int lastButton1aState = 0;
  int button1aState = 0;
  int lastButton2aState = 0;
  int button2aState = 0;

  while (true) {

    //Average the samples.

    // Sample LFO value and average.  Maybe not as important with LFO as with a VCO
    // Also, alternate sampling between channels.
    counter++;
    if (counter > 3) {
      counter = 0;
    }

    if ( counter % 2 == 0) {
   
      int speed_read1 = analogRead(A0);
      oscFreq1 = map(speed_read1, 0, 1023, LFO1_LOW,  LFO1_HIGH);
    } else {
      int speed_read2 = analogRead(A1);
      oscFreq2 = map(speed_read2, 0, 1023, LFO2_LOW,  LFO2_HIGH);
    }

    if (VERBOSE_LOGS == 1) {
      Serial.print( getState(lfo_1a_state));
      Serial.print( ":");
      Serial.print( lfo_1a_value);
      Serial.print( "\t");

      Serial.print( getState(lfo_1b_state));
      Serial.print( ":");
      Serial.print( lfo_1b_value);
      Serial.print( "\t");



      Serial.print( getState(lfo_2a_state));
      Serial.print( ":");
      Serial.print( lfo_2a_value);

      Serial.print( "\t");
      Serial.print( getState(lfo_2b_state));
      Serial.print( ":");
      Serial.print( lfo_1b_value);

      Serial.println( " ");

    }


    analogWrite(3, lfo_1a_value);
    analogWrite(5, lfo_1b_value);
    analogWrite(6, lfo_2a_value);
    analogWrite(11, lfo_2b_value);

    // Read toggle buttons every x loops to save cycles and double as a debounce.

    if (counter2 > 16) {
      counter2 = 0;
    }

    if (counter2 == 0) {
      button1aState = digitalRead(A2);
      // compare the buttonState to its previous state
      if (button1aState != lastButton1aState) {
        // if the state has changed, increment the counter
        if (button1aState == HIGH) {
          lfo_1a_state = toggleState(lfo_1a_state);
          printStates();
        }
      }
      lastButton1aState = button1aState;

      button2aState = digitalRead(A3);
      // compare the buttonState to its previous state
      if (button2aState != lastButton2aState) {
        // if the state has changed, increment the counter
        if (button2aState == HIGH) {
          lfo_2a_state = toggleState(lfo_2a_state);
          printStates();
        }
      }
      lastButton2aState = button2aState;

    }
    counter2++;


  }

}
