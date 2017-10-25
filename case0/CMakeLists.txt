cmake_minimum_required(VERSION 3.6)
project(case0)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        build/case0/src_hardware_indep/actions.c
        build/case0/src_hardware_indep/actions.h
        build/case0/src_hardware_indep/controlplane.c
        build/case0/src_hardware_indep/data_plane_data.h
        build/case0/src_hardware_indep/dataplane.c
        build/case0/src_hardware_indep/parser.c
        build/case0/src_hardware_indep/parser.h
        build/case0/src_hardware_indep/tables.c
        src/hardware_dep/dpdk/data_plane/dpdk_lib.c
        src/hardware_dep/dpdk/data_plane/dpdk_primitives.c
        src/hardware_dep/dpdk/data_plane/dpdk_tables.c
        src/hardware_dep/dpdk/includes/aliases.h
        src/hardware_dep/dpdk/includes/dpdk_lib.h
        src/hardware_dep/dpdk/includes/dpdk_primitives.h
        src/hardware_dep/dpdk/includes/dpdk_tables.h
        src/hardware_dep/dpdk/main.c
        src/hardware_dep/dpdk/main_loop.c
        src/hardware_dep/freescale/data_plane/backend.c
        src/hardware_dep/freescale/data_plane/freescale_tables.c
        src/hardware_dep/freescale/includes/aliases.h
        src/hardware_dep/freescale/includes/backend.h
        src/hardware_dep/freescale/includes/freescale_primitives.h
        src/hardware_dep/freescale/includes/freescale_tables.h
        src/hardware_dep/freescale/main.c
        src/hardware_dep/shared/ctrl_plane/controller.c
        src/hardware_dep/shared/ctrl_plane/controller.h
        src/hardware_dep/shared/ctrl_plane/ctrl_plane_backend.c
        src/hardware_dep/shared/ctrl_plane/ctrl_plane_backend.h
        src/hardware_dep/shared/ctrl_plane/dpdk_controller.c
        src/hardware_dep/shared/ctrl_plane/dpdk_l3_controller.c
        src/hardware_dep/shared/ctrl_plane/fifo.c
        src/hardware_dep/shared/ctrl_plane/fifo.h
        src/hardware_dep/shared/ctrl_plane/handlers.c
        src/hardware_dep/shared/ctrl_plane/handlers.h
        src/hardware_dep/shared/ctrl_plane/messages.c
        src/hardware_dep/shared/ctrl_plane/messages.h
        src/hardware_dep/shared/ctrl_plane/sock_helpers.c
        src/hardware_dep/shared/ctrl_plane/sock_helpers.h
        src/hardware_dep/shared/ctrl_plane/threadpool.c
        src/hardware_dep/shared/ctrl_plane/threadpool.h
        src/hardware_dep/shared/data_plane/ternary_naive.c
        src/hardware_dep/shared/data_plane/vector.c
        src/hardware_dep/shared/includes/backend.h
        src/hardware_dep/shared/includes/dataplane.h
        src/hardware_dep/shared/includes/ternary_naive.h
        src/hardware_dep/shared/includes/vector.h)

include_directories(src/hardware_dep/dpdk/includes)
include_directories(src/hardware_dep/freescale/includes)
include_directories(src/hardware_dep/shared/includes)

add_executable(case0 ${SOURCE_FILES})