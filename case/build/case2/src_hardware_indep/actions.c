#include "dpdk_lib.h"// sugar@20
#include "actions.h"// sugar@21
#include <unistd.h>// sugar@22
#include <arpa/inet.h>// sugar@23

extern backend bg;// sugar@25

void action_code_no_op(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
}// sugar@453

void action_code_drop(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
}// sugar@453

void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
}// sugar@453

void action_code_on_miss(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
}// sugar@453

void action_code_acl_drop(packet_descriptor_t *pd, lookup_table_t **tables,
                          struct action_acl_drop_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    value32 = 1;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_acl_metadata_acl_op, value32)// sugar@43
// sugar@147
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_acl_metadata_acl_reason, parameters.reason, 2)// sugar@189
// sugar@449
}// sugar@453

void action_code_acl_permit(packet_descriptor_t *pd, lookup_table_t **tables,
                            struct action_acl_permit_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    value32 = 0;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_acl_metadata_acl_op, value32)// sugar@43
// sugar@147
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_acl_metadata_acl_reason, parameters.reason, 2)// sugar@189
// sugar@449
}// sugar@453

void action_code_acl_alert(packet_descriptor_t *pd, lookup_table_t **tables,
                           struct action_acl_alert_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    value32 = 2;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_acl_metadata_acl_op, value32)// sugar@43
// sugar@147
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_acl_metadata_acl_reason, parameters.reason, 2)// sugar@189
// sugar@449
}// sugar@453

void action_code_acl_feature(packet_descriptor_t *pd, lookup_table_t **tables,
                             struct action_acl_feature_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    MODIFY_INT32_BYTEBUF(pd, field_instance_acl_metadata_enable_mac_acl, parameters.enable_mac, 1)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_acl_metadata_enable_ipv4_acl, parameters.enable_ipv4, 1)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_acl_metadata_enable_icmp_acl, parameters.enable_icmp, 1)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_acl_metadata_enable_vlan_acl, parameters.enable_vlan, 1)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_acl_metadata_enable_tcp_acl, parameters.enable_tcp, 1)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_acl_metadata_enable_udp_acl, parameters.enable_udp, 1)// sugar@189
// sugar@449
}// sugar@453

void action_code_rewrite_udp_src(packet_descriptor_t *pd, lookup_table_t **tables,
                                 struct action_rewrite_udp_src_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    debug("in the action_code_rewrite_tcp_dst function.\n");
    debug("parameters.port[0] = %x.\n", *((uint8_t *)parameters.port));
    debug("parameters.port[1] = %x.\n", *((uint8_t *)parameters.port + 1));
    MODIFY_INT32_BYTEBUF(pd, field_instance_udp_src_port, parameters.port, 2)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_ip_src_addr, parameters.addr, 4)// sugar@189
// sugar@449
    value32 = 1;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_update_udp_checksum, value32)// sugar@43
// sugar@147
// sugar@449
}// sugar@453

void action_code_rewrite_udp_dst(packet_descriptor_t *pd, lookup_table_t **tables,
                                 struct action_rewrite_udp_dst_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    MODIFY_INT32_BYTEBUF(pd, field_instance_udp_dst_port, parameters.port, 2)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_ip_dst_addr, parameters.addr, 4)// sugar@189
// sugar@449
    value32 = 1;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_update_udp_checksum, value32)// sugar@43
// sugar@147
// sugar@449
}// sugar@453

void action_code_rewrite_tcp_src(packet_descriptor_t *pd, lookup_table_t **tables,
                                 struct action_rewrite_tcp_src_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    MODIFY_INT32_BYTEBUF(pd, field_instance_tcp_src_port, parameters.port, 2)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_ip_src_addr, parameters.addr, 4)// sugar@189
// sugar@449
    value32 = 1;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_update_tcp_checksum, value32)// sugar@43
// sugar@147
// sugar@449
}// sugar@453

void action_code_rewrite_tcp_dst(packet_descriptor_t *pd, lookup_table_t **tables,
                                 struct action_rewrite_tcp_dst_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    MODIFY_INT32_BYTEBUF(pd, field_instance_tcp_dst_port, parameters.port, 2)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_ip_dst_addr, parameters.addr, 4)// sugar@189
// sugar@449
    value32 = 1;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_update_tcp_checksum, value32)// sugar@43
// sugar@147
// sugar@449
}// sugar@453

void action_code_rewrite_twice_udp(packet_descriptor_t *pd, lookup_table_t **tables,
                                   struct action_rewrite_twice_udp_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    MODIFY_INT32_BYTEBUF(pd, field_instance_udp_src_port, parameters.src_port, 2)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_udp_dst_port, parameters.dst_port, 2)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_ip_src_addr, parameters.src_addr, 4)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_ip_dst_addr, parameters.dst_addr, 4)// sugar@189
// sugar@449
    value32 = 1;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_update_udp_checksum, value32)// sugar@43
// sugar@147
// sugar@449
}// sugar@453

void action_code_rewrite_twice_tcp(packet_descriptor_t *pd, lookup_table_t **tables,
                                   struct action_rewrite_twice_tcp_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    MODIFY_INT32_BYTEBUF(pd, field_instance_tcp_src_port, parameters.src_port, 2)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_tcp_dst_port, parameters.dst_port, 2)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_ip_src_addr, parameters.src_addr, 4)// sugar@189
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_ip_dst_addr, parameters.dst_addr, 4)// sugar@189
// sugar@449
    value32 = 1;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_update_tcp_checksum, value32)// sugar@43
// sugar@147
// sugar@449
}// sugar@453

void action_code_get_tcp_information(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    value32 = pd->fields.field_instance_tcp_src_port;// sugar@52
    pd->fields.attr_field_instance_tcp_src_port = MODIFIED;// sugar@53
// sugar@166
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_l4_src_port, value32)// sugar@43
// sugar@167
// sugar@449
    value32 = pd->fields.field_instance_tcp_dst_port;// sugar@52
    pd->fields.attr_field_instance_tcp_dst_port = MODIFIED;// sugar@53
// sugar@166
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_l4_dst_port, value32)// sugar@43
// sugar@167
// sugar@449
    value32 = 1;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_enable_nat, value32)// sugar@43
// sugar@147
// sugar@449
}// sugar@453

// FIXME: the value here is in
void action_code_get_udp_information(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    debug("in the action_code_get_udp_information.\n");
    // FIXME: here is the original value of l4_metadata. It is the key!
    value32 = pd->fields.field_instance_udp_src_port;// sugar@52
    pd->fields.attr_field_instance_udp_src_port = MODIFIED;// sugar@53
    debug("value32 = %x.\n", value32);
// sugar@166
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_l4_src_port, value32)// sugar@43
    debug("field_instance_nat_metadata_l4_src_port = %x.\n", FIELD_BYTES(pd, field_instance_nat_metadata_l4_src_port));
// sugar@167
// sugar@449
    value32 = pd->fields.field_instance_udp_dst_port;// sugar@52
    pd->fields.attr_field_instance_udp_dst_port = MODIFIED;// sugar@53
    debug("value32 = %x.\n", value32);
// sugar@166
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_l4_dst_port, value32)// sugar@43
    debug("field_instance_nat_metadata_l4_dst_port = %x.\n", FIELD_BYTES(pd, field_instance_nat_metadata_l4_dst_port));
// sugar@167
// sugar@449
    value32 = 1;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_enable_nat, value32)// sugar@43
// sugar@147
// sugar@449
}// sugar@453

void action_code_disable_nat(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    value32 = 0;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_nat_metadata_enable_nat, value32)// sugar@43
// sugar@147
// sugar@449
}// sugar@453

void action_code_learning(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    struct type_field_list fields;// sugar@371
    fields.fields_quantity = 2;// sugar@373
    fields.field_offsets = malloc(sizeof(uint8_t * ) * fields.fields_quantity);// sugar@374
    fields.field_widths = malloc(sizeof(uint8_t * ) * fields.fields_quantity);// sugar@375
    fields.field_offsets[0] = (uint8_t *) field_desc(pd, field_instance_ethernet_src_mac).byte_addr;// sugar@379
    fields.field_widths[0] = field_desc(pd, field_instance_ethernet_src_mac).bitwidth;// sugar@380
    fields.field_offsets[1] = (uint8_t *) field_desc(pd, field_instance_vlan_vid).byte_addr;// sugar@379
    fields.field_widths[1] = field_desc(pd, field_instance_vlan_vid).bitwidth;// sugar@380

    generate_digest(bg, "learn_list", 0, &fields);
    sleep(1);// sugar@386
// sugar@449
}// sugar@453

void action_code_mcast(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    value32 = 1;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_route_metadata_route, value32)// sugar@43
// sugar@147
// sugar@449
}// sugar@453

void
action_code_ucast(packet_descriptor_t *pd, lookup_table_t **tables, struct action_ucast_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    value32 = 2;// sugar@146
    MODIFY_INT32_INT32_AUTO(pd, field_instance_route_metadata_route, value32)// sugar@43
// sugar@147
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_route_metadata_lan, parameters.lan, 1)// sugar@189
// sugar@449
}// sugar@453

void action_code_set_nhop(packet_descriptor_t *pd, lookup_table_t **tables,
                          struct action_set_nhop_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    if (6 < field_desc(pd, field_instance_ethernet_src_mac).bytewidth) {// sugar@193
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_src_mac, parameters.src_mac, 6);                // sugar@194
    } else {// sugar@195
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_src_mac,
                               parameters.src_mac + (6 - field_desc(pd, field_instance_ethernet_src_mac).bytewidth),
                               field_desc(pd, field_instance_ethernet_src_mac).bytewidth)// sugar@196
    }// sugar@197
// sugar@449
    if (6 < field_desc(pd, field_instance_ethernet_dst_mac).bytewidth) {// sugar@193
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_dst_mac, parameters.dst_mac, 6);                // sugar@194
    } else {// sugar@195
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_dst_mac,
                               parameters.dst_mac + (6 - field_desc(pd, field_instance_ethernet_dst_mac).bytewidth),
                               field_desc(pd, field_instance_ethernet_dst_mac).bytewidth)// sugar@196
    }// sugar@197
// sugar@449
}// sugar@453

void action_code_set_nhop_with_vlan(packet_descriptor_t *pd, lookup_table_t **tables,
                                    struct action_set_nhop_with_vlan_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    if (6 < field_desc(pd, field_instance_ethernet_src_mac).bytewidth) {// sugar@193
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_src_mac, parameters.src_mac, 6);                // sugar@194
    } else {// sugar@195
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_src_mac,
                               parameters.src_mac + (6 - field_desc(pd, field_instance_ethernet_src_mac).bytewidth),
                               field_desc(pd, field_instance_ethernet_src_mac).bytewidth)// sugar@196
    }// sugar@197
// sugar@449
    if (6 < field_desc(pd, field_instance_ethernet_dst_mac).bytewidth) {// sugar@193
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_dst_mac, parameters.dst_mac, 6);                // sugar@194
    } else {// sugar@195
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_dst_mac,
                               parameters.dst_mac + (6 - field_desc(pd, field_instance_ethernet_dst_mac).bytewidth),
                               field_desc(pd, field_instance_ethernet_dst_mac).bytewidth)// sugar@196
    }// sugar@197
// sugar@449
    MODIFY_INT32_BYTEBUF(pd, field_instance_vlan_vid, parameters.vid, 2)// sugar@189
// sugar@449
}// sugar@453

void action_code_forwarding(packet_descriptor_t *pd, lookup_table_t **tables,
                            struct action_forwarding_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    MODIFY_INT32_BYTEBUF(pd, field_instance_standard_metadata_egress_spec, parameters.port, 2)// sugar@189
// sugar@449
}// sugar@453

void action_code_set_multicast(packet_descriptor_t *pd, lookup_table_t **tables,
                               struct action_set_multicast_params parameters) {// sugar@441
    uint32_t value32, res32, mask32;// sugar@442
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@443
    MODIFY_INT32_BYTEBUF(pd, field_instance_intrinsic_metadata_mcast_grp, parameters.grp, 2)// sugar@189
// sugar@449
}// sugar@453

