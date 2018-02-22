#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "ftdispi.h"

static int exitRequested = 0;
/*
 * sigintHandler --
 *
 *    SIGINT handler, so we can gracefully exit when the user hits ctrl-C.
 */

static void
sigintHandler(int signum)
{
   exitRequested = 1;
}

void usage(char * name)
{
    fprintf(stderr, "usage: %s [options]\n", name);
    fprintf(stderr, "\t-p <number> Search for device with PID == number\n");
    fprintf(stderr, "\t-v <number> Search for device with VID == number\n");
}

int main(int argc, char **argv)
{
    struct ftdi_context    fc;
    struct ftdispi_context fsc;
    int vid = 0x0403;
    int pid = 0x6011;
    uint8_t buf[256];

    int i;

    if (ftdi_init(&fc) < 0)
    {
        fprintf(stderr, "ftdi_init failed\n");
        return 1;
    }
    while ((i = getopt(argc, argv, "p:v:")) != -1)
    {
        switch (i)
        {
        case 'p':
            pid = strtoul(optarg, NULL, 0);
            break;
        case 'v':
            vid = strtoul(optarg, NULL, 0);
            break;
        default:
            usage(argv[0]);
            exit(-1);
        }
    }
    i = ftdi_usb_open(&fc, vid, pid);
    if (i < 0 && i != -5)
    {
        fprintf(stderr,
                "OPEN: %s\n",
                ftdi_get_error_string(&fc));
        exit(-1);
    }
    ftdispi_open(&fsc, &fc, INTERFACE_ANY);
    ftdispi_setmode(&fsc, 1, 0, 0, 0, 0, FTDISPI_GPO0);
    ftdispi_setclock(&fsc, 2000000);
    puts("Hit ^C to abort");
    signal(SIGINT, sigintHandler);
    do {
        ftdispi_write_read(&fsc, "Test", 4, buf, 1, 0);
    }while  (!exitRequested);
    signal(SIGINT, SIG_DFL);
    puts("Done");
    ftdispi_close(&fsc, 1);
    return 0;
}
