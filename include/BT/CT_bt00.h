//
// Created by Gustavo Viegas on 2017/03
//

#ifndef CT_BT00_H
#define CT_BT00_H

#include <stdint.h>
#include <stdbool.h>

// BT00 - General Configuration
//
typedef struct {
  unsigned data_order : 1;
  unsigned char_format : 3;
  unsigned : 4;
  unsigned time_format : 3;
  unsigned data_access_method : 2;
  unsigned id_format : 1;
  unsigned int_format : 2;
  unsigned non_int_format_1 : 4;
  unsigned non_int_format_2 : 4;
  char manufacturer[4];
  uint8_t nameplate_type;
  uint8_t default_set_used;
  uint8_t procedure_param_length;
  uint8_t response_data_length;
  uint8_t standard_version;
  uint8_t standard_revision;
  uint8_t dim_basic_tables_used;
  uint8_t dim_extended_tables_used;
  uint8_t dim_basic_procedures_used;
  uint8_t dim_extended_procedures_used;
  uint8_t manufacturer_status_length;
  uint8_t number_pending_tables;
  // Set of basic tables used
  bool bt00_used : 1;
  bool bt01_used : 1;
  bool bt02_used : 1;
  bool bt03_used : 1;
  bool bt04_used : 1;
  bool bt05_used : 1;
  bool bt06_used : 1;
  bool bt07_used : 1;
  bool bt08_used : 1;
  bool : 1;
  bool bt10_used : 1;
  bool bt11_used : 1;
  bool bt12_used : 1;
  bool bt13_used : 1;
  bool bt14_used : 1;
  bool bt15_used : 1;
  bool bt16_used : 1;
  unsigned : 3;
  bool bt20_used : 1;
  bool bt21_used : 1;
  bool bt22_used : 1;
  bool bt23_used : 1;
  bool bt24_used : 1;
  bool bt25_used : 1;
  bool bt26_used : 1;
  bool bt27_used : 1;
  bool bt28_used : 1;
  bool : 1;
  bool bt30_used : 1;
  bool bt31_used : 1;
  bool bt32_used : 1;
  bool bt33_used : 1;
  bool bt34_used : 1;
  unsigned : 5;
  bool bt40_used : 1;
  bool bt41_used : 1;
  bool bt42_used : 1;
  bool bt43_used : 1;
  bool bt44_used : 1;
  bool bt45_used : 1;
  unsigned : 4;
  bool bt50_used : 1;
  bool bt51_used : 1;
  bool bt52_used : 1;
  bool bt53_used : 1;
  bool bt54_used : 1;
  bool bt55_used : 1;
  bool bt56_used : 1;
  unsigned : 3;
  bool bt60_used : 1;
  bool bt61_used : 1;
  bool bt62_used : 1;
  bool bt63_used : 1;
  bool bt64_used : 1;
  bool bt65_used : 1;
  bool bt66_used : 1;
  bool bt67_used : 1;
  unsigned : 2;
  bool bt70_used : 1;
  bool bt71_used : 1;
  bool bt72_used : 1;
  bool bt73_used : 1;
  bool bt74_used : 1;
  bool bt75_used : 1;
  bool bt76_used : 1;
  unsigned : 4;
  // Set of extended tables used
  bool et00_used : 1;
  bool et01_used : 1;
  bool et02_used : 1;
  bool et03_used : 1;
  bool et04_used : 1;
  bool et05_used : 1;
  bool et06_used : 1;
  bool et07_used : 1;
  bool et08_used : 1;
  bool et09_used : 1;
  bool et10_used : 1;
  bool et11_used : 1;
  bool et12_used : 1;
  bool et13_used : 1;
  bool et14_used : 1;
  bool et15_used : 1;
  bool et16_used : 1;
  bool et17_used : 1;
  bool et18_used : 1;
  bool et19_used : 1;
  bool et20_used : 1;
  bool et21_used : 1;
  bool et22_used : 1;
  bool et23_used : 1;
  bool et24_used : 1;
  bool et25_used : 1;
  bool et26_used : 1;
  bool et27_used : 1;
  bool et28_used : 1;
  bool et29_used : 1;
  bool et30_used : 1;
  bool et31_used : 1;
  bool et32_used : 1;
  bool et33_used : 1;
  bool et34_used : 1;
  bool et35_used : 1;
  bool et36_used : 1;
  bool et37_used : 1;
  bool et38_used : 1;
  bool et39_used : 1;
  bool et40_used : 1;
  bool et41_used : 1;
  bool et42_used : 1;
  bool et43_used : 1;
  bool et44_used : 1;
  bool et45_used : 1;
  bool et46_used : 1;
  bool et47_used : 1;
  bool et48_used : 1;
  bool et49_used : 1;
  bool et50_used : 1;
  bool et51_used : 1;
  bool et52_used : 1;
  bool et53_used : 1;
  bool et54_used : 1;
  bool et55_used : 1;
  bool et56_used : 1;
  bool et57_used : 1;
  bool et58_used : 1;
  bool et59_used : 1;
  bool et60_used : 1;
  bool et61_used : 1;
  bool et62_used : 1;
  bool et63_used : 1;
  bool et64_used : 1;
  bool et65_used : 1;
  bool et66_used : 1;
  bool et67_used : 1;
  bool et68_used : 1;
  bool et69_used : 1;
  bool et70_used : 1;
  bool et71_used : 1;
  unsigned : 8;
  // Set of basic procedures used
  bool bp00_used : 1;
  bool bp01_used : 1;
  bool bp02_used : 1;
  bool bp03_used : 1;
  bool bp04_used : 1;
  bool bp05_used : 1;
  bool bp06_used : 1;
  bool bp07_used : 1;
  bool bp08_used : 1;
  bool bp09_used : 1;
  bool bp10_used : 1;
  bool bp11_used : 1;
  bool bp12_used : 1;
  bool bp13_used : 1;
  bool bp14_used : 1;
  bool bp15_used : 1;
  // Set of extended procedures used
  bool ep00_used : 1;
  bool ep01_used : 1;
  bool ep02_used : 1;
  bool ep03_used : 1;
  bool ep04_used : 1;
  bool ep05_used : 1;
  bool ep06_used : 1;
  bool ep07_used : 1;
  bool ep08_used : 1;
  bool ep09_used : 1;
  bool ep10_used : 1;
  bool ep11_used : 1;
  bool ep12_used : 1;
  bool ep13_used : 1;
  bool ep14_used : 1;
  bool ep15_used : 1;
  bool ep16_used : 1;
  bool ep17_used : 1;
  bool ep18_used : 1;
  bool ep19_used : 1;
  bool ep20_used : 1;
  bool ep21_used : 1;
  bool ep22_used : 1;
  bool ep23_used : 1;
  bool ep24_used : 1;
  bool ep25_used : 1;
  bool ep26_used : 1;
  bool ep27_used : 1;
  bool ep28_used : 1;
  bool ep29_used : 1;
  bool ep30_used : 1;
  bool ep31_used : 1;
  bool ep32_used : 1;
  bool ep33_used : 1;
  bool ep34_used : 1;
  bool ep35_used : 1;
  bool ep36_used : 1;
  bool ep37_used : 1;
  bool ep38_used : 1;
  bool ep39_used : 1;
  bool ep40_used : 1;
  bool ep41_used : 1;
  bool ep42_used : 1;
  bool ep43_used : 1;
  bool ep44_used : 1;
  bool ep45_used : 1;
  bool ep46_used : 1;
  bool ep47_used : 1;
  unsigned : 8;
  // Set of basic tables write privileges
  bool bt00_write : 1;
  bool bt01_write : 1;
  bool bt02_write : 1;
  bool bt03_write : 1;
  bool bt04_write : 1;
  bool bt05_write : 1;
  bool bt06_write : 1;
  bool bt07_write : 1;
  bool bt08_write : 1;
  bool : 1;
  bool bt10_write : 1;
  bool bt11_write : 1;
  bool bt12_write : 1;
  bool bt13_write : 1;
  bool bt14_write : 1;
  bool bt15_write : 1;
  bool bt16_write : 1;
  unsigned : 3;
  bool bt20_write : 1;
  bool bt21_write : 1;
  bool bt22_write : 1;
  bool bt23_write : 1;
  bool bt24_write : 1;
  bool bt25_write : 1;
  bool bt26_write : 1;
  bool bt27_write : 1;
  bool bt28_write : 1;
  bool : 1;
  bool bt30_write : 1;
  bool bt31_write : 1;
  bool bt32_write : 1;
  bool bt33_write : 1;
  bool bt34_write : 1;
  unsigned : 5;
  bool bt40_write : 1;
  bool bt41_write : 1;
  bool bt42_write : 1;
  bool bt43_write : 1;
  bool bt44_write : 1;
  bool bt45_write : 1;
  unsigned : 4;
  bool bt50_write : 1;
  bool bt51_write : 1;
  bool bt52_write : 1;
  bool bt53_write : 1;
  bool bt54_write : 1;
  bool bt55_write : 1;
  bool bt56_writee : 1;
  unsigned : 3;
  bool bt60_write : 1;
  bool bt61_write : 1;
  bool bt62_write : 1;
  bool bt63_write : 1;
  bool bt64_write : 1;
  bool bt65_write : 1;
  bool bt66_write : 1;
  bool bt67_write : 1;
  unsigned : 2;
  bool bt70_write : 1;
  bool bt71_write : 1;
  bool bt72_write : 1;
  bool bt73_write : 1;
  bool bt74_write : 1;
  bool bt75_write : 1;
  bool bt76_write : 1;
  unsigned : 4;
  // Set of extended tables write privileges
  bool et00_write : 1;
  bool et01_write : 1;
  bool et02_write : 1;
  bool et03_write : 1;
  bool et04_write : 1;
  bool et05_write : 1;
  bool et06_write : 1;
  bool et07_write : 1;
  bool et08_write : 1;
  bool et09_write : 1;
  bool et10_write : 1;
  bool et11_write : 1;
  bool et12_write : 1;
  bool et13_write : 1;
  bool et14_write : 1;
  bool et15_write : 1;
  bool et16_write : 1;
  bool et17_write : 1;
  bool et18_write : 1;
  bool et19_write : 1;
  bool et20_write : 1;
  bool et21_write : 1;
  bool et22_write : 1;
  bool et23_write : 1;
  bool et24_write : 1;
  bool et25_write : 1;
  bool et26_write : 1;
  bool et27_write : 1;
  bool et28_write : 1;
  bool et29_write : 1;
  bool et30_write : 1;
  bool et31_write : 1;
  bool et32_write : 1;
  bool et33_write : 1;
  bool et34_write : 1;
  bool et35_write : 1;
  bool et36_write : 1;
  bool et37_write : 1;
  bool et38_write : 1;
  bool et39_write : 1;
  bool et40_write : 1;
  bool et41_write : 1;
  bool et42_write : 1;
  bool et43_write : 1;
  bool et44_write : 1;
  bool et45_write : 1;
  bool et46_write : 1;
  bool et47_write : 1;
  bool et48_write : 1;
  bool et49_write : 1;
  bool et50_write : 1;
  bool et51_write : 1;
  bool et52_write : 1;
  bool et53_write : 1;
  bool et54_write : 1;
  bool et55_write : 1;
  bool et56_write : 1;
  bool et57_write : 1;
  bool et58_write : 1;
  bool et59_write : 1;
  bool et60_write : 1;
  bool et61_write : 1;
  bool et62_write : 1;
  bool et63_write : 1;
  bool et64_write : 1;
  bool et65_write : 1;
  bool et66_write : 1;
  bool et67_write : 1;
  bool et68_write : 1;
  bool et69_write : 1;
  bool et70_write : 1;
  bool et71_write : 1;
  unsigned : 8;
} ctBT00_t;

#endif // CT_BT00_H