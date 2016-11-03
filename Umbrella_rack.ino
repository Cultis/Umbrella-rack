// Wifi access point
#define SSID        "XXXX"                          
#define PASS        "XXXX"                           

// Weather Underground setup
#define DEST_HOST   "api.wunderground"             
#define DEST_IP     "192.254.235.21"                 

void setup() 
{

// Initialize the BUILTIN_LED pin as an output 
  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT); 
}

void loop() {

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
