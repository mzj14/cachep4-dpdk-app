#include "dpdk_lib.h"// sugar@22
#include "actions.h"// sugar@23

extern void table_setdefault_promote(int tableid, uint8_t *value);// sugar@25
extern void exact_add_promote(int tableid, uint8_t *key, uint8_t *value);// sugar@26
extern void lpm_add_promote(int tableid, uint8_t *key, uint8_t depth, uint8_t *value);// sugar@27
extern void ternary_add_promote(int tableid, uint8_t *key, uint8_t *mask, uint8_t *value);// sugar@28

extern void table_mac_acl_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_ipv4_acl_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_tcp_acl_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_udp_acl_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_get_acl_features_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_cache_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_mac_learning_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_routable_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_unicast_routing_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_switching_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_multicast_routing_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_igmp_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31

uint8_t reverse_buffer[34];// sugar@35
void// sugar@40
mac_acl_add(// sugar@41
        uint8_t field_instance_ethernet_src_mac[6],// sugar@44
        uint8_t field_instance_ethernet_src_mac_mask[6],// sugar@47
        uint8_t field_instance_ethernet_dst_mac[6],// sugar@44
        uint8_t field_instance_ethernet_dst_mac_mask[6],// sugar@47
        uint8_t field_instance_ethernet_eth_type[2],// sugar@44
        uint8_t field_instance_ethernet_eth_type_mask[2],// sugar@47
        struct mac_acl_action action)// sugar@51
{// sugar@52
    uint8_t key[14];// sugar@53
    uint8_t mask[14];// sugar@55
    memcpy(key + 0, field_instance_ethernet_src_mac, 6);// sugar@61
    memcpy(mask + 0, field_instance_ethernet_src_mac_mask, 6);// sugar@63
    memcpy(key + 6, field_instance_ethernet_dst_mac, 6);// sugar@61
    memcpy(mask + 6, field_instance_ethernet_dst_mac_mask, 6);// sugar@63
    memcpy(key + 12, field_instance_ethernet_eth_type, 2);// sugar@61
    memcpy(mask + 12, field_instance_ethernet_eth_type_mask, 2);// sugar@63
    ternary_add_promote(TABLE_mac_acl, (uint8_t *) key, (uint8_t *) mask, (uint8_t * ) & action);// sugar@84
}// sugar@85

void// sugar@87
mac_acl_setdefault(struct mac_acl_action action)// sugar@88
{// sugar@89
    table_setdefault_promote(TABLE_mac_acl, (uint8_t * ) & action);// sugar@90
}// sugar@91
void// sugar@40
ipv4_acl_add(// sugar@41
        uint8_t field_instance_ip_src_addr[4],// sugar@44
        uint8_t field_instance_ip_src_addr_mask[4],// sugar@47
        uint8_t field_instance_ip_dst_addr[4],// sugar@44
        uint8_t field_instance_ip_dst_addr_mask[4],// sugar@47
        uint8_t field_instance_ip_proto[1],// sugar@44
        uint8_t field_instance_ip_proto_mask[1],// sugar@47
        struct ipv4_acl_action action)// sugar@51
{// sugar@52
    uint8_t key[9];// sugar@53
    uint8_t mask[9];// sugar@55
    memcpy(key + 0, field_instance_ip_src_addr, 4);// sugar@61
    memcpy(mask + 0, field_instance_ip_src_addr_mask, 4);// sugar@63
    memcpy(key + 4, field_instance_ip_dst_addr, 4);// sugar@61
    memcpy(mask + 4, field_instance_ip_dst_addr_mask, 4);// sugar@63
    memcpy(key + 8, field_instance_ip_proto, 1);// sugar@61
    memcpy(mask + 8, field_instance_ip_proto_mask, 1);// sugar@63
    ternary_add_promote(TABLE_ipv4_acl, (uint8_t *) key, (uint8_t *) mask, (uint8_t * ) & action);// sugar@84
}// sugar@85

void// sugar@87
ipv4_acl_setdefault(struct ipv4_acl_action action)// sugar@88
{// sugar@89
    table_setdefault_promote(TABLE_ipv4_acl, (uint8_t * ) & action);// sugar@90
}// sugar@91
void// sugar@40
tcp_acl_add(// sugar@41
        uint8_t field_instance_tcp_src_port[2],// sugar@44
        uint8_t field_instance_tcp_src_port_mask[2],// sugar@47
        uint8_t field_instance_tcp_dst_port[2],// sugar@44
        uint8_t field_instance_tcp_dst_port_mask[2],// sugar@47
        uint8_t field_instance_tcp_flags[1],// sugar@44
        uint8_t field_instance_tcp_flags_mask[1],// sugar@47
        struct tcp_acl_action action)// sugar@51
{// sugar@52
    uint8_t key[5];// sugar@53
    uint8_t mask[5];// sugar@55
    memcpy(key + 0, field_instance_tcp_src_port, 2);// sugar@61
    memcpy(mask + 0, field_instance_tcp_src_port_mask, 2);// sugar@63
    memcpy(key + 2, field_instance_tcp_dst_port, 2);// sugar@61
    memcpy(mask + 2, field_instance_tcp_dst_port_mask, 2);// sugar@63
    memcpy(key + 4, field_instance_tcp_flags, 1);// sugar@61
    memcpy(mask + 4, field_instance_tcp_flags_mask, 1);// sugar@63
    ternary_add_promote(TABLE_tcp_acl, (uint8_t *) key, (uint8_t *) mask, (uint8_t * ) & action);// sugar@84
}// sugar@85

void// sugar@87
tcp_acl_setdefault(struct tcp_acl_action action)// sugar@88
{// sugar@89
    table_setdefault_promote(TABLE_tcp_acl, (uint8_t * ) & action);// sugar@90
}// sugar@91
void// sugar@40
udp_acl_add(// sugar@41
        uint8_t field_instance_udp_src_port[2],// sugar@44
        uint8_t field_instance_udp_src_port_mask[2],// sugar@47
        uint8_t field_instance_udp_dst_port[2],// sugar@44
        uint8_t field_instance_udp_dst_port_mask[2],// sugar@47
        struct udp_acl_action action)// sugar@51
{// sugar@52
    uint8_t key[4];// sugar@53
    uint8_t mask[4];// sugar@55
    memcpy(key + 0, field_instance_udp_src_port, 2);// sugar@61
    memcpy(mask + 0, field_instance_udp_src_port_mask, 2);// sugar@63
    memcpy(key + 2, field_instance_udp_dst_port, 2);// sugar@61
    memcpy(mask + 2, field_instance_udp_dst_port_mask, 2);// sugar@63
    ternary_add_promote(TABLE_udp_acl, (uint8_t *) key, (uint8_t *) mask, (uint8_t * ) & action);// sugar@84
}// sugar@85

void// sugar@87
udp_acl_setdefault(struct udp_acl_action action)// sugar@88
{// sugar@89
    table_setdefault_promote(TABLE_udp_acl, (uint8_t * ) & action);// sugar@90
}// sugar@91
void// sugar@40
get_acl_features_add(// sugar@41
        uint8_t field_instance_ip_src_addr[4],// sugar@44
        uint8_t field_instance_ip_src_addr_mask[4],// sugar@47
        uint8_t field_instance_ip_dst_addr[4],// sugar@44
        uint8_t field_instance_ip_dst_addr_mask[4],// sugar@47
        struct get_acl_features_action action)// sugar@51
{// sugar@52
    uint8_t key[8];// sugar@53
    uint8_t mask[8];// sugar@55
    memcpy(key + 0, field_instance_ip_src_addr, 4);// sugar@61
    memcpy(mask + 0, field_instance_ip_src_addr_mask, 4);// sugar@63
    memcpy(key + 4, field_instance_ip_dst_addr, 4);// sugar@61
    memcpy(mask + 4, field_instance_ip_dst_addr_mask, 4);// sugar@63
    ternary_add_promote(TABLE_get_acl_features, (uint8_t *) key, (uint8_t *) mask, (uint8_t * ) & action);// sugar@84
}// sugar@85

void// sugar@87
get_acl_features_setdefault(struct get_acl_features_action action)// sugar@88
{// sugar@89
    table_setdefault_promote(TABLE_get_acl_features, (uint8_t * ) & action);// sugar@90
}// sugar@91
void// sugar@40
cache_add(// sugar@41
        uint8_t field_instance_standard_metadata_ingress_port[2],// sugar@44
        uint8_t field_instance_standard_metadata_ingress_port_mask[2],// sugar@47
        uint8_t field_instance_ethernet_src_mac[6],// sugar@44
        uint8_t field_instance_ethernet_src_mac_mask[6],// sugar@47
        uint8_t field_instance_ethernet_dst_mac[6],// sugar@44
        uint8_t field_instance_ethernet_dst_mac_mask[6],// sugar@47
        uint8_t field_instance_ethernet_eth_type[2],// sugar@44
        uint8_t field_instance_ethernet_eth_type_mask[2],// sugar@47
        uint8_t field_instance_ip_src_addr[4],// sugar@44
        uint8_t field_instance_ip_src_addr_mask[4],// sugar@47
        uint8_t field_instance_ip_dst_addr[4],// sugar@44
        uint8_t field_instance_ip_dst_addr_mask[4],// sugar@47
        uint8_t field_instance_ip_proto[1],// sugar@44
        uint8_t field_instance_ip_proto_mask[1],// sugar@47
        uint8_t field_instance_tcp_src_port[2],// sugar@44
        uint8_t field_instance_tcp_src_port_mask[2],// sugar@47
        uint8_t field_instance_tcp_dst_port[2],// sugar@44
        uint8_t field_instance_tcp_dst_port_mask[2],// sugar@47
        uint8_t field_instance_udp_src_port[2],// sugar@44
        uint8_t field_instance_udp_src_port_mask[2],// sugar@47
        uint8_t field_instance_udp_dst_port[2],// sugar@44
        uint8_t field_instance_udp_dst_port_mask[2],// sugar@47
        uint8_t field_instance_tcp_flags[1],// sugar@44
        uint8_t field_instance_tcp_flags_mask[1],// sugar@47
        struct cache_action action)// sugar@51
{// sugar@52
    uint8_t key[34];// sugar@53
    uint8_t mask[34];// sugar@55
    memcpy(key + 0, field_instance_standard_metadata_ingress_port, 2);// sugar@61
    memcpy(mask + 0, field_instance_standard_metadata_ingress_port_mask, 2);// sugar@63
    memcpy(key + 2, field_instance_ethernet_src_mac, 6);// sugar@61
    memcpy(mask + 2, field_instance_ethernet_src_mac_mask, 6);// sugar@63
    memcpy(key + 8, field_instance_ethernet_dst_mac, 6);// sugar@61
    memcpy(mask + 8, field_instance_ethernet_dst_mac_mask, 6);// sugar@63
    memcpy(key + 14, field_instance_ethernet_eth_type, 2);// sugar@61
    memcpy(mask + 14, field_instance_ethernet_eth_type_mask, 2);// sugar@63
    memcpy(key + 16, field_instance_ip_src_addr, 4);// sugar@61
    memcpy(mask + 16, field_instance_ip_src_addr_mask, 4);// sugar@63
    memcpy(key + 20, field_instance_ip_dst_addr, 4);// sugar@61
    memcpy(mask + 20, field_instance_ip_dst_addr_mask, 4);// sugar@63
    memcpy(key + 24, field_instance_ip_proto, 1);// sugar@61
    memcpy(mask + 24, field_instance_ip_proto_mask, 1);// sugar@63
    memcpy(key + 25, field_instance_tcp_src_port, 2);// sugar@61
    memcpy(mask + 25, field_instance_tcp_src_port_mask, 2);// sugar@63
    memcpy(key + 27, field_instance_tcp_dst_port, 2);// sugar@61
    memcpy(mask + 27, field_instance_tcp_dst_port_mask, 2);// sugar@63
    memcpy(key + 29, field_instance_udp_src_port, 2);// sugar@61
    memcpy(mask + 29, field_instance_udp_src_port_mask, 2);// sugar@63
    memcpy(key + 31, field_instance_udp_dst_port, 2);// sugar@61
    memcpy(mask + 31, field_instance_udp_dst_port_mask, 2);// sugar@63
    memcpy(key + 33, field_instance_tcp_flags, 1);// sugar@61
    memcpy(mask + 33, field_instance_tcp_flags_mask, 1);// sugar@63
    ternary_add_promote(TABLE_cache, (uint8_t *) key, (uint8_t *) mask, (uint8_t * ) & action);// sugar@84
}// sugar@85

void// sugar@87
cache_setdefault(struct cache_action action)// sugar@88
{// sugar@89
    table_setdefault_promote(TABLE_cache, (uint8_t * ) & action);// sugar@90
}// sugar@91
void// sugar@40
mac_learning_add(// sugar@41
        uint8_t field_instance_ethernet_src_mac[6],// sugar@44
        uint8_t field_instance_vlan_vid[2],// sugar@44
        struct mac_learning_action action)// sugar@51
{// sugar@52
    uint8_t key[8];// sugar@53
    memcpy(key + 0, field_instance_ethernet_src_mac, 6);// sugar@61
    memcpy(key + 6, field_instance_vlan_vid, 2);// sugar@61
    exact_add_promote(TABLE_mac_learning, (uint8_t *) key, (uint8_t * ) & action);// sugar@82
}// sugar@85

void// sugar@87
mac_learning_setdefault(struct mac_learning_action action)// sugar@88
{// sugar@89
    table_setdefault_promote(TABLE_mac_learning, (uint8_t * ) & action);// sugar@90
}// sugar@91
void// sugar@40
routable_add(// sugar@41
        uint8_t field_instance_ethernet_src_mac[6],// sugar@44
        uint8_t field_instance_ethernet_dst_mac[6],// sugar@44
        uint8_t field_instance_vlan_vid[2],// sugar@44
        struct routable_action action)// sugar@51
{// sugar@52
    uint8_t key[14];// sugar@53
    memcpy(key + 0, field_instance_ethernet_src_mac, 6);// sugar@61
    memcpy(key + 6, field_instance_ethernet_dst_mac, 6);// sugar@61
    memcpy(key + 12, field_instance_vlan_vid, 2);// sugar@61
    exact_add_promote(TABLE_routable, (uint8_t *) key, (uint8_t * ) & action);// sugar@82
}// sugar@85

void// sugar@87
routable_setdefault(struct routable_action action)// sugar@88
{// sugar@89
    table_setdefault_promote(TABLE_routable, (uint8_t * ) & action);// sugar@90
}// sugar@91
void// sugar@40
unicast_routing_add(// sugar@41
        uint8_t field_instance_ip_dst_addr[4],// sugar@44
        struct unicast_routing_action action)// sugar@51
{// sugar@52
    uint8_t key[4];// sugar@53
    memcpy(key + 0, field_instance_ip_dst_addr, 4);// sugar@61
    exact_add_promote(TABLE_unicast_routing, (uint8_t *) key, (uint8_t * ) & action);// sugar@82
}// sugar@85

void// sugar@87
unicast_routing_setdefault(struct unicast_routing_action action)// sugar@88
{// sugar@89
    table_setdefault_promote(TABLE_unicast_routing, (uint8_t * ) & action);// sugar@90
}// sugar@91
void// sugar@40
switching_add(// sugar@41
        uint8_t field_instance_ethernet_dst_mac[6],// sugar@44
        uint8_t field_instance_vlan_vid[2],// sugar@44
        struct switching_action action)// sugar@51
{// sugar@52
    uint8_t key[8];// sugar@53
    memcpy(key + 0, field_instance_ethernet_dst_mac, 6);// sugar@61
    memcpy(key + 6, field_instance_vlan_vid, 2);// sugar@61
    exact_add_promote(TABLE_switching, (uint8_t *) key, (uint8_t * ) & action);// sugar@82
}// sugar@85

void// sugar@87
switching_setdefault(struct switching_action action)// sugar@88
{// sugar@89
    table_setdefault_promote(TABLE_switching, (uint8_t * ) & action);// sugar@90
}// sugar@91
void// sugar@40
multicast_routing_add(// sugar@41
        uint8_t field_instance_ip_dst_addr[4],// sugar@44
        uint8_t field_instance_ip_dst_addr_prefix_length,// sugar@50
        struct multicast_routing_action action)// sugar@51
{// sugar@52
    uint8_t key[4];// sugar@53
    memcpy(key + 0, field_instance_ip_dst_addr, 4);// sugar@61
    uint8_t prefix_length = 0;// sugar@67
    prefix_length += field_instance_ip_dst_addr_prefix_length;// sugar@74
    int c, d;// sugar@75
    for (c = 3, d = 0; c >= 0; c--, d++) *(reverse_buffer + d) = *(key + c);// sugar@76
    for (c = 0; c < 4; c++) *(key + c) = *(reverse_buffer + c);// sugar@77
    lpm_add_promote(TABLE_multicast_routing, (uint8_t *) key, prefix_length, (uint8_t * ) & action);// sugar@78
}// sugar@85

void// sugar@87
multicast_routing_setdefault(struct multicast_routing_action action)// sugar@88
{// sugar@89
    table_setdefault_promote(TABLE_multicast_routing, (uint8_t * ) & action);// sugar@90
}// sugar@91
void// sugar@40
igmp_add(// sugar@41
        uint8_t field_instance_ip_dst_addr[4],// sugar@44
        uint8_t field_instance_ip_dst_addr_prefix_length,// sugar@50
        uint8_t field_instance_vlan_vid[2],// sugar@44
        uint8_t field_instance_standard_metadata_ingress_port[2],// sugar@44
        struct igmp_action action)// sugar@51
{// sugar@52
    uint8_t key[8];// sugar@53
    memcpy(key + 0, field_instance_vlan_vid, 2);// sugar@61
    memcpy(key + 2, field_instance_standard_metadata_ingress_port, 2);// sugar@61
    memcpy(key + 4, field_instance_ip_dst_addr, 4);// sugar@61
    uint8_t prefix_length = 0;// sugar@67
    prefix_length += field_instance_ip_dst_addr_prefix_length;// sugar@74
    prefix_length += 12;// sugar@72
    prefix_length += 9;// sugar@72
    int c, d;// sugar@75
    for (c = 7, d = 0; c >= 0; c--, d++) *(reverse_buffer + d) = *(key + c);// sugar@76
    for (c = 0; c < 8; c++) *(key + c) = *(reverse_buffer + c);// sugar@77
    lpm_add_promote(TABLE_igmp, (uint8_t *) key, prefix_length, (uint8_t * ) & action);// sugar@78
}// sugar@85

void// sugar@87
igmp_setdefault(struct igmp_action action)// sugar@88
{// sugar@89
    table_setdefault_promote(TABLE_igmp, (uint8_t * ) & action);// sugar@90
}// sugar@91
void// sugar@95
mac_acl_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@96
    uint8_t *field_instance_ethernet_src_mac = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->bitmap);// sugar@105
    uint8_t *field_instance_ethernet_src_mac_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->mask);// sugar@106
    uint8_t *field_instance_ethernet_dst_mac = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->bitmap);// sugar@105
    uint8_t *field_instance_ethernet_dst_mac_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->mask);// sugar@106
    uint8_t *field_instance_ethernet_eth_type = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->bitmap);// sugar@105
    uint8_t *field_instance_ethernet_eth_type_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->mask);// sugar@106
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@108
        struct mac_acl_action action;// sugar@109
        action.action_id = action_acl_alert;// sugar@110
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to mac_acl with action acl_alert\n");// sugar@115
        mac_acl_add(// sugar@116
                field_instance_ethernet_src_mac,// sugar@119
                field_instance_ethernet_src_mac_mask,// sugar@123
                field_instance_ethernet_dst_mac,// sugar@119
                field_instance_ethernet_dst_mac_mask,// sugar@123
                field_instance_ethernet_eth_type,// sugar@119
                field_instance_ethernet_eth_type_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@108
        struct mac_acl_action action;// sugar@109
        action.action_id = action_acl_permit;// sugar@110
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to mac_acl with action acl_permit\n");// sugar@115
        mac_acl_add(// sugar@116
                field_instance_ethernet_src_mac,// sugar@119
                field_instance_ethernet_src_mac_mask,// sugar@123
                field_instance_ethernet_dst_mac,// sugar@119
                field_instance_ethernet_dst_mac_mask,// sugar@123
                field_instance_ethernet_eth_type,// sugar@119
                field_instance_ethernet_eth_type_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@108
        struct mac_acl_action action;// sugar@109
        action.action_id = action_acl_drop;// sugar@110
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to mac_acl with action acl_drop\n");// sugar@115
        mac_acl_add(// sugar@116
                field_instance_ethernet_src_mac,// sugar@119
                field_instance_ethernet_src_mac_mask,// sugar@123
                field_instance_ethernet_dst_mac,// sugar@119
                field_instance_ethernet_dst_mac_mask,// sugar@123
                field_instance_ethernet_eth_type,// sugar@119
                field_instance_ethernet_eth_type_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@108
        struct mac_acl_action action;// sugar@109
        action.action_id = action_nop;// sugar@110
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to mac_acl with action nop\n");// sugar@115
        mac_acl_add(// sugar@116
                field_instance_ethernet_src_mac,// sugar@119
                field_instance_ethernet_src_mac_mask,// sugar@123
                field_instance_ethernet_dst_mac,// sugar@119
                field_instance_ethernet_dst_mac_mask,// sugar@123
                field_instance_ethernet_eth_type,// sugar@119
                field_instance_ethernet_eth_type_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@126
}// sugar@127
void// sugar@95
ipv4_acl_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@96
    uint8_t *field_instance_ip_src_addr = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->bitmap);// sugar@105
    uint8_t *field_instance_ip_src_addr_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->mask);// sugar@106
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->bitmap);// sugar@105
    uint8_t *field_instance_ip_dst_addr_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->mask);// sugar@106
    uint8_t *field_instance_ip_proto = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->bitmap);// sugar@105
    uint8_t *field_instance_ip_proto_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->mask);// sugar@106
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@108
        struct ipv4_acl_action action;// sugar@109
        action.action_id = action_acl_permit;// sugar@110
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to ipv4_acl with action acl_permit\n");// sugar@115
        ipv4_acl_add(// sugar@116
                field_instance_ip_src_addr,// sugar@119
                field_instance_ip_src_addr_mask,// sugar@123
                field_instance_ip_dst_addr,// sugar@119
                field_instance_ip_dst_addr_mask,// sugar@123
                field_instance_ip_proto,// sugar@119
                field_instance_ip_proto_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@108
        struct ipv4_acl_action action;// sugar@109
        action.action_id = action_acl_alert;// sugar@110
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to ipv4_acl with action acl_alert\n");// sugar@115
        ipv4_acl_add(// sugar@116
                field_instance_ip_src_addr,// sugar@119
                field_instance_ip_src_addr_mask,// sugar@123
                field_instance_ip_dst_addr,// sugar@119
                field_instance_ip_dst_addr_mask,// sugar@123
                field_instance_ip_proto,// sugar@119
                field_instance_ip_proto_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@108
        struct ipv4_acl_action action;// sugar@109
        action.action_id = action_acl_drop;// sugar@110
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to ipv4_acl with action acl_drop\n");// sugar@115
        ipv4_acl_add(// sugar@116
                field_instance_ip_src_addr,// sugar@119
                field_instance_ip_src_addr_mask,// sugar@123
                field_instance_ip_dst_addr,// sugar@119
                field_instance_ip_dst_addr_mask,// sugar@123
                field_instance_ip_proto,// sugar@119
                field_instance_ip_proto_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@108
        struct ipv4_acl_action action;// sugar@109
        action.action_id = action_nop;// sugar@110
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to ipv4_acl with action nop\n");// sugar@115
        ipv4_acl_add(// sugar@116
                field_instance_ip_src_addr,// sugar@119
                field_instance_ip_src_addr_mask,// sugar@123
                field_instance_ip_dst_addr,// sugar@119
                field_instance_ip_dst_addr_mask,// sugar@123
                field_instance_ip_proto,// sugar@119
                field_instance_ip_proto_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@126
}// sugar@127
void// sugar@95
tcp_acl_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@96
    uint8_t *field_instance_tcp_src_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->bitmap);// sugar@105
    uint8_t *field_instance_tcp_src_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->mask);// sugar@106
    uint8_t *field_instance_tcp_dst_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->bitmap);// sugar@105
    uint8_t *field_instance_tcp_dst_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->mask);// sugar@106
    uint8_t *field_instance_tcp_flags = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->bitmap);// sugar@105
    uint8_t *field_instance_tcp_flags_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->mask);// sugar@106
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@108
        struct tcp_acl_action action;// sugar@109
        action.action_id = action_acl_permit;// sugar@110
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to tcp_acl with action acl_permit\n");// sugar@115
        tcp_acl_add(// sugar@116
                field_instance_tcp_src_port,// sugar@119
                field_instance_tcp_src_port_mask,// sugar@123
                field_instance_tcp_dst_port,// sugar@119
                field_instance_tcp_dst_port_mask,// sugar@123
                field_instance_tcp_flags,// sugar@119
                field_instance_tcp_flags_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@108
        struct tcp_acl_action action;// sugar@109
        action.action_id = action_acl_alert;// sugar@110
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to tcp_acl with action acl_alert\n");// sugar@115
        tcp_acl_add(// sugar@116
                field_instance_tcp_src_port,// sugar@119
                field_instance_tcp_src_port_mask,// sugar@123
                field_instance_tcp_dst_port,// sugar@119
                field_instance_tcp_dst_port_mask,// sugar@123
                field_instance_tcp_flags,// sugar@119
                field_instance_tcp_flags_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@108
        struct tcp_acl_action action;// sugar@109
        action.action_id = action_acl_drop;// sugar@110
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to tcp_acl with action acl_drop\n");// sugar@115
        tcp_acl_add(// sugar@116
                field_instance_tcp_src_port,// sugar@119
                field_instance_tcp_src_port_mask,// sugar@123
                field_instance_tcp_dst_port,// sugar@119
                field_instance_tcp_dst_port_mask,// sugar@123
                field_instance_tcp_flags,// sugar@119
                field_instance_tcp_flags_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@108
        struct tcp_acl_action action;// sugar@109
        action.action_id = action_nop;// sugar@110
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to tcp_acl with action nop\n");// sugar@115
        tcp_acl_add(// sugar@116
                field_instance_tcp_src_port,// sugar@119
                field_instance_tcp_src_port_mask,// sugar@123
                field_instance_tcp_dst_port,// sugar@119
                field_instance_tcp_dst_port_mask,// sugar@123
                field_instance_tcp_flags,// sugar@119
                field_instance_tcp_flags_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@126
}// sugar@127
void// sugar@95
udp_acl_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@96
    uint8_t *field_instance_udp_src_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->bitmap);// sugar@105
    uint8_t *field_instance_udp_src_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->mask);// sugar@106
    uint8_t *field_instance_udp_dst_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->bitmap);// sugar@105
    uint8_t *field_instance_udp_dst_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->mask);// sugar@106
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@108
        struct udp_acl_action action;// sugar@109
        action.action_id = action_acl_permit;// sugar@110
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to udp_acl with action acl_permit\n");// sugar@115
        udp_acl_add(// sugar@116
                field_instance_udp_src_port,// sugar@119
                field_instance_udp_src_port_mask,// sugar@123
                field_instance_udp_dst_port,// sugar@119
                field_instance_udp_dst_port_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@108
        struct udp_acl_action action;// sugar@109
        action.action_id = action_acl_alert;// sugar@110
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to udp_acl with action acl_alert\n");// sugar@115
        udp_acl_add(// sugar@116
                field_instance_udp_src_port,// sugar@119
                field_instance_udp_src_port_mask,// sugar@123
                field_instance_udp_dst_port,// sugar@119
                field_instance_udp_dst_port_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@108
        struct udp_acl_action action;// sugar@109
        action.action_id = action_acl_drop;// sugar@110
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to udp_acl with action acl_drop\n");// sugar@115
        udp_acl_add(// sugar@116
                field_instance_udp_src_port,// sugar@119
                field_instance_udp_src_port_mask,// sugar@123
                field_instance_udp_dst_port,// sugar@119
                field_instance_udp_dst_port_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@108
        struct udp_acl_action action;// sugar@109
        action.action_id = action_nop;// sugar@110
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to udp_acl with action nop\n");// sugar@115
        udp_acl_add(// sugar@116
                field_instance_udp_src_port,// sugar@119
                field_instance_udp_src_port_mask,// sugar@123
                field_instance_udp_dst_port,// sugar@119
                field_instance_udp_dst_port_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@126
}// sugar@127
void// sugar@95
get_acl_features_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@96
    uint8_t *field_instance_ip_src_addr = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->bitmap);// sugar@105
    uint8_t *field_instance_ip_src_addr_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->mask);// sugar@106
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->bitmap);// sugar@105
    uint8_t *field_instance_ip_dst_addr_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->mask);// sugar@106
    if (strcmp("acl_feature", ctrl_m->action_name) == 0) {// sugar@108
        struct get_acl_features_action action;// sugar@109
        action.action_id = action_acl_feature;// sugar@110
        uint8_t *enable_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.acl_feature_params.enable_mac, enable_mac, 1);// sugar@113
        uint8_t *enable_vlan = (uint8_t * )(
                (struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@112
        memcpy(action.acl_feature_params.enable_vlan, enable_vlan, 1);// sugar@113
        uint8_t *enable_ipv4 = (uint8_t * )(
                (struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@112
        memcpy(action.acl_feature_params.enable_ipv4, enable_ipv4, 1);// sugar@113
        uint8_t *enable_icmp = (uint8_t * )(
                (struct p4_action_parameter *) ctrl_m->action_params[3])->bitmap;// sugar@112
        memcpy(action.acl_feature_params.enable_icmp, enable_icmp, 1);// sugar@113
        uint8_t *enable_tcp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[4])->bitmap;// sugar@112
        memcpy(action.acl_feature_params.enable_tcp, enable_tcp, 1);// sugar@113
        uint8_t *enable_udp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[5])->bitmap;// sugar@112
        memcpy(action.acl_feature_params.enable_udp, enable_udp, 1);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to get_acl_features with action acl_feature\n");// sugar@115
        get_acl_features_add(// sugar@116
                field_instance_ip_src_addr,// sugar@119
                field_instance_ip_src_addr_mask,// sugar@123
                field_instance_ip_dst_addr,// sugar@119
                field_instance_ip_dst_addr_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@126
}// sugar@127
void// sugar@95
cache_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@96
    uint8_t *field_instance_standard_metadata_ingress_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->bitmap);// sugar@105
    uint8_t *field_instance_standard_metadata_ingress_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->mask);// sugar@106
    uint8_t *field_instance_ethernet_src_mac = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->bitmap);// sugar@105
    uint8_t *field_instance_ethernet_src_mac_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->mask);// sugar@106
    uint8_t *field_instance_ethernet_dst_mac = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->bitmap);// sugar@105
    uint8_t *field_instance_ethernet_dst_mac_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->mask);// sugar@106
    uint8_t *field_instance_ethernet_eth_type = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[3])->bitmap);// sugar@105
    uint8_t *field_instance_ethernet_eth_type_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[3])->mask);// sugar@106
    uint8_t *field_instance_ip_src_addr = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[4])->bitmap);// sugar@105
    uint8_t *field_instance_ip_src_addr_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[4])->mask);// sugar@106
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[5])->bitmap);// sugar@105
    uint8_t *field_instance_ip_dst_addr_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[5])->mask);// sugar@106
    uint8_t *field_instance_ip_proto = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[6])->bitmap);// sugar@105
    uint8_t *field_instance_ip_proto_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[6])->mask);// sugar@106
    uint8_t *field_instance_tcp_src_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[7])->bitmap);// sugar@105
    uint8_t *field_instance_tcp_src_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[7])->mask);// sugar@106
    uint8_t *field_instance_tcp_dst_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[8])->bitmap);// sugar@105
    uint8_t *field_instance_tcp_dst_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[8])->mask);// sugar@106
    uint8_t *field_instance_udp_src_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[9])->bitmap);// sugar@105
    uint8_t *field_instance_udp_src_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[9])->mask);// sugar@106
    uint8_t *field_instance_udp_dst_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[10])->bitmap);// sugar@105
    uint8_t *field_instance_udp_dst_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[10])->mask);// sugar@106
    uint8_t *field_instance_tcp_flags = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[11])->bitmap);// sugar@105
    uint8_t *field_instance_tcp_flags_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[11])->mask);// sugar@106
    if (strcmp("cache_block", ctrl_m->action_name) == 0) {// sugar@108
        struct cache_action action;// sugar@109
        action.action_id = action_cache_block;// sugar@110
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to cache with action cache_block\n");// sugar@115
        cache_add(// sugar@116
                field_instance_standard_metadata_ingress_port,// sugar@119
                field_instance_standard_metadata_ingress_port_mask,// sugar@123
                field_instance_ethernet_src_mac,// sugar@119
                field_instance_ethernet_src_mac_mask,// sugar@123
                field_instance_ethernet_dst_mac,// sugar@119
                field_instance_ethernet_dst_mac_mask,// sugar@123
                field_instance_ethernet_eth_type,// sugar@119
                field_instance_ethernet_eth_type_mask,// sugar@123
                field_instance_ip_src_addr,// sugar@119
                field_instance_ip_src_addr_mask,// sugar@123
                field_instance_ip_dst_addr,// sugar@119
                field_instance_ip_dst_addr_mask,// sugar@123
                field_instance_ip_proto,// sugar@119
                field_instance_ip_proto_mask,// sugar@123
                field_instance_tcp_src_port,// sugar@119
                field_instance_tcp_src_port_mask,// sugar@123
                field_instance_tcp_dst_port,// sugar@119
                field_instance_tcp_dst_port_mask,// sugar@123
                field_instance_udp_src_port,// sugar@119
                field_instance_udp_src_port_mask,// sugar@123
                field_instance_udp_dst_port,// sugar@119
                field_instance_udp_dst_port_mask,// sugar@123
                field_instance_tcp_flags,// sugar@119
                field_instance_tcp_flags_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
    if (strcmp("cache_action", ctrl_m->action_name) == 0) {// sugar@108
        struct cache_action action;// sugar@109
        action.action_id = action_cache_action;// sugar@110
        uint8_t *port = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.cache_action_params.port, port, 2);// sugar@113
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@112
        memcpy(action.cache_action_params.src_mac, src_mac, 6);// sugar@113
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@112
        memcpy(action.cache_action_params.dst_mac, dst_mac, 6);// sugar@113
        uint8_t *vid = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[3])->bitmap;// sugar@112
        memcpy(action.cache_action_params.vid, vid, 2);// sugar@113
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[4])->bitmap;// sugar@112
        memcpy(action.cache_action_params.grp, grp, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to cache with action cache_action\n");// sugar@115
        cache_add(// sugar@116
                field_instance_standard_metadata_ingress_port,// sugar@119
                field_instance_standard_metadata_ingress_port_mask,// sugar@123
                field_instance_ethernet_src_mac,// sugar@119
                field_instance_ethernet_src_mac_mask,// sugar@123
                field_instance_ethernet_dst_mac,// sugar@119
                field_instance_ethernet_dst_mac_mask,// sugar@123
                field_instance_ethernet_eth_type,// sugar@119
                field_instance_ethernet_eth_type_mask,// sugar@123
                field_instance_ip_src_addr,// sugar@119
                field_instance_ip_src_addr_mask,// sugar@123
                field_instance_ip_dst_addr,// sugar@119
                field_instance_ip_dst_addr_mask,// sugar@123
                field_instance_ip_proto,// sugar@119
                field_instance_ip_proto_mask,// sugar@123
                field_instance_tcp_src_port,// sugar@119
                field_instance_tcp_src_port_mask,// sugar@123
                field_instance_tcp_dst_port,// sugar@119
                field_instance_tcp_dst_port_mask,// sugar@123
                field_instance_udp_src_port,// sugar@119
                field_instance_udp_src_port_mask,// sugar@123
                field_instance_udp_dst_port,// sugar@119
                field_instance_udp_dst_port_mask,// sugar@123
                field_instance_tcp_flags,// sugar@119
                field_instance_tcp_flags_mask,// sugar@123
                action);// sugar@124
    } else// sugar@125
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@126
}// sugar@127
void// sugar@95
mac_learning_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@96
    uint8_t *field_instance_ethernet_src_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@100
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@100
    if (strcmp("learning", ctrl_m->action_name) == 0) {// sugar@108
        struct mac_learning_action action;// sugar@109
        action.action_id = action_learning;// sugar@110
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to mac_learning with action learning\n");// sugar@115
        mac_learning_add(// sugar@116
                field_instance_ethernet_src_mac,// sugar@119
                field_instance_vlan_vid,// sugar@119
                action);// sugar@124
    } else// sugar@125
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@108
        struct mac_learning_action action;// sugar@109
        action.action_id = action_nop;// sugar@110
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to mac_learning with action nop\n");// sugar@115
        mac_learning_add(// sugar@116
                field_instance_ethernet_src_mac,// sugar@119
                field_instance_vlan_vid,// sugar@119
                action);// sugar@124
    } else// sugar@125
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@126
}// sugar@127
void// sugar@95
routable_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@96
    uint8_t *field_instance_ethernet_src_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@100
    uint8_t *field_instance_ethernet_dst_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@100
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[2])->bitmap);// sugar@100
    if (strcmp("ucast", ctrl_m->action_name) == 0) {// sugar@108
        struct routable_action action;// sugar@109
        action.action_id = action_ucast;// sugar@110
        uint8_t *lan = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.ucast_params.lan, lan, 1);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to routable with action ucast\n");// sugar@115
        routable_add(// sugar@116
                field_instance_ethernet_src_mac,// sugar@119
                field_instance_ethernet_dst_mac,// sugar@119
                field_instance_vlan_vid,// sugar@119
                action);// sugar@124
    } else// sugar@125
    if (strcmp("mcast", ctrl_m->action_name) == 0) {// sugar@108
        struct routable_action action;// sugar@109
        action.action_id = action_mcast;// sugar@110
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to routable with action mcast\n");// sugar@115
        routable_add(// sugar@116
                field_instance_ethernet_src_mac,// sugar@119
                field_instance_ethernet_dst_mac,// sugar@119
                field_instance_vlan_vid,// sugar@119
                action);// sugar@124
    } else// sugar@125
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@126
}// sugar@127
void// sugar@95
unicast_routing_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@96
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@100
    if (strcmp("set_nhop", ctrl_m->action_name) == 0) {// sugar@108
        struct unicast_routing_action action;// sugar@109
        action.action_id = action_set_nhop;// sugar@110
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.set_nhop_params.src_mac, src_mac, 6);// sugar@113
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@112
        memcpy(action.set_nhop_params.dst_mac, dst_mac, 6);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to unicast_routing with action set_nhop\n");// sugar@115
        unicast_routing_add(// sugar@116
                field_instance_ip_dst_addr,// sugar@119
                action);// sugar@124
    } else// sugar@125
    if (strcmp("set_nhop_with_vlan", ctrl_m->action_name) == 0) {// sugar@108
        struct unicast_routing_action action;// sugar@109
        action.action_id = action_set_nhop_with_vlan;// sugar@110
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.set_nhop_with_vlan_params.src_mac, src_mac, 6);// sugar@113
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@112
        memcpy(action.set_nhop_with_vlan_params.dst_mac, dst_mac, 6);// sugar@113
        uint8_t *vid = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@112
        memcpy(action.set_nhop_with_vlan_params.vid, vid, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to unicast_routing with action set_nhop_with_vlan\n");// sugar@115
        unicast_routing_add(// sugar@116
                field_instance_ip_dst_addr,// sugar@119
                action);// sugar@124
    } else// sugar@125
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@126
}// sugar@127
void// sugar@95
switching_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@96
    uint8_t *field_instance_ethernet_dst_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@100
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@100
    if (strcmp("forwarding", ctrl_m->action_name) == 0) {// sugar@108
        struct switching_action action;// sugar@109
        action.action_id = action_forwarding;// sugar@110
        uint8_t *port = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.forwarding_params.port, port, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to switching with action forwarding\n");// sugar@115
        switching_add(// sugar@116
                field_instance_ethernet_dst_mac,// sugar@119
                field_instance_vlan_vid,// sugar@119
                action);// sugar@124
    } else// sugar@125
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@126
}// sugar@127
void// sugar@95
multicast_routing_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@96
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_lpm *) ctrl_m->field_matches[0])->bitmap);// sugar@102
    uint16_t field_instance_ip_dst_addr_prefix_length = ((struct p4_field_match_lpm *) ctrl_m->field_matches[0])->prefix_length;// sugar@103
    if (strcmp("set_multicast", ctrl_m->action_name) == 0) {// sugar@108
        struct multicast_routing_action action;// sugar@109
        action.action_id = action_set_multicast;// sugar@110
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.set_multicast_params.grp, grp, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to multicast_routing with action set_multicast\n");// sugar@115
        multicast_routing_add(// sugar@116
                field_instance_ip_dst_addr,// sugar@119
                field_instance_ip_dst_addr_prefix_length,// sugar@121
                action);// sugar@124
    } else// sugar@125
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@126
}// sugar@127
void// sugar@95
igmp_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@96
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_lpm *) ctrl_m->field_matches[0])->bitmap);// sugar@102
    uint16_t field_instance_ip_dst_addr_prefix_length = ((struct p4_field_match_lpm *) ctrl_m->field_matches[0])->prefix_length;// sugar@103
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@100
    uint8_t *field_instance_standard_metadata_ingress_port = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[2])->bitmap);// sugar@100
    if (strcmp("set_multicast", ctrl_m->action_name) == 0) {// sugar@108
        struct igmp_action action;// sugar@109
        action.action_id = action_set_multicast;// sugar@110
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@112
        memcpy(action.set_multicast_params.grp, grp, 2);// sugar@113
        debug("Reply from the control plane arrived.\n");// sugar@114
        debug("Adding new entry to igmp with action set_multicast\n");// sugar@115
        igmp_add(// sugar@116
                field_instance_ip_dst_addr,// sugar@119
                field_instance_ip_dst_addr_prefix_length,// sugar@121
                field_instance_vlan_vid,// sugar@119
                field_instance_standard_metadata_ingress_port,// sugar@119
                action);// sugar@124
    } else// sugar@125
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@126
}// sugar@127
void// sugar@130
mac_acl_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@131
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@132
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@134
        struct mac_acl_action action;// sugar@135
        action.action_id = action_acl_alert;// sugar@136
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for mac_acl with action acl_alert\n");// sugar@141
        mac_acl_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@134
        struct mac_acl_action action;// sugar@135
        action.action_id = action_acl_permit;// sugar@136
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for mac_acl with action acl_permit\n");// sugar@141
        mac_acl_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@134
        struct mac_acl_action action;// sugar@135
        action.action_id = action_acl_drop;// sugar@136
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for mac_acl with action acl_drop\n");// sugar@141
        mac_acl_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@134
        struct mac_acl_action action;// sugar@135
        action.action_id = action_nop;// sugar@136
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for mac_acl with action nop\n");// sugar@141
        mac_acl_setdefault(action);// sugar@142
    } else// sugar@143
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@144
}// sugar@145
void// sugar@130
ipv4_acl_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@131
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@132
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@134
        struct ipv4_acl_action action;// sugar@135
        action.action_id = action_acl_permit;// sugar@136
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for ipv4_acl with action acl_permit\n");// sugar@141
        ipv4_acl_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@134
        struct ipv4_acl_action action;// sugar@135
        action.action_id = action_acl_alert;// sugar@136
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for ipv4_acl with action acl_alert\n");// sugar@141
        ipv4_acl_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@134
        struct ipv4_acl_action action;// sugar@135
        action.action_id = action_acl_drop;// sugar@136
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for ipv4_acl with action acl_drop\n");// sugar@141
        ipv4_acl_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@134
        struct ipv4_acl_action action;// sugar@135
        action.action_id = action_nop;// sugar@136
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for ipv4_acl with action nop\n");// sugar@141
        ipv4_acl_setdefault(action);// sugar@142
    } else// sugar@143
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@144
}// sugar@145
void// sugar@130
tcp_acl_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@131
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@132
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@134
        struct tcp_acl_action action;// sugar@135
        action.action_id = action_acl_permit;// sugar@136
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for tcp_acl with action acl_permit\n");// sugar@141
        tcp_acl_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@134
        struct tcp_acl_action action;// sugar@135
        action.action_id = action_acl_alert;// sugar@136
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for tcp_acl with action acl_alert\n");// sugar@141
        tcp_acl_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@134
        struct tcp_acl_action action;// sugar@135
        action.action_id = action_acl_drop;// sugar@136
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for tcp_acl with action acl_drop\n");// sugar@141
        tcp_acl_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@134
        struct tcp_acl_action action;// sugar@135
        action.action_id = action_nop;// sugar@136
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for tcp_acl with action nop\n");// sugar@141
        tcp_acl_setdefault(action);// sugar@142
    } else// sugar@143
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@144
}// sugar@145
void// sugar@130
udp_acl_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@131
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@132
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@134
        struct udp_acl_action action;// sugar@135
        action.action_id = action_acl_permit;// sugar@136
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for udp_acl with action acl_permit\n");// sugar@141
        udp_acl_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@134
        struct udp_acl_action action;// sugar@135
        action.action_id = action_acl_alert;// sugar@136
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for udp_acl with action acl_alert\n");// sugar@141
        udp_acl_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@134
        struct udp_acl_action action;// sugar@135
        action.action_id = action_acl_drop;// sugar@136
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for udp_acl with action acl_drop\n");// sugar@141
        udp_acl_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@134
        struct udp_acl_action action;// sugar@135
        action.action_id = action_nop;// sugar@136
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for udp_acl with action nop\n");// sugar@141
        udp_acl_setdefault(action);// sugar@142
    } else// sugar@143
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@144
}// sugar@145
void// sugar@130
get_acl_features_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@131
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@132
    if (strcmp("acl_feature", ctrl_m->action_name) == 0) {// sugar@134
        struct get_acl_features_action action;// sugar@135
        action.action_id = action_acl_feature;// sugar@136
        uint8_t *enable_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.acl_feature_params.enable_mac, enable_mac, 1);// sugar@139
        uint8_t *enable_vlan = (uint8_t * )(
                (struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@138
        memcpy(action.acl_feature_params.enable_vlan, enable_vlan, 1);// sugar@139
        uint8_t *enable_ipv4 = (uint8_t * )(
                (struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@138
        memcpy(action.acl_feature_params.enable_ipv4, enable_ipv4, 1);// sugar@139
        uint8_t *enable_icmp = (uint8_t * )(
                (struct p4_action_parameter *) ctrl_m->action_params[3])->bitmap;// sugar@138
        memcpy(action.acl_feature_params.enable_icmp, enable_icmp, 1);// sugar@139
        uint8_t *enable_tcp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[4])->bitmap;// sugar@138
        memcpy(action.acl_feature_params.enable_tcp, enable_tcp, 1);// sugar@139
        uint8_t *enable_udp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[5])->bitmap;// sugar@138
        memcpy(action.acl_feature_params.enable_udp, enable_udp, 1);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for get_acl_features with action acl_feature\n");// sugar@141
        get_acl_features_setdefault(action);// sugar@142
    } else// sugar@143
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@144
}// sugar@145
void// sugar@130
cache_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@131
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@132
    if (strcmp("cache_block", ctrl_m->action_name) == 0) {// sugar@134
        struct cache_action action;// sugar@135
        action.action_id = action_cache_block;// sugar@136
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for cache with action cache_block\n");// sugar@141
        cache_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("cache_action", ctrl_m->action_name) == 0) {// sugar@134
        struct cache_action action;// sugar@135
        action.action_id = action_cache_action;// sugar@136
        uint8_t *port = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.cache_action_params.port, port, 2);// sugar@139
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@138
        memcpy(action.cache_action_params.src_mac, src_mac, 6);// sugar@139
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@138
        memcpy(action.cache_action_params.dst_mac, dst_mac, 6);// sugar@139
        uint8_t *vid = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[3])->bitmap;// sugar@138
        memcpy(action.cache_action_params.vid, vid, 2);// sugar@139
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[4])->bitmap;// sugar@138
        memcpy(action.cache_action_params.grp, grp, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for cache with action cache_action\n");// sugar@141
        cache_setdefault(action);// sugar@142
    } else// sugar@143
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@144
}// sugar@145
void// sugar@130
mac_learning_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@131
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@132
    if (strcmp("learning", ctrl_m->action_name) == 0) {// sugar@134
        struct mac_learning_action action;// sugar@135
        action.action_id = action_learning;// sugar@136
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for mac_learning with action learning\n");// sugar@141
        mac_learning_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@134
        struct mac_learning_action action;// sugar@135
        action.action_id = action_nop;// sugar@136
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for mac_learning with action nop\n");// sugar@141
        mac_learning_setdefault(action);// sugar@142
    } else// sugar@143
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@144
}// sugar@145
void// sugar@130
routable_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@131
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@132
    if (strcmp("ucast", ctrl_m->action_name) == 0) {// sugar@134
        struct routable_action action;// sugar@135
        action.action_id = action_ucast;// sugar@136
        uint8_t *lan = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.ucast_params.lan, lan, 1);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for routable with action ucast\n");// sugar@141
        routable_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("mcast", ctrl_m->action_name) == 0) {// sugar@134
        struct routable_action action;// sugar@135
        action.action_id = action_mcast;// sugar@136
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for routable with action mcast\n");// sugar@141
        routable_setdefault(action);// sugar@142
    } else// sugar@143
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@144
}// sugar@145
void// sugar@130
unicast_routing_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@131
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@132
    if (strcmp("set_nhop", ctrl_m->action_name) == 0) {// sugar@134
        struct unicast_routing_action action;// sugar@135
        action.action_id = action_set_nhop;// sugar@136
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.set_nhop_params.src_mac, src_mac, 6);// sugar@139
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@138
        memcpy(action.set_nhop_params.dst_mac, dst_mac, 6);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for unicast_routing with action set_nhop\n");// sugar@141
        unicast_routing_setdefault(action);// sugar@142
    } else// sugar@143
    if (strcmp("set_nhop_with_vlan", ctrl_m->action_name) == 0) {// sugar@134
        struct unicast_routing_action action;// sugar@135
        action.action_id = action_set_nhop_with_vlan;// sugar@136
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.set_nhop_with_vlan_params.src_mac, src_mac, 6);// sugar@139
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@138
        memcpy(action.set_nhop_with_vlan_params.dst_mac, dst_mac, 6);// sugar@139
        uint8_t *vid = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@138
        memcpy(action.set_nhop_with_vlan_params.vid, vid, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for unicast_routing with action set_nhop_with_vlan\n");// sugar@141
        unicast_routing_setdefault(action);// sugar@142
    } else// sugar@143
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@144
}// sugar@145
void// sugar@130
switching_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@131
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@132
    if (strcmp("forwarding", ctrl_m->action_name) == 0) {// sugar@134
        struct switching_action action;// sugar@135
        action.action_id = action_forwarding;// sugar@136
        uint8_t *port = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.forwarding_params.port, port, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for switching with action forwarding\n");// sugar@141
        switching_setdefault(action);// sugar@142
    } else// sugar@143
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@144
}// sugar@145
void// sugar@130
multicast_routing_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@131
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@132
    if (strcmp("set_multicast", ctrl_m->action_name) == 0) {// sugar@134
        struct multicast_routing_action action;// sugar@135
        action.action_id = action_set_multicast;// sugar@136
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.set_multicast_params.grp, grp, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for multicast_routing with action set_multicast\n");// sugar@141
        multicast_routing_setdefault(action);// sugar@142
    } else// sugar@143
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@144
}// sugar@145
void// sugar@130
igmp_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@131
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@132
    if (strcmp("set_multicast", ctrl_m->action_name) == 0) {// sugar@134
        struct igmp_action action;// sugar@135
        action.action_id = action_set_multicast;// sugar@136
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@138
        memcpy(action.set_multicast_params.grp, grp, 2);// sugar@139
        debug("Message from the control plane arrived.\n");// sugar@140
        debug("Set default action for igmp with action set_multicast\n");// sugar@141
        igmp_setdefault(action);// sugar@142
    } else// sugar@143
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@144
}// sugar@145
void recv_from_controller(struct p4_ctrl_msg *ctrl_m) {// sugar@148
    debug("MSG from controller %d %s\n", ctrl_m->type, ctrl_m->table_name);// sugar@149
    if (ctrl_m->type == P4T_ADD_TABLE_ENTRY) {// sugar@150
        if (strcmp("mac_acl", ctrl_m->table_name) == 0)// sugar@152
            mac_acl_add_table_entry(ctrl_m);// sugar@153
        else// sugar@154
        if (strcmp("ipv4_acl", ctrl_m->table_name) == 0)// sugar@152
            ipv4_acl_add_table_entry(ctrl_m);// sugar@153
        else// sugar@154
        if (strcmp("tcp_acl", ctrl_m->table_name) == 0)// sugar@152
            tcp_acl_add_table_entry(ctrl_m);// sugar@153
        else// sugar@154
        if (strcmp("udp_acl", ctrl_m->table_name) == 0)// sugar@152
            udp_acl_add_table_entry(ctrl_m);// sugar@153
        else// sugar@154
        if (strcmp("get_acl_features", ctrl_m->table_name) == 0)// sugar@152
            get_acl_features_add_table_entry(ctrl_m);// sugar@153
        else// sugar@154
        if (strcmp("cache", ctrl_m->table_name) == 0)// sugar@152
            cache_add_table_entry(ctrl_m);// sugar@153
        else// sugar@154
        if (strcmp("mac_learning", ctrl_m->table_name) == 0)// sugar@152
            mac_learning_add_table_entry(ctrl_m);// sugar@153
        else// sugar@154
        if (strcmp("routable", ctrl_m->table_name) == 0)// sugar@152
            routable_add_table_entry(ctrl_m);// sugar@153
        else// sugar@154
        if (strcmp("unicast_routing", ctrl_m->table_name) == 0)// sugar@152
            unicast_routing_add_table_entry(ctrl_m);// sugar@153
        else// sugar@154
        if (strcmp("switching", ctrl_m->table_name) == 0)// sugar@152
            switching_add_table_entry(ctrl_m);// sugar@153
        else// sugar@154
        if (strcmp("multicast_routing", ctrl_m->table_name) == 0)// sugar@152
            multicast_routing_add_table_entry(ctrl_m);// sugar@153
        else// sugar@154
        if (strcmp("igmp", ctrl_m->table_name) == 0)// sugar@152
            igmp_add_table_entry(ctrl_m);// sugar@153
        else// sugar@154
            debug("Table add entry: table name mismatch (%s).\n", ctrl_m->table_name);// sugar@155
    }// sugar@156
    else if (ctrl_m->type == P4T_SET_DEFAULT_ACTION) {// sugar@157
        if (strcmp("mac_acl", ctrl_m->table_name) == 0)// sugar@159
            mac_acl_set_default_table_action(ctrl_m);// sugar@160
        else// sugar@161
        if (strcmp("ipv4_acl", ctrl_m->table_name) == 0)// sugar@159
            ipv4_acl_set_default_table_action(ctrl_m);// sugar@160
        else// sugar@161
        if (strcmp("tcp_acl", ctrl_m->table_name) == 0)// sugar@159
            tcp_acl_set_default_table_action(ctrl_m);// sugar@160
        else// sugar@161
        if (strcmp("udp_acl", ctrl_m->table_name) == 0)// sugar@159
            udp_acl_set_default_table_action(ctrl_m);// sugar@160
        else// sugar@161
        if (strcmp("get_acl_features", ctrl_m->table_name) == 0)// sugar@159
            get_acl_features_set_default_table_action(ctrl_m);// sugar@160
        else// sugar@161
        if (strcmp("cache", ctrl_m->table_name) == 0)// sugar@159
            cache_set_default_table_action(ctrl_m);// sugar@160
        else// sugar@161
        if (strcmp("mac_learning", ctrl_m->table_name) == 0)// sugar@159
            mac_learning_set_default_table_action(ctrl_m);// sugar@160
        else// sugar@161
        if (strcmp("routable", ctrl_m->table_name) == 0)// sugar@159
            routable_set_default_table_action(ctrl_m);// sugar@160
        else// sugar@161
        if (strcmp("unicast_routing", ctrl_m->table_name) == 0)// sugar@159
            unicast_routing_set_default_table_action(ctrl_m);// sugar@160
        else// sugar@161
        if (strcmp("switching", ctrl_m->table_name) == 0)// sugar@159
            switching_set_default_table_action(ctrl_m);// sugar@160
        else// sugar@161
        if (strcmp("multicast_routing", ctrl_m->table_name) == 0)// sugar@159
            multicast_routing_set_default_table_action(ctrl_m);// sugar@160
        else// sugar@161
        if (strcmp("igmp", ctrl_m->table_name) == 0)// sugar@159
            igmp_set_default_table_action(ctrl_m);// sugar@160
        else// sugar@161
            debug("Table setdefault: table name mismatch (%s).\n", ctrl_m->table_name);// sugar@162
    }// sugar@163
}// sugar@164
backend bg;// sugar@168
void init_control_plane()// sugar@169
{// sugar@170
    debug("Creating control plane connection...\n");// sugar@171
    bg = create_backend(3, 1000, "localhost", 11111, recv_from_controller);// sugar@172
    launch_backend(bg);// sugar@173
    /*// sugar@174
    */// sugar@185
}// sugar@186
