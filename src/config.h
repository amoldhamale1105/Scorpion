#ifndef CONFIG_H
#define CONFIG_H

#define KERNEL_CODE_SELECTOR 0x08
#define KERNEL_DATA_SELECTOR 0x10

#define SCORPION_TOTAL_INTERRUPTS 512

// 100 MB heap size
#define SCORPION_HEAP_SIZE_BYTES 104857600
#define SCORPION_HEAP_BLOCK_SIZE 4096
#define SCORPION_HEAP_ADDRESS 0x01000000
#define SCORPION_HEAP_TABLE_ADDRESS 0x00007E00

#define SCORPION_SECTOR_SIZE 512
#endif
