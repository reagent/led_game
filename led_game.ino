const byte PUSHED = 0;

const byte redPin   = 9;
const byte greenPin = 10;
const byte bluePin  = 11;

const byte redControlPin   = 3;
const byte greenControlPin = 5;
const byte blueControlPin  = 6;

const byte speakerPin = A0;

const byte buttonPin = 2;

const byte redDialPin   = A1;
const byte greenDialPin = A2;
const byte blueDialPin  = A3;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(redControlPin, OUTPUT);
  pinMode(greenControlPin, OUTPUT);
  pinMode(blueControlPin, OUTPUT);

  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);

  pinMode(2, INPUT);

  randomSeed(millis());

  Serial.begin(9600);
}

void loop() {
  if (digitalRead(buttonPin) == PUSHED) { playGame(); }
}


void playGame() {
  byte redValue   = randomFrequency();
  byte greenValue = randomFrequency();
  byte blueValue  = randomFrequency();

  Serial.print("Red: ");
  Serial.println(redValue);

  Serial.print("Green: ");
  Serial.println(greenValue);

  Serial.print("Blue: ");
  Serial.println(blueValue);

  // Reset LED
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);

  turnOnLed(redPin, redValue);
  playReadyTone(speakerPin);
  digitalWrite(redPin, LOW);

  turnOnLed(greenPin, greenValue);
  playReadyTone(speakerPin);
  digitalWrite(greenPin, LOW);

  turnOnLed(bluePin, blueValue);
  playReadyTone(speakerPin);
  digitalWrite(bluePin, LOW);

  turnOnLed(redPin, redValue);
  turnOnLed(greenPin, greenValue);
  turnOnLed(bluePin, blueValue);
  playGoTone(speakerPin);

  byte userSelectedRed, userSelectedGreen, userSelectedBlue;

  // Collect player input until button is pressed
  while (digitalRead(buttonPin) != PUSHED) {
    userSelectedRed   = readLedValueFromDial(redDialPin);
    userSelectedGreen = readLedValueFromDial(greenDialPin);
    userSelectedBlue  = readLedValueFromDial(blueDialPin);

    turnOnLed(redControlPin, userSelectedRed);
    turnOnLed(greenControlPin, userSelectedGreen);
    analogWrite(blueControlPin, userSelectedBlue);
  }

  // Button was pushed!
  Serial.print("Red: ");
  Serial.print(userSelectedRed);
  Serial.print(" (actual: ");
  Serial.print(redValue);
  Serial.println(")");

  Serial.print("Green: ");
  Serial.print(userSelectedGreen);
  Serial.print(" (actual: ");
  Serial.print(greenValue);
  Serial.println(")");

  Serial.print("Blue: ");
  Serial.print(userSelectedBlue);
  Serial.print(" (actual: ");
  Serial.print(blueValue);
  Serial.println(")");

  if (userSelectedRed == redValue && userSelectedGreen == greenValue && userSelectedBlue == blueValue) {
    playTone(speakerPin, 700, 1000);
  } else {
    playTone(speakerPin, 200, 1000);
  }

  digitalWrite(redControlPin, LOW);
  digitalWrite(greenControlPin, LOW);
  digitalWrite(blueControlPin, LOW);

  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);

}

// Blocks for duration
void playTone(byte pin, short frequency, short duration) {
  tone(pin, frequency, duration);
  delay(duration);
  noTone(pin);
}

void playReadyTone(byte pin) {
  short duration = 400;

  playTone(pin, 400, duration);
  delay(duration);
}

void playGoTone(byte pin) {
  playTone(pin, 600, 1000);
}

void turnOnLed(byte pin, byte value) {
  if (value == 0) {
    digitalWrite(pin, LOW);
  } else {
    analogWrite(pin, value);
  }
}

byte randomFrequency() {
  byte frequencies[] = {0, 128, 255};
  byte index = random(0, 3);

  return frequencies[index];
}

short readLedValueFromDial(short pin) {
  short dialFrequencies[] = {0, 256, 512, 768, 1023},
        selectedFrequency = analogRead(pin);

  byte ledFrequencies[] = {0, 128, 128, 128, 255};

  for (int i = 0; i < 5; i++) {
    if (selectedFrequency <= dialFrequencies[i]) {
      return ledFrequencies[i];
    }
  }
}

void testLeds() {
  int frequencies[] = {0, 64, 128, 192, 255};

  for (int i = 0; i < 5; i++) {
    playTone(speakerPin, 400, 500);

    turnOnLed(redPin, frequencies[i]);
    delay(500);
    digitalWrite(redPin, LOW);

    turnOnLed(greenPin, frequencies[i]);
    delay(500);
    digitalWrite(greenPin, LOW);

    turnOnLed(bluePin, frequencies[i]);
    delay(500);
    digitalWrite(bluePin, LOW);

    turnOnLed(redPin, frequencies[i]);
    turnOnLed(greenPin, frequencies[i]);
    turnOnLed(bluePin, frequencies[i]);

    delay(500);
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }

  playTone(speakerPin, 600, 500);
}