#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

const constexpr int CV_1_PIN(A7);
const constexpr int CV_2_PIN(A6);
const constexpr int CV_3_PIN(A3);
const constexpr int CV_4_PIN(A2);
const constexpr int CV_5_PIN(A1);
const constexpr int CV_6_PIN(A0);

const constexpr int POT_1_PIN(A20);
const constexpr int POT_2_PIN(A19);
const constexpr int POT_3_PIN(A18);
const constexpr int POT_4_PIN(A17);
const constexpr int POT_5_PIN(A16);
const constexpr int POT_6_PIN(A15);

const constexpr int LED_1_PIN( 28 );
const constexpr int LED_2_PIN( 29 );
const constexpr int LED_3_PIN( 30 );

const constexpr int NUM_CVS(6);
const constexpr int CV_PINS[NUM_CVS] = { CV_1_PIN, CV_2_PIN, CV_3_PIN, CV_4_PIN, CV_5_PIN, CV_6_PIN };

const constexpr int NUM_POTS(6);
const constexpr int POT_PINS[NUM_CVS] = { POT_1_PIN, POT_2_PIN, POT_3_PIN, POT_4_PIN, POT_5_PIN, POT_6_PIN };

const constexpr int NUM_LEDS(3);
const constexpr int LED_PINS[NUM_LEDS] = { LED_1_PIN, LED_2_PIN, LED_3_PIN };

AudioInputI2S            audio_input;
AudioOutputI2S           audio_output;
AudioControlWM8731       wm8731;

//AudioSynthWaveform       wave_generator;
//AudioConnection          patch_cord_1( wave_generator, 0, audio_output, 0 );
AudioConnection          patch_cord_1( audio_input, 0, audio_output, 0 );


void setup() 
{  
  Serial.begin(9600);
  delay(5);
  
  wm8731.enable();
  wm8731.volume(1.0f);
  wm8731.inputLevel(1.0f);
  wm8731.inputSelect(AUDIO_INPUT_LINEIN);

  AudioMemory(24);

  //Serial.begin(9600);
  /*
  wave_generator.begin(WAVEFORM_SINE);
  wave_generator.amplitude(1.0f);
  wave_generator.frequency(440.0f);*/

  Serial.println("Setup finished!");

  for( int i = 0; i < NUM_CVS; ++i )
  {
    pinMode(CV_PINS[i], INPUT);
  }

  for( int i = 0; i < NUM_POTS; ++i )
  {
    pinMode(POT_PINS[i], INPUT);
  }

  for( int i = 0; i < NUM_LEDS; ++i )
  {
    pinMode(LED_PINS[i], OUTPUT);
  }
}

void loop()
{
  // CV
  Serial.print("CV ");
  for( int i = 0; i < NUM_CVS; ++i )
  {
    int cv_val = analogRead(CV_PINS[i]);
    Serial.print( cv_val );
    Serial.print(" ");
  }

  // Pots
  Serial.print("\tPOTS ");
  for( int i = 0; i < NUM_POTS; ++i )
  {
    int pot_val = analogRead(POT_PINS[i]);
    Serial.print( pot_val );
    Serial.print(" ");
  }

  Serial.println("\n");
  // LEDs
  static bool on = true;
  static int next_toggle = 0;
  const int time_ms = millis();
  if( time_ms > next_toggle )
  {
    on = !on;
    next_toggle = time_ms + 1000;
  }

  for( int i = 0; i < NUM_LEDS; ++i )
  {
    digitalWrite(LED_PINS[i], on ? HIGH : LOW);
  }
  
  delay(10);
}
