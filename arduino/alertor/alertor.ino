#include "Button2.h"

#define BUTTON_PIN 16
#define DEBOUNCE_MS 50
#define DOUBLECLICK_MS 300
#define LONGCLICK_MS 3000
#define LED_BLUE_PIN 5
#define LED_RED_PIN 0
#define LED_WHITE_PIN 4

Button2 button;

int colorState = 1;
bool startState = false;

void setup() {
  Serial.begin(9600);

  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_WHITE_PIN, OUTPUT);

  button.begin(BUTTON_PIN);
  button.setLongClickTime(LONGCLICK_MS);

  button.setChangedHandler(changed);
  button.setPressedHandler(pressed);
  button.setReleasedHandler(released);

  button.setTapHandler(mainSwitch);
  // button.setClickHandler(click); // this will only be called upon release
  button.setLongClickDetectedHandler(longClickDetected); // this will only be called upon detection
  button.setLongClickHandler(longClick);
  
  // button.setDoubleClickHandler(doubleClick);
  // button.setTripleClickHandler(tripleClick);
}

void loop() {
  button.loop();

  if (startState == false) {
    switchOn();

    startState = true;
  }
}

void mainSwitch(Button2& btn) {
  switch(colorState) {
    case -1:
      switchOff();
    break;
    case 0:
      switchOn();
    break;
    case 1:
      switchOnBlue();
    break;
    case 2:
      switchOnWhite();
    break;
    case 3:
      switchOnRed();
    break;
  }
}

void switchOff() {
  colorState = 1;

  digitalWrite(LED_BLUE_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_WHITE_PIN, LOW);
}

void switchOn() {
  colorState = 1;

  digitalWrite(LED_BLUE_PIN, HIGH);
  digitalWrite(LED_RED_PIN, HIGH);
  digitalWrite(LED_WHITE_PIN, HIGH);
}

void switchOnBlue() {
  colorState = 2;

  digitalWrite(LED_BLUE_PIN, HIGH);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_WHITE_PIN, LOW);
}

void switchOnRed() {
  colorState = -1;

  digitalWrite(LED_BLUE_PIN, LOW);
  digitalWrite(LED_RED_PIN, HIGH);
  digitalWrite(LED_WHITE_PIN, LOW);
}

void switchOnWhite() {
  colorState = 3;

  digitalWrite(LED_BLUE_PIN, LOW);
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_WHITE_PIN, HIGH);
}

// Events handlers
void changed(Button2& btn) {
  Serial.println("changed");
}

void click(Button2& btn) {
  Serial.println("click\n");
}

void doubleClick(Button2& btn) {
  Serial.println("double click\n");
}

void longClick(Button2& btn) {
Serial.println("long click\n");
}

void longClickDetected(Button2& btn) {
  Serial.println("long click detected");
}

void pressed(Button2& btn) {
  Serial.println("pressed");
}

void released(Button2& btn) {
  Serial.print("released: ");
  Serial.println(btn.wasPressedFor());
}

void tap(Button2& btn) {
  Serial.println("tap");
}

void tripleClick(Button2& btn) {
  Serial.println("triple click\n");
}