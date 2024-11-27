#ifndef __BLEINTERFACE_H_
#define __BLEINTERFACE_H_

#include <stdint.h>

void ble_on();
void ble_off();

void ble_notify_bpm();

extern bool ble_new_value_received;
extern uint16_t ble_bpm_received;
extern bool ble_play_status_received;

#endif