#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

//Firebase settings
#define FIREBASE_HOST "carpark1-eeeef.firebaseio.com"
#define FIREBASE_AUTH "OY6jX0N0GcCphcsQZnX3BoDk56NS20ZpnbuTUXXp"

//Wi-Fi settings
#define WIFI_SSID "harshank"
#define WIFI_PASSWORD "10203040"
#define trigPin 12
#define echoPin 14
#define USONIC_DIV 0.034

FirebaseData firebaseData;
int per;

void setup() {
  // put your setup code here, to run once:
  
Serial.begin(115200);                                   // Select the same baud rate if you want to see the datas on Serial Monitor

  Serial.println("Serial communication started\n\n");  
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);


  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // connect to firebase

  Firebase.reconnectWiFi(true);
  delay(1000);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
}

void loop() {
  // put your main code here, to run repeatedly:
long duration;
long distance;


  
digitalWrite(trigPin, HIGH);
delayMicroseconds(11);
digitalWrite(trigPin, LOW);


duration = pulseIn(echoPin, HIGH);
distance= duration * USONIC_DIV/2;
per = map(distance, 6, 21, 100, 0);
Firebase.setInt(firebaseData, "/ledStatus4", per);


Serial.println(per);

delay(1000);
}
