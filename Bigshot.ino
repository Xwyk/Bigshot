#include <A4988.h>
#include <BasicStepperDriver.h>
#include <Arduino.h>

// Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
#define MOTOR_STEPS 200
#define RPM 120

// Since microstepping is set externally, make sure this matches the selected mode
// If it doesn't, the motor will move at a different RPM than chosen
// 1=full step, 2=half step etc.
#define MICROSTEPS 1

// All the wires needed for full functionality
#define DIR 8
#define STEP 9
//Uncomment line to use enable/disable functionality
//#define SLEEP 13

// Pin definitions
const int buttonClockwise = 2;
const int buttonCounterClockwise = 3;
const int potentiometerSpeed = A0;

// Variable declarations
BasicStepperDriver driver(MOTOR_STEPS, DIR, STEP); // STEP and DIR pins of the A4988 driver
int motorSpeed = 0; // Motor speed value (0 to 255)
bool clockwise = false; // Indicates if the motor is rotating clockwise
bool counterclockwise = false; // Indicates if the motor is rotating counterclockwise

void setup() {
	// Pin configuration
	pinMode(buttonClockwise, INPUT_PULLUP);
	pinMode(buttonCounterClockwise, INPUT_PULLUP);
	pinMode(potentiometerSpeed, INPUT);
	pinMode(13, OUTPUT);

	// A4988 driver initialization
	driver.begin(RPM, MICROSTEPS);
}

void loop() {
	// Read buttons
	clockwise = !digitalRead(buttonClockwise);
	counterclockwise = !digitalRead(buttonCounterClockwise);

	// Read potentiometer
	motorSpeed = analogRead(potentiometerSpeed) /25; // Conversion of analog value to a value between 0 and 255
	driver.setRPM(motorSpeed);
	// Motor control
	if (clockwise) {
		driver.move(MOTOR_STEPS);
	} else if (counterclockwise) {
		driver.move(-MOTOR_STEPS);
	} else {
		// Motor stop
		driver.stop();
	}
}