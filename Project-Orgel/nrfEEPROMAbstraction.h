#ifndef _NRFEEPROMABSTRACTION_H_ && defined(NRF51)
#define _NRFEEPROMABSTRACTION_H_

#include <Arduino.h>
#include <EEPROM.h>
#include "EepromAbstraction.h"

class NrfEEPROMAbstraction : public EepromAbstraction
{
private:
    EEPROMClass *eepromProxy;

public:
    NrfEEPROMAbstraction(EEPROMClass *proxy)
    {
        this->eepromProxy = proxy;
        EEPROM.begin();             // <- will not work if put in setup()
    }

    void setProxy(EEPROMClass *proxy)
    {
        this->eepromProxy = proxy;
    }

    uint8_t read8(EepromPosition pos) override
    {
        uint8_t res = 0;
        eepromProxy->get(pos, res);
        return res;
    }

    uint16_t read16(EepromPosition pos) override
    {
        uint16_t res = 0;
        eepromProxy->get(pos, res);
        return res;
    }

    uint32_t read32(EepromPosition pos) override
    {
        uint32_t res = 0;
        eepromProxy->get(pos, res);
        return res;
    }

    void write8(EepromPosition pos, uint8_t val) override
    {
        if (read8(pos) != val)
        {
            eepromProxy->put(pos, val);
        }
    }

    void write16(EepromPosition pos, uint16_t val) override
    {
        if (read16(pos) != val)
        {
            eepromProxy->put(pos, val);
        }
    }

    void write32(EepromPosition pos, uint32_t val) override
    {
        if (read32(pos) != val)
        {
            eepromProxy->put(pos, val);
        }
    }

    void readIntoMemArray(uint8_t *memDest, EepromPosition romSrc, uint8_t len) override
    {
        for (int i = 0; i < len; i++)
        {
            eepromProxy->get(romSrc + i, *memDest);
            memDest++;
        }
    }

    void writeArrayToRom(EepromPosition romDest, const uint8_t *memSrc, uint8_t len) override
    {
        for (int i = 0; i < len; i++)
        {
            eepromProxy->write(romDest + i, *memSrc);
            memSrc++;
        }
    }
};

#endif // _NVSEEPROMABSTRACTION_H_