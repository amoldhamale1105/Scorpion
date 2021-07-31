#ifndef ELFLOADER_H
#define ELFLOADER_H

#include <stdint.h>
#include <stddef.h>

#include "elf.h"
#include "config.h"

struct elf_file
{
    char filename[SCORPION_MAX_PATH];

    int in_memory_size;

    //Physical memory address where the elf file is loaded in memory
    void* elf_memory;

    //The virtual base address of the first loadable segment/section
    void* virtual_base_address;

    //The ending virtual address
    void* virtual_end_address;

    //Physical base address of the first loadable segment/section
    void* physical_base_address;

    //Physical end address of this binary
    void* physical_end_address;
};

int elf_load(const char* filename, struct elf_file** file_out);
void elf_close(struct elf_file* file);
void* elf_virtual_base(struct elf_file* file);
void* elf_virtual_end(struct elf_file* file);
void* elf_phys_base(struct elf_file* file);
void* elf_phys_end(struct elf_file* file);

#endif