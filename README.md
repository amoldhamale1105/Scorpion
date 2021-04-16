# Scorpion
A multi-threaded kernel built in protected mode for the x86 architecture

# Build and test instructions:
The current version of the kernel code is WIP. It jumps infinitely once loaded at 1M in memory
gcc cross compiler is built for the kernel
execute the shell script build.sh to set the env variables needed for the cross compiler and generate the os.bin using make config
load the binary in the qemu emulator using qemu-system-x86_64 -hda ./os.bin
No output seen at the current dev stage since the kernel is jumps infinitely after loading.
