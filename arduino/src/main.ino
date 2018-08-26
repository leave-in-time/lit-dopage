#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <Button.h>

// reader
PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);
// button
Button button = Button(4, INPUT_PULLUP);
// relais
#define RELAY_1 5
#define RELAY_2 6

String okCode = "p1";
String state = "id";
bool started = false;

void setup(void) {
	Serial.begin(115200);
	// reader
	nfc.begin();
	//relais
	pinMode(RELAY_1, OUTPUT);
	digitalWrite(RELAY_1, LOW);
	pinMode(RELAY_2, OUTPUT);
	digitalWrite(RELAY_2, LOW);
}

void loop(void) {
	if (Serial.available() > 0) {
		char initCmd = Serial.read();
		if (initCmd == '#') {
			state = "id";
			Serial.print(state);
			lock();
			started = true;
		}
	}
	if (started) {
		check();
		if (button.uniquePress()) {
			delay(100);
			analyse();
		}
		// delay(100);
	}
}

void check() {
	if (nfc.tagPresent()) {
		NfcTag tag = nfc.read();
		if (tag.hasNdefMessage()) {
			NdefMessage message = tag.getNdefMessage();
			if (message.getRecordCount() == 1) {
				NdefRecord record = message.getRecord(0);
				int payloadLength = record.getPayloadLength();
				byte payload[payloadLength];
				record.getPayload(payload);
				String payloadAsString = "";
				for (int c = 3; c < payloadLength; c++) {
					payloadAsString += (char)payload[c];
				}
				state = payloadAsString;
			} else idle();
		} else idle();
	} else idle();
}

void analyse() {
	if (state != "id") {
		Serial.print("sc");
		delay(1950);
		check();
		Serial.print(state);
		if (state == okCode) unlock();
		else lock();
	}
}

void unlock() {
	digitalWrite(RELAY_1, HIGH);
	digitalWrite(RELAY_2, HIGH);
}

void lock() {
	digitalWrite(RELAY_1, LOW);
	digitalWrite(RELAY_2, LOW);
}

void idle() {
	String prevState = state;
	state = "id";
	if (prevState != state) {
		Serial.print(state);
		lock();
	}
}
