//
// Created by Gustavo Viegas on 2017/04
//

#ifndef CT_ET11_H
#define CT_ET11_H

#include <stdint.h>
#include <stdbool.h>

// ET11 - MFG Dimension
//
typedef struct {
  uint8_t number_devices;
  uint8_t config_entry_size;
  uint8_t status_entry_size;
  uint8_t on_demand_request_queue_size;
  uint8_t on_demand_request_entry_size;
  uint16_t data_entry_size;
  uint16_t transaction_request_length;
  uint16_t transaction_response_length;
  uint8_t on_demand_write_entry_size;
  uint8_t phase_measurement_data_size;
  uint8_t config_entry_2_size;
  uint8_t osgp_device_onetime_read_queue_size;
  uint8_t mbus_onetime_read_queue_size;
  uint8_t osgp_device_onetime_read_request_entry_size;
  uint8_t mbus_onetime_read_request_entry_size;
  uint8_t number_group_ids;
  uint8_t number_harmonics;
  uint8_t mbus_multicast_msg_length;
  uint8_t et22_alarm_size;
  uint8_t mep_data_sources;
  uint8_t et48_entry_count;
  uint8_t max_critical_events_bitmaps;
  uint8_t et57_entry_count;
  uint8_t time_based_relay_switces;
} ctET11_t;

#endif // CT_ET11_H