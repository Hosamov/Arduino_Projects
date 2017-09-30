
#include <SPI.h>
#include <WiFi101.h>
#include <avr/wdt.h>

boolean reading     = false; //TRUE while GET request being received
String  get_request = "";    //Holds the GET request

char ssid[] = "mynetwork";   //  your network SSID (name)
char pass[] = "xxxxxxxxxx";  // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)


#define IDLE_TIMEOUT_MS 3000 //Amount of time to wait with no data
//received before closing connection.

//what page to grab:
#define WEBSITE "arduino.mcoale.com"
#define WEBPAGE "/atwinc1500.txt"

int status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "arduino.mcoale.com";    // name address for Google (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

int connectTimeout = 5000;  //Max time to wait for server connection
int repeat_counter = 0;

void setup() {
  WiFi.setPins(8,7,4);
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  initWifi();
  connect_wifi();
  printWiFiStatus();
}

void loop() {
  repeat_counter++;
  Serial.print(F("Repeat counter: ")); Serial.println(repeat_counter); //Prints out how many times script has repeated
  connect_tcp();
  Serial.print(F("Starting connection to: "));
  Serial.println(WEBSITE);
  Serial.println(F("Connecting"));

  if (client.connected()) {
    Serial.println(F("Connected"));
    make_get_request();
    Serial.println(F("Request sent"));
  } else {
    Serial.println(F("Connection failed"));
    return;
  }
  Serial.println(F("-------------------------------------"));
  /* Read data until either the connection is closed, or hte idle timeout is reached */
  unsigned long lastRead = millis();
  while (client.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
    boolean currentLineIsBlank = true;
    get_request                = "";
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
      if (reading && c == '\n') {      //if reading and there is a new line
        parseGetRequest(get_request);  //parse string: get_request
        break;                         //break out of while loop             
      }
      if (reading) {
        get_request += c;
      }
      if (reading && c == '\n') {
        break;
      }
      if (c == '\n' && currentLineIsBlank)  {
        reading = true; // Found the body of the server response, start reading
      }
      if (c == '\n') {
        currentLineIsBlank = true;
      }
      else if (c != '\r') {
        currentLineIsBlank = false;

      }
    }
  }
  client.stop();

  Serial.println(F(""));
  Serial.println(F("-------------------------------------"));
  Serial.println(F("client disconnected"));
  delay(10000);
  //while (true);
}
//**Code below originally in loop function**
// if there are incoming bytes available
// from the server, read them and print them:
//while (client.available()) {
//char c = client.read();
//Serial.write(c);
// }

// if the server's disconnected, stop the client:
//if (!client.connected()) {
//Serial.println();
//Serial.println("disconnecting from server.");
//client.stop();

// do nothing forevermore:
//  while (true);
//}


String parseGetRequest(String &str) {
  Serial.print(F("Parsing this string: "));
  Serial.println(str);
  int led_index   = str.indexOf("led");
  int led_pin     = str[led_index + 3] - '0';
  int led_val     = str[led_index + 5] - '0';
  executeInstruction(led_pin, led_val);
}

void executeInstruction(int pin, int val) {
  Serial.println(F("Executing instruction"));
  pinMode(pin, OUTPUT);
  digitalWrite(pin, val);
  Serial.println(F("Done!"));
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

//ADDED:
void make_get_request() {
  client.print(F("GET "));
  client.print(WEBPAGE);
  client.print(F(" HTTP/1.1\r\n"));
  client.print(F("Host: ")); client.print(WEBSITE); client.print(F("\r\n"));
  client.print(F("\r\n"));
  client.println();
}


void connect_tcp() {
  uint32_t t = millis();
  do {
    client = client.connect(server, 80);
  }
  while ((!client.connected()) &&
         ((millis() - t) < connectTimeout));
}

void initWifi() {
  Serial.println(F("\nInitializing wireless device ..."));
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println(F("Unable to initialize device. Check connections."));
    while (true);
  }
}

void connect_wifi() {
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    //Connect to WPA/WPA2 network. Change this line if using or WEP network:
    status = WiFi.begin(ssid, pass);

    //wait 10 seconds for connection
    delay(IDLE_TIMEOUT_MS);
  }
  Serial.println("Connected to wifi network");
}





