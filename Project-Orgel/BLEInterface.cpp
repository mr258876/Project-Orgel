#include "BLEInterface.h"
#include <NimBLEDevice.h>
#include "Project-Orgel_menu.h"

static bool BLEStarted = false;

static NimBLEServer *pBLEServer = nullptr;
static NimBLEAdvertising *pBLEAdvertising = nullptr;
static NimBLEService *pOrgelService = nullptr;
static NimBLECharacteristic *pOrgelCharacteristic = nullptr;

static const NimBLEUUID BLE_ORGEL_SERVICE_UUID(0x00003200, 0x0000, 0x1000, 0x74EE55C0F7E56C13); // 0x74EE55C0F7E56C13 is 16-bit MD5 of "Project-Orgel"
static const NimBLEUUID BLE_ORGEL_CHAR_UUID(0x00003201, 0x0000, 0x1000, 0x74EE55C0F7E56C13);

// Callback class for handling API characteristic read and write events
class OrgelInCharacteristicCallbacks : public NimBLECharacteristicCallbacks
{
    void onWrite(NimBLECharacteristic *pCharacteristic)
    {
        /* read */
        NimBLEAttValue value = pCharacteristic->getValue();
        if (value.length() == 3)
        {
            uint16_t current_bpm = 0;
            memcpy(&current_bpm, value.data(), 2);
            menuBPM.setCurrentValue(current_bpm);

            bool current_play_status = false;
            menuPlay.setBoolean(value.data()[2]);
        }
        // Ignore if data size != 3
    }

    void onRead(NimBLECharacteristic *pCharacteristic)
    {
        uint8_t buf[3];
        uint16_t bpm = menuBPM.getCurrentValue();
        memcpy(buf, &bpm, 2);
        buf[2] = menuPlay.getBoolean() ? 1 : 0;
        pCharacteristic->setValue(buf, 3);
    }
};

void interface_setup()
{
    // Setup current time service
    pOrgelService = pBLEServer->createService(BLE_ORGEL_SERVICE_UUID);
    pOrgelCharacteristic = pOrgelService->createCharacteristic(
        BLE_ORGEL_CHAR_UUID,
        NIMBLE_PROPERTY::WRITE| NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY // Allow all devices to write due to web ble bug on windows
    );
    pOrgelCharacteristic->setCallbacks(new OrgelInCharacteristicCallbacks());
    pOrgelService->start();

    // Add service to advertising
    pBLEAdvertising->addServiceUUID(pOrgelService->getUUID());
}

void ble_on()
{
    if (!BLEStarted)
    {
        NimBLEDevice::init("Project-Orgel");

        // Enable IRK distribution from both ends
        NimBLEDevice::setSecurityInitKey(BLE_SM_PAIR_KEY_DIST_ENC | BLE_SM_PAIR_KEY_DIST_ID);
        NimBLEDevice::setSecurityRespKey(BLE_SM_PAIR_KEY_DIST_ENC | BLE_SM_PAIR_KEY_DIST_ID);

        // Enable pairing & RPA
#if defined(ESP_PLATFORM)
        NimBLEDevice::setOwnAddrType(BLE_OWN_ADDR_PUBLIC, false);
#endif
        NimBLEDevice::setSecurityAuth(true, true, true);

        pBLEServer = NimBLEDevice::createServer();

        pBLEAdvertising = NimBLEDevice::getAdvertising();
        interface_setup();
        pBLEAdvertising->start();

        // pBLEServer->setCallbacks(new ServerCallbacks());

        BLEStarted = true;
    }
}
void ble_off()
{
    if (BLEStarted)
    {
        NimBLEDevice::stopAdvertising();
        NimBLEDevice::deinit(true);
        pBLEAdvertising = nullptr;
        pBLEServer = nullptr;
        pOrgelService = nullptr;
        pOrgelCharacteristic = nullptr;

        BLEStarted = false;
    }
}

void ble_notify_bpm()
{
    if (pOrgelCharacteristic)
    {
        uint8_t buf[3];
        uint16_t bpm = menuBPM.getCurrentValue();
        memcpy(buf, &bpm, 2);
        buf[2] = menuPlay.getBoolean() ? 1 : 0;
        pOrgelCharacteristic->setValue(buf, 3);
        pOrgelCharacteristic->notify();
    }
}