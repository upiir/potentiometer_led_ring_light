// learn how to do multiplexing with LED ring light for potentiometer and Arduino UNO

// created by upir, 2023
// youtube channel: https://www.youtube.com/upir_upir

// Source files: https://github.com/upiir/potentiometer_led_ring_light
// Youtube video: https://youtu.be/tHL4RYGSvg4
// WOKWI sketch multiplexing: https://wokwi.com/projects/381014443625021441

// Links from the video:
// LED ring light: https://s.click.aliexpress.com/e/_DmvHFpp
// Arduino UNO: https://s.click.aliexpress.com/e/_AXDw1h
// Arduino prototyping shield: https://s.click.aliexpress.com/e/_ApbCwx
// Breadboard wires: https://s.click.aliexpress.com/e/_Dkbngin

// Related videos with Arduino UNO and 128x64 OLED screen:
// Arduino + OLED displays: https://www.youtube.com/playlist?list=PLjQRaMdk7pBZ1UV3IL5ol8Qc7R9k-kwXA


int pins_C[] = {2, 12, 11, 10}; // pins for common cathode (-)
int pins_L[] = {13, 5, 3, 4, 9, 8, 7, 6}; // LED pins (+)


int show_value = 0; // which LED to show on the ring light


void setup() {

  // set pins for common cathode as output, set them to LOW
  for (int i = 0; i < 4; i++) {
    pinMode(pins_C[i], OUTPUT);
    digitalWrite(pins_C[i], LOW);
  }

  // set pins for LEDs as outputs, set them to LOW
  for (int i = 0; i < 8; i++) {
    pinMode(pins_L[i], OUTPUT);
    digitalWrite(pins_L[i], LOW);
  }

  pinMode(A0, INPUT); // pin A0 is input used to read potentiometer value

}



// the loop function runs over and over again forever
void loop() {


 int pot_value = analogRead(A0); // read the value of the potentiometer
 show_value = constrain(map(pot_value, 0, 1010, -1, 31), -1, 31); // remap the value, as there are only 32 LEDs, the potentiometer should go all the way to 1023, but mine is broken = restricting the range to only 1010
  

// go over all the comon cathodes (-)
for (int i = 0; i < 4; i++) {
  digitalWrite(pins_C[i], LOW); // set one of the cathodes to LOW, all the others to HIGH
  digitalWrite(pins_C[(i+1)%4], HIGH);
  digitalWrite(pins_C[(i+2)%4], HIGH);
  digitalWrite(pins_C[(i+3)%4], HIGH); 


  // go over all the LED pins (+)
  for (int j = 0; j < 8; j++) {

    //if (show_value == ((i*8+j))) { // if we should show the value, light up the LED
    if (show_value >= ((i*8+j))) { // if we should show the value, light up the LED
    
      digitalWrite(pins_L[j], HIGH);
      //delay(1);
      delayMicroseconds(200);
      digitalWrite(pins_L[j], LOW);  
    } // otherwise, do nothing
  }



       
}

}
