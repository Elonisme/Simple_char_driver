#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_DATA_SIZE 256

int main() {
    char data[MAX_DATA_SIZE];

    // Open the character device file
    int fd = open("/dev/simple_char_driver", O_RDWR);

    if (fd < 0) {
        perror("Failed to open the device");
        return -1;
    }

    // Read data from the device
    char read_data[MAX_DATA_SIZE];
    ssize_t bytes_read = read(fd, read_data, sizeof(read_data) - 1);

    if (bytes_read < 0) {
        perror("Failed to read from the device");
        close(fd);
        return -1;
    }

    read_data[bytes_read] = '\0'; // Null-terminate the string

    printf("Data read from the device: %s\n", read_data);

    // Close the device file
    close(fd);

    return 0;
}
