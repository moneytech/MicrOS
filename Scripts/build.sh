#!/bin/bash

# Compile bootloader
Tools/nasm.exe Source/Bootloader/bootloader.asm -f bin -o Build/bootloader.bin

if [ ! -f Build/bootloader.bin ]; then
    echo "Bootloader build error!"
    exit
fi

# Compile kernel startup
Tools/nasm.exe Source/Kernel/startup.asm -f elf32 -o Build/Kernel/startup.o

if [ ! -f Build/Kernel/startup.o ]; then
    echo "Kernel startup build error!"
    exit
fi

# Go to directory where all kernel output files will be stored
cd Build/Kernel

# Find all source files with *.c extension
SourceFiles=`find ../.. -name '*.c'`

# Compile kernel
i386-elf-gcc -c $SourceFiles -ffreestanding -Wall -Wextra

if [ $? -ne 0 ]; then
    echo "Kernel build error!"
    exit
fi

# Back to the main project directory
cd ../..

# Find all output files with *.o extension
OutputFiles=`find . -name '*.o'`

# Link kernel output files
i386-elf-gcc -T Source/linker.ld -o Build/kernel.bin -ffreestanding -O2 -nostdlib $OutputFiles -lgcc

if [ $? -ne 0 ]; then
    echo "Linker error!"
    exit
fi

# Upload bootloader to the floppy
Tools/dd.exe if=Build/bootloaderr.bin bs=512 of=Build/floppy.img

# Mount floppy
imdisk -a -f Build/floppy.img -m F:

# Copy kernel to the floppy
cp Build/kernel.bin F:/kernel.bin

# Unmount floppy
imdisk -D -m F: