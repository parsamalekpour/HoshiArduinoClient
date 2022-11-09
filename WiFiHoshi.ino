#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Eshtad R&D";
const char* password = "Eshtad88992988";

#define host  "http://hoshikala.ir/iot/"
#define getApp  "loglastjson.php"
#define setApp "insert.php"
#define token  "uqurzeVV8Sweqtqhhyqw"
#define id  "122"
#define getURL host getApp "?tkn=" token "&id=" id 
#define setURL host setApp "?tkn=" token "&id=" id 
const int interval = 20*1000;
int lastMilis;
String payload;

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP);


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected");
  
  // timeClient.begin();
  // timeClient.update();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  if(millis()>lastMilis + interval){
    lastMilis = millis();
    HTTPClient http;  //Declare an object of class HTTPClient

    String Payload;
    http.begin(getURL);  //Specify request destination
    int httpCode = http.GET();

    if (httpCode > 0) { //Check the returning code
    payload = http.getString();   //Get the request response payload
    int ina = ParsePayload("ina").toInt();
    digitalWrite(LED_BUILTIN,!ina);
    
    } 

    http.end();   //Close connection 
            
  }
   
}

String ParsePayload(char* label){
payload.replace("\"","");
payload.replace("}",",");
payload.replace("{","");
int start = payload.indexOf(label,0) + String(label).length()+1;
int end = payload.indexOf(",",start);
String data = payload.substring(start,end);
Serial.println(data); 
return data; 
}

void GetLastRow(){

}



