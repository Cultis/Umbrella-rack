#include <ESP8266WiFi.h>

// Wifi access point
#define WLAN_SSID   "XXXX"                          
#define WLAN_PASS   "XXXX"                           

// Weather Underground setup
#define DEST_HOST   "api.wunderground"             
#define DEST_IP     "192.254.235.21"      

void setup() 
{
// Set datarate
  Serial.begin(115200);
  delay(10);

// Define LED pins as an output 
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT); 

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}

void loop() 
{
  
// LED triggers based on API data
  if (APIrain => 10 && APIrain <= 30)  
  {
    digitalWrite(16, HIGH);
  }
  
  if (APIrain > 30 && APIrain <= 70) 
  {
    digitalWrite(16, HIGH);
    digitalWrite(5, HIGH); 
  }
    
  if (APIrain > 70)  
  {
    digitalWrite(16, HIGH);            
    digitalWrite(5, HIGH); 
    digitalWrite(4, HIGH);
  }
  else 
  {
    digitalWrite(16, LOW);            
    digitalWrite(5, LOW); 
    digitalWrite(4, LOW);
  }
}
