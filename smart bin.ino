#include <WiFi.h>
#include <ESP32Servo.h>
#include <ThingSpeak.h>

const char* SSID= "Wokwi-GUEST";
const char* Password= "";

WiFiClient client; //Creates a WiFiClient object
const int channel_number= 2834140;
const char* api_key= "MDPRLBCN9BQWJSRR"; //write api key
const char* server= "api.thingspeak.com";

#define trig_pin 32
#define echo_pin 33
#define pir_pin 12
#define servo_pin 14
#define led_green 18
#define led_yellow 19
#define led_orange 21
#define led_red 22

Servo lid_control;

void setup(){
  Serial.begin(115200);

  WiFi.begin(SSID, Password); //for internet access
  WiFi.mode(WIFI_STA); //to connect esp32 to existin wifi
  ThingSpeak.begin(client); // ThingSpeak communication

  pinMode (trig_pin, OUTPUT);
  pinMode (echo_pin, INPUT);
  pinMode (pir_pin, INPUT);
  pinMode (servo_pin, OUTPUT);
  pinMode (led_green, OUTPUT);
  pinMode (led_yellow, OUTPUT);
  pinMode (led_orange, OUTPUT);
  pinMode (led_red, OUTPUT);

  pinMode(pir_pin, INPUT_PULLDOWN);

  lid_control.attach(servo_pin);
}

int bin_level_(){
  digitalWrite(led_green, LOW);
  digitalWrite(led_yellow, LOW);
  digitalWrite(led_orange, LOW);
  digitalWrite(led_red, LOW);

  digitalWrite(trig_pin, LOW);
  delay(2);
  digitalWrite(trig_pin, HIGH);
  delay(10);
  digitalWrite(trig_pin, LOW);
  int duration= pulseIn(echo_pin, HIGH);
  int distance= duration* 0.034/2;

  int bin_height= 100; //in cm
  int bin_level= 100- distance;

  if(bin_level>=30 && bin_level<50){
    digitalWrite(led_green, HIGH);  //if level>=30 and level<50
  }
  else if(bin_level>=50 && bin_level<85){
    digitalWrite(led_green, HIGH);  //if level>=50 and level<85
    digitalWrite(led_yellow, HIGH);
  }
  else if(bin_level>=85 && bin_level<90){
    digitalWrite(led_green, HIGH);  //if level>85 and level<90
    digitalWrite(led_yellow, HIGH);
    digitalWrite(led_orange, HIGH);
  }
  else if(bin_level>90){
    digitalWrite(led_green, HIGH);  //if level>90
    digitalWrite(led_yellow, HIGH);
    digitalWrite(led_orange, HIGH);
    digitalWrite(led_red, HIGH);
  }
  return bin_level; 
}

void lid(){
  int motion_detected= digitalRead(pir_pin);
  Serial.println(motion_detected);
  if(motion_detected==HIGH){
    Serial.println("Lid Opened");
    lid_control.write(90);
  }
  else{
  Serial.println("Lid Closed");
    lid_control.write(0);
  }delay(500);
}

void to_thingspeak(int bin_level){
  ThingSpeak.setField(1, bin_level);
  int status = ThingSpeak.writeFields(channel_number, api_key); 

if(status == 200){ //200 is an HTTP status code that means "OK" 
    Serial.println("Data sent to ThingSpeak successfully.");
}
else{
    Serial.println("Failed to send data.");
}

}

void loop(){
  lid();
  int bin_level = bin_level_();

  to_thingspeak(bin_level);
  Serial.println("BIN LEVEL: ");
  Serial.println(bin_level);
  delay(1000);
}