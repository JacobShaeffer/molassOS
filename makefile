CC=i686-elf-gcc
DISK?=iso/disk

.PHONY: clean install

tty.o: tty.c tty.h
	$(CC) -std=gnu99 -ffreestanding -g -c $< -o $@
kernel.o: kernel.c tty.h
	$(CC) -std=gnu99 -ffreestanding -g -c $< -o $@
start.o: start.s
	$(CC) -std=gnu99 -ffreestanding -g -c $< -o $@

DEPENDENCIES:= linker.ld kernel.o start.o tty.o
kernel.elf: $(DEPENDENCIES)
	$(CC) -ffreestanding -nostdlib -g -T $(DEPENDENCIES) -o kernel.elf -lgcc

clean:
	rm -rf *.o *.elf 

install: kernel.elf
	mkdir $(DISK)
	mkdir $(DISK)/boot
	mkdir $(DISK)/boot/grub
	cp $< $(DISK)/boot/
	echo 'set timeout=0' >> $(DISK)/boot/grub/grub.cfg
	echo 'set default=0' >> $(DISK)/boot/grub/grub.cfg
	echo '' >> $(DISK)/boot/grub/grub.cfg
	echo 'menuentry "molassOS"{' >> $(DISK)/boot/grub/grub.cfg
	echo '	multiboot /boot/kernel.elf' >> $(DISK)/boot/grub/grub.cfg
	echo '	boot' >> $(DISK)/boot/grub/grub.cfg
	echo '}' >> $(DISK)/boot/grub/grub.cfg
	grub-mkrescue -o molassOS.iso $(DISK)
	rm -rf $(DISK)	
