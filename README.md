# Scorpion
A multi-threaded kernel built in protected mode for the x86 architecture  
The kernel was developed using custom built gcc cross compiler from source  
Scorpion has almost all of the fundamental components encompassed in a full blown monolithic kernel  
Scorpion is a monolithic kernel used to demonstrate how kernel's behave and can be built from the ground up  
The constant and extensive reference used during development of Scorpion is: https://wiki.osdev.org/Main_Page  

Following are some of the attributes of Scorpion:  
- Interrupt descriptor table
- Programmable Interrupt Controller
- Heap
- Paging
- Reading from the hard disk
- FAT16 filesystem driver core and VFS(Virtual filesystem)
- User space
- TSS (Task Switch Segment)
- Task and process foundation
- GDT (Global Descriptor Table)
- Interrupt `0x80` for user space process and kernel communication
- Kernel/system commands
- PS2 port keyboard driver
- Shell program to utilize the kernel
- ELF program loader
- Custom stdlib functions for user space programs
- Loading other programs in shell
- Handling program crashes
- Multitasking

All attributes of the kernel may not be captured here and can keep improving over time but the above ones will remain as the core properties.

## Prerequisites 
There are some prerequisites to build and test Scorpion  
- A Debian Linux host machine (either a VM or Debian Linux running on a physical machine)
- qemu-x86 to simulate the bootloader on kernel
- Alternatively a physical machine capable of running x86 programs
- A working keyboard with PS2 port connected to the physical machine to pipe in commands on the shell to interact with the kernel. If you're using qemu, the default keyboard on your laptop will work just fine

## Build the kernel and bootloader
Before building the kernel and bootloader, we need to get the environment ready by building the cross-compiler. A cross-compiler is needed because your host may have a different architecture than the target we are the running the kernel on.

### Install dependencies
Install cross-compiler dependencies with the following commands:
```
sudo apt install build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev
```

### Download source code
Download the source code for bin utils and gcc into `$HOME/src` directory using the following links:  
- Bin utils release 2.36: https://gnu.org/software/binutils/
- GCC release 10.2.0: https://gnu.org/software/gcc/

Extract both downloads in the `$HOME/src` directory

### Build gcc
Now let's convert the source into compiler object files for our target  
First some env vars need to be set to enable make to install compiled binaries at the right location  
```
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
```
#### Binutils
Run the following command to build binutils. Do not forget to replace x.y.z with your own version.  
```
cd $HOME/src
 
mkdir build-binutils
cd build-binutils
../binutils-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
```

#### GCC
Run the following command to build gcc. Do not forget to replace x.y.z with your own version.  
```
cd $HOME/src
 
# The $PREFIX/bin dir _must_ be in the PATH. We did that above.
which -- $TARGET-as || echo $TARGET-as is not in the PATH
 
mkdir build-gcc
cd build-gcc
../gcc-x.y.z/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
```

Once all above steps are complete, go ahead and test if your cross-compiler is successfully built and installed or not with the following command:
```
$HOME/opt/cross/bin/$TARGET-gcc --version
```
Now that our cross compiler is ready, we are ready to build Scorpion with the bootloader. Run the following at the root of the project structure  
```
./build.sh
```
If the build succeeds, 3 binaries should be generated in the `bin` directory at the root of the project
- The MBR bootloader `boot.bin`
- The kernel binary `kernel.bin`
- The Scorpion OS binary which contains the bootloader and the entire kernel `scorpion.bin`

## Run/Test Scorpion
Its time to run Scorpion OS using the output generated binaries in the previous section. Run the following command in the terminal to simulate Scorpion with qemu
```
qemu-system-i386 -hda ./bin/scorpion.bin 
```

A shell prompt should be activated with Scorpion Version on top left. You can now start typing at the shell. A sample program called `blank.elf` has been created and loaded on the Scorpion hard drive for it to be able to access.  
Load the program into memory by executing the following on the Scorpion command prompt  
```
> blank.elf
```
The program can also be loaded with arguments which can be handled by the ensuing user process as follows:
```
> blank.elf 55 21 tree
```
An output like this should be generated depending on whether the program is loaded with or without arguments:

