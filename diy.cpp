#include <Wire.h> 
#include <hd44780.h>  // Include hd44780 library 
#include <hd44780ioClass/hd44780_I2Cexp.h>  // Include the I2C 
expander IO class 
#include <SoftwareSerial.h>  // Include the SoftwareSerial library for 
Bluetooth communication 
// Define the I2C address for the LCD 
#define I2C_ADDR 0x27 // Adjust this based on the actual address of 
your LCD 
// Flex Sensor Connections 


const int flexSensorPin1 = A0; 
const int flexSensorPin2 = A1; 
const int flexSensorPin3 = A2; 
const int flexSensorPin4 = A3; 
// Initialize the LCD object 
hd44780_I2Cexp lcd; // Initialize the LCD object with I2C expander 
// Bluetooth module RX and TX pins 
const int bluetoothRx = 2; // Connect Bluetooth TX to pin 2 
const int bluetoothTx = 3; // Connect Bluetooth RX to pin 3 
// Initialize SoftwareSerial object for Bluetooth communication 
SoftwareSerial bluetooth(bluetoothRx, bluetoothTx); 
// Piezo buzzer pin 
const int buzzerPin = 4; // Connect piezo buzzer to pin 4 
// Previous gesture to check for changes 
String prevGesture = ""; 
void setup() { 
Serial.begin(9600); 
bluetooth.begin(9600); // Initialize Bluetooth serial communication 
lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows 
lcd.setCursor(0, 0); 
lcd.print("Flex Gesture:"); 
pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output 
} 
void loop() { 
// Read analog values from flex sensors 
int flexValue1 = analogRead(flexSensorPin1); 
int flexValue2 = analogRead(flexSensorPin2); 
int flexValue3 = analogRead(flexSensorPin3); 
int flexValue4 = analogRead(flexSensorPin4); 
// Update LCD with gesture 
String gesture; 
if (flexValue1 > 990 && flexValue2 > 1006 && flexValue3 <= 980 && 
f
 lexValue4 <= 980) { 
gesture = "Victory"; 
} else if (flexValue1 <= 990 && flexValue2 <= 1008 && flexValue3 <= 
980 && flexValue4 >= 979) { 
gesture = "Washroom"; 
} else if (flexValue1 >= 990 && flexValue2 < 1009 && flexValue3 <= 
980 && flexValue4 >= 978) { 
gesture = "rock"; 
} else if (flexValue1 <= 990 && flexValue2 <= 1008 && flexValue3 <= 
980 && flexValue4 <= 980) { 
gesture = "Food"; 
} else if (flexValue1 >= 990 && flexValue2 <= 1009 && flexValue3 <= 
980 && flexValue4 < 978) { 
gesture = "I wanna say something"; 
} else if (flexValue1 <= 990 && flexValue2 >= 1009 && flexValue3 >= 
980 && flexValue4 > 978) { 
gesture = "HELP"; 
// Activate piezo buzzer for help 
tone(buzzerPin, 1000); // Play a tone of 1000 Hz 
delay(1000); // Wait for 1 second 
noTone(buzzerPin); // Stop the tone 
} else if (flexValue1 >= 990 && flexValue2 >= 1008 && flexValue3 >= 
980 && flexValue4 >= 979) { 
gesture = "hello"; 
}  else if (flexValue1 >= 990 && flexValue2 >= 1008 && flexValue3 >= 
980 && flexValue4 <= 978) { 
gesture = "name:diyteam22"; 
}  
else { 
gesture = " "; 
} 
// Check if the current gesture is different from the previous gesture 
if (gesture != prevGesture) { 
// Display gesture on LCD 
lcd.clear(); 
lcd.setCursor(0, 0); 
lcd.print(gesture); 
// Send gesture via Bluetooth 
bluetooth.println(gesture); 
// Print gesture on Serial monitor 
Serial.println("Gesture detected: " + gesture); 
// Update previous gesture 
prevGesture = gesture; 
} 
delay(100); // Add a small delay to reduce processing load 
}
