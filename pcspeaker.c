#include <fcntl.h>
#include <linux/kd.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define PIT_FREQUENCY 1193180

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s FREQUENCY_HZ DURATION_MS\n", argv[0]);
        return EXIT_FAILURE;
    }

    int frequency = atoi(argv[1]);
    int duration_ms = atoi(argv[2]);

    if (frequency <= 0 || duration_ms <= 0) {
        fprintf(stderr, "Frequency and duration must be positive.\n");
        return EXIT_FAILURE;
    }

    int console = open("/dev/console", O_WRONLY);

    if (console == -1) {
        perror("open /dev/console");
        return EXIT_FAILURE;
    }

    int divisor = PIT_FREQUENCY / frequency;
    int argument = (duration_ms << 16) | divisor;

    if (ioctl(console, KDMKTONE, argument) == -1) {
        perror("KDMKTONE");
        close(console);
        return EXIT_FAILURE;
    }

    close(console);
    return EXIT_SUCCESS;
}

