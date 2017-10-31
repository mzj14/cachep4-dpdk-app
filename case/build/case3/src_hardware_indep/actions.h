 #ifndef __ACTION_INFO_GENERATED_H__// sugar@14
 #define __ACTION_INFO_GENERATED_H__// sugar@15
 

 #define FIELD(name, length) uint8_t name[(length + 7) / 8];// sugar@18

 enum actions {// sugar@21
 action_acl_alert,// sugar@27
 action_acl_permit,// sugar@27
 action_acl_drop,// sugar@27
 action_nop,// sugar@27
 action_acl_feature,// sugar@27
 action_on_miss,// sugar@27
 action_rewrite_tcp_src,// sugar@27
 action_rewrite_udp_src,// sugar@27
 action_rewrite_tcp_dst,// sugar@27
 action_rewrite_udp_dst,// sugar@27
 action_rewrite_twice_tcp,// sugar@27
 action_rewrite_twice_udp,// sugar@27
 action_get_tcp_information,// sugar@27
 action_get_udp_information,// sugar@27
 action_disable_nat,// sugar@27
 action_ipsg_miss,// sugar@27
 action_set_storm_control_meter,// sugar@27
 action_set_vrf,// sugar@27
 action_learning,// sugar@27
 action_ucast,// sugar@27
 action_mcast,// sugar@27
 action_set_nhop,// sugar@27
 action_set_nhop_with_vlan,// sugar@27
 action_forwarding,// sugar@27
 action_set_multicast,// sugar@27
 };// sugar@28
 struct action_acl_alert_params {// sugar@34
 FIELD(reason, 12);// sugar@36
 };// sugar@37
 struct action_acl_permit_params {// sugar@34
 FIELD(reason, 12);// sugar@36
 };// sugar@37
 struct action_acl_drop_params {// sugar@34
 FIELD(reason, 12);// sugar@36
 };// sugar@37
 struct action_acl_feature_params {// sugar@34
 FIELD(enable_mac, 1);// sugar@36
 FIELD(enable_vlan, 1);// sugar@36
 FIELD(enable_ipv4, 1);// sugar@36
 FIELD(enable_icmp, 1);// sugar@36
 FIELD(enable_tcp, 1);// sugar@36
 FIELD(enable_udp, 1);// sugar@36
 };// sugar@37
 struct action_rewrite_tcp_src_params {// sugar@34
 FIELD(addr, 32);// sugar@36
 FIELD(port, 16);// sugar@36
 };// sugar@37
 struct action_rewrite_udp_src_params {// sugar@34
 FIELD(addr, 32);// sugar@36
 FIELD(port, 16);// sugar@36
 };// sugar@37
 struct action_rewrite_tcp_dst_params {// sugar@34
 FIELD(addr, 32);// sugar@36
 FIELD(port, 16);// sugar@36
 };// sugar@37
 struct action_rewrite_udp_dst_params {// sugar@34
 FIELD(addr, 32);// sugar@36
 FIELD(port, 16);// sugar@36
 };// sugar@37
 struct action_rewrite_twice_tcp_params {// sugar@34
 FIELD(src_addr, 32);// sugar@36
 FIELD(dst_addr, 32);// sugar@36
 FIELD(src_port, 16);// sugar@36
 FIELD(dst_port, 16);// sugar@36
 };// sugar@37
 struct action_rewrite_twice_udp_params {// sugar@34
 FIELD(src_addr, 32);// sugar@36
 FIELD(dst_addr, 32);// sugar@36
 FIELD(src_port, 16);// sugar@36
 FIELD(dst_port, 16);// sugar@36
 };// sugar@37
 struct action_set_storm_control_meter_params {// sugar@34
 FIELD(meter_idx, 16);// sugar@36
 };// sugar@37
 struct action_set_vrf_params {// sugar@34
 FIELD(vrf, 16);// sugar@36
 };// sugar@37
 struct action_ucast_params {// sugar@34
 FIELD(lan, 4);// sugar@36
 };// sugar@37
 struct action_set_nhop_params {// sugar@34
 FIELD(src_mac, 48);// sugar@36
 FIELD(dst_mac, 48);// sugar@36
 };// sugar@37
 struct action_set_nhop_with_vlan_params {// sugar@34
 FIELD(src_mac, 48);// sugar@36
 FIELD(dst_mac, 48);// sugar@36
 FIELD(vid, 12);// sugar@36
 };// sugar@37
 struct action_forwarding_params {// sugar@34
 FIELD(port, 9);// sugar@36
 };// sugar@37
 struct action_set_multicast_params {// sugar@34
 FIELD(grp, 16);// sugar@36
 };// sugar@37
 struct mac_acl_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_acl_alert_params acl_alert_params;// sugar@46
 struct action_acl_permit_params acl_permit_params;// sugar@46
 struct action_acl_drop_params acl_drop_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct ipv4_acl_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_acl_permit_params acl_permit_params;// sugar@46
 struct action_acl_alert_params acl_alert_params;// sugar@46
 struct action_acl_drop_params acl_drop_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct tcp_acl_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_acl_permit_params acl_permit_params;// sugar@46
 struct action_acl_alert_params acl_alert_params;// sugar@46
 struct action_acl_drop_params acl_drop_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct udp_acl_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_acl_permit_params acl_permit_params;// sugar@46
 struct action_acl_alert_params acl_alert_params;// sugar@46
 struct action_acl_drop_params acl_drop_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct get_acl_features_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_acl_feature_params acl_feature_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct nat_src_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_rewrite_tcp_src_params rewrite_tcp_src_params;// sugar@46
 struct action_rewrite_udp_src_params rewrite_udp_src_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct nat_dst_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_rewrite_tcp_dst_params rewrite_tcp_dst_params;// sugar@46
 struct action_rewrite_udp_dst_params rewrite_udp_dst_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct nat_twice_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_rewrite_twice_tcp_params rewrite_twice_tcp_params;// sugar@46
 struct action_rewrite_twice_udp_params rewrite_twice_udp_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct nat_flow_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_rewrite_twice_tcp_params rewrite_twice_tcp_params;// sugar@46
 struct action_rewrite_twice_udp_params rewrite_twice_udp_params;// sugar@46
 struct action_rewrite_tcp_dst_params rewrite_tcp_dst_params;// sugar@46
 struct action_rewrite_udp_dst_params rewrite_udp_dst_params;// sugar@46
 struct action_rewrite_tcp_src_params rewrite_tcp_src_params;// sugar@46
 struct action_rewrite_udp_src_params rewrite_udp_src_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct nat_get_l4_infomation_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
     };// sugar@47
 };// sugar@48
 struct ipsg_permit_special_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
     };// sugar@47
 };// sugar@48
 struct ipsg_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
     };// sugar@47
 };// sugar@48
 struct storm_control_tbl_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_set_storm_control_meter_params set_storm_control_meter_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct port_vlan_to_vrf_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_set_vrf_params set_vrf_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct mac_learning_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
     };// sugar@47
 };// sugar@48
 struct routable_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_ucast_params ucast_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct unicast_routing_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_set_nhop_params set_nhop_params;// sugar@46
 struct action_set_nhop_with_vlan_params set_nhop_with_vlan_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct switching_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_forwarding_params forwarding_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct multicast_routing_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_set_multicast_params set_multicast_params;// sugar@46
     };// sugar@47
 };// sugar@48
 struct igmp_action {// sugar@41
     int action_id;// sugar@42
     union {// sugar@43
 struct action_set_multicast_params set_multicast_params;// sugar@46
     };// sugar@47
 };// sugar@48
 void apply_table_mac_acl(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_acl_alert(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_alert_params);// sugar@54
 void action_code_acl_permit(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_permit_params);// sugar@54
 void action_code_acl_drop(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_drop_params);// sugar@54
 void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void apply_table_ipv4_acl(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_acl_permit(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_permit_params);// sugar@54
 void action_code_acl_alert(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_alert_params);// sugar@54
 void action_code_acl_drop(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_drop_params);// sugar@54
 void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void apply_table_tcp_acl(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_acl_permit(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_permit_params);// sugar@54
 void action_code_acl_alert(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_alert_params);// sugar@54
 void action_code_acl_drop(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_drop_params);// sugar@54
 void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void apply_table_udp_acl(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_acl_permit(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_permit_params);// sugar@54
 void action_code_acl_alert(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_alert_params);// sugar@54
 void action_code_acl_drop(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_drop_params);// sugar@54
 void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void apply_table_get_acl_features(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_acl_feature(packet_descriptor_t *pd, lookup_table_t **tables, struct action_acl_feature_params);// sugar@54
 void apply_table_nat_src(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_on_miss(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void action_code_rewrite_tcp_src(packet_descriptor_t *pd, lookup_table_t **tables, struct action_rewrite_tcp_src_params);// sugar@54
 void action_code_rewrite_udp_src(packet_descriptor_t *pd, lookup_table_t **tables, struct action_rewrite_udp_src_params);// sugar@54
 void apply_table_nat_dst(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_on_miss(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void action_code_rewrite_tcp_dst(packet_descriptor_t *pd, lookup_table_t **tables, struct action_rewrite_tcp_dst_params);// sugar@54
 void action_code_rewrite_udp_dst(packet_descriptor_t *pd, lookup_table_t **tables, struct action_rewrite_udp_dst_params);// sugar@54
 void apply_table_nat_twice(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_on_miss(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void action_code_rewrite_twice_tcp(packet_descriptor_t *pd, lookup_table_t **tables, struct action_rewrite_twice_tcp_params);// sugar@54
 void action_code_rewrite_twice_udp(packet_descriptor_t *pd, lookup_table_t **tables, struct action_rewrite_twice_udp_params);// sugar@54
 void apply_table_nat_flow(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void action_code_rewrite_twice_tcp(packet_descriptor_t *pd, lookup_table_t **tables, struct action_rewrite_twice_tcp_params);// sugar@54
 void action_code_rewrite_twice_udp(packet_descriptor_t *pd, lookup_table_t **tables, struct action_rewrite_twice_udp_params);// sugar@54
 void action_code_rewrite_tcp_dst(packet_descriptor_t *pd, lookup_table_t **tables, struct action_rewrite_tcp_dst_params);// sugar@54
 void action_code_rewrite_udp_dst(packet_descriptor_t *pd, lookup_table_t **tables, struct action_rewrite_udp_dst_params);// sugar@54
 void action_code_rewrite_tcp_src(packet_descriptor_t *pd, lookup_table_t **tables, struct action_rewrite_tcp_src_params);// sugar@54
 void action_code_rewrite_udp_src(packet_descriptor_t *pd, lookup_table_t **tables, struct action_rewrite_udp_src_params);// sugar@54
 void apply_table_nat_get_l4_infomation(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_get_tcp_information(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void action_code_get_udp_information(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void action_code_disable_nat(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void apply_table_ipsg_permit_special(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void action_code_ipsg_miss(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void apply_table_ipsg(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_on_miss(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void apply_table_storm_control_tbl(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void action_code_set_storm_control_meter(packet_descriptor_t *pd, lookup_table_t **tables, struct action_set_storm_control_meter_params);// sugar@54
 void apply_table_port_vlan_to_vrf(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_set_vrf(packet_descriptor_t *pd, lookup_table_t **tables, struct action_set_vrf_params);// sugar@54
 void apply_table_mac_learning(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_learning(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void action_code_nop(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void apply_table_routable(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_ucast(packet_descriptor_t *pd, lookup_table_t **tables, struct action_ucast_params);// sugar@54
 void action_code_mcast(packet_descriptor_t *pd, lookup_table_t **tables);// sugar@56
 void apply_table_unicast_routing(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_set_nhop(packet_descriptor_t *pd, lookup_table_t **tables, struct action_set_nhop_params);// sugar@54
 void action_code_set_nhop_with_vlan(packet_descriptor_t *pd, lookup_table_t **tables, struct action_set_nhop_with_vlan_params);// sugar@54
 void apply_table_switching(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_forwarding(packet_descriptor_t *pd, lookup_table_t **tables, struct action_forwarding_params);// sugar@54
 void apply_table_multicast_routing(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_set_multicast(packet_descriptor_t *pd, lookup_table_t **tables, struct action_set_multicast_params);// sugar@54
 void apply_table_igmp(packet_descriptor_t *pd, lookup_table_t** tables);// sugar@51
 void action_code_set_multicast(packet_descriptor_t *pd, lookup_table_t **tables, struct action_set_multicast_params);// sugar@54
 #endif// sugar@58
