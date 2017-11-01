CC=gcc
CFLAGS=-Wall -pthread -std=c99
LIB=

all: dpdk_l3_controller dpdk_case0_controller dpdk_case0_cache_controller dpdk_case1_controller dpdk_case1_cache_controller dpdk_case2_controller dpdk_case2_cache_controller dpdk_case3_cache_controller

dpdk_l3_controller:
	$(CC) $(CFLAGS) $(LIB) handlers.c controller.c messages.c sock_helpers.c threadpool.c fifo.c dpdk_l3_controller.c -o dpdk_l3_controller

dpdk_case0_controller:
	$(CC) $(CFLAGS) $(LIB) handlers.c controller.c messages.c sock_helpers.c threadpool.c fifo.c dpdk_case0_controller.c -o dpdk_case0_controller

dpdk_case0_cache_controller:
	$(CC) $(CFLAGS) $(LIB) handlers.c controller.c messages.c sock_helpers.c threadpool.c fifo.c dpdk_case0_cache_controller.c -o dpdk_case0_cache_controller

dpdk_case1_controller:
	$(CC) $(CFLAGS) $(LIB) handlers.c controller.c messages.c sock_helpers.c threadpool.c fifo.c dpdk_case1_controller.c -o dpdk_case1_controller

dpdk_case1_cache_controller:
	$(CC) $(CFLAGS) $(LIB) handlers.c controller.c messages.c sock_helpers.c threadpool.c fifo.c dpdk_case1_cache_controller.c -o dpdk_case1_cache_controller

dpdk_case2_controller:
	$(CC) $(CFLAGS) $(LIB) handlers.c controller.c messages.c sock_helpers.c threadpool.c fifo.c dpdk_case2_controller.c -o dpdk_case2_controller

dpdk_case2_cache_controller:
	$(CC) $(CFLAGS) $(LIB) handlers.c controller.c messages.c sock_helpers.c threadpool.c fifo.c dpdk_case2_cache_controller.c -o dpdk_case2_cache_controller

dpdk_case3_cache_controller:
	$(CC) $(CFLAGS) $(LIB) handlers.c controller.c messages.c sock_helpers.c threadpool.c fifo.c dpdk_case3_cache_controller.c -o dpdk_case3_cache_controller

clean:
	rm -f dpdk_l3_controller dpdk_case0_controller dpdk_case0_cache_controller dpdk_case1_controller dpdk_case1_cache_controller dpdk_case2_controller dpdk_case2_cache_controller dpdk_case3_cache_controller

