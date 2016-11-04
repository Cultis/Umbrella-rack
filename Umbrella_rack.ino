#include <ESP8266WiFi.h>

// Wifi access point
#define SSID        "XXXX"                                        // Wifi SSID
#define PASS        "XXXX"                                        // WiFi Password

// Weather Underground setup
#define DEST_HOST   "api.wunderground"                            // API site host
#define DEST_IP     "192.254.235.21"                              // API site IP address

#define TIMEOUT     5000                                          //ms

int APIrain;                                                   

void setup()  
{

// Set datarate
  Serial.begin(115200);                 
  Serial.setTimeout(TIMEOUT);             
  
  delay(2000);                           

// Define LED pins as an output 
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT); 

// Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(SSID);

  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
}

void loop() 
{
  String cmd;                                                    // Command string to the ESP8266
  
  // Build HTTP request.
  cmd = "GET ";
  cmd += "http://api.wunderground.com/api/<API KEY>/forecast/q/autoip.json";
  cmd += " HTTP/1.1\r\n\r\n";

  Serial.print(APIrain);
  
  // LED triggers based on API data
  if (APIrain > 10)                                               // LEDs off when rain < 10%
  {
    digitalWrite(2, LOW);            
    digitalWrite(5, LOW); 
    digitalWrite(4, LOW);
  }
  if (APIrain >= 10 && APIrain <= 30)                             // 1 LED on when pop >= 10% and <= 30%                          
  {
    digitalWrite(2, HIGH);
    digitalWrite(5, LOW); 
    digitalWrite(4, LOW);
  }
  
  if (APIrain > 30 && APIrain <= 60)                              // 2 LEDs on when pop > 30% and <= 60%
  {
    digitalWrite(2, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW); 
  }
    
  if (APIrain > 60)                                               // 3 LEDs on when pop > 60%
  {
    digitalWrite(2, HIGH);            
    digitalWrite(5, HIGH); 
    digitalWrite(4, HIGH);
  }                 

  delay(3*60*1000);                                               // 3 minute delay                             
}
