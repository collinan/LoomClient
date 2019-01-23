#include <SPI.h>
#include <WiFi101.h>
#include <DHT.h>// temperatue and Humidity sensor lib
//#include <arduino_secrets.h>

#define DHTPIN 6 //temperatue and Humidity sensor
#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

//char ssid[]=SECRET_SSID;//your network SSID (name)
//char pass[]=SECRET_PASS;//your network password (use for WPA, or use a key for WEP)


//char ssid[]="SDTeam6";//your network SSID (name)
char ssid[]="robot";//your network SSID (name)
char pass[]="password2";//your network password (use for WPA, or use a key for WEP)

String DeviceID ="123456";

int KeyIndex=0;//your network key Index number (for WEP)

int status = WL_IDLE_STATUS;// the WiFi radio's status


//Socket
const uint16_t port = 8090;
//const char * host = "192.168.1.122";//ip on which server is running
const char * host = "10.0.1.2";//ip on which server is running


void setup(){
	WiFi.setPins(8,7,4,2);

	//Initialize serial and wait for port to open
	Serial.begin(9600);
	while(!Serial){
		;
	}

Serial.println(F("DHTxx test!"));

  dht.begin();
	//WifiSecureConnect();
	WifiOpenConnect();
}

/*-----------------Start: Main Loop-----------------*/
void loop(){


  ReadTempHum();

delay(12000);
	//ServerCommunication();

}
/*-----------------End:Main Loop-----------------*/


/*-----------------Start: Secure Wifi Connect -----------------*/
void WifiSecureConnect(){

	//attempt to connect to  WiFi network:
	while(status != WL_CONNECTED){
		//Serial.print("Attempting to connect to SSID: ");
		//Serial.println(ssid);

		//Connect to WPA/WPA2 network
		status = WiFi.begin(ssid, pass);
		//Connect to WPE
		//status = WiFI.begin(ssid,KeyIndex,key);

		//wait 10 seconds for connection
		delay(10000);
	}

	//Once you are connected
	//Serial.print("You're conected to the network");
	printWiFiStatus();
}
/*-----------------End: Secure Wifi Connect -----------------*/

/*-----------------Start: Open Wifi Connect -----------------*/
void WifiOpenConnect(){
	while (status != WL_CONNECTED){
		Serial.print("Attempting to connct to open SSID: ");
	//	Serial.println(ssid);
		status =WiFi.begin(ssid);

		delay (10000);
	}
	printWiFiStatus();
	
}
/*-----------------End: Open Wifi Connect -----------------*/


/*-----------------Start: Print wifi Status -----------------*/
void printWiFiStatus(){
	//print the SSID of the network you're attached to:
	//Serial.print("Network SSID: ");
	//Serial.println(WiFi.SSID());
	//print network type:
	byte encryption = WiFi.encryptionType();
	//Serial.print(" Network Encryption Type:");
	//Serial.println(encryption, HEX);
	//Serial.println(" ------------------------------------------");

	//print your WiFi sheild's IP address:
	IPAddress ip = WiFi.localIP();
	//Serial.print("My IP Address: ");
	//Serial.println(ip);

	//print your MAC address:
	byte mac[6];
	WiFi.macAddress(mac);
	//Serial.print("My MAC address: ");
	//Serial.print(mac[5],HEX);
	//Serial.print(":");
//	Serial.print(mac[4],HEX);
//	Serial.print(":");
//	Serial.print(mac[3],HEX);
//	Serial.print(":");
//	Serial.print(mac[2],HEX);
//	Serial.print(":");
//	Serial.print(mac[1],HEX);
//	Serial.print(":");
//	Serial.println(mac[0],HEX);

	//print the received signal strength:
	long rssi = WiFi.RSSI();
//	Serial.print("Signal strength (RSSI):");
//	Serial.print(rssi);
//	Serial.println(" dBm");
}
/*-----------------End: Print wifi Status -----------------*/


/*-----------------Start: Server Communication-----------------*/
void ServerCommunication(String ID, String msg){

//	Serial.print("Attempting to connect to Server/Host:");
//	Serial.print(host);
//	Serial.print(" : ");
//	Serial.print("Port");
//	Serial.println(port);

	WiFiClient client;

	if(!client.connect(host,port)){
		Serial.println("Connection failed");
		delay(5000);
		return;
	}

//	Serial.println("Connected to server successful!");

String message= String("Device: "+ID+" "+msg+"$$");
	//sending data to server
//	Serial.print("Sending Data to server:");
//  Serial.println("msg");
	if(client.connected()){
		//client.println("This is my data sent by client");
   client.println(message);
	}

	//wait for server to sent message
	//timeout after 6 seconds
	unsigned long timeout = millis();
	while (client.available() == 0){ //while no bytes recived
		if(millis() - timeout > 6000){
//			Serial.println("-----Done waiting-----");
			client.stop();
			delay(5000);
			return;
		}
	}

	//Server message received
//	Serial.println("Server message received");
	while(client.available()){
		char ch = static_cast<char>(client.read());
//		Serial.print(ch);
	}

//	Serial.println();

	//End Connection
//	Serial.println("Ending connection with Server");
	client.stop(); 


	
//	Serial.println();
	return;
}
/*-----------------Start: Server Communication-----------------*/





/*-----------------Start: Temperature and Humidity Sensor-----------------*/
void ReadTempHum(){
delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  String Humidity= String(h,3);
  String TempC = String(t,3); 
  String TempF = String(f,3);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


// Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);


Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

String message = String("Humidity: "+Humidity+"%  Temperature: "+TempC +"°C "+ TempF+ "°F");  
//send to server
ServerCommunication(DeviceID, message);
}
/*-----------------End: Temperature and Humidity Sensor-----------------*/








