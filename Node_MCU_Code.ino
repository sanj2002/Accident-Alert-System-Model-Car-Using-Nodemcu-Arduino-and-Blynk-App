#define BLYNK_TEMPLATE_ID "TMPL5QS8eR_6"
#define BLYNK_DEVICE_NAME "New Project"
#include<Wire.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define ENA D0
#define IN1 D3
#define IN2 D4
#define IN3 D5
#define IN4 D6
#define ENB D7
BlynkTimer timer;
WidgetMap myMap(V0);
WidgetLED led4(V4);
unsigned int move_index = 1;
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;
char auth[] = "c_hYlT_VOy4RHzzQyQbXpV0o2_nkuRY4";
char ssid[] = "Hotspot";
char pass[] = "12345678@@##";
void setup() {
 Wire.begin();
 Serial.begin(9600);
 pinMode(ENA, OUTPUT);
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 pinMode(ENB, OUTPUT);

 Blynk.begin(auth, ssid, pass);
}
BLYNK_WRITE(V6) {
 forward = param.asInt();
}
BLYNK_WRITE(V7) {
 backward = param.asInt();
}
BLYNK_WRITE(V8) {
 left = param.asInt();
}
BLYNK_WRITE(V9) {
 right = param.asInt();
}
BLYNK_WRITE(V10) {
 Speed = param.asInt();
}
void smartcar() {
 if (forward == 1) {
 carforward();
 Serial.println("carforward");
 } else if (backward == 1) {
 carbackward();
 Serial.println("carbackward");
 } else if (left == 1) {
 carturnleft();
 Serial.println("carfleft");
 } else if (right == 1) {
 carturnright();
 Serial.println("carright");
 } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
 carStop();
 Serial.println("carstop");
 }
}

void carforward() {
 analogWrite(ENA, Speed);
 analogWrite(ENB, Speed);
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
}
void carbackward() {
 analogWrite(ENA, Speed);
 analogWrite(ENB, Speed);
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
}
void carturnleft() {
 analogWrite(ENA, Speed);
 analogWrite(ENB, Speed);
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
}
void carturnright() {
 analogWrite(ENA, Speed);
 analogWrite(ENB, Speed);
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
}
void carStop() {
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, LOW);
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, LOW);
}
void loop() {
 Blynk.run();
 smartcar();
 Wire.requestFrom(2,30);
 String string,string1,string2,string3,string4,string5,string6;
 do
 {
 char c = Wire.read();
 string = string+c;
 string1 = string.substring(0,8);
 string2 = string.substring(9,17);
 string4 = string.substring(18,21);
 string5 = string.substring(22,25);
 string6 = string.substring(26,27);
 string3 = string.substring(28);
 } while (Wire.available());
 char buf1[10];
 char buf2[10];
 char buf3[10];
 char buf4[10];
 char buf5[10];
 char buf6[10];
 Serial.println(string);
 string1.toCharArray(buf1, 10);
 long lati = atol(buf1);
 Serial.println((lati*0.000001),6);
 string2.toCharArray(buf2, 10);
 long longi = atol(buf2);
 Serial.println((longi*0.000001),6);
 string3.toCharArray(buf3, 10);
 int Speed = atoi(buf3);
 int count = atoi(buf6);
 Serial.println(Speed);
 Blynk.virtualWrite(V1, String((lati*0.000001), 6));
 Blynk.virtualWrite(V2, String((longi*0.000001), 6));
 myMap.location(move_index, (lati*0.000001), (longi*0.000001), "GPS_Location");
 Blynk.virtualWrite(V5, String(count));
 Blynk.virtualWrite(V3, String(Speed));
 string4.toCharArray(buf4, 10);
 string5.toCharArray(buf5, 10);
 string6.toCharArray(buf6,10);
 int Xaxis = atoi(buf4);
 int Yaxis = atoi(buf5);

 Serial.print("X-axis :");
 Serial.println(Xaxis);
 Serial.print("Y-axis :");
 Serial.println(Yaxis);
 Serial.println();
 if (Xaxis<=270 || Yaxis<=270 || Xaxis>=390 || Yaxis>=390)
 {
 led4.on();
 delay(10);
 led4.off();
 delay(10);
 }
 else
 {
 led4.off();
 }
} 
