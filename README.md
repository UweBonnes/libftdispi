libftdispi modified for higher throughput
=================

Based on
https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/libftdispi/libftdispi-0.2.3.tar.bz2

Modified to use:
- libftdi1
- ftdi1 asynchronous read feature
- "SEND_IMMEDIATE" to avoid FTDI latency timer

Observed shortcomings:
- SPI data send from target during write to target is not captured
