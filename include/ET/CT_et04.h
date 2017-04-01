//
// Created by Gustavo Viegas on 2017/04
//

#ifndef CT_ET04_H
#define CT_ET04_H

#include <stdint.h>
#include <stdbool.h>
#include "CT_date.h"

// ET04 - System Information
//
typedef struct {
  uint32_t sequence_number;
  uint8_t transceiver_id[6];
  uint8_t subnet_id;
  uint8_t node_id;
  bool explicit_msg_received : 1;
  bool force_cnfg : 1;
  bool request_transceiver_state : 1;
  bool disable_plc_encryption : 1;
  bool disable_eeprom_lock : 1;
  unsigned transceiver_phase : 3;
  uint8_t rated_frequency;
  uint8_t program_id[8];
  uint8_t self_id[30];
  uint8_t pk_access;
  uint8_t max_power_outages_recorded;
  uint8_t unused1; // don't ask
  uint8_t max_number_te_registers;
  uint16_t registration_current;
  uint16_t max_current;
  uint16_t rated_voltage;
  unsigned inactive_phases : 3;
  int16_t dst_offtime_delta;
  uint8_t self_read_hour;
  uint8_t self_read_minute;
  uint8_t stop_mode_config;
  uint8_t reserved1[3];
  bool rk_bp10_ep16_access : 1;
  bool test_point : 1;
  bool test_point_confirmed : 1;
  bool lp_use_skipped : 1;
  uint8_t transceiver_state;
  uint8_t phse_rotation_changed;
  uint16_t plc_comm_inactive_time_threshold;
  ctLtimeDate_t broadcast_receipt;
  uint32_t broadcast_base;
  uint16_t broadcast_delta;
  uint16_t reverse_rotation_alarm_current_threshold;
  uint8_t plc_signal_quality_status;
  uint16_t auto_discovery_ta;
  uint16_t auto_discovery_to;
  uint8_t auto_discovery_disable;
  int16_t reserved2;
  uint16_t events_outage_threshold;
  uint16_t nvm_size;
  uint8_t safe_image_locked;
  uint32_t mep_sequence_number;
  uint16_t unused2; // ...
  uint8_t premise_power_generation;
  uint8_t power_outage_threshold;
  uint8_t phase_loss_threshold;
  uint8_t reserved3;
  uint8_t clock_error_tier;
  uint16_t unused3;
  uint8_t idt_version;
  uint8_t tilt_timer;
} ctET04_t;

#endif // CT_ET04_H