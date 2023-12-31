/*
  Repeating Wifi Web Client

  This sketch connects to a a web server and makes a request
  using an LinkIt 7697 HDK.

  Circuit:
  * LinkIt 7697 HDK to pins SPI pins and pin 7

  created 23 April 2012
  modified 31 May 2012
  by Tom Igoe
  modified 13 Jan 2014
  by Federico Vanzati
  modified Jan 2017
  by MediaTek Labs
  
  http://www.arduino.cc/en/Tutorial/WifiWebClientRepeating
  This code is in the public domain.
*/

#include <LWiFi.h>

char ssid[] = "vivo 1935";      //  your network SSID (name)
char pass[] = "12345678";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

// Initialize the Wifi client library
WiFiClient client;

// server address:
char server[] = "192.168.43.1";
//IPAddress server(64,131,82,241);

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds

void setup() {
	//Initialize serial and wait for port to open:
	Serial.begin(9600);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	// attempt to connect to Wifi network:
	while (status != WL_CONNECTED) {
		Serial.print("Attempting to connect to SSID: ");
		Serial.println(ssid);
		// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
		status = WiFi.begin(ssid, pass);
	}
	// you're connected now, so print out the status:
	printWifiStatus();
}

void loop() {
	// if there's incoming data from the net connection.
	// send it out the serial port.  This is for debugging
	// purposes only:
	while (client.available()) {
		char c = client.read();
		Serial.write(c);
	}

	// if ten seconds have passed since your last connection,
	// then connect again and send data:
	if (millis() - lastConnectionTime > postingInterval) {
		httpRequest();
	}

}

// this method makes a HTTP connection to the server:
void httpRequest() {
	// close any connection before send a new request.
	// This will free the socket on the WiFi shield
	client.stop();

	// if there's a successful connection:
	if (client.connect(server, 1880)) {
		Serial.println("connecting...");
		// send the HTTP PUT request:
		client.println("GET /data HTTP/1.1");
		client.println("Host: 192.168.43.1");
		client.println("User-Agent: ArduinoWiFi/1.1");
		client.println("Connection: close");
		client.println();

		// note the time that the connection was made:
		lastConnectionTime = millis();
	} else {
		// if you couldn't make a connection:
		Serial.println("connection failed");
	}
}


void printWifiStatus() {
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
