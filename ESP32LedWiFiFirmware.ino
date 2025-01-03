#include <WiFi.h>
#include <WebSocketsClient.h>

const char* ssid     = "WIFI_NAME"; // setup you WiFi name
const char* password = "WIFI_PASSWORD_123"; // setup your password
const char* websockets_server_host = "192.168.100.18";
const uint16_t websockets_server_port = 5000;

// GPIO ID to control connected LED
const int ledPin =  4;

const int MAX_WIFI_ATTEMPTS_COUNT = 20;

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) 
{
	if (type == WStype_TEXT) 
	{
		//Serial.printf("Message: %s\n", payload);
		String message = String((char*)payload);

		if (message == "LED is on")
		{
			Serial.println("Turning LED ON");
			digitalWrite(ledPin, HIGH);
		}

		if (message == "LED is off")
		{
			Serial.println("Turning LED OFF");
			digitalWrite(ledPin, LOW);
		}
	}
}

void setup()
{
	Serial.begin(115200);
	Serial.print("Setup GPIO...\n");

	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW); // Ensure LED base state is OFF

	Serial.print("Setup WiFi...\n");
	WiFi.disconnect(true, true);
	WiFi.begin(ssid, password);
	uint8_t wifiAttempts = 0;
	while (WiFi.status() != WL_CONNECTED && wifiAttempts < MAX_WIFI_ATTEMPTS_COUNT)
	{
		Serial.print(".");
		delay(1000);
		if(wifiAttempts == 10)
		{
			WiFi.disconnect(true, true);
			WiFi.begin(ssid, password);
		}
		wifiAttempts++;
	}

	if (WiFi.status() == WL_CONNECTED)
	{
		Serial.print("WiFi configured");
		Serial.println(WiFi.localIP());

		Serial.println("Setup web server...\n");
		webSocket.begin(websockets_server_host, websockets_server_port, "/ws");
		webSocket.onEvent(webSocketEvent);
	}
	else
	{
		WiFi.disconnect(true, true);
		Serial.print("WiFi isn't setup");
	}
}

void loop()
{
	webSocket.loop();
}