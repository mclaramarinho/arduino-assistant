#include <driver/i2s.h>

int LED_LOADING_INDICATOR = 13;

boolean isLoaded = false;
unsigned long loadingStartTime;
const unsigned long loadingDuration = 5000; 

void setup() {

  // Setup loading indicator led pin
  pinMode(LED_LOADING_INDICATOR, OUTPUT);
  digitalWrite(LED_LOADING_INDICATOR, LOW); 
  
  loadingStartTime = millis();
}

void loop() {
  handleLoading();
}  

void handleLoading(){
  unsigned long currentMillis = millis();

  if(!isLoaded){
    if(currentMillis - loadingStartTime >= loadingDuration){
      digitalWrite(LED_LOADING_INDICATOR, HIGH);
      return;
    }
    blinkLight();
  }
}
void blinkLight(){
  digitalWrite(LED_LOADING_INDICATOR, HIGH);
  delay(500);
  digitalWrite(LED_LOADING_INDICATOR, LOW);
  delay(1000);
}
