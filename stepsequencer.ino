//#include <Audio.h>
//#include <Wire.h>
//#include <SPI.h>
//#include <SD.h>
//#include <SerialFlash.h>
//
//// GUItool: begin automatically generated code
//AudioSynthWaveform       waveform1;      //xy=278,376
//AudioOutputAnalog        dac1;           //xy=575,397
//AudioConnection          patchCord1(waveform1, dac1);
//// GUItool: end automatically generated code




int buttons[4] = {25, 26, 27, 28};

int ledPins[4] = {1, 2, 3, 4};


int totalLeds = 4;

int tempoVal = A20;

boolean lastButtonState[4] = {LOW, LOW, LOW, LOW};

boolean buttonState[4] = {LOW, LOW, LOW, LOW};

boolean on[4] = {false, false, false, false};

int tempo = 0;



int currentStep = 0;

unsigned long lastStepTime = 0;


//int potPins[4] = {A19, A18, A17, A16};
//
//int potVal[4] = {0, 0, 0, 0};



//int mappedTempoVal = 0;
//
//int mappedPotVals[4] = {0, 0, 0, 0};
//
//int frequencyNote[4] = {0, 0, 0, 0};
//
//int middleC = 261;
//
//int quantizeSwitchPin = 30;

//int quantizied[4] = {0, 0, 0, 0};








//  Serial.begin(9600);
//  AudioMemory(12); //always include this when using the Teensy Audio Library even if you don't know what it is yet!
//  waveform1.begin(WAVEFORM_SINE); //produces a sine wave
//  waveform1.amplitude(0.4); //amplitude (volume) can be 0 to 1
//  waveform1.frequency(262);

void setup() {
  pinMode(buttons[0], INPUT);
  pinMode(buttons[1], INPUT);
  pinMode(buttons[2], INPUT);
  pinMode(buttons[3], INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }


}

void loop() {
  tempoVal = analogRead(A20); // pot5 controls the speed and is the pot closest to the left hand
  sequence(); // function to have the sounds be controlled by 4 pots and speed by the first one
  checkButtons(); //function to check whether the button was previously on or off
  //determines current and last button state so that buttons trigger on or off
  setLed();
}




void checkButtons() {
  for (int i = 0; i < 4; i++) {
    lastButtonState[i] = buttonState[i];
    buttonState[i] = digitalRead(buttons[i]);

    if (buttonState[i] == HIGH && lastButtonState[i] == LOW) {
      if (on[i] == false) {
        on[i] = true;
      } else if (on[i] == true) {
        on[i] = false;
      }
    }
  }
}

void setLed() {
  for (int i = 0; i < 4; i++) {
    if (on[i] == true || currentStep == i) {
      digitalWrite(ledPins[i], HIGH);
    } else if (on[i] == false) {
      digitalWrite(ledPins[i], LOW);
    }
  }
}



void sequence() { //sequencing function

  tempo = analogRead(A20);

  if (millis() > lastStepTime + tempo) {

    //turn stuff off for previous currentStep
    usbMIDI.sendNoteOff(60, 0, 1);
    //        digitalWrite(ledPins[currentStep], LOW);

    //increment currentStep
    currentStep = currentStep + 1;
    if (currentStep > 3) {
      currentStep = 0;
    }
    lastStepTime = millis();

    //do stuff with the actual new currentStep
    //        digitalWrite(ledPins[currentStep], HIGH);
    //        waveform1.frequency(261, [currentStep]);
    usbMIDI.sendNoteOn(60, 127, 1);



  }
}

void backSequence() {

  tempo = analogRead(A20);


  if (millis() > lastStepTime + tempo) {

    //turn stuff off for previous currentStep
    usbMIDI.sendNoteOff(60, 0, 1);
    digitalWrite(ledPins[currentStep], LOW);

    //increment currentStep
    currentStep = currentStep - 1;
    if (currentStep < 0) {
      currentStep = 3;
    }
    lastStepTime = millis();

    //do stuff with the actual new currentStep
    digitalWrite(ledPins[currentStep], HIGH);
//    waveform1.frequency(261, [currentStep]);
    usbMIDI.sendNoteOn(60, 127, 1);



  }

}
