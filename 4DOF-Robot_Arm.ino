#include <Servo.h>
#include <IRremote.h>

// Servo objects
Servo base = Servo();
Servo updown = Servo();
Servo frontback = Servo();
Servo arm = Servo();

// Servo angles
int angel1 = 90; // Base
int angel2 = 90; // arm
int angel3 = 90; // elbow
int angel4 = 0;  // claw

#define IR_PIN 3 // Define IR receiver pin

void setup() {
  IrReceiver.begin(IR_PIN); // Initialize the IR receiver
  base.attach(9);           // Attach base servo to pin 9
  updown.attach(11);        // Attach arm servo to pin 11
  frontback.attach(10);     // Attach elbow servo to pin 10
  arm.attach(6);            // Attach claw servo to pin 6

  // Initialize servos to default positions
  base.write(angel1);
  updown.write(angel2);
  frontback.write(angel3);
  arm.write(angel4);

  Serial.begin(9600); // Begin serial communication
}

void loop() {
  if (IrReceiver.decode()) { // Check IR signal received
    uint16_t command = IrReceiver.decodedIRData.command; // Get command value
    Serial.print("Received IR Command: ");
    Serial.println(command, HEX); // Print IR command in hexadecimal format

    // Base left
    if (command == 0x8) { // hex command
      for (int i = 0; i < 10; i++) {
        angel1 = constrain(angel1 + 1, 0, 180);
        base.write(angel1);
        delay(100);
      }
    }

    // Base right
    if (command == 0x5A) { // hex command
      for (int i = 0; i < 10; i++) {
        angel1 = constrain(angel1 - 1, 0, 180);
        base.write(angel1);
        delay(100);
      }
    }

    // arm up
    if (command == 0x52) { // hex command
      for (int i = 0; i < 10; i++) {
        angel2 = constrain(angel2 + 1, 0, 180);
        updown.write(angel2);
        delay(100);
      }
    }

    // arm down
    if (command == 0x18) { // hex command
      for (int i = 0; i < 10; i++) {
        angel2 = constrain(angel2 - 1, 0, 180);
        updown.write(angel2);
        delay(100);
      }
    }

    // elbow up
    if (command == 0x46) { // hex command
      for (int i = 0; i < 10; i++) {
        angel3 = constrain(angel3 + 1, 0, 120);
        frontback.write(angel3);
        delay(100);
      }
    }

    // elbow down 
    if (command == 0x15) { // hex command
      for (int i = 0; i < 10; i++) {
        angel3 = constrain(angel3 - 1, 0, 120);
        frontback.write(angel3);
        delay(100);
      }
    }

    // Arm open
    if (command == 0x44) { // hex command
      for (int i = 0; i < 10; i++) {
        angel4 = constrain(angel4 + 1, 0, 90);
        arm.write(angel4);
        delay(100);
      }
    }

    // Arm close
    if (command == 0x43) { // hex command
      for (int i = 0; i < 10; i++) {
        angel4 = constrain(angel4 - 1, 0, 90);
        arm.write(angel4);
        delay(100);
      }
    }

    IrReceiver.resume(); // resume to next IR signal
  }
}