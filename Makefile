usb-cdc-monitor: Makefile src/main.c inc/utils.h src/utils.c
	gcc -o usb-cdc-monitor src/main.c src/utils.c src/usb.c -lusb-1.0

test_runner: Makefile tests/cu_tests.c inc/utils.h src/utils.c
	gcc -g -o cu_tests tests/cu_tests.c src/utils.c -lcunit
