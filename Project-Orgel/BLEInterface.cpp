#include "BLEInterface.h"
#include <NimBLEDevice.h>
#include "Project-Orgel_menu.h"
#include "lv_i18n.h"

bool ble_new_value_received = false;
uint16_t ble_bpm_received = 0;
bool ble_play_status_received = false;

static bool BLEStarted = false;

static NimBLEServer *pBLEServer = nullptr;
static NimBLEAdvertising *pBLEAdvertising = nullptr;
static NimBLEService *pOrgelService = nullptr;
static NimBLECharacteristic *pOrgelCharacteristic = nullptr;

static const NimBLEUUID BLE_ORGEL_SERVICE_UUID(0x00003200, 0x0000, 0x1000, 0x74EE55C0F7E56C13); // 0x74EE55C0F7E56C13 is 16-digit MD5 of "Project-Orgel"
static const NimBLEUUID BLE_ORGEL_CHAR_UUID(0x00003201, 0x0000, 0x1000, 0x74EE55C0F7E56C13);

static void set_bpm_values(NimBLECharacteristic *pCharacteristic)
{
    uint8_t buf[4];
    buf[0] = 0;
    buf[1] = menuPlay.getBoolean() ? 1 : 0;
    uint16_t bpm = menuBPM.getCurrentValue();
    memcpy(buf + 2, &bpm, 2);
    pCharacteristic->setValue(buf, 4);
}

// Callback class for handling API characteristic read and write events
class OrgelInCharacteristicCallbacks : public NimBLECharacteristicCallbacks
{
    void onWrite(NimBLECharacteristic *pCharacteristic)
    {
        /* read */
        NimBLEAttValue value = pCharacteristic->getValue();
        if (value.length() == 4)
        {
            ble_play_status_received = value.data()[1];
            memcpy(&ble_bpm_received, value.data() + 2, 2);
            ble_new_value_received = true;
        }
        else if (value.length() == 20) {
            // value.data();
        }
    }

    void onRead(NimBLECharacteristic *pCharacteristic)
    {
        set_bpm_values(pCharacteristic);
    }
};

static OrgelInCharacteristicCallbacks orgelInCharCb;

void interface_setup()
{
    // Setup current time service
    pOrgelService = pBLEServer->createService(BLE_ORGEL_SERVICE_UUID);
    pOrgelCharacteristic = pOrgelService->createCharacteristic(
        BLE_ORGEL_CHAR_UUID,
#if defined(ESP_PLATFORM)
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE_ENC | NIMBLE_PROPERTY::READ_ENC | NIMBLE_PROPERTY::NOTIFY // Only allow paired devices to write
#else
        NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY // Allow any device to read/write
#endif
    );
    pOrgelCharacteristic->setCallbacks(&orgelInCharCb);
    pOrgelService->start();

    // Add service to advertising
    pBLEAdvertising->addServiceUUID(pOrgelService->getUUID());
}

// class ServerCallbacks : public NimBLEServerCallbacks
// {
// private:
//     uint32_t pin = 0;
// public:
//     bool onConfirmPIN(uint32_t providedPIN) override
//     {
//         return (this->pin == providedPIN);
//     }

//     uint32_t onPassKeyRequest() override
//     {
//         randomSeed(analogRead(0));
//         if (renderer.getDialog() && !renderer.getDialog()->isInUse())
//         {
//             this->pin = random(0, 1000000);
//             char buf[7];
//             ltoaClrBuff(buf, pin, 6, '0', sizeof(buf));
//             renderer.getDialog()->setButtons(BTNTYPE_NONE, BTNTYPE_OK);
//             renderer.getDialog()->show(_("Pairing PIN"), true);
//             renderer.getDialog()->copyIntoBuffer(buf);
//         }
//         return this->pin;
//     }
// };

// static ServerCallbacks serverCb;

void ble_on()
{
    if (!BLEStarted)
    {
        NimBLEDevice::init("Project-Orgel");

        // Set IO Cap to Display only, so we will display PIN code on pairing
        // NimBLEDevice::setSecurityIOCap(BLE_HS_IO_DISPLAY_ONLY);
        NimBLEDevice::setSecurityIOCap(BLE_HS_IO_NO_INPUT_OUTPUT);

        // Enable IRK distribution from both ends
        NimBLEDevice::setSecurityInitKey(BLE_SM_PAIR_KEY_DIST_ENC | BLE_SM_PAIR_KEY_DIST_ID);
        NimBLEDevice::setSecurityRespKey(BLE_SM_PAIR_KEY_DIST_ENC | BLE_SM_PAIR_KEY_DIST_ID);

        // Enable pairing & RPA
#if defined(ESP_PLATFORM)
        NimBLEDevice::setOwnAddrType(BLE_OWN_ADDR_RANDOM, false);
        NimBLEDevice::setSecurityAuth(true, true, true);
#else
        NimBLEDevice::setSecurityAuth(false, false, false);
#endif

        pBLEServer = NimBLEDevice::createServer();

        pBLEAdvertising = NimBLEDevice::getAdvertising();
        interface_setup();
        pBLEAdvertising->start();

        // pBLEServer->setCallbacks(&serverCb);

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
        set_bpm_values(pOrgelCharacteristic);
        pOrgelCharacteristic->notify();
    }
}