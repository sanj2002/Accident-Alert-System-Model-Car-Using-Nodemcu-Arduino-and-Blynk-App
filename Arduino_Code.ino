#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>
const int Xpin=A0;
const int Ypin=A1;
static int speed_count = 0;
int toggle_state = 0;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
SoftwareSerial GPS(3,4); //GPS TX pin to 3 and RX pin to 4
TinyGPS gps;
SoftwareSerial GSMSerial(5,6); //GSM TX pin to 5 and RX pin to 6
void setup()
{
 lcd.begin(16,2);
 GSMSerial.begin(9600);
 Serial.begin(9600);
 GPS.begin(9600);
 Wire.begin(2);
 Wire.onRequest(Request);
 lcd.setCursor(0,0);
 lcd.print("Welcome to SJC");
 Serial.println("Welcome to SJC");
 delay(3000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Course faculty :");
 lcd.setCursor(0,1);
 lcd.print("Rekha MN Mam");
 Serial.println("Course faculty: Rekha MN Mam");
 delay(3000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("End Evaluation");
 Serial.println("End Evaluation");
 lcd.setCursor(0,1);
 lcd.print("Group Members :");
 Serial.println("Group Members");
 Serial.println(" Prajwal N ");
 Serial.println(" Jeevan R Gowda ");
 Serial.println(" Lakshmi ");
 Serial.println(" Pranath ");
 delay(3000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(" Prajwal N ");
 lcd.setCursor(0,1);
 lcd.print(" Jeevan R Gowda ");
 delay(3000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print(" Lakshmi ");
 lcd.setCursor(0,1);
 lcd.print(" Pranath ");
 delay(3000);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Vehicle Tracking");
 Serial.println("Vehicle Tracking");
 lcd.setCursor(0,1);
 lcd.print("Accident Alert System");
 Serial.println("Accident Alert System");
 delay(3000);
 lcd.clear();
 Serial.println("Establishing Connection..............!!");
}
long lat,lon;
char lati[16];
char longi[16];
char Speed[5];
char Xaxi[5];
char Yaxi[5];
char SpeedCount[5];
char latitude1[50];
char longitude1[50];
void loop()
{
 char cdata;
 int fkmph=0;
 int Xaxis=330;
 int Yaxis=330;
 byte a;
 if(GPS.available())
 {
 a=GPS.read();
 while(gps.encode(a)) // encode gps data
 {
 Serial.println("Connection Estbalished Succesfully");
 gps.get_position(&lat,&lon); // get latitude and longitude
 //Serial.print("Position:");
 //Serial.print((lat*0.000001),6);
 //Serial.print(",");
 //Serial.println((lon*0.000001),6);
 lcd.setCursor(0,0);
 lcd.print((lat*0.000001),6);
 lcd.print(" |Speed");
 lcd.setCursor(0,1);
 lcd.print((lon*0.000001),6);
 fkmph = gps.f_speed_kmph(); // speed in km/hr
 //Serial.print("SPEED: ");
 //Serial.println(fkmph);
 lcd.print(" |:");
 lcd.print(fkmph);
 lcd.print(" ");
 //lcd.clear(14);

 ltoa(lat,lati,10);
 //Serial.println(lati);

 ltoa(lon,longi,10);
 //Serial.println(longi);
 itoa(fkmph,Speed,10);
 //Serial.println(Speed);
 Serial.println("Connection Estbalished Succesfully");
 Xaxis=analogRead(Xpin);
 Yaxis=analogRead(Ypin);
 itoa(Xaxis,Xaxi,10);
 //Serial.println(Xaxi);
 itoa(Yaxis,Yaxi,10);
 //Serial.println(Yaxi);
 itoa(speed_count,SpeedCount,5);
 //Serial.print("X :");
 //Serial.println(Xaxis);
 //Serial.print("Y :");
 //Serial.println(Yaxis);
 //Serial.println();
 if (fkmph>=10)
 {
 if(toggle_state == 0){
 SendMessage();
 toggle_state =1;
 }
 }
 else {
 toggle_state = 0;
 }

 if (Xaxis>=390 || Yaxis>=390 || Xaxis<=270 || Yaxis<=270)
 {
 AccidentMessage();
 }
 }
 }
}
void Request()
{
 Wire.write(lati);
 Wire.write(",");
 Wire.write(longi);
 Wire.write(",");
 Wire.write(Xaxi);
 Wire.write(",");
 Wire.write(Yaxi);
 Wire.write(",");
 Wire.write(SpeedCount);
 Wire.write(",");
 Wire.write(Speed);
 Wire.write("\n");
}
void SendMessage()
{
 GSMSerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
 delay(1000); // Delay of 1000 milli seconds or 1 second
 GSMSerial.println("AT+CMGS=\"+91***********\"\r"); // Replace x with mobile number
 delay(1000);
 GSMSerial.println("Your vehicle crossed the speed limit of 10kmh"); // The SMS text you want to send
 delay(100);
 GSMSerial.println((char)26);// ASCII code of CTRL+Z
 delay(1000);
 speed_count++;
}
void AccidentMessage()
{
 GSMSerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
 delay(1000); // Delay of 1000 milli seconds or 1 second
 GSMSerial.println("AT+CMGS=\"+91**********\"\r"); // Replace x with mobile number
 delay(1000);
 GSMSerial.println("Accident Alert......!"); // The SMS text you want to send
 GSMSerial.print("https://www.google.com/maps/search/?api=1&query=");
 GSMSerial.print(lat*0.000001,6);
 GSMSerial.print("%2C");
 GSMSerial.print(lon*0.000001,6);
 delay(100);
 GSMSerial.println((char)26); // ASCII code of CTRL+Z
 delay(1000);
} 
