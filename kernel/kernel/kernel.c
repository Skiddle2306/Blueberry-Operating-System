#include <stdio.h>
#include <kernel/tty.h>

void kernel_main(void) {
	terminal_initialize();
	printf("Hello, Blueberry!\n");
	printf("Name: %s\n", "Blueberry");
	printf("Character: %c\n", 'B');
	printf("Progress: 100%%\n");
	printf("Trailing percent: %");
	printf("%d %d %x", -123,156, 48879u);

}
