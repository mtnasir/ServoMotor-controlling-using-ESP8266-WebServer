#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

Servo myservo; 
ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

// Replace with your network credentials 
const char* ssid = "Mohammad.1"; 
const char* password = "N@A@S@I@R";
// Set web server port number to 80 
//WiFiServer server(80); 

IPAddress local_IP(192, 168, 1, 142);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional



void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();
void ServoSetValue();


int DervoPin=D5;


void setup(void){
   myservo.attach(DervoPin);  // attaches the servo on GIO2 to the servo object

  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());// this will display the Ip address of the Pi which should be entered into your browser

  
 
   server.on("/", HTTP_GET, handleRoot);        // Call the 'handleRoot' function when a client requests URI "/"
  //server.on("/login", HTTP_POST, handleLogin); // Call the 'handleLogin' function when a POST request is made to URI "/login"
  server.onNotFound(handleNotFound);           // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"
  server.on("/Servo", ServoSetValue);  
  
  server.begin();                            // Actually start the server
  Serial.println("HTTP server started");
 
}



void handleRoot() {    
    Serial.println("handleRoot");
  server.send(200, "text/plain", "IOT Servo motor control"); 

}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void ServoSetValue(){
   String SSS="NaN";

    Serial.println("ServoRoot");
 Serial.println(server.args());
for (int i = 0; i < server.args(); i++) {
//ip Address:port Number/Servo?ServoAngle=90
// http://192.168.1.142/Servo?ServoAngle=90

 Serial.println(server.argName(i));
if (server.argName(i)=="ServoAngle"){
   SSS=server.arg(i);
 // int ServoAngle1= SSS.toInt();
  myservo.write(SSS.toInt());              // tell servo to go to position in variable 'ServoAngle'
   Serial.println(SSS);
  };
} 
  //analogWrite(D0,Pump);

 String rrr = "The Servo motor angle is = " + SSS;
  Serial.println(rrr);
  server.send(200, "text/plan", rrr);
};

    
void loop(void){
  server.handleClient(); // Listen for HTTP requests from clients
  delay(5);
}
