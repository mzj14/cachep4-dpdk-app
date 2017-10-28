#ifndef __ACTION_INFO_GENERATED_H__// sugar@14
#define __ACTION_INFO_GENERATED_H__// sugar@15


#define FIELD(name, length) uint8_t name[(length + 7) / 8];// sugar@18

enum actions {// sugar@21
    action_acl_alert,// sugar@27
    action_acl_permit,// sugar@27
    action_acl_drop,// sugar@27
    action_nop,// sugar@27
    action_acl_feature,// sugar@27
    action_learning,// sugar@27
    action_ucast,// sugar@27
    action_mcast,// sugar@27
    action_set_nhop,// sugar@27
    action_set_nhop_with_vlan,// sugar@27
    action_forwarding,// sugar@27
    action_set_multicast,// sugar@27
};// sugar@28
struct action_acl_alert_params {// sugar@33
    FIELD(reason, 12);// sugar@35
};// sugar@36
struct action_acl_permit_params {// sugar@33
    FIELD(reason, 12);// sugar@35
};// sugar@36
struct action_acl_drop_params {// sugar@33
    FIELD(reason, 12);// sugar@35
};// sugar@36
struct action_acl_feature_params {// sugar@33
    FIELD(enable_mac, 1);// sugar@35
    FIELD(enable_vlan, 1);// sugar@35
    FIELD(enable_ipv4, 1);// sugar@35
    FIELD(enable_icmp, 1);// sugar@35
    FIELD(enable_tcp, 1);// sugar@35
    FIELD(enable_udp, 1);// sugar@35
};// sugar@36
struct action_ucast_params {// sugar@33
    FIELD(lan, 4);// sugar@35
};// sugar@36
struct action_set_nhop_params {// sugar@33
    FIELD(src_mac, 48);// sugar@35
    FIELD(dst_mac, 48);// sugar@35
};// sugar@36
struct action_set_nhop_with_vlan_params {// sugar@33
    FIELD(src_mac, 48);// sugar@35
    FIELD(dst_mac, 48);// sugar@35
    FIELD(vid, 12);// sugar@35
};// sugar@36
struct action_forwarding_params {// sugar@33
    FIELD(port, 9);// sugar@35
};// sugar@36
struct action_set_multicast_params {// sugar@33
    FIELD(grp, 16);// sugar@35
};// sugar@36
struct mac_acl_action {// sugar@39
    int action_id;// sugar@40
    union {// sugar@41
        struct action_acl_alert_params acl_alert_params;// sugar@44
        struct action_acl_permit_params acl_permit_params;// sugar@44
        struct action_acl_drop_params acl_drop_params;// sugar@44
    };// sugar@45
};// sugar@46
struct ipv4_acl_action {// sugar@39
    int action_id;// sugar@40
    union {// sugar@41
        struct action_acl_permit_params acl_permit_params;// sugar@44
        struct action_acl_alert_params acl_alert_params;// sugar@44
        struct action_acl_drop_params acl_drop_params;// sugar@44
    };// sugar@45
};// sugar@46
struct tcp_acl_action {// sugar@39
    int action_id;// sugar@40
    union {// sugar@41
        struct action_acl_permit_params acl_permit_params;// sugar@44
        struct action_acl_alert_params acl_alert_params;// sugar@44
        struct action_acl_drop_params acl_drop_params;// sugar@44
    };// sugar@45
};// sugar@46
struct udp_acl_action {// sugar@39
    int action_id;// sugar@40
    union {// sugar@41
        struct action_acl_permit_params acl_permit_params;// sugar@44
        struct action_acl_alert_params acl_alert_params;// sugar@44
        struct action_acl_drop_params acl_drop_params;// sugar@44
    };// sugar@45
};// sugar@46
struct get_acl_features_action {// sugar@39
    int action_id;// sugar@40
    union {// sugar@41
        struct action_acl_feature_params acl_feature_params;// sugar@44
    };// sugar@45
};// sugar@46
struct mac_learning_action {// sugar@39
    int action_id;// sugar@40
    union {// sugar@41
    };// sugar@45
};// sugar@46
struct routable_action {// sugar@39
    int action_id;// sugar@40
    union {// sugar@41
        struct action_ucast_params ucast_params;// sugar@44
    };// sugar@45
};// sugar@46
struct unicast_routing_action {// sugar@39
    int action_id;// sugar@40
    union {// sugar@41
        struct action_set_nhop_params set_nhop_params;// sugar@44
        struct action_set_nhop_with_vlan_params set_nhop_with_vlan_params;// sugar@44
    };// sugar@45
};// sugar@46
struct switching_action {// sugar@39
    int action_id;// sugar@40
    union {// sugar@41
        struct action_forwarding_params forwarding_params;// sugar@44
    };// sugar@45
};// sugar@46
struct multicast_routing_action {// sugar@39
    int action_id;// sugar@40
    union {// sugar@41
        struct action_set_multicast_params set_multicast_params;// sugar@44
    };// sugar@45
};// sugar@46
struct igmp_action {// sugar@39
    int action_id;// sugar@40
    union {// sugar@41
        struct action_set_multicast_params set_multicast_params;// sugar@44
    };// sugar@45
};// sugar@46
void apply_table_mac_acl(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@49
void action_code_acl_alert(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_alert_params);// sugar@52
void
action_code_acl_permit(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_permit_params);// sugar@52
void action_code_acl_drop(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_drop_params);// sugar@52
void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@54
void apply_table_ipv4_acl(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@49
void
action_code_acl_permit(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_permit_params);// sugar@52
void action_code_acl_alert(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_alert_params);// sugar@52
void action_code_acl_drop(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_drop_params);// sugar@52
void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@54
void apply_table_tcp_acl(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@49
void
action_code_acl_permit(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_permit_params);// sugar@52
void action_code_acl_alert(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_alert_params);// sugar@52
void action_code_acl_drop(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_drop_params);// sugar@52
void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@54
void apply_table_udp_acl(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@49
void
action_code_acl_permit(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_permit_params);// sugar@52
void action_code_acl_alert(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_alert_params);// sugar@52
void action_code_acl_drop(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_drop_params);// sugar@52
void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@54
void apply_table_get_acl_features(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@49
void
action_code_acl_feature(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_feature_params);// sugar@52
void apply_table_mac_learning(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@49
void action_code_learning(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@54
void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@54
void apply_table_routable(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@49
void action_code_ucast(packet_descriptor_t *pd, lookup_table_t **tables, struct action_ucast_params);// sugar@52
void action_code_mcast(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@54
void apply_table_unicast_routing(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@49
void action_code_set_nhop(packet_descriptor_t *pd, lookup_table_t **tables, struct action_set_nhop_params);// sugar@52
void action_code_set_nhop_with_vlan(packet_descriptor_t *pd, lookup_table_t **tables,
                                    struct action_set_nhop_with_vlan_params);// sugar@52
void apply_table_switching(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@49
void
action_code_forwarding(packet_descriptor_t *pd, lookup_table_t **tables, struct action_forwarding_params);// sugar@52
void apply_table_multicast_routing(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@49
void action_code_set_multicast(packet_descriptor_t *pd, lookup_table_t **tables,
                               struct action_set_multicast_params);// sugar@52
void apply_table_igmp(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@49
void action_code_set_multicast(packet_descriptor_t *pd, lookup_table_t **tables,
                               struct action_set_multicast_params);// sugar@52
#endif// sugar@56
