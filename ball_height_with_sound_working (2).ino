/****************************************
Example Sound Level Sketch for the
Adafruit Microphone Amplifier
****************************************/

const int sampleWindow = 100; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
const int motorPin = 9;

//  for noise generation***********
/*unsigned long int reg;
int frequency = 100;
const int buzzerPin = 3;*/

void setup()
{
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);

  //for noise generation**********
  /*pinMode(buzzerPin, OUTPUT);
  reg = 0x55aa55aaL; //The seed for the bitstream. It can be anything except 0.
  */
}


void loop()
{
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  // collect data for 50 mS
  while (millis() - startMillis < sampleWindow)
  {
    sample = analogRead(0);
    if (sample < 1024)  // toss out spurious readings
    {
      if (sample > signalMax)
      {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  double volts = (peakToPeak * 3.3) / 1.24;  // convert to volts

  Serial.println(volts);

  //frequency = map(volts, 700, 1800, 500, 1000);
 // generateNoise(frequency);

  if (volts <= 700) {
    Serial.println("within 700");
    analogWrite(motorPin, 50);
    //generateNoise(frequency);

  } else if ((volts > 700) && (volts <= 800)) {
    Serial.println("within 800");
    analogWrite(motorPin, 70);

  } else if ((volts > 800) && (volts <= 900)) {
    Serial.println("within 900");
    analogWrite(motorPin, 80);

  } else if ((volts > 900) && (volts <= 1000)) {
    Serial.println("within 1100");
    analogWrite(motorPin, 110);

  } else if (volts > 1000) {
    Serial.println("> 1100");
    analogWrite(motorPin, 130);

  }

}

/*
void generateNoise(int frequency) {
  unsigned long int newr;
  unsigned char lobit;
  unsigned char b31, b29, b25, b24;

  // Extract four chosen bits from the 32-bit register
  b31 = (reg & (1L << 31)) >> 31;
  b29 = (reg & (1L << 29)) >> 29;
  b25 = (reg & (1L << 25)) >> 25;
  b24 = (reg & (1L << 24)) >> 24;

  // EXOR the four bits together
  lobit = b31 ^ b29 ^ b25 ^ b24;

  // Shift and incorporate new bit at bit position 0
  newr = (reg << 1) | lobit;

  // Replace register with new value
  reg = newr;

  // Drive speaker pin from bit 0 of 'reg'
  digitalWrite(buzzerPin, reg & 1);

  // Delay (50) corresponds to 20kHz, but the actual frequency of updates
  // will be lower, due to computation time and loop overhead
  //delayMicroseconds(frequency);    // Changing this value changes the frequency.
  delayMicroseconds(frequency);
}
*/

