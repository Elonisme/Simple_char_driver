#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_DATA_SIZE 256

int main() {
    char data[MAX_DATA_SIZE];

    // Get the data from user input
    printf("Enter data to be written to the device: ");
    if (fgets(data, sizeof(data), stdin) == NULL) {
        perror("Failed to read data");
        return -1;
    }

    // Remove the newline character if present
    data[strcspn(data, "\n")] = '\0';

    // Open the character device file
    int fd = open("/dev/simple_char_driver", O_WRONLY);

    if (fd < 0) {
        perror("Failed to open the device");
        return -1;
    }

    // Write data to the device
    ssize_t bytes_written = write(fd, data, strlen(data));

    if (bytes_written < 0) {
        perror("Failed to write to the device");
        close(fd);
        return -1;
    }

    printf("Data written to the device: %s\n", data);

    // Close the device file
    close(fd);

    return 0;
}
