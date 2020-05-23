/* DHT */

#include "DHT.h"
#include <ESP8266WiFi.h>
const char WiFiPassword[] = "12345678";
const char AP_NameChar[] = "PROYECTOFinal" ;

#define DHTPIN D2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

const int FOTOPIN = A0;
int valorSensor = 0;

WiFiServer server(80);//http://192.168.4.1/
 
String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><title>PROYECTO Final</title></head><body><div id='main'><h2>PROYECTO Final</h2>";
String html_2 = "<form id='F1' action='HUMEDAD'>Humedad</form><br>";
String html_3 = "<form id='F2' action='TEMPERATURA'>Temperatura</form><br>";
String html_4 = "<form id='F3' action='LUMINOSIDAD'>Luminosidad</form><br>";
String html_5 = "</div></body></html>";

String request = "";

void setup() {
  boolean conn = WiFi.softAP(AP_NameChar, WiFiPassword);
  server.begin();

   // put your setup code here, to run once:
  //Serial.begin(115200);
  Serial.println("DHTxx test!");

  dht.begin();

  pinMode(FOTOPIN, INPUT);
  Serial.begin(115200);
  //Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  //float luminosidad = analogRead(FOTOPIN);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");

  }

  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F");
  Serial.print(" \t");
  valorSensor = analogRead(FOTOPIN);
  valorSensor = valorSensor*95;
  Serial.print("\tValor del luminosidad: ");
  Serial.println(valorSensor);


      // Check if a client has connected
    WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    // Read the first line of the request
    request = client.readStringUntil('\r');

    client.flush();
    
    client.print( header );
    client.print( html_1 );
    client.print( html_2 );
    client.print( html_3 );
    client.print( html_4);
    client.print( html_5);
  }
