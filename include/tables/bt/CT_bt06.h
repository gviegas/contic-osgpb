//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT06_H
#define CT_BT06_H

#include <stdint.h>

// BT06 - Utility Information
//
typedef struct {
  char owner_name[20];
  char utility_division[20];
  uint8_t service_point[10]; // NOTE: Packed BCD encoding
  uint8_t electrical_addr[10]; // NOTE: Packed BCD encoding
  uint8_t device_id[10]; // NOTE: Packed BCD encoding
  uint8_t utility_serial_number[10]; // NOTE: Packed BCD encoding
  uint8_t customer_id[10]; // NOTE: Packed BCD encoding
  char coordinate_1[10];
  char coordinate_2[10];
  char coordinate_3[10];
  char tariff_id[8];
  char configuration_sw_vendor[4];
  uint8_t conf_sw_version_number;
  uint8_t conf_sw_revision_number;
  char programmation_sw_vendor[4];
  uint8_t prog_sw_version_number;
  uint8_t prog_sw_revision_number;
  char programmer_name[10];
  char miscellane_id[30];
} ctBT06_t;

#endif // CT_BT06_H