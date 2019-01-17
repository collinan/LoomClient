#include <SPI.h>
#include <WiFi101.h>
//#include <arduino_secrets.h>


//char ssid[]=SECRET_SSID;//your network SSID (name)
//char pass[]=SECRET_PASS;//your network password (use for WPA, or use a key for WEP)


char ssid[]="SDTeam6";//your network SSID (name)
char pass[]="password2";//your network password (use for WPA, or use a key for WEP)

int KeyIndex=0;//your network key Index number (for WEP)

int status = WL_IDLE_STATUS;// the WiFi radio's status


//Socket
const uint16_t port = 8090;
const char * host = "192.168.1.122";//ip on which server is running



void setup(){
	WiFi.setPins(8,7,4,2);

	//Initialize serial and wait for port to open
	Serial.begin(9600);
	while(!Serial){
		;
	}

	WiFiConnect();

}

/*-----------------Main Loop-----------------*/
void loop(){


	

	ServerCommunication();
	
}
/*-----------------Main Loop-----------------*/



void WiFiConnect(){

	//attempt to connect to  WiFi network:
	while(status != WL_CONNECTED){
		Serial.print("Attempting to connect to SSID: ");
		Serial.println(ssid);

		//Connect to WPA/WPA2 network
		status = WiFi.begin(ssid, pass);
		//Connect to WPE
		//status = WiFI.begin(ssid,KeyIndex,key);

		//wait 10 seconds for connection
		delay(10000);
	}

	//Once you are connected
	Serial.print("You're conected to the network");
	printWiFiStatus();
}

void printWiFiStatus(){
	//print the SSID of the network you're attached to:
	Serial.print("SSID: ");
	Serial.println(WiFi.SSID());

	//print your WiFi sheild's IP address:
	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");
	Serial.println(ip);

	//print the received signal strength:
	long rssi = WiFi.RSSI();
	Serial.print("Signal strength (RSSI):");
	Serial.print(rssi);
	Serial.println(" dBm");

}

void ServerCommunication(){

Serial.print("Attempting to connect to Host:");
Serial.print(host);
Serial.print(" : ");
Serial.print("Port");
Serial.println(port);

WiFiClient client;

if(!client.connect(host,port)){
Serial.println("Connection failed");
delay(5000);
return;
}

Serial.println("Connected to server successful!");

//sending data to server
Serial.println("Sending Data to server");
if(client.connected()){
  client.println("This is my data sent by client");
}

//wait for server to sent message
//timeout after 6 seconds
unsigned long timeout = millis();
while (client.available() == 0){ //while no bytes recived
if(millis() - timeout > 6000){
Serial.println("-----Done waiting-----");
client.stop();
delay(5000);
return;
}
}

//Server message received
Serial.println("Server message received");
while(client.available()){
char ch = static_cast<char>(client.read());
Serial.print(ch);
}

Serial.println();

//End Connection
Serial.println("Ending connection with Server");
client.stop(); 


delay(120000);
Serial.println();
return;
}











