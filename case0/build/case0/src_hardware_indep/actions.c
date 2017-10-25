#include "dpdk_lib.h"// sugar@20
#include "actions.h"// sugar@21
#include <unistd.h>// sugar@22
#include <arpa/inet.h>// sugar@23

extern backend bg;// sugar@25

void action_code_no_op(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@439
    uint32_t value32, res32, mask32;// sugar@440
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@441
}// sugar@451

void action_code_drop(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@439
    uint32_t value32, res32, mask32;// sugar@440
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@441
}// sugar@451

void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@439
    uint32_t value32, res32, mask32;// sugar@440
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@441
}// sugar@451

void action_code_learning(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@439
    uint32_t value32, res32, mask32;// sugar@440
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@441
    struct type_field_list fields;// sugar@369
    fields.fields_quantity = 2;// sugar@371
    fields.field_offsets = malloc(sizeof(uint8_t * ) * fields.fields_quantity);// sugar@372
    fields.field_widths = malloc(sizeof(uint8_t * ) * fields.fields_quantity);// sugar@373
    fields.field_offsets[0] = (uint8_t *) field_desc(pd, field_instance_ethernet_src_mac).byte_addr;// sugar@377
    fields.field_widths[0] = field_desc(pd, field_instance_ethernet_src_mac).bitwidth;// sugar@378
    fields.field_offsets[1] = (uint8_t *) field_desc(pd, field_instance_vlan_vid).byte_addr;// sugar@377
    fields.field_widths[1] = field_desc(pd, field_instance_vlan_vid).bitwidth;// sugar@378

    generate_digest(bg, "learn_list", 0, &fields);
    sleep(1);// sugar@384
// sugar@447
}// sugar@451

void action_code_mcast(packet_descriptor_t *pd, lookup_table_t **tables) {// sugar@439
    uint32_t value32, res32, mask32;// sugar@440
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@441
    value32 = 1;// sugar@144
    MODIFY_INT32_INT32_AUTO(pd, field_instance_route_metadata_route, value32)// sugar@41
// sugar@145
// sugar@447
}// sugar@451

void
action_code_ucast(packet_descriptor_t *pd, lookup_table_t **tables, struct action_ucast_params parameters) {// sugar@439
    uint32_t value32, res32, mask32;// sugar@440
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@441
    value32 = 2;// sugar@144
    MODIFY_INT32_INT32_AUTO(pd, field_instance_route_metadata_route, value32)// sugar@41
// sugar@145
// sugar@447
    MODIFY_INT32_BYTEBUF(pd, field_instance_route_metadata_lan, parameters.lan, 1)// sugar@187
// sugar@447
}// sugar@451

void action_code_set_nhop(packet_descriptor_t *pd, lookup_table_t **tables,
                          struct action_set_nhop_params parameters) {// sugar@439
    uint32_t value32, res32, mask32;// sugar@440
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@441
    if (6 < field_desc(pd, field_instance_ethernet_src_mac).bytewidth) {// sugar@191
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_src_mac, parameters.src_mac, 6);                // sugar@192
    } else {// sugar@193
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_src_mac,
                               parameters.src_mac + (6 - field_desc(pd, field_instance_ethernet_src_mac).bytewidth),
                               field_desc(pd, field_instance_ethernet_src_mac).bytewidth)// sugar@194
    }// sugar@195
// sugar@447
    if (6 < field_desc(pd, field_instance_ethernet_dst_mac).bytewidth) {// sugar@191
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_dst_mac, parameters.dst_mac, 6);                // sugar@192
    } else {// sugar@193
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_dst_mac,
                               parameters.dst_mac + (6 - field_desc(pd, field_instance_ethernet_dst_mac).bytewidth),
                               field_desc(pd, field_instance_ethernet_dst_mac).bytewidth)// sugar@194
    }// sugar@195
// sugar@447
}// sugar@451

void action_code_set_nhop_with_vlan(packet_descriptor_t *pd, lookup_table_t **tables,
                                    struct action_set_nhop_with_vlan_params parameters) {// sugar@439
    uint32_t value32, res32, mask32;// sugar@440
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@441
    if (6 < field_desc(pd, field_instance_ethernet_src_mac).bytewidth) {// sugar@191
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_src_mac, parameters.src_mac, 6);                // sugar@192
    } else {// sugar@193
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_src_mac,
                               parameters.src_mac + (6 - field_desc(pd, field_instance_ethernet_src_mac).bytewidth),
                               field_desc(pd, field_instance_ethernet_src_mac).bytewidth)// sugar@194
    }// sugar@195
// sugar@447
    if (6 < field_desc(pd, field_instance_ethernet_dst_mac).bytewidth) {// sugar@191
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_dst_mac, parameters.dst_mac, 6);                // sugar@192
    } else {// sugar@193
        MODIFY_BYTEBUF_BYTEBUF(pd, field_instance_ethernet_dst_mac,
                               parameters.dst_mac + (6 - field_desc(pd, field_instance_ethernet_dst_mac).bytewidth),
                               field_desc(pd, field_instance_ethernet_dst_mac).bytewidth)// sugar@194
    }// sugar@195
// sugar@447
    MODIFY_INT32_BYTEBUF(pd, field_instance_vlan_vid, parameters.vid, 2)// sugar@187
// sugar@447
}// sugar@451

void action_code_forwarding(packet_descriptor_t *pd, lookup_table_t **tables,
                            struct action_forwarding_params parameters) {// sugar@439
    uint32_t value32, res32, mask32;// sugar@440
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@441
    MODIFY_INT32_BYTEBUF(pd, field_instance_standard_metadata_egress_spec, parameters.port, 2)// sugar@187
// sugar@447
}// sugar@451

void action_code_set_multicast(packet_descriptor_t *pd, lookup_table_t **tables,
                               struct action_set_multicast_params parameters) {// sugar@439
    uint32_t value32, res32, mask32;// sugar@440
    (void) value32;
    (void) res32;
    (void) mask32;// sugar@441
    MODIFY_INT32_BYTEBUF(pd, field_instance_intrinsic_metadata_mcast_grp, parameters.grp, 2)// sugar@187
// sugar@447
}// sugar@451

