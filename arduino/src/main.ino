#include <SPI.h>
#include <Reader.h>
#include <Button.h>

// flags
String okCode = "00";
String state = "id";
bool started = false;

// nfc reader
#define RST_PIN 10
#define SS1_PIN 9
MFRC522 nfc(SS1_PIN, RST_PIN);
Reader reader(nfc, RST_PIN, okCode);

// relais
#define RELAY_PIN 5

// buttons
Button scanBtn = Button(7, INPUT_PULLUP);
Button reportBtn = Button(6, INPUT_PULLUP);


void setup() {
	Serial.begin(115200);
	// reader
	SPI.begin();
	reader.init();
	// reader starts in low power mode
	pinMode(RST_PIN, OUTPUT);
	digitalWrite(RST_PIN, LOW);
	// relais
	pinMode(RELAY_PIN, OUTPUT);
	digitalWrite(RELAY_PIN, LOW);
}

void loop() {
	if (Serial.available() > 0) {
		char cmd = Serial.read();
		// init
		if (cmd == '#') {
			lock();
			started = true;
		}
		else if (cmd == '$') {
			unlock();
		}
	}
	if (started) {
		if (state != "re") check();
		if (scanBtn.uniquePress()) {
			delay(100);
			if (state == "re") idle();
			else analyse();
		}
		if (reportBtn.uniquePress()) { //  && state != "sc" ?
			delay(100);
			state = "re";
			Serial.print(state);
		}
		// delay(100);
	}
}

void check() {
	String result = reader.getPayload();
	if (result == "nok") idle();
	else state = result;
}

void analyse() {
	if (state != "id") {
		Serial.print("sc");
		delay(1950);
		check();
		Serial.print(state);
		// if (state == okCode) unlock();
		// else lock();
	}
}

void unlock() {
	digitalWrite(RELAY_PIN, HIGH);
}

void lock() {
	digitalWrite(RELAY_PIN, LOW);
}

void idle() {
	String prevState = state;
	state = "id";
	if (prevState != state) {
		Serial.print(state);
		lock();
	}
}
