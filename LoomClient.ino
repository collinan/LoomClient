#include <SPI.h>
#include <WiFi101.h>
//#include <arduino_secrets.h>


//char ssid[]=SECRET_SSID;//your network SSID (name)
//char pass[]=SECRET_PASS;//your network password (use for WPA, or use a key for WEP)


char ssid[]="SDTeam6";//your network SSID (name)
char pass[]="password2";//your network password (use for WPA, or use a key for WEP)

int KeyIndex=0;//your network key Index number (for WEP)

int status = WL_IDLE_STATUS;// the WiFi radio's status

void setup(){
	WiFi.setPins(8,7,4,2);

	//Initialize serial and wait for port to open
	Serial.begin(9600);
	while(!Serial){
		;
	}

	//attempt to connect ti WiFi network:
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


void loop(){


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

