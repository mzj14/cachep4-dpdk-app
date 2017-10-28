#include "dpdk_lib.h"// sugar@62
#include "actions.h" // apply_table_* and action_code_*// sugar@63

extern int verify_packet(packet_descriptor_t *pd);// sugar@65

void print_mac(uint8_t *v) {
    printf("%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX\n", v[0], v[1], v[2], v[3], v[4], v[5]);
}// sugar@67
void print_ip(uint8_t *v) { printf("%d.%d.%d.%d\n", v[0], v[1], v[2], v[3]); }// sugar@68

static inline void p4_pe_header_too_short(packet_descriptor_t *pd) {// sugar@72
    pd->dropped = 1;// sugar@74
}// sugar@77
static inline void p4_pe_default(packet_descriptor_t *pd) {// sugar@72
    pd->dropped = 1;// sugar@74
}// sugar@77
static inline void p4_pe_checksum(packet_descriptor_t *pd) {// sugar@72
    pd->dropped = 1;// sugar@74
}// sugar@77
static inline void p4_pe_unhandled_select(packet_descriptor_t *pd) {// sugar@72
    pd->dropped = 1;// sugar@74
}// sugar@77
static inline void p4_pe_index_out_of_bounds(packet_descriptor_t *pd) {// sugar@72
    pd->dropped = 1;// sugar@74
}// sugar@77
static inline void p4_pe_header_too_long(packet_descriptor_t *pd) {// sugar@72
    pd->dropped = 1;// sugar@74
}// sugar@77
static inline void p4_pe_out_of_packet(packet_descriptor_t *pd) {// sugar@72
    pd->dropped = 1;// sugar@74
}// sugar@77
static void// sugar@81
extract_header_standard_metadata(uint8_t *buf, packet_descriptor_t *pd) {// sugar@82
    pd->headers[header_instance_standard_metadata].pointer = buf;// sugar@83
}// sugar@90

static void// sugar@81
extract_header_ethernet(uint8_t *buf, packet_descriptor_t *pd) {// sugar@82
    pd->headers[header_instance_ethernet].pointer = buf;// sugar@83
}// sugar@90

static void// sugar@81
extract_header_ip(uint8_t *buf, packet_descriptor_t *pd) {// sugar@82
    pd->headers[header_instance_ip].pointer = buf;// sugar@83
}// sugar@90

static void// sugar@81
extract_header_tcp(uint8_t *buf, packet_descriptor_t *pd) {// sugar@82
    pd->headers[header_instance_tcp].pointer = buf;// sugar@83
}// sugar@90

static void// sugar@81
extract_header_arp(uint8_t *buf, packet_descriptor_t *pd) {// sugar@82
    pd->headers[header_instance_arp].pointer = buf;// sugar@83
}// sugar@90

static void// sugar@81
extract_header_icmp(uint8_t *buf, packet_descriptor_t *pd) {// sugar@82
    pd->headers[header_instance_icmp].pointer = buf;// sugar@83
}// sugar@90

static void// sugar@81
extract_header_udp(uint8_t *buf, packet_descriptor_t *pd) {// sugar@82
    pd->headers[header_instance_udp].pointer = buf;// sugar@83
}// sugar@90

static void// sugar@81
extract_header_vlan(uint8_t *buf, packet_descriptor_t *pd) {// sugar@82
    pd->headers[header_instance_vlan].pointer = buf;// sugar@83
}// sugar@90

static void// sugar@81
extract_header_intrinsic_metadata(uint8_t *buf, packet_descriptor_t *pd) {// sugar@82
    pd->headers[header_instance_intrinsic_metadata].pointer = buf;// sugar@83
}// sugar@90

static void// sugar@81
extract_header_route_metadata(uint8_t *buf, packet_descriptor_t *pd) {// sugar@82
    pd->headers[header_instance_route_metadata].pointer = buf;// sugar@83
}// sugar@90

static void parse_state_start(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables);// sugar@94
static void parse_state_parse_vlan(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables);// sugar@94
static void parse_state_parse_arp(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables);// sugar@94
static void parse_state_parse_ip(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables);// sugar@94
static void parse_state_parse_icmp(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables);// sugar@94
static void parse_state_parse_tcp(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables);// sugar@94
static void parse_state_parse_udp(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables);// sugar@94

static inline void build_key_start(packet_descriptor_t *pd, uint8_t *buf, uint8_t *key) {// sugar@100
    debug("in the build_key_start function.\n");
    EXTRACT_INT32_BITS(pd, field_instance_ethernet_eth_type, *(uint32_t *) key);// sugar@109
    debug("key[0] = %x\n", key[0]);
    debug("key[1] = %x\n", key[1]);
    key += sizeof(uint32_t);// sugar@110
}// sugar@119
static inline void build_key_parse_vlan(packet_descriptor_t *pd, uint8_t *buf, uint8_t *key) {// sugar@100
    EXTRACT_INT32_BITS(pd, field_instance_vlan_eth_type, *(uint32_t *) key)// sugar@109
    key += sizeof(uint32_t);// sugar@110
}// sugar@119
static inline void build_key_parse_ip(packet_descriptor_t *pd, uint8_t *buf, uint8_t *key) {// sugar@100
    EXTRACT_INT32_BITS(pd, field_instance_ip_proto, *(uint32_t *) key)// sugar@109
    key += sizeof(uint32_t);// sugar@110
}// sugar@119
static void parse_state_start(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables)// sugar@122
{// sugar@123
    debug("enter the parse start function.\n");
    uint32_t value32;// sugar@124
    (void) value32;// sugar@125
    extract_header_ethernet(buf, pd);// sugar@130
    buf += pd->headers[header_instance_ethernet].length;// sugar@131
    debug("pd->headers[header_instance_ethernet].length = %d\n", pd->headers[header_instance_ethernet].length);
    uint8_t key[2];// sugar@157
    build_key_start(pd, buf, key);// sugar@158
    uint8_t case_value_0[2] = {// sugar@171
            8,// sugar@173
            0,// sugar@173
    };// sugar@174
    debug("key[0] = %x\n", key[0]);
    debug("key[1] = %x\n", key[1]);
    if (memcmp(key, case_value_0, 2) == 0)// sugar@175
        return parse_state_parse_ip(pd, buf, tables);// sugar@21
// sugar@176
    uint8_t case_value_1[2] = {// sugar@171
            8,// sugar@173
            6,// sugar@173
    };// sugar@174
    if (memcmp(key, case_value_1, 2) == 0)// sugar@175
        return parse_state_parse_arp(pd, buf, tables);// sugar@21
// sugar@176
    uint8_t case_value_2[2] = {// sugar@171
            129,// sugar@173
            0,// sugar@173
    };// sugar@174
    if (memcmp(key, case_value_2, 2) == 0)// sugar@175
        return parse_state_parse_vlan(pd, buf, tables);// sugar@21
// sugar@176
    {// sugar@25
        if (verify_packet(pd)) p4_pe_checksum(pd);// sugar@26
        return apply_table_cache(pd, tables);// sugar@27
    }// sugar@28
// sugar@166
}// sugar@189

static void parse_state_parse_vlan(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables)// sugar@122
{// sugar@123
    uint32_t value32;// sugar@124
    (void) value32;// sugar@125
    extract_header_vlan(buf, pd);// sugar@130
    buf += pd->headers[header_instance_vlan].length;// sugar@131
    EXTRACT_INT32_AUTO(pd, field_instance_vlan_vid, value32)// sugar@135
    pd->fields.field_instance_vlan_vid = value32;// sugar@136
    pd->fields.attr_field_instance_vlan_vid = 0;// sugar@137
    uint8_t key[2];// sugar@157
    build_key_parse_vlan(pd, buf, key);// sugar@158
    uint8_t case_value_0[2] = {// sugar@171
            8,// sugar@173
            0,// sugar@173
    };// sugar@174
    if (memcmp(key, case_value_0, 2) == 0)// sugar@175
        return parse_state_parse_ip(pd, buf, tables);// sugar@21
// sugar@176
    uint8_t case_value_1[2] = {// sugar@171
            8,// sugar@173
            6,// sugar@173
    };// sugar@174
    if (memcmp(key, case_value_1, 2) == 0)// sugar@175
        return parse_state_parse_arp(pd, buf, tables);// sugar@21
// sugar@176
    {// sugar@25
        if (verify_packet(pd)) p4_pe_checksum(pd);// sugar@26
        return apply_table_cache(pd, tables);// sugar@27
    }// sugar@28
// sugar@166
}// sugar@189

static void parse_state_parse_arp(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables)// sugar@122
{// sugar@123
    uint32_t value32;// sugar@124
    (void) value32;// sugar@125
    extract_header_arp(buf, pd);// sugar@130
    buf += pd->headers[header_instance_arp].length;// sugar@131
    {// sugar@25
        if (verify_packet(pd)) p4_pe_checksum(pd);// sugar@26
        return apply_table_cache(pd, tables);// sugar@27
    }// sugar@28
// sugar@154
}// sugar@189

static void parse_state_parse_ip(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables)// sugar@122
{// sugar@123
    debug("enter the parse IP function.\n");
    uint32_t value32;// sugar@124
    (void) value32;// sugar@125
    extract_header_ip(buf, pd);// sugar@130
    buf += pd->headers[header_instance_ip].length;// sugar@131
    uint8_t key[1];// sugar@157
    build_key_parse_ip(pd, buf, key);// sugar@158
    uint8_t case_value_0[1] = {// sugar@171
            6,// sugar@173
    };// sugar@174
    if (memcmp(key, case_value_0, 1) == 0)// sugar@175
        return parse_state_parse_tcp(pd, buf, tables);// sugar@21
// sugar@176
    uint8_t case_value_1[1] = {// sugar@171
            17,// sugar@173
    };// sugar@174
    if (memcmp(key, case_value_1, 1) == 0)// sugar@175
        return parse_state_parse_udp(pd, buf, tables);// sugar@21
// sugar@176
    uint8_t case_value_2[1] = {// sugar@171
            1,// sugar@173
    };// sugar@174
    if (memcmp(key, case_value_2, 1) == 0)// sugar@175
        return parse_state_parse_icmp(pd, buf, tables);// sugar@21
// sugar@176
    {// sugar@25
        if (verify_packet(pd)) p4_pe_checksum(pd);// sugar@26
        return apply_table_cache(pd, tables);// sugar@27
    }// sugar@28
// sugar@166
}// sugar@189

static void parse_state_parse_icmp(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables)// sugar@122
{// sugar@123
    uint32_t value32;// sugar@124
    (void) value32;// sugar@125
    extract_header_icmp(buf, pd);// sugar@130
    buf += pd->headers[header_instance_icmp].length;// sugar@131
    {// sugar@25
        if (verify_packet(pd)) p4_pe_checksum(pd);// sugar@26
        return apply_table_cache(pd, tables);// sugar@27
    }// sugar@28
// sugar@154
}// sugar@189

static void parse_state_parse_tcp(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables)// sugar@122
{// sugar@123
    uint32_t value32;// sugar@124
    (void) value32;// sugar@125
    extract_header_tcp(buf, pd);// sugar@130
    buf += pd->headers[header_instance_tcp].length;// sugar@131
    {// sugar@25
        if (verify_packet(pd)) p4_pe_checksum(pd);// sugar@26
        return apply_table_cache(pd, tables);// sugar@27
    }// sugar@28
// sugar@154
}// sugar@189

static void parse_state_parse_udp(packet_descriptor_t *pd, uint8_t *buf, lookup_table_t **tables)// sugar@122
{// sugar@123
    uint32_t value32;// sugar@124
    (void) value32;// sugar@125
    extract_header_udp(buf, pd);// sugar@130
    buf += pd->headers[header_instance_udp].length;// sugar@131
    {// sugar@25
        if (verify_packet(pd)) p4_pe_checksum(pd);// sugar@26
        return apply_table_cache(pd, tables);// sugar@27
    }// sugar@28
// sugar@154
}// sugar@189

void parse_packet(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@192
    parse_state_start(pd, pd->data, tables);// sugar@193
}// sugar@194
