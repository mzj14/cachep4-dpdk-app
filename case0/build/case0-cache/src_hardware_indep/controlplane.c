#include "dpdk_lib.h"// sugar@22
#include "actions.h"// sugar@23

extern void table_setdefault_promote(int tableid, uint8_t *value);// sugar@25
extern void exact_add_promote(int tableid, uint8_t *key, uint8_t *value);// sugar@26
extern void lpm_add_promote(int tableid, uint8_t *key, uint8_t depth, uint8_t *value);// sugar@27
extern void ternary_add_promote(int tableid, uint8_t *key, uint8_t *mask, uint8_t *value);// sugar@28

extern void table_cache_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_mac_learning_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_routable_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_unicast_routing_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_switching_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_multicast_routing_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31
extern void table_igmp_key(packet_descriptor_t *pd, uint8_t *key); // defined in dataplane.c// sugar@31

uint8_t reverse_buffer[19];// sugar@35
void// sugar@39
cache_add(// sugar@40
        uint8_t field_instance_standard_metadata_ingress_port[2],// sugar@43
        uint8_t field_instance_ethernet_src_mac[6],// sugar@43
        uint8_t field_instance_ethernet_dst_mac[6],// sugar@43
        uint8_t field_instance_ip_dst_addr[4],// sugar@43
        uint8_t field_instance_vlan_vid[2],// sugar@43
        struct cache_action action)// sugar@49
{// sugar@50
    uint8_t key[19];// sugar@51
    memcpy(key + 0, field_instance_standard_metadata_ingress_port, 2);// sugar@56
    memcpy(key + 2, field_instance_ethernet_src_mac, 6);// sugar@56
    memcpy(key + 8, field_instance_ethernet_dst_mac, 6);// sugar@56
    memcpy(key + 14, field_instance_ip_dst_addr, 4);// sugar@56
    memcpy(key + 18, field_instance_vlan_vid, 2);// sugar@56
    exact_add_promote(TABLE_cache, (uint8_t *) key, (uint8_t * ) & action);// sugar@74
}// sugar@75

void// sugar@77
cache_setdefault(struct cache_action action)// sugar@78
{// sugar@79
    table_setdefault_promote(TABLE_cache, (uint8_t * ) & action);// sugar@80
}// sugar@81
void// sugar@39
mac_learning_add(// sugar@40
        uint8_t field_instance_ethernet_src_mac[6],// sugar@43
        uint8_t field_instance_vlan_vid[2],// sugar@43
        struct mac_learning_action action)// sugar@49
{// sugar@50
    uint8_t key[8];// sugar@51
    memcpy(key + 0, field_instance_ethernet_src_mac, 6);// sugar@56
    memcpy(key + 6, field_instance_vlan_vid, 2);// sugar@56
    exact_add_promote(TABLE_mac_learning, (uint8_t *) key, (uint8_t * ) & action);// sugar@74
}// sugar@75

void// sugar@77
mac_learning_setdefault(struct mac_learning_action action)// sugar@78
{// sugar@79
    table_setdefault_promote(TABLE_mac_learning, (uint8_t * ) & action);// sugar@80
}// sugar@81
void// sugar@39
routable_add(// sugar@40
        uint8_t field_instance_ethernet_src_mac[6],// sugar@43
        uint8_t field_instance_ethernet_dst_mac[6],// sugar@43
        uint8_t field_instance_vlan_vid[2],// sugar@43
        struct routable_action action)// sugar@49
{// sugar@50
    uint8_t key[14];// sugar@51
    memcpy(key + 0, field_instance_ethernet_src_mac, 6);// sugar@56
    memcpy(key + 6, field_instance_ethernet_dst_mac, 6);// sugar@56
    memcpy(key + 12, field_instance_vlan_vid, 2);// sugar@56
    exact_add_promote(TABLE_routable, (uint8_t *) key, (uint8_t * ) & action);// sugar@74
}// sugar@75

void// sugar@77
routable_setdefault(struct routable_action action)// sugar@78
{// sugar@79
    table_setdefault_promote(TABLE_routable, (uint8_t * ) & action);// sugar@80
}// sugar@81
void// sugar@39
unicast_routing_add(// sugar@40
        uint8_t field_instance_ip_dst_addr[4],// sugar@43
        struct unicast_routing_action action)// sugar@49
{// sugar@50
    uint8_t key[4];// sugar@51
    memcpy(key + 0, field_instance_ip_dst_addr, 4);// sugar@56
    exact_add_promote(TABLE_unicast_routing, (uint8_t *) key, (uint8_t * ) & action);// sugar@74
}// sugar@75

void// sugar@77
unicast_routing_setdefault(struct unicast_routing_action action)// sugar@78
{// sugar@79
    table_setdefault_promote(TABLE_unicast_routing, (uint8_t * ) & action);// sugar@80
}// sugar@81
void// sugar@39
switching_add(// sugar@40
        uint8_t field_instance_ethernet_dst_mac[6],// sugar@43
        uint8_t field_instance_vlan_vid[2],// sugar@43
        struct switching_action action)// sugar@49
{// sugar@50
    uint8_t key[8];// sugar@51
    memcpy(key + 0, field_instance_ethernet_dst_mac, 6);// sugar@56
    memcpy(key + 6, field_instance_vlan_vid, 2);// sugar@56
    exact_add_promote(TABLE_switching, (uint8_t *) key, (uint8_t * ) & action);// sugar@74
}// sugar@75

void// sugar@77
switching_setdefault(struct switching_action action)// sugar@78
{// sugar@79
    table_setdefault_promote(TABLE_switching, (uint8_t * ) & action);// sugar@80
}// sugar@81
void// sugar@39
multicast_routing_add(// sugar@40
        uint8_t field_instance_ip_dst_addr[4],// sugar@43
        struct multicast_routing_action action)// sugar@49
{// sugar@50
    uint8_t key[4];// sugar@51
    memcpy(key + 0, field_instance_ip_dst_addr, 4);// sugar@56
    exact_add_promote(TABLE_multicast_routing, (uint8_t *) key, (uint8_t * ) & action);// sugar@74
}// sugar@75

void// sugar@77
multicast_routing_setdefault(struct multicast_routing_action action)// sugar@78
{// sugar@79
    table_setdefault_promote(TABLE_multicast_routing, (uint8_t * ) & action);// sugar@80
}// sugar@81
void// sugar@39
igmp_add(// sugar@40
        uint8_t field_instance_ip_dst_addr[4],// sugar@43
        uint8_t field_instance_vlan_vid[2],// sugar@43
        uint8_t field_instance_standard_metadata_ingress_port[2],// sugar@43
        struct igmp_action action)// sugar@49
{// sugar@50
    uint8_t key[7];// sugar@51
    memcpy(key + 0, field_instance_ip_dst_addr, 4);// sugar@56
    memcpy(key + 4, field_instance_vlan_vid, 2);// sugar@56
    memcpy(key + 6, field_instance_standard_metadata_ingress_port, 2);// sugar@56
    exact_add_promote(TABLE_igmp, (uint8_t *) key, (uint8_t * ) & action);// sugar@74
}// sugar@75

void// sugar@77
igmp_setdefault(struct igmp_action action)// sugar@78
{// sugar@79
    table_setdefault_promote(TABLE_igmp, (uint8_t * ) & action);// sugar@80
}// sugar@81
void// sugar@85
cache_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@86
    uint8_t *field_instance_standard_metadata_ingress_port = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@90
    uint8_t *field_instance_ethernet_src_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@90
    uint8_t *field_instance_ethernet_dst_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[2])->bitmap);// sugar@90
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[3])->bitmap);// sugar@90
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[4])->bitmap);// sugar@90
    if (strcmp("cache_action", ctrl_m->action_name) == 0) {// sugar@95
        struct cache_action action;// sugar@96
        action.action_id = action_cache_action;// sugar@97
        uint8_t *port = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@99
        memcpy(action.cache_action_params.port, port, 2);// sugar@100
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@99
        memcpy(action.cache_action_params.src_mac, src_mac, 6);// sugar@100
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@99
        memcpy(action.cache_action_params.dst_mac, dst_mac, 6);// sugar@100
        uint8_t *vid = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[3])->bitmap;// sugar@99
        memcpy(action.cache_action_params.vid, vid, 2);// sugar@100
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[4])->bitmap;// sugar@99
        memcpy(action.cache_action_params.grp, grp, 2);// sugar@100
        debug("Reply from the control plane arrived.\n");// sugar@101
        debug("Adding new entry to cache with action cache_action\n");// sugar@102
        cache_add(// sugar@103
                field_instance_standard_metadata_ingress_port,// sugar@106
                field_instance_ethernet_src_mac,// sugar@106
                field_instance_ethernet_dst_mac,// sugar@106
                field_instance_ip_dst_addr,// sugar@106
                field_instance_vlan_vid,// sugar@106
                action);// sugar@109
    } else// sugar@110
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@111
}// sugar@112
void// sugar@85
mac_learning_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@86
    uint8_t *field_instance_ethernet_src_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@90
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@90
    if (strcmp("learning", ctrl_m->action_name) == 0) {// sugar@95
        struct mac_learning_action action;// sugar@96
        action.action_id = action_learning;// sugar@97
        debug("Reply from the control plane arrived.\n");// sugar@101
        debug("Adding new entry to mac_learning with action learning\n");// sugar@102
        mac_learning_add(// sugar@103
                field_instance_ethernet_src_mac,// sugar@106
                field_instance_vlan_vid,// sugar@106
                action);// sugar@109
    } else// sugar@110
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@95
        struct mac_learning_action action;// sugar@96
        action.action_id = action_nop;// sugar@97
        debug("Reply from the control plane arrived.\n");// sugar@101
        debug("Adding new entry to mac_learning with action nop\n");// sugar@102
        mac_learning_add(// sugar@103
                field_instance_ethernet_src_mac,// sugar@106
                field_instance_vlan_vid,// sugar@106
                action);// sugar@109
    } else// sugar@110
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@111
}// sugar@112
void// sugar@85
routable_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@86
    uint8_t *field_instance_ethernet_src_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@90
    uint8_t *field_instance_ethernet_dst_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@90
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[2])->bitmap);// sugar@90
    if (strcmp("ucast", ctrl_m->action_name) == 0) {// sugar@95
        struct routable_action action;// sugar@96
        action.action_id = action_ucast;// sugar@97
        uint8_t *lan = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@99
        memcpy(action.ucast_params.lan, lan, 1);// sugar@100
        debug("Reply from the control plane arrived.\n");// sugar@101
        debug("Adding new entry to routable with action ucast\n");// sugar@102
        routable_add(// sugar@103
                field_instance_ethernet_src_mac,// sugar@106
                field_instance_ethernet_dst_mac,// sugar@106
                field_instance_vlan_vid,// sugar@106
                action);// sugar@109
    } else// sugar@110
    if (strcmp("mcast", ctrl_m->action_name) == 0) {// sugar@95
        struct routable_action action;// sugar@96
        action.action_id = action_mcast;// sugar@97
        debug("Reply from the control plane arrived.\n");// sugar@101
        debug("Adding new entry to routable with action mcast\n");// sugar@102
        routable_add(// sugar@103
                field_instance_ethernet_src_mac,// sugar@106
                field_instance_ethernet_dst_mac,// sugar@106
                field_instance_vlan_vid,// sugar@106
                action);// sugar@109
    } else// sugar@110
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@111
}// sugar@112
void// sugar@85
unicast_routing_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@86
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@90
    if (strcmp("set_nhop", ctrl_m->action_name) == 0) {// sugar@95
        struct unicast_routing_action action;// sugar@96
        action.action_id = action_set_nhop;// sugar@97
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@99
        memcpy(action.set_nhop_params.src_mac, src_mac, 6);// sugar@100
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@99
        memcpy(action.set_nhop_params.dst_mac, dst_mac, 6);// sugar@100
        debug("Reply from the control plane arrived.\n");// sugar@101
        debug("Adding new entry to unicast_routing with action set_nhop\n");// sugar@102
        unicast_routing_add(// sugar@103
                field_instance_ip_dst_addr,// sugar@106
                action);// sugar@109
    } else// sugar@110
    if (strcmp("set_nhop_with_vlan", ctrl_m->action_name) == 0) {// sugar@95
        struct unicast_routing_action action;// sugar@96
        action.action_id = action_set_nhop_with_vlan;// sugar@97
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@99
        memcpy(action.set_nhop_with_vlan_params.src_mac, src_mac, 6);// sugar@100
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@99
        memcpy(action.set_nhop_with_vlan_params.dst_mac, dst_mac, 6);// sugar@100
        uint8_t *vid = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@99
        memcpy(action.set_nhop_with_vlan_params.vid, vid, 2);// sugar@100
        debug("Reply from the control plane arrived.\n");// sugar@101
        debug("Adding new entry to unicast_routing with action set_nhop_with_vlan\n");// sugar@102
        unicast_routing_add(// sugar@103
                field_instance_ip_dst_addr,// sugar@106
                action);// sugar@109
    } else// sugar@110
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@111
}// sugar@112
void// sugar@85
switching_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@86
    uint8_t *field_instance_ethernet_dst_mac = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@90
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@90
    if (strcmp("forwarding", ctrl_m->action_name) == 0) {// sugar@95
        struct switching_action action;// sugar@96
        action.action_id = action_forwarding;// sugar@97
        uint8_t *port = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@99
        memcpy(action.forwarding_params.port, port, 2);// sugar@100
        debug("Reply from the control plane arrived.\n");// sugar@101
        debug("Adding new entry to switching with action forwarding\n");// sugar@102
        switching_add(// sugar@103
                field_instance_ethernet_dst_mac,// sugar@106
                field_instance_vlan_vid,// sugar@106
                action);// sugar@109
    } else// sugar@110
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@111
}// sugar@112
void// sugar@85
multicast_routing_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@86
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@90
    if (strcmp("set_multicast", ctrl_m->action_name) == 0) {// sugar@95
        struct multicast_routing_action action;// sugar@96
        action.action_id = action_set_multicast;// sugar@97
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@99
        memcpy(action.set_multicast_params.grp, grp, 2);// sugar@100
        debug("Reply from the control plane arrived.\n");// sugar@101
        debug("Adding new entry to multicast_routing with action set_multicast\n");// sugar@102
        multicast_routing_add(// sugar@103
                field_instance_ip_dst_addr,// sugar@106
                action);// sugar@109
    } else// sugar@110
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@111
}// sugar@112
void// sugar@85
igmp_add_table_entry(struct p4_ctrl_msg *ctrl_m) {// sugar@86
    uint8_t *field_instance_ip_dst_addr = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[0])->bitmap);// sugar@90
    uint8_t *field_instance_vlan_vid = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[1])->bitmap);// sugar@90
    uint8_t *field_instance_standard_metadata_ingress_port = (uint8_t * )(
            ((struct p4_field_match_exact *) ctrl_m->field_matches[2])->bitmap);// sugar@90
    if (strcmp("set_multicast", ctrl_m->action_name) == 0) {// sugar@95
        struct igmp_action action;// sugar@96
        action.action_id = action_set_multicast;// sugar@97
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@99
        memcpy(action.set_multicast_params.grp, grp, 2);// sugar@100
        debug("Reply from the control plane arrived.\n");// sugar@101
        debug("Adding new entry to igmp with action set_multicast\n");// sugar@102
        igmp_add(// sugar@103
                field_instance_ip_dst_addr,// sugar@106
                field_instance_vlan_vid,// sugar@106
                field_instance_standard_metadata_ingress_port,// sugar@106
                action);// sugar@109
    } else// sugar@110
        debug("Table add entry: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@111
}// sugar@112
void// sugar@115
cache_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@116
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@117
    if (strcmp("cache_action", ctrl_m->action_name) == 0) {// sugar@119
        struct cache_action action;// sugar@120
        action.action_id = action_cache_action;// sugar@121
        uint8_t *port = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@123
        memcpy(action.cache_action_params.port, port, 2);// sugar@124
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@123
        memcpy(action.cache_action_params.src_mac, src_mac, 6);// sugar@124
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@123
        memcpy(action.cache_action_params.dst_mac, dst_mac, 6);// sugar@124
        uint8_t *vid = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[3])->bitmap;// sugar@123
        memcpy(action.cache_action_params.vid, vid, 2);// sugar@124
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[4])->bitmap;// sugar@123
        memcpy(action.cache_action_params.grp, grp, 2);// sugar@124
        debug("Message from the control plane arrived.\n");// sugar@125
        debug("Set default action for cache with action cache_action\n");// sugar@126
        cache_setdefault(action);// sugar@127
    } else// sugar@128
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@129
}// sugar@130
void// sugar@115
mac_learning_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@116
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@117
    if (strcmp("learning", ctrl_m->action_name) == 0) {// sugar@119
        struct mac_learning_action action;// sugar@120
        action.action_id = action_learning;// sugar@121
        debug("Message from the control plane arrived.\n");// sugar@125
        debug("Set default action for mac_learning with action learning\n");// sugar@126
        mac_learning_setdefault(action);// sugar@127
    } else// sugar@128
    if (strcmp("nop", ctrl_m->action_name) == 0) {// sugar@119
        struct mac_learning_action action;// sugar@120
        action.action_id = action_nop;// sugar@121
        debug("Message from the control plane arrived.\n");// sugar@125
        debug("Set default action for mac_learning with action nop\n");// sugar@126
        mac_learning_setdefault(action);// sugar@127
    } else// sugar@128
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@129
}// sugar@130
void// sugar@115
routable_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@116
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@117
    if (strcmp("ucast", ctrl_m->action_name) == 0) {// sugar@119
        struct routable_action action;// sugar@120
        action.action_id = action_ucast;// sugar@121
        uint8_t *lan = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@123
        memcpy(action.ucast_params.lan, lan, 1);// sugar@124
        debug("Message from the control plane arrived.\n");// sugar@125
        debug("Set default action for routable with action ucast\n");// sugar@126
        routable_setdefault(action);// sugar@127
    } else// sugar@128
    if (strcmp("mcast", ctrl_m->action_name) == 0) {// sugar@119
        struct routable_action action;// sugar@120
        action.action_id = action_mcast;// sugar@121
        debug("Message from the control plane arrived.\n");// sugar@125
        debug("Set default action for routable with action mcast\n");// sugar@126
        routable_setdefault(action);// sugar@127
    } else// sugar@128
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@129
}// sugar@130
void// sugar@115
unicast_routing_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@116
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@117
    if (strcmp("set_nhop", ctrl_m->action_name) == 0) {// sugar@119
        struct unicast_routing_action action;// sugar@120
        action.action_id = action_set_nhop;// sugar@121
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@123
        memcpy(action.set_nhop_params.src_mac, src_mac, 6);// sugar@124
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@123
        memcpy(action.set_nhop_params.dst_mac, dst_mac, 6);// sugar@124
        debug("Message from the control plane arrived.\n");// sugar@125
        debug("Set default action for unicast_routing with action set_nhop\n");// sugar@126
        unicast_routing_setdefault(action);// sugar@127
    } else// sugar@128
    if (strcmp("set_nhop_with_vlan", ctrl_m->action_name) == 0) {// sugar@119
        struct unicast_routing_action action;// sugar@120
        action.action_id = action_set_nhop_with_vlan;// sugar@121
        uint8_t *src_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@123
        memcpy(action.set_nhop_with_vlan_params.src_mac, src_mac, 6);// sugar@124
        uint8_t *dst_mac = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[1])->bitmap;// sugar@123
        memcpy(action.set_nhop_with_vlan_params.dst_mac, dst_mac, 6);// sugar@124
        uint8_t *vid = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[2])->bitmap;// sugar@123
        memcpy(action.set_nhop_with_vlan_params.vid, vid, 2);// sugar@124
        debug("Message from the control plane arrived.\n");// sugar@125
        debug("Set default action for unicast_routing with action set_nhop_with_vlan\n");// sugar@126
        unicast_routing_setdefault(action);// sugar@127
    } else// sugar@128
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@129
}// sugar@130
void// sugar@115
switching_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@116
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@117
    if (strcmp("forwarding", ctrl_m->action_name) == 0) {// sugar@119
        struct switching_action action;// sugar@120
        action.action_id = action_forwarding;// sugar@121
        uint8_t *port = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@123
        memcpy(action.forwarding_params.port, port, 2);// sugar@124
        debug("Message from the control plane arrived.\n");// sugar@125
        debug("Set default action for switching with action forwarding\n");// sugar@126
        switching_setdefault(action);// sugar@127
    } else// sugar@128
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@129
}// sugar@130
void// sugar@115
multicast_routing_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@116
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@117
    if (strcmp("set_multicast", ctrl_m->action_name) == 0) {// sugar@119
        struct multicast_routing_action action;// sugar@120
        action.action_id = action_set_multicast;// sugar@121
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@123
        memcpy(action.set_multicast_params.grp, grp, 2);// sugar@124
        debug("Message from the control plane arrived.\n");// sugar@125
        debug("Set default action for multicast_routing with action set_multicast\n");// sugar@126
        multicast_routing_setdefault(action);// sugar@127
    } else// sugar@128
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@129
}// sugar@130
void// sugar@115
igmp_set_default_table_action(struct p4_ctrl_msg *ctrl_m) {// sugar@116
    debug("Action name: %s\n", ctrl_m->action_name);// sugar@117
    if (strcmp("set_multicast", ctrl_m->action_name) == 0) {// sugar@119
        struct igmp_action action;// sugar@120
        action.action_id = action_set_multicast;// sugar@121
        uint8_t *grp = (uint8_t * )((struct p4_action_parameter *) ctrl_m->action_params[0])->bitmap;// sugar@123
        memcpy(action.set_multicast_params.grp, grp, 2);// sugar@124
        debug("Message from the control plane arrived.\n");// sugar@125
        debug("Set default action for igmp with action set_multicast\n");// sugar@126
        igmp_setdefault(action);// sugar@127
    } else// sugar@128
        debug("Table setdefault: action name mismatch (%s).\n", ctrl_m->action_name);// sugar@129
}// sugar@130
void recv_from_controller(struct p4_ctrl_msg *ctrl_m) {// sugar@133
    debug("MSG from controller %d %s\n", ctrl_m->type, ctrl_m->table_name);// sugar@134
    if (ctrl_m->type == P4T_ADD_TABLE_ENTRY) {// sugar@135
        if (strcmp("cache", ctrl_m->table_name) == 0)// sugar@137
            cache_add_table_entry(ctrl_m);// sugar@138
        else// sugar@139
        if (strcmp("mac_learning", ctrl_m->table_name) == 0)// sugar@137
            mac_learning_add_table_entry(ctrl_m);// sugar@138
        else// sugar@139
        if (strcmp("routable", ctrl_m->table_name) == 0)// sugar@137
            routable_add_table_entry(ctrl_m);// sugar@138
        else// sugar@139
        if (strcmp("unicast_routing", ctrl_m->table_name) == 0)// sugar@137
            unicast_routing_add_table_entry(ctrl_m);// sugar@138
        else// sugar@139
        if (strcmp("switching", ctrl_m->table_name) == 0)// sugar@137
            switching_add_table_entry(ctrl_m);// sugar@138
        else// sugar@139
        if (strcmp("multicast_routing", ctrl_m->table_name) == 0)// sugar@137
            multicast_routing_add_table_entry(ctrl_m);// sugar@138
        else// sugar@139
        if (strcmp("igmp", ctrl_m->table_name) == 0)// sugar@137
            igmp_add_table_entry(ctrl_m);// sugar@138
        else// sugar@139
            debug("Table add entry: table name mismatch (%s).\n", ctrl_m->table_name);// sugar@140
    }// sugar@141
    else if (ctrl_m->type == P4T_SET_DEFAULT_ACTION) {// sugar@142
        if (strcmp("cache", ctrl_m->table_name) == 0)// sugar@144
            cache_set_default_table_action(ctrl_m);// sugar@145
        else// sugar@146
        if (strcmp("mac_learning", ctrl_m->table_name) == 0)// sugar@144
            mac_learning_set_default_table_action(ctrl_m);// sugar@145
        else// sugar@146
        if (strcmp("routable", ctrl_m->table_name) == 0)// sugar@144
            routable_set_default_table_action(ctrl_m);// sugar@145
        else// sugar@146
        if (strcmp("unicast_routing", ctrl_m->table_name) == 0)// sugar@144
            unicast_routing_set_default_table_action(ctrl_m);// sugar@145
        else// sugar@146
        if (strcmp("switching", ctrl_m->table_name) == 0)// sugar@144
            switching_set_default_table_action(ctrl_m);// sugar@145
        else// sugar@146
        if (strcmp("multicast_routing", ctrl_m->table_name) == 0)// sugar@144
            multicast_routing_set_default_table_action(ctrl_m);// sugar@145
        else// sugar@146
        if (strcmp("igmp", ctrl_m->table_name) == 0)// sugar@144
            igmp_set_default_table_action(ctrl_m);// sugar@145
        else// sugar@146
            debug("Table setdefault: table name mismatch (%s).\n", ctrl_m->table_name);// sugar@147
    }// sugar@148
}// sugar@149
backend bg;// sugar@153
void init_control_plane()// sugar@154
{// sugar@155
    debug("Creating control plane connection...\n");// sugar@156
    bg = create_backend(3, 1000, "localhost", 11110, recv_from_controller);// sugar@157
    launch_backend(bg);// sugar@158
    /*// sugar@159
    */// sugar@170
}// sugar@171
