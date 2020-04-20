#config.json should be in /home/fd/microbit-samples

#include "MicroBit.h"
MicroBit uBit;

#define EVENT_ID    8888
#define DC_BUTTON_LEFT   76
#define DC_BUTTON_RIGHT  82
#define DC_BUTTON_STOP   82

int fd = 0;

void onConnected(MicroBitEvent) {
   //uBit.display.print("C");
}

void onDisconnected(MicroBitEvent){
   //uBit.display.print("D");
}

void onControllerEvent(MicroBitEvent e) {
	if (e.value == DC_BUTTON_LEFT)  {
		
		if(fd >= 180) {
			fd = 180;
		} else {
			fd = fd + 5;
		}

		//uBit.io.P0.setServoPulseUs(50);
        uBit.io.P0.setServoValue(fd);
        //uBit.sleep(400);
	}

	if (e.value == DC_BUTTON_RIGHT)  {
		if(fd <= 0) {
			fd = 0;
		} else {
			fd = fd - 5;
		}

		//uBit.io.P0.setServoPulseUs(50);
		uBit.io.P0.setServoValue(fd);
        //uBit.sleep(400);

	}

}

int main() {
    uBit.init();
	uBit.display.scroll("DC");

	uBit.messageBus.listen(EVENT_ID, 0, onControllerEvent);
	uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_CONNECTED, onConnected);
    uBit.messageBus.listen(MICROBIT_ID_BLE, MICROBIT_BLE_EVT_DISCONNECTED, onDisconnected);
	uBit.messageBus.listen(EVENT_ID, 0, onControllerEvent);

    release_fiber();
}
