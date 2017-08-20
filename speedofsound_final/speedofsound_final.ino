//HC RS04 Ultrasonic ranging module
int triggerPort = 9;
int echoPort = 8;
float pingTime;
float speedOfSound;
int targetDistance=10; //Distance to Target in cm

#define BUTTON 10 
#define LUMIN 11

#define NOTE_A4 440

int l = 255;

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
 
void setup() {
  pinMode(BUTTON, INPUT);
  pinMode( triggerPort, OUTPUT );
  pinMode( echoPort, INPUT );
  pinMode(LUMIN, OUTPUT);
  
  Serial.begin( 9600 );
  Serial.println( "Ultrasonic ranging module: ");
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2); 
}
 
void loop() {
// set the cursor to column 0, line 1
// (note: line 1 is the second row, since counting begins with 0):
  
delay(500);
while(digitalRead(BUTTON) == LOW) {             // waits into this while until val = HIGH (button pressed)
  analogWrite(LUMIN, 0);  // turn LED off 
  lcd.clear();
  noTone(12);
}                             
  
analogWrite(LUMIN, l);  // turn LED on

  digitalWrite(triggerPort, LOW); //Set trigger pin low
  delayMicroseconds(2000); //Let signal settle
  digitalWrite(triggerPort, HIGH); //Set trigPin high
  delayMicroseconds(10); //Delay in high state
  digitalWrite(triggerPort, LOW); //ping has now been sent
  
//digitalWrite(triggerPort, LOW);			// set to LOW trigger's output
//digitalWrite(triggerPort, HIGH);		// send a 10us pulse to the trigger
//delayMicroseconds( 10 );
//digitalWrite(triggerPort, LOW);
// 
//long duration = pulseIn(echoPort, HIGH);
// 
//long r = 3.4 * duration / 2;			// here we calculate the distance using duration
//
//float distance = r / 100.00;
//
//lcd.setCursor(0, 0);
//lcd.print("time: ");
//lcd.print(duration);
//lcd.print(" us    ");
//lcd.setCursor(0, 1);
//
// 
//
//if( duration > 38000 ) {lcd.println("out of reach    "); tone(12, NOTE_A4);}		// if duration is greater than 38ms, the obstacle is out of reach
//else { lcd.print("dist: "); lcd.print(distance); lcd.println(" cm    "); noTone(12);}
// 
//
//delay( 1000 );							// wait for 1s
  
  pingTime = pulseIn(echoPort, HIGH);  //pingTime is presented in microceconds
 
  //speedOfSound = (targetDistance*2)/pingTime*(1000000)*3600/63360;        //converts to miles per hour
  speedOfSound = (targetDistance*2)/pingTime*(10000);
  Serial.print("The Speed of Sound is: ");
  Serial.print(speedOfSound);
  Serial.println(" m/s");
  Serial.print("The Time taken is: ");
  Serial.print(pingTime);
  Serial.println(" s");

  lcd.setCursor(0, 0);
lcd.print("time: ");
lcd.print(pingTime);
lcd.print(" us    ");
lcd.setCursor(0, 1);
//
// 
//
//if( duration > 38000 ) {lcd.println("out of reach    "); tone(12, NOTE_A4);}    // if duration is greater than 38ms, the obstacle is out of reach
lcd.print("speed: "); lcd.print(speedOfSound); lcd.println(" m/s    "); noTone(12);
delay( 1000 );
}
