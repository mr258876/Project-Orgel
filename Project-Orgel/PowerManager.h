#ifndef _POWERMANAGER_H_
#define _POWERMANAGER_H_

#include <Arduino.h>

/*
    @brief Voltage enum
*/
enum
{
    PM_VOLTAGE_5V = 0,
    PM_VOLTAGE_9V,
    PM_VOLTAGE_12V,
    PM_VOLTAGE_15V,
    PM_VOLTAGE_20V,
    PM_VOLTAGE_NONE = 255,
};
typedef uint8_t pm_voltage_t;

/*
    @brief Power manager class for CH224K
*/
class PowerManager
{
private:
    uint8_t PG, CFG1, CFG2, CFG3;
    pm_voltage_t current_level = PM_VOLTAGE_NONE;

public:
    PowerManager() { PG, CFG1, CFG2, CFG3 = 255; };
    PowerManager(uint8_t PG, uint8_t CFG1, uint8_t CFG2, uint8_t CFG3)
    {
        this->PG = PG;
        this->CFG1 = CFG1;
        this->CFG2 = CFG2;
        this->CFG3 = CFG3;
    };
    ~PowerManager() {};

    inline void begin()
    {
        if (PG == -1)
            return;

        pinMode(PG, INPUT_PULLUP);
        pinMode(CFG1, OUTPUT);
        pinMode(CFG2, OUTPUT);
        pinMode(CFG3, OUTPUT);

        current_level = PM_VOLTAGE_5V;
        acquireVoltage(current_level);
    };

    /*
        @brief Check power good singal
    */
    inline bool powerGood() { return PG == -1 ? true : !digitalRead(PG); };

    /*
        @brief
    */
    inline void acquireVoltage(pm_voltage_t voltage)
    {
        if (PG == -1)
            return;

        current_level = voltage;
        switch (current_level)
        {
        case PM_VOLTAGE_5V:
            digitalWrite(CFG1, 1);
            digitalWrite(CFG2, 0);
            digitalWrite(CFG3, 0);
            break;
        case PM_VOLTAGE_9V:
            digitalWrite(CFG1, 0);
            digitalWrite(CFG2, 0);
            digitalWrite(CFG3, 0);
            break;
        case PM_VOLTAGE_12V:
            digitalWrite(CFG1, 0);
            digitalWrite(CFG2, 0);
            digitalWrite(CFG3, 1);
            break;
        case PM_VOLTAGE_15V:
            digitalWrite(CFG1, 0);
            digitalWrite(CFG2, 1);
            digitalWrite(CFG3, 1);
            break;
        case PM_VOLTAGE_20V:
            digitalWrite(CFG1, 0);
            digitalWrite(CFG2, 1);
            digitalWrite(CFG3, 0);
            break;
        default:
            break;
        }
    };

    /*
        @brief Get current acquired power level
    */
    pm_voltage_t getCurrentVoltageLevel() { return current_level; };
};

#endif