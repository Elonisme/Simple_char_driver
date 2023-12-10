obj-m += simple_char_driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o read read.c 
	gcc -o write write.c
	chmod +x load_module.sh
	chmod +x unload_module.sh

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -rf read write