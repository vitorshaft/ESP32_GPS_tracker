#include <Arduino.h>
 // Define the RX and TX pins for Serial 2
 #define RXD2 16
 #define TXD2 17
 
 #define GPS_BAUD 9600
 
 // Create an instance of the HardwareSerial class for Serial 2
 HardwareSerial gpsSerial(2);
 double latitude;
 double longitude;
 
void split(String texto){
  int i1 = texto.indexOf(',');
  String satelite = texto.substring(0, i1);

  int it;
  int ia;
  int i2;
  int i3;
  int i4;

  String latitudeDeg;
  String latitudeMin;
  String hemisferio;
  String longitudeDeg;
  String longitudeMin;
  String hemisLong;

  if(satelite == "GPGLL"){
    i2 = texto.indexOf(',', i1+1);
    i3 = texto.indexOf(',', i2+1);
    i4 = texto.indexOf(',', i3+1);

    latitudeDeg = texto.substring(i1 + 1, i1+3);
    latitudeMin = texto.substring(i1+4, i2);
    hemisferio = texto.substring(i2 + 1, i3);
    longitudeDeg = texto.substring(i3 + 1, i3+3);
    longitudeMin = texto.substring(i3+4, i4);
    hemisLong = texto.substring(i4 + 1, i4+3);
  }
  else if(satelite == "GPGGA"){
    it = texto.indexOf(',', i1+1);
    i2 = texto.indexOf(',', it+1);
    i3 = texto.indexOf(',', i2+1);
    i4 = texto.indexOf(',',i3+1);
    
    latitudeDeg = texto.substring(it + 1, it+3);
    latitudeMin = texto.substring(it+4, i2);
    hemisferio = texto.substring(i2 + 1, i3);
    longitudeDeg = texto.substring(i3 + 1, i3+3);
    longitudeMin = texto.substring(i3+4, i4);
    hemisLong = texto.substring(i4 + 1, i4+3);
  }

  else if(satelite == "GPRMC"){
    it = texto.indexOf(',', i1+1);
    ia = texto.indexOf(',', it+1);
    i2 = texto.indexOf(',', ia+1);
    i3 = texto.indexOf(',', i2+1);
    i4 = texto.indexOf(',', i3+1);
    
    latitudeDeg = texto.substring(ia + 1, ia+3);
    latitudeMin = texto.substring(ia+4, i2);
    hemisferio = texto.substring(i2 + 1, i3);
    longitudeDeg = texto.substring(i3 + 1, i3+3);
    longitudeMin = texto.substring(i3+4, i4);
    hemisLong = texto.substring(i4 + 1, i4+3);
  }

  else{
    latitudeDeg = "00";
    latitudeMin = "00.00000";
    hemisferio = "X";
    longitudeDeg = "00";
    latitudeMin = "00.00000";
    hemisLong = "Y";
  }

  Serial.println(satelite);
  Serial.println(latitudeDeg);
  Serial.println(hemisferio);
  Serial.println(longitudeDeg);
  Serial.println(hemisLong);

  float latitude = latitudeDeg.toFloat()+(latitudeMin.toFloat()/60.00);
  float longitude = longitudeDeg.toFloat()+(longitudeMin.toFloat()/60.00);

  if(hemisLong == "W"){
    longitude*=-1;
  }
  if(hemisferio == "S"){
    latitude*=-1;
  }
/* 
  if(coord){
    if(hemisLong == "W"){
      longitude*=-1;
    }
    //return(longitude);
  }
  else{
    if(hemisferio == "S"){
      latitude*=-1;
    }
    //return(latitude);
  } 
  */
}

 void setup(){
   // Serial Monitor
   Serial.begin(9600);
   
   // Start Serial 2 with the defined RX and TX pins and a baud rate of 9600
   gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
   Serial.println("Serial 2 started at 9600 baud rate");
 }
 
 void loop(){
  /*
   while (gpsSerial.available() > 0){
     // get the byte data from the GPS
     char gpsData = gpsSerial.read();
     Serial.print(gpsData);
   }
  */
   String strGPS = gpsSerial.readStringUntil('$');
   Serial.println(strGPS);
   Serial.println("Split: ");
   split(strGPS);
   Serial.print("Latitude: ");
   Serial.println(latitude, 6);
   Serial.print("longitude: ");
   Serial.println(longitude, 6);
   
   delay(1000);
   Serial.println("-------------------------------");
 }