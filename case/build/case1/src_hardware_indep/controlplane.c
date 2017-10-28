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
extern void table_mac_learning_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_routable_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_unicast_routing_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_switching_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_multicast_routing_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_igmp_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31

uint8_t reverse_buffer[14];// sugar@35
void// sugar@39
mac_acl_add(// sugar@40
        uint8_t field_instance_ethernet_src_mac[6],// sugar@43
        uint8_t field_instance_ethernet_src_mac_mask[6],// sugar@46
        uint8_t field_instance_ethernet_dst_mac[6],// sugar@43
        uint8_t field_instance_ethernet_dst_mac_mask[6],// sugar@46
        uint8_t field_instance_ethernet_eth_type[2],// sugar@43
        uint8_t field_instance_ethernet_eth_type_mask[2],// sugar@46
        struct mac_acl_action action)// sugar@49
{// sugar@50
    uint8_t key[14];// sugar@51
    uint8_t mask[14];// sugar@53
    memcpy(key + 0, field_instance_ethernet_src_mac, 6);// sugar@58
    memcpy(mask + 0, field_instance_ethernet_src_mac_mask, 6);// sugar@60
    memcpy(key + 6, field_instance_ethernet_dst_mac, 6);// sugar@58
    memcpy(mask + 6, field_instance_ethernet_dst_mac_mask, 6);// sugar@60
    memcpy(key + 12, field_instance_ethernet_eth_type, 2);// sugar@58
    memcpy(mask + 12, field_instance_ethernet_eth_type_mask, 2);// sugar@60
    ternary_add_promote(TABLE_mac_acl, (uint8_t *) key, (uint8_t *) mask, (uint8_t * ) & action);// sugar@80
}// sugar@81

void// sugar@83
mac_acl_setdefault(struct mac_acl_action action)// sugar@84
{// sugar@85
    table_setdefault_promote(TABLE_mac_acl, (uint8_t * ) & action);// sugar@86
}// sugar@87
void// sugar@39
ipv4_acl_add(// sugar@40
        uint8_t field_instance_ip_src_addr[4],// sugar@43
        uint8_t field_instance_ip_src_addr_mask[4],// sugar@46
        uint8_t field_instance_ip_dst_addr[4],// sugar@43
        uint8_t field_instance_ip_dst_addr_mask[4],// sugar@46
        uint8_t field_instance_ip_proto[1],// sugar@43
        uint8_t field_instance_ip_proto_mask[1],// sugar@46
        struct ipv4_acl_action action)// sugar@49
{// sugar@50
    uint8_t key[9];// sugar@51
    uint8_t mask[9];// sugar@53
    memcpy(key + 0, field_instance_ip_src_addr, 4);// sugar@58
    memcpy(mask + 0, field_instance_ip_src_addr_mask, 4);// sugar@60
    memcpy(key + 4, field_instance_ip_dst_addr, 4);// sugar@58
    memcpy(mask + 4, field_instance_ip_dst_addr_mask, 4);// sugar@60
    memcpy(key + 8, field_instance_ip_proto, 1);// sugar@58
    memcpy(mask + 8, field_instance_ip_proto_mask, 1);// sugar@60
    ternary_add_promote(TABLE_ipv4_acl, (uint8_t *) key, (uint8_t *) mask, (uint8_t * ) & action);// sugar@80
}// sugar@81

void// sugar@83
ipv4_acl_setdefault(struct ipv4_acl_action action)// sugar@84
{// sugar@85
    table_setdefault_promote(TABLE_ipv4_acl, (uint8_t * ) & action);// sugar@86
}// sugar@87
void// sugar@39
tcp_acl_add(// sugar@40
        uint8_t field_instance_tcp_src_port[2],// sugar@43
        uint8_t field_instance_tcp_src_port_mask[2],// sugar@46
        uint8_t field_instance_tcp_dst_port[2],// sugar@43
        uint8_t field_instance_tcp_dst_port_mask[2],// sugar@46
        uint8_t field_instance_tcp_flags[1],// sugar@43
        uint8_t field_instance_tcp_flags_mask[1],// sugar@46
        struct tcp_acl_action action)// sugar@49
{// sugar@50
    uint8_t key[5];// sugar@51
    uint8_t mask[5];// sugar@53
    memcpy(key + 0, field_instance_tcp_src_port, 2);// sugar@58
    memcpy(mask + 0, field_instance_tcp_src_port_mask, 2);// sugar@60
    memcpy(key + 2, field_instance_tcp_dst_port, 2);// sugar@58
    memcpy(mask + 2, field_instance_tcp_dst_port_mask, 2);// sugar@60
    memcpy(key + 4, field_instance_tcp_flags, 1);// sugar@58
    memcpy(mask + 4, field_instance_tcp_flags_mask, 1);// sugar@60
    ternary_add_promote(TABLE_tcp_acl, (uint8_t *) key, (uint8_t *) mask, (uint8_t * ) & action);// sugar@80
}// sugar@81

void// sugar@83
tcp_acl_setdefault(struct tcp_acl_action action)// sugar@84
{// sugar@85
    table_setdefault_promote(TABLE_tcp_acl, (uint8_t * ) & action);// sugar@86
}// sugar@87
void// sugar@39
udp_acl_add(// sugar@40
        uint8_t field_instance_udp_src_port[2],// sugar@43
        uint8_t field_instance_udp_src_port_mask[2],// sugar@46
        uint8_t field_instance_udp_dst_port[2],// sugar@43
        uint8_t field_instance_udp_dst_port_mask[2],// sugar@46
        struct udp_acl_action action)// sugar@49
{// sugar@50
    uint8_t key[4];// sugar@51
    uint8_t mask[4];// sugar@53
    memcpy(key + 0, field_instance_udp_src_port, 2);// sugar@58
    memcpy(mask + 0, field_instance_udp_src_port_mask, 2);// sugar@60
    memcpy(key + 2, field_instance_udp_dst_port, 2);// sugar@58
    memcpy(mask + 2, field_instance_udp_dst_port_mask, 2);// sugar@60
    ternary_add_promote(TABLE_udp_acl, (uint8_t *) key, (uint8_t *) mask, (uint8_t * ) & action);// sugar@80
}// sugar@81

void// sugar@83
udp_acl_setdefault(struct udp_acl_action action)// sugar@84
{// sugar@85
    table_setdefault_promote(TABLE_udp_acl, (uint8_t * ) & action);// sugar@86
}// sugar@87
void// sugar@39
get_acl_features_add(// sugar@40
        uint8_t field_instance_ip_src_addr[4],// sugar@43
        uint8_t field_instance_ip_src_addr_mask[4],// sugar@46
        uint8_t field_instance_ip_dst_addr[4],// sugar@43
        uint8_t field_instance_ip_dst_addr_mask[4],// sugar@46
        struct get_acl_features_action action)// sugar@49
{// sugar@50
    uint8_t key[8];// sugar@51
    uint8_t mask[8];// sugar@53
    memcpy(key + 0, field_instance_ip_src_addr, 4);// sugar@58
    memcpy(mask + 0, field_instance_ip_src_addr_mask, 4);// sugar@60
    memcpy(key + 4, field_instance_ip_dst_addr, 4);// sugar@58
    memcpy(mask + 4, field_instance_ip_dst_addr_mask, 4);// sugar@60
    ternary_add_promote(TABLE_get_acl_features, (uint8_t *) key, (uint8_t *) mask, (uint8_t * ) & action);// sugar@80
}// sugar@81

void// sugar@83
get_acl_features_setdefault(struct get_acl_features_action action)// sugar@84
{// sugar@85
    table_setdefault_promote(TABLE_get_acl_features, (uint8_t * ) & action);// sugar@86
}// sugar@87
void// sugar@39
mac_learning_add(// sugar@40
        uint8_t field_instance_ethernet_src_mac[6],// sugar@43
        uint8_t field_instance_vlan_vid[2],// sugar@43
        struct mac_learning_action action)// sugar@49
{// sugar@50
    uint8_t key[8];// sugar@51
    memcpy(key + 0, field_instance_ethernet_src_mac, 6);// sugar@58
    memcpy(key + 6, field_instance_vlan_vid, 2);// sugar@58
    exact_add_promote(TABLE_mac_learning, (uint8_t *) key, (uint8_t * ) & action);// sugar@78
}// sugar@81

void// sugar@83
mac_learning_setdefault(struct mac_learning_action action)// sugar@84
{// sugar@85
    table_setdefault_promote(TABLE_mac_learning, (uint8_t * ) & action);// sugar@86
}// sugar@87
void// sugar@39
routable_add(// sugar@40
        uint8_t field_instance_ethernet_src_mac[6],// sugar@43
        uint8_t field_instance_ethernet_dst_mac[6],// sugar@43
        uint8_t field_instance_vlan_vid[2],// sugar@43
        struct routable_action action)// sugar@49
{// sugar@50
    uint8_t key[14];// sugar@51
    memcpy(key + 0, field_instance_ethernet_src_mac, 6);// sugar@58
    memcpy(key + 6, field_instance_ethernet_dst_mac, 6);// sugar@58
    memcpy(key + 12, field_instance_vlan_vid, 2);// sugar@58
    exact_add_promote(TABLE_routable, (uint8_t *) key, (uint8_t * ) & action);// sugar@78
}// sugar@81

void// sugar@83
routable_setdefault(struct routable_action action)// sugar@84
{// sugar@85
    table_setdefault_promote(TABLE_routable, (uint8_t * ) & action);// sugar@86
}// sugar@87
void// sugar@39
unicast_routing_add(// sugar@40
        uint8_t field_instance_ip_dst_addr[4],// sugar@43
        struct unicast_routing_action action)// sugar@49
{// sugar@50
    uint8_t key[4];// sugar@51
    memcpy(key + 0, field_instance_ip_dst_addr, 4);// sugar@58
    exact_add_promote(TABLE_unicast_routing, (uint8_t *) key, (uint8_t * ) & action);// sugar@78
}// sugar@81

void// sugar@83
unicast_routing_setdefault(struct unicast_routing_action action)// sugar@84
{// sugar@85
    table_setdefault_promote(TABLE_unicast_routing, (uint8_t * ) & action);// sugar@86
}// sugar@87
void// sugar@39
switching_add(// sugar@40
        uint8_t field_instance_ethernet_dst_mac[6],// sugar@43
        uint8_t field_instance_vlan_vid[2],// sugar@43
        struct switching_action action)// sugar@49
{// sugar@50
    uint8_t key[8];// sugar@51
    memcpy(key + 0, field_instance_ethernet_dst_mac, 6);// sugar@58
    memcpy(key + 6, field_instance_vlan_vid, 2);// sugar@58
    exact_add_promote(TABLE_switching, (uint8_t *) key, (uint8_t * ) & action);// sugar@78
}// sugar@81

void// sugar@83
switching_setdefault(struct switching_action action)// sugar@84
{// sugar@85
    table_setdefault_promote(TABLE_switching, (uint8_t * ) & action);// sugar@86
}// sugar@87
void// sugar@39
multicast_routing_add(// sugar@40
        uint8_t field_instance_ip_dst_addr[4],// sugar@43
        uint8_t field_instance_ip_dst_addr_prefix_length,// sugar@48
        struct multicast_routing_action action)// sugar@49
{// sugar@50
    uint8_t key[4];// sugar@51
    memcpy(key + 0, field_instance_ip_dst_addr, 4);// sugar@58
    uint8_t prefix_length = 0;// sugar@63
    prefix_length += field_instance_ip_dst_addr_prefix_length;// sugar@70
    int c, d;// sugar@71
    for (c = 3, d = 0; c >= 0; c--, d++) *(reverse_buffer + d) = *(key + c);// sugar@72
    for (c = 0; c < 4; c++) *(key + c) = *(reverse_buffer + c);// sugar@73
    lpm_add_promote(TABLE_multicast_routing, (uint8_t *) key, prefix_length, (uint8_t * ) & action);// sugar@74
}// sugar@81

void// sugar@83
multicast_routing_setdefault(struct multicast_routing_action action)// sugar@84
{// sugar@85
    table_setdefault_promote(TABLE_multicast_routing, (uint8_t * ) & action);// sugar@86
}// sugar@87
void// sugar@39
igmp_add(// sugar@40
        uint8_t field_instance_ip_dst_addr[4],// sugar@43
        uint8_t field_instance_ip_dst_addr_prefix_length,// sugar@48
        uint8_t field_instance_vlan_vid[2],// sugar@43
        uint8_t field_instance_standard_metadata_ingress_port[2],// sugar@43
        struct igmp_action action)// sugar@49
{// sugar@50
    uint8_t key[8];// sugar@51
    memcpy(key + 0, field_instance_vlan_vid, 2);// sugar@58
    memcpy(key + 2, field_instance_standard_metadata_ingress_port, 2);// sugar@58
    memcpy(key + 4, field_instance_ip_dst_addr, 4);// sugar@58
    uint8_t prefix_length = 0;// sugar@63
    prefix_length += field_instance_ip_dst_addr_prefix_length;// sugar@70
    prefix_length += 12;// sugar@68
    prefix_length += 9;// sugar@68
    int c, d;// sugar@71
    for (c = 7, d = 0; c >= 0; c--, d++) *(reverse_buffer + d) = *(key + c);// sugar@72
    for (c = 0; c < 8; c++) *(key + c) = *(reverse_buffer + c);// sugar@73
    lpm_add_promote(TABLE_igmp, (uint8_t *) key, prefix_length, (uint8_t * ) & action);// sugar@74
}// sugar@81

void// sugar@83
igmp_setdefault(struct igmp_action action)// sugar@84
{// sugar@85
    table_setdefault_promote(TABLE_igmp, (uint8_t * ) & action);// sugar@86
}// sugar@87
void// sugar@91
mac_acl_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@92
    uint8_t *field_instance_ethernet_src_mac = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->bitmap);// sugar@101
    uint8_t *field_instance_ethernet_src_mac_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->mask);// sugar@102
    uint8_t *field_instance_ethernet_dst_mac = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->bitmap);// sugar@101
    uint8_t *field_instance_ethernet_dst_mac_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->mask);// sugar@102
    uint8_t *field_instance_ethernet_eth_type = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->bitmap);// sugar@101
    uint8_t *field_instance_ethernet_eth_type_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->mask);// sugar@102
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@104
        struct mac_acl_action action;// sugar@105
        action.action_id = action_acl_alert;// sugar@106
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to mac_acl with action acl_alert\n");// sugar@111
        mac_acl_add(// sugar@112
                field_instance_ethernet_src_mac,// sugar@115
                field_instance_ethernet_src_mac_mask,// sugar@119
                field_instance_ethernet_dst_mac,// sugar@115
                field_instance_ethernet_dst_mac_mask,// sugar@119
                field_instance_ethernet_eth_type,// sugar@115
                field_instance_ethernet_eth_type_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@104
        struct mac_acl_action action;// sugar@105
        action.action_id = action_acl_permit;// sugar@106
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to mac_acl with action acl_permit\n");// sugar@111
        mac_acl_add(// sugar@112
                field_instance_ethernet_src_mac,// sugar@115
                field_instance_ethernet_src_mac_mask,// sugar@119
                field_instance_ethernet_dst_mac,// sugar@115
                field_instance_ethernet_dst_mac_mask,// sugar@119
                field_instance_ethernet_eth_type,// sugar@115
                field_instance_ethernet_eth_type_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@104
        struct mac_acl_action action;// sugar@105
        action.action_id = action_acl_drop;// sugar@106
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to mac_acl with action acl_drop\n");// sugar@111
        mac_acl_add(// sugar@112
                field_instance_ethernet_src_mac,// sugar@115
                field_instance_ethernet_src_mac_mask,// sugar@119
                field_instance_ethernet_dst_mac,// sugar@115
                field_instance_ethernet_dst_mac_mask,// sugar@119
                field_instance_ethernet_eth_type,// sugar@115
                field_instance_ethernet_eth_type_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@104
        struct mac_acl_action action;// sugar@105
        action.action_id = action_nop;// sugar@106
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to mac_acl with action nop\n");// sugar@111
        mac_acl_add(// sugar@112
                field_instance_ethernet_src_mac,// sugar@115
                field_instance_ethernet_src_mac_mask,// sugar@119
                field_instance_ethernet_dst_mac,// sugar@115
                field_instance_ethernet_dst_mac_mask,// sugar@119
                field_instance_ethernet_eth_type,// sugar@115
                field_instance_ethernet_eth_type_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@122
}// sugar@123
void// sugar@91
ipv4_acl_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@92
    uint8_t *field_instance_ip_src_addr = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->bitmap);// sugar@101
    uint8_t *field_instance_ip_src_addr_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->mask);// sugar@102
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->bitmap);// sugar@101
    uint8_t *field_instance_ip_dst_addr_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->mask);// sugar@102
    uint8_t *field_instance_ip_proto = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->bitmap);// sugar@101
    uint8_t *field_instance_ip_proto_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->mask);// sugar@102
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@104
        struct ipv4_acl_action action;// sugar@105
        action.action_id = action_acl_permit;// sugar@106
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to ipv4_acl with action acl_permit\n");// sugar@111
        ipv4_acl_add(// sugar@112
                field_instance_ip_src_addr,// sugar@115
                field_instance_ip_src_addr_mask,// sugar@119
                field_instance_ip_dst_addr,// sugar@115
                field_instance_ip_dst_addr_mask,// sugar@119
                field_instance_ip_proto,// sugar@115
                field_instance_ip_proto_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@104
        struct ipv4_acl_action action;// sugar@105
        action.action_id = action_acl_alert;// sugar@106
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to ipv4_acl with action acl_alert\n");// sugar@111
        ipv4_acl_add(// sugar@112
                field_instance_ip_src_addr,// sugar@115
                field_instance_ip_src_addr_mask,// sugar@119
                field_instance_ip_dst_addr,// sugar@115
                field_instance_ip_dst_addr_mask,// sugar@119
                field_instance_ip_proto,// sugar@115
                field_instance_ip_proto_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@104
        struct ipv4_acl_action action;// sugar@105
        action.action_id = action_acl_drop;// sugar@106
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to ipv4_acl with action acl_drop\n");// sugar@111
        ipv4_acl_add(// sugar@112
                field_instance_ip_src_addr,// sugar@115
                field_instance_ip_src_addr_mask,// sugar@119
                field_instance_ip_dst_addr,// sugar@115
                field_instance_ip_dst_addr_mask,// sugar@119
                field_instance_ip_proto,// sugar@115
                field_instance_ip_proto_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@104
        struct ipv4_acl_action action;// sugar@105
        action.action_id = action_nop;// sugar@106
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to ipv4_acl with action nop\n");// sugar@111
        ipv4_acl_add(// sugar@112
                field_instance_ip_src_addr,// sugar@115
                field_instance_ip_src_addr_mask,// sugar@119
                field_instance_ip_dst_addr,// sugar@115
                field_instance_ip_dst_addr_mask,// sugar@119
                field_instance_ip_proto,// sugar@115
                field_instance_ip_proto_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@122
}// sugar@123
void// sugar@91
tcp_acl_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@92
    uint8_t *field_instance_tcp_src_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->bitmap);// sugar@101
    uint8_t *field_instance_tcp_src_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->mask);// sugar@102
    uint8_t *field_instance_tcp_dst_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->bitmap);// sugar@101
    uint8_t *field_instance_tcp_dst_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->mask);// sugar@102
    uint8_t *field_instance_tcp_flags = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->bitmap);// sugar@101
    uint8_t *field_instance_tcp_flags_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[2])->mask);// sugar@102
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@104
        struct tcp_acl_action action;// sugar@105
        action.action_id = action_acl_permit;// sugar@106
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to tcp_acl with action acl_permit\n");// sugar@111
        tcp_acl_add(// sugar@112
                field_instance_tcp_src_port,// sugar@115
                field_instance_tcp_src_port_mask,// sugar@119
                field_instance_tcp_dst_port,// sugar@115
                field_instance_tcp_dst_port_mask,// sugar@119
                field_instance_tcp_flags,// sugar@115
                field_instance_tcp_flags_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@104
        struct tcp_acl_action action;// sugar@105
        action.action_id = action_acl_alert;// sugar@106
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to tcp_acl with action acl_alert\n");// sugar@111
        tcp_acl_add(// sugar@112
                field_instance_tcp_src_port,// sugar@115
                field_instance_tcp_src_port_mask,// sugar@119
                field_instance_tcp_dst_port,// sugar@115
                field_instance_tcp_dst_port_mask,// sugar@119
                field_instance_tcp_flags,// sugar@115
                field_instance_tcp_flags_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@104
        struct tcp_acl_action action;// sugar@105
        action.action_id = action_acl_drop;// sugar@106
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to tcp_acl with action acl_drop\n");// sugar@111
        tcp_acl_add(// sugar@112
                field_instance_tcp_src_port,// sugar@115
                field_instance_tcp_src_port_mask,// sugar@119
                field_instance_tcp_dst_port,// sugar@115
                field_instance_tcp_dst_port_mask,// sugar@119
                field_instance_tcp_flags,// sugar@115
                field_instance_tcp_flags_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@104
        struct tcp_acl_action action;// sugar@105
        action.action_id = action_nop;// sugar@106
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to tcp_acl with action nop\n");// sugar@111
        tcp_acl_add(// sugar@112
                field_instance_tcp_src_port,// sugar@115
                field_instance_tcp_src_port_mask,// sugar@119
                field_instance_tcp_dst_port,// sugar@115
                field_instance_tcp_dst_port_mask,// sugar@119
                field_instance_tcp_flags,// sugar@115
                field_instance_tcp_flags_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@122
}// sugar@123
void// sugar@91
udp_acl_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@92
    uint8_t *field_instance_udp_src_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->bitmap);// sugar@101
    uint8_t *field_instance_udp_src_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->mask);// sugar@102
    uint8_t *field_instance_udp_dst_port = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->bitmap);// sugar@101
    uint8_t *field_instance_udp_dst_port_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->mask);// sugar@102
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@104
        struct udp_acl_action action;// sugar@105
        action.action_id = action_acl_permit;// sugar@106
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to udp_acl with action acl_permit\n");// sugar@111
        udp_acl_add(// sugar@112
                field_instance_udp_src_port,// sugar@115
                field_instance_udp_src_port_mask,// sugar@119
                field_instance_udp_dst_port,// sugar@115
                field_instance_udp_dst_port_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@104
        struct udp_acl_action action;// sugar@105
        action.action_id = action_acl_alert;// sugar@106
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to udp_acl with action acl_alert\n");// sugar@111
        udp_acl_add(// sugar@112
                field_instance_udp_src_port,// sugar@115
                field_instance_udp_src_port_mask,// sugar@119
                field_instance_udp_dst_port,// sugar@115
                field_instance_udp_dst_port_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@104
        struct udp_acl_action action;// sugar@105
        action.action_id = action_acl_drop;// sugar@106
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to udp_acl with action acl_drop\n");// sugar@111
        udp_acl_add(// sugar@112
                field_instance_udp_src_port,// sugar@115
                field_instance_udp_src_port_mask,// sugar@119
                field_instance_udp_dst_port,// sugar@115
                field_instance_udp_dst_port_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@104
        struct udp_acl_action action;// sugar@105
        action.action_id = action_nop;// sugar@106
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to udp_acl with action nop\n");// sugar@111
        udp_acl_add(// sugar@112
                field_instance_udp_src_port,// sugar@115
                field_instance_udp_src_port_mask,// sugar@119
                field_instance_udp_dst_port,// sugar@115
                field_instance_udp_dst_port_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@122
}// sugar@123
void// sugar@91
get_acl_features_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@92
    uint8_t *field_instance_ip_src_addr = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->bitmap);// sugar@101
    uint8_t *field_instance_ip_src_addr_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[0])->mask);// sugar@102
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->bitmap);// sugar@101
    uint8_t *field_instance_ip_dst_addr_mask = (uint8_t * )(
            ((struct p4_field_match_ternary *) ctrl_m->field_matches[1])->mask);// sugar@102
    if (strcmp("acl_feature", ctrl_m->action_name) == 0) {// sugar@104
        struct get_acl_features_action action;// sugar@105
        action.action_id = action_acl_feature;// sugar@106
        uint8_t *enable_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.acl_feature_params.enable_mac, enable_mac, 1);// sugar@109
        uint8_t *enable_vlan = (uint8_t * )(
                (struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@108
        memcpy(action.acl_feature_params.enable_vlan, enable_vlan, 1);// sugar@109
        uint8_t *enable_ipv4 = (uint8_t * )(
                (struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@108
        memcpy(action.acl_feature_params.enable_ipv4, enable_ipv4, 1);// sugar@109
        uint8_t *enable_icmp = (uint8_t * )(
                (struct p4_action_parameter *) ctrl_m->action_params[3])->bitmap;// sugar@108
        memcpy(action.acl_feature_params.enable_icmp, enable_icmp, 1);// sugar@109
        uint8_t *enable_tcp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[4])->bitmap;// sugar@108
        memcpy(action.acl_feature_params.enable_tcp, enable_tcp, 1);// sugar@109
        uint8_t *enable_udp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[5])->bitmap;// sugar@108
        memcpy(action.acl_feature_params.enable_udp, enable_udp, 1);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to get_acl_features with action acl_feature\n");// sugar@111
        get_acl_features_add(// sugar@112
                field_instance_ip_src_addr,// sugar@115
                field_instance_ip_src_addr_mask,// sugar@119
                field_instance_ip_dst_addr,// sugar@115
                field_instance_ip_dst_addr_mask,// sugar@119
                action);// sugar@120
    } else// sugar@121
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@122
}// sugar@123
void// sugar@91
mac_learning_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@92
    uint8_t *field_instance_ethernet_src_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@96
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@96
    if (strcmp("learning", ctrl_m->action_name) == 0) {// sugar@104
        struct mac_learning_action action;// sugar@105
        action.action_id = action_learning;// sugar@106
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to mac_learning with action learning\n");// sugar@111
        mac_learning_add(// sugar@112
                field_instance_ethernet_src_mac,// sugar@115
                field_instance_vlan_vid,// sugar@115
                action);// sugar@120
    } else// sugar@121
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@104
        struct mac_learning_action action;// sugar@105
        action.action_id = action_nop;// sugar@106
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to mac_learning with action nop\n");// sugar@111
        mac_learning_add(// sugar@112
                field_instance_ethernet_src_mac,// sugar@115
                field_instance_vlan_vid,// sugar@115
                action);// sugar@120
    } else// sugar@121
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@122
}// sugar@123
void// sugar@91
routable_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@92
    uint8_t *field_instance_ethernet_src_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@96
    uint8_t *field_instance_ethernet_dst_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@96
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[2])->bitmap);// sugar@96
    if (strcmp("ucast", ctrl_m->action_name) == 0) {// sugar@104
        struct routable_action action;// sugar@105
        action.action_id = action_ucast;// sugar@106
        uint8_t *lan = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.ucast_params.lan, lan, 1);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to routable with action ucast\n");// sugar@111
        routable_add(// sugar@112
                field_instance_ethernet_src_mac,// sugar@115
                field_instance_ethernet_dst_mac,// sugar@115
                field_instance_vlan_vid,// sugar@115
                action);// sugar@120
    } else// sugar@121
    if (strcmp("mcast", ctrl_m->action_name) == 0) {// sugar@104
        struct routable_action action;// sugar@105
        action.action_id = action_mcast;// sugar@106
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to routable with action mcast\n");// sugar@111
        routable_add(// sugar@112
                field_instance_ethernet_src_mac,// sugar@115
                field_instance_ethernet_dst_mac,// sugar@115
                field_instance_vlan_vid,// sugar@115
                action);// sugar@120
    } else// sugar@121
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@122
}// sugar@123
void// sugar@91
unicast_routing_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@92
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@96
    if (strcmp("set_nhop", ctrl_m->action_name) == 0) {// sugar@104
        struct unicast_routing_action action;// sugar@105
        action.action_id = action_set_nhop;// sugar@106
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.set_nhop_params.src_mac, src_mac, 6);// sugar@109
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@108
        memcpy(action.set_nhop_params.dst_mac, dst_mac, 6);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to unicast_routing with action set_nhop\n");// sugar@111
        unicast_routing_add(// sugar@112
                field_instance_ip_dst_addr,// sugar@115
                action);// sugar@120
    } else// sugar@121
    if (strcmp("set_nhop_with_vlan", ctrl_m->action_name) == 0) {// sugar@104
        struct unicast_routing_action action;// sugar@105
        action.action_id = action_set_nhop_with_vlan;// sugar@106
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.set_nhop_with_vlan_params.src_mac, src_mac, 6);// sugar@109
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@108
        memcpy(action.set_nhop_with_vlan_params.dst_mac, dst_mac, 6);// sugar@109
        uint8_t *vid = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@108
        memcpy(action.set_nhop_with_vlan_params.vid, vid, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to unicast_routing with action set_nhop_with_vlan\n");// sugar@111
        unicast_routing_add(// sugar@112
                field_instance_ip_dst_addr,// sugar@115
                action);// sugar@120
    } else// sugar@121
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@122
}// sugar@123
void// sugar@91
switching_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@92
    uint8_t *field_instance_ethernet_dst_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@96
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@96
    if (strcmp("forwarding", ctrl_m->action_name) == 0) {// sugar@104
        struct switching_action action;// sugar@105
        action.action_id = action_forwarding;// sugar@106
        uint8_t *port = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.forwarding_params.port, port, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to switching with action forwarding\n");// sugar@111
        switching_add(// sugar@112
                field_instance_ethernet_dst_mac,// sugar@115
                field_instance_vlan_vid,// sugar@115
                action);// sugar@120
    } else// sugar@121
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@122
}// sugar@123
void// sugar@91
multicast_routing_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@92
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_lpm *) ctrl_m->field_matches[0])->bitmap);// sugar@98
    uint16_t field_instance_ip_dst_addr_prefix_length = ((struct p4_field_match_lpm *) ctrl_m->field_matches[0])->prefix_length;// sugar@99
    if (strcmp("set_multicast", ctrl_m->action_name) == 0) {// sugar@104
        struct multicast_routing_action action;// sugar@105
        action.action_id = action_set_multicast;// sugar@106
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.set_multicast_params.grp, grp, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to multicast_routing with action set_multicast\n");// sugar@111
        multicast_routing_add(// sugar@112
                field_instance_ip_dst_addr,// sugar@115
                field_instance_ip_dst_addr_prefix_length,// sugar@117
                action);// sugar@120
    } else// sugar@121
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@122
}// sugar@123
void// sugar@91
igmp_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@92
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_lpm *) ctrl_m->field_matches[0])->bitmap);// sugar@98
    uint16_t field_instance_ip_dst_addr_prefix_length = ((struct p4_field_match_lpm *) ctrl_m->field_matches[0])->prefix_length;// sugar@99
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@96
    uint8_t *field_instance_standard_metadata_ingress_port = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[2])->bitmap);// sugar@96
    if (strcmp("set_multicast", ctrl_m->action_name) == 0) {// sugar@104
        struct igmp_action action;// sugar@105
        action.action_id = action_set_multicast;// sugar@106
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@108
        memcpy(action.set_multicast_params.grp, grp, 2);// sugar@109
        debug("Reply from the control plane arrived.\n");// sugar@110
        debug("Adding new entry to igmp with action set_multicast\n");// sugar@111
        igmp_add(// sugar@112
                field_instance_ip_dst_addr,// sugar@115
                field_instance_ip_dst_addr_prefix_length,// sugar@117
                field_instance_vlan_vid,// sugar@115
                field_instance_standard_metadata_ingress_port,// sugar@115
                action);// sugar@120
    } else// sugar@121
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@122
}// sugar@123
void// sugar@126
mac_acl_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@127
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@128
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@130
        struct mac_acl_action action;// sugar@131
        action.action_id = action_acl_alert;// sugar@132
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for mac_acl with action acl_alert\n");// sugar@137
        mac_acl_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@130
        struct mac_acl_action action;// sugar@131
        action.action_id = action_acl_permit;// sugar@132
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for mac_acl with action acl_permit\n");// sugar@137
        mac_acl_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@130
        struct mac_acl_action action;// sugar@131
        action.action_id = action_acl_drop;// sugar@132
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for mac_acl with action acl_drop\n");// sugar@137
        mac_acl_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@130
        struct mac_acl_action action;// sugar@131
        action.action_id = action_nop;// sugar@132
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for mac_acl with action nop\n");// sugar@137
        mac_acl_setdefault(action);// sugar@138
    } else// sugar@139
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@140
}// sugar@141
void// sugar@126
ipv4_acl_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@127
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@128
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@130
        struct ipv4_acl_action action;// sugar@131
        action.action_id = action_acl_permit;// sugar@132
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for ipv4_acl with action acl_permit\n");// sugar@137
        ipv4_acl_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@130
        struct ipv4_acl_action action;// sugar@131
        action.action_id = action_acl_alert;// sugar@132
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for ipv4_acl with action acl_alert\n");// sugar@137
        ipv4_acl_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@130
        struct ipv4_acl_action action;// sugar@131
        action.action_id = action_acl_drop;// sugar@132
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for ipv4_acl with action acl_drop\n");// sugar@137
        ipv4_acl_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@130
        struct ipv4_acl_action action;// sugar@131
        action.action_id = action_nop;// sugar@132
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for ipv4_acl with action nop\n");// sugar@137
        ipv4_acl_setdefault(action);// sugar@138
    } else// sugar@139
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@140
}// sugar@141
void// sugar@126
tcp_acl_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@127
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@128
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@130
        struct tcp_acl_action action;// sugar@131
        action.action_id = action_acl_permit;// sugar@132
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for tcp_acl with action acl_permit\n");// sugar@137
        tcp_acl_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@130
        struct tcp_acl_action action;// sugar@131
        action.action_id = action_acl_alert;// sugar@132
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for tcp_acl with action acl_alert\n");// sugar@137
        tcp_acl_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@130
        struct tcp_acl_action action;// sugar@131
        action.action_id = action_acl_drop;// sugar@132
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for tcp_acl with action acl_drop\n");// sugar@137
        tcp_acl_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@130
        struct tcp_acl_action action;// sugar@131
        action.action_id = action_nop;// sugar@132
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for tcp_acl with action nop\n");// sugar@137
        tcp_acl_setdefault(action);// sugar@138
    } else// sugar@139
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@140
}// sugar@141
void// sugar@126
udp_acl_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@127
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@128
    if (strcmp("acl_permit", ctrl_m->action_name) == 0) {// sugar@130
        struct udp_acl_action action;// sugar@131
        action.action_id = action_acl_permit;// sugar@132
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_permit_params.reason, reason, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for udp_acl with action acl_permit\n");// sugar@137
        udp_acl_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("acl_alert", ctrl_m->action_name) == 0) {// sugar@130
        struct udp_acl_action action;// sugar@131
        action.action_id = action_acl_alert;// sugar@132
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_alert_params.reason, reason, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for udp_acl with action acl_alert\n");// sugar@137
        udp_acl_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("acl_drop", ctrl_m->action_name) == 0) {// sugar@130
        struct udp_acl_action action;// sugar@131
        action.action_id = action_acl_drop;// sugar@132
        uint8_t *reason = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_drop_params.reason, reason, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for udp_acl with action acl_drop\n");// sugar@137
        udp_acl_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@130
        struct udp_acl_action action;// sugar@131
        action.action_id = action_nop;// sugar@132
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for udp_acl with action nop\n");// sugar@137
        udp_acl_setdefault(action);// sugar@138
    } else// sugar@139
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@140
}// sugar@141
void// sugar@126
get_acl_features_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@127
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@128
    if (strcmp("acl_feature", ctrl_m->action_name) == 0) {// sugar@130
        struct get_acl_features_action action;// sugar@131
        action.action_id = action_acl_feature;// sugar@132
        uint8_t *enable_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.acl_feature_params.enable_mac, enable_mac, 1);// sugar@135
        uint8_t *enable_vlan = (uint8_t * )(
                (struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@134
        memcpy(action.acl_feature_params.enable_vlan, enable_vlan, 1);// sugar@135
        uint8_t *enable_ipv4 = (uint8_t * )(
                (struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@134
        memcpy(action.acl_feature_params.enable_ipv4, enable_ipv4, 1);// sugar@135
        uint8_t *enable_icmp = (uint8_t * )(
                (struct p4_action_parameter *) ctrl_m->action_params[3])->bitmap;// sugar@134
        memcpy(action.acl_feature_params.enable_icmp, enable_icmp, 1);// sugar@135
        uint8_t *enable_tcp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[4])->bitmap;// sugar@134
        memcpy(action.acl_feature_params.enable_tcp, enable_tcp, 1);// sugar@135
        uint8_t *enable_udp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[5])->bitmap;// sugar@134
        memcpy(action.acl_feature_params.enable_udp, enable_udp, 1);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for get_acl_features with action acl_feature\n");// sugar@137
        get_acl_features_setdefault(action);// sugar@138
    } else// sugar@139
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@140
}// sugar@141
void// sugar@126
mac_learning_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@127
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@128
    if (strcmp("learning", ctrl_m->action_name) == 0) {// sugar@130
        struct mac_learning_action action;// sugar@131
        action.action_id = action_learning;// sugar@132
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for mac_learning with action learning\n");// sugar@137
        mac_learning_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@130
        struct mac_learning_action action;// sugar@131
        action.action_id = action_nop;// sugar@132
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for mac_learning with action nop\n");// sugar@137
        mac_learning_setdefault(action);// sugar@138
    } else// sugar@139
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@140
}// sugar@141
void// sugar@126
routable_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@127
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@128
    if (strcmp("ucast", ctrl_m->action_name) == 0) {// sugar@130
        struct routable_action action;// sugar@131
        action.action_id = action_ucast;// sugar@132
        uint8_t *lan = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.ucast_params.lan, lan, 1);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for routable with action ucast\n");// sugar@137
        routable_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("mcast", ctrl_m->action_name) == 0) {// sugar@130
        struct routable_action action;// sugar@131
        action.action_id = action_mcast;// sugar@132
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for routable with action mcast\n");// sugar@137
        routable_setdefault(action);// sugar@138
    } else// sugar@139
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@140
}// sugar@141
void// sugar@126
unicast_routing_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@127
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@128
    if (strcmp("set_nhop", ctrl_m->action_name) == 0) {// sugar@130
        struct unicast_routing_action action;// sugar@131
        action.action_id = action_set_nhop;// sugar@132
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.set_nhop_params.src_mac, src_mac, 6);// sugar@135
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@134
        memcpy(action.set_nhop_params.dst_mac, dst_mac, 6);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for unicast_routing with action set_nhop\n");// sugar@137
        unicast_routing_setdefault(action);// sugar@138
    } else// sugar@139
    if (strcmp("set_nhop_with_vlan", ctrl_m->action_name) == 0) {// sugar@130
        struct unicast_routing_action action;// sugar@131
        action.action_id = action_set_nhop_with_vlan;// sugar@132
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.set_nhop_with_vlan_params.src_mac, src_mac, 6);// sugar@135
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@134
        memcpy(action.set_nhop_with_vlan_params.dst_mac, dst_mac, 6);// sugar@135
        uint8_t *vid = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@134
        memcpy(action.set_nhop_with_vlan_params.vid, vid, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for unicast_routing with action set_nhop_with_vlan\n");// sugar@137
        unicast_routing_setdefault(action);// sugar@138
    } else// sugar@139
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@140
}// sugar@141
void// sugar@126
switching_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@127
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@128
    if (strcmp("forwarding", ctrl_m->action_name) == 0) {// sugar@130
        struct switching_action action;// sugar@131
        action.action_id = action_forwarding;// sugar@132
        uint8_t *port = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.forwarding_params.port, port, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for switching with action forwarding\n");// sugar@137
        switching_setdefault(action);// sugar@138
    } else// sugar@139
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@140
}// sugar@141
void// sugar@126
multicast_routing_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@127
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@128
    if (strcmp("set_multicast", ctrl_m->action_name) == 0) {// sugar@130
        struct multicast_routing_action action;// sugar@131
        action.action_id = action_set_multicast;// sugar@132
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.set_multicast_params.grp, grp, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for multicast_routing with action set_multicast\n");// sugar@137
        multicast_routing_setdefault(action);// sugar@138
    } else// sugar@139
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@140
}// sugar@141
void// sugar@126
igmp_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@127
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@128
    if (strcmp("set_multicast", ctrl_m->action_name) == 0) {// sugar@130
        struct igmp_action action;// sugar@131
        action.action_id = action_set_multicast;// sugar@132
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@134
        memcpy(action.set_multicast_params.grp, grp, 2);// sugar@135
        debug("Message from the control plane arrived.\n");// sugar@136
        debug("Set default action for igmp with action set_multicast\n");// sugar@137
        igmp_setdefault(action);// sugar@138
    } else// sugar@139
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@140
}// sugar@141
void recv_from_controller(struct p4_ctrl_msg *ctrl_m) {// sugar@144
    debug("MSG from controller %d %s\n", ctrl_m->type, ctrl_m->table_name);// sugar@145
    if (ctrl_m->type == P4T_ADD_TABLE_ENTRY) {// sugar@146
        if (strcmp("mac_acl", ctrl_m->table_name) == 0)// sugar@148
            mac_acl_add_table_entry(ctrl_m);// sugar@149
        else// sugar@150
        if (strcmp("ipv4_acl", ctrl_m->table_name) == 0)// sugar@148
            ipv4_acl_add_table_entry(ctrl_m);// sugar@149
        else// sugar@150
        if (strcmp("tcp_acl", ctrl_m->table_name) == 0)// sugar@148
            tcp_acl_add_table_entry(ctrl_m);// sugar@149
        else// sugar@150
        if (strcmp("udp_acl", ctrl_m->table_name) == 0)// sugar@148
            udp_acl_add_table_entry(ctrl_m);// sugar@149
        else// sugar@150
        if (strcmp("get_acl_features", ctrl_m->table_name) == 0)// sugar@148
            get_acl_features_add_table_entry(ctrl_m);// sugar@149
        else// sugar@150
        if (strcmp("mac_learning", ctrl_m->table_name) == 0)// sugar@148
            mac_learning_add_table_entry(ctrl_m);// sugar@149
        else// sugar@150
        if (strcmp("routable", ctrl_m->table_name) == 0)// sugar@148
            routable_add_table_entry(ctrl_m);// sugar@149
        else// sugar@150
        if (strcmp("unicast_routing", ctrl_m->table_name) == 0)// sugar@148
            unicast_routing_add_table_entry(ctrl_m);// sugar@149
        else// sugar@150
        if (strcmp("switching", ctrl_m->table_name) == 0)// sugar@148
            switching_add_table_entry(ctrl_m);// sugar@149
        else// sugar@150
        if (strcmp("multicast_routing", ctrl_m->table_name) == 0)// sugar@148
            multicast_routing_add_table_entry(ctrl_m);// sugar@149
        else// sugar@150
        if (strcmp("igmp", ctrl_m->table_name) == 0)// sugar@148
            igmp_add_table_entry(ctrl_m);// sugar@149
        else// sugar@150
            debug("Table add entry: table name mismatch (%s).\n", ctrl_m->table_name);// sugar@151
    }// sugar@152
    else if (ctrl_m->type == P4T_SET_DEFAULT_ACTION) {// sugar@153
        if (strcmp("mac_acl", ctrl_m->table_name) == 0)// sugar@155
            mac_acl_set_default_table_action(ctrl_m);// sugar@156
        else// sugar@157
        if (strcmp("ipv4_acl", ctrl_m->table_name) == 0)// sugar@155
            ipv4_acl_set_default_table_action(ctrl_m);// sugar@156
        else// sugar@157
        if (strcmp("tcp_acl", ctrl_m->table_name) == 0)// sugar@155
            tcp_acl_set_default_table_action(ctrl_m);// sugar@156
        else// sugar@157
        if (strcmp("udp_acl", ctrl_m->table_name) == 0)// sugar@155
            udp_acl_set_default_table_action(ctrl_m);// sugar@156
        else// sugar@157
        if (strcmp("get_acl_features", ctrl_m->table_name) == 0)// sugar@155
            get_acl_features_set_default_table_action(ctrl_m);// sugar@156
        else// sugar@157
        if (strcmp("mac_learning", ctrl_m->table_name) == 0)// sugar@155
            mac_learning_set_default_table_action(ctrl_m);// sugar@156
        else// sugar@157
        if (strcmp("routable", ctrl_m->table_name) == 0)// sugar@155
            routable_set_default_table_action(ctrl_m);// sugar@156
        else// sugar@157
        if (strcmp("unicast_routing", ctrl_m->table_name) == 0)// sugar@155
            unicast_routing_set_default_table_action(ctrl_m);// sugar@156
        else// sugar@157
        if (strcmp("switching", ctrl_m->table_name) == 0)// sugar@155
            switching_set_default_table_action(ctrl_m);// sugar@156
        else// sugar@157
        if (strcmp("multicast_routing", ctrl_m->table_name) == 0)// sugar@155
            multicast_routing_set_default_table_action(ctrl_m);// sugar@156
        else// sugar@157
        if (strcmp("igmp", ctrl_m->table_name) == 0)// sugar@155
            igmp_set_default_table_action(ctrl_m);// sugar@156
        else// sugar@157
            debug("Table setdefault: table name mismatch (%s).\n", ctrl_m->table_name);// sugar@158
    }// sugar@159
}// sugar@160
backend bg;// sugar@164
void init_control_plane()// sugar@165
{// sugar@166
    debug("Creating control plane connection...\n");// sugar@167
    bg = create_backend(3, 1000, "localhost", 11111, recv_from_controller);// sugar@168
    launch_backend(bg);// sugar@169
    /*// sugar@170
    */// sugar@181
}// sugar@182
