 #include "dataplane.h"// sugar@18
 #include "actions.h"// sugar@19
 #include "data_plane_data.h"// sugar@20

 lookup_table_t table_config[NB_TABLES] = {// sugar@22
 {// sugar@25
  .name= "mac_acl",// sugar@26
  .id = TABLE_mac_acl,// sugar@27
  .type = LOOKUP_TERNARY,// sugar@28
  .key_size = 16,// sugar@29
  .val_size = sizeof(struct mac_acl_action),// sugar@30
  .min_size = 0, //None,// sugar@31
  .max_size = 255 //None// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "ipv4_acl",// sugar@26
  .id = TABLE_ipv4_acl,// sugar@27
  .type = LOOKUP_TERNARY,// sugar@28
  .key_size = 11,// sugar@29
  .val_size = sizeof(struct ipv4_acl_action),// sugar@30
  .min_size = 0, //None,// sugar@31
  .max_size = 255 //None// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "tcp_acl",// sugar@26
  .id = TABLE_tcp_acl,// sugar@27
  .type = LOOKUP_TERNARY,// sugar@28
  .key_size = 7,// sugar@29
  .val_size = sizeof(struct tcp_acl_action),// sugar@30
  .min_size = 0, //None,// sugar@31
  .max_size = 255 //None// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "udp_acl",// sugar@26
  .id = TABLE_udp_acl,// sugar@27
  .type = LOOKUP_TERNARY,// sugar@28
  .key_size = 6,// sugar@29
  .val_size = sizeof(struct udp_acl_action),// sugar@30
  .min_size = 0, //None,// sugar@31
  .max_size = 255 //None// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "get_acl_features",// sugar@26
  .id = TABLE_get_acl_features,// sugar@27
  .type = LOOKUP_TERNARY,// sugar@28
  .key_size = 10,// sugar@29
  .val_size = sizeof(struct get_acl_features_action),// sugar@30
  .min_size = 0, //None,// sugar@31
  .max_size = 255 //None// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "nat_src",// sugar@26
  .id = TABLE_nat_src,// sugar@27
  .type = LOOKUP_EXACT,// sugar@28
  .key_size = 9,// sugar@29
  .val_size = sizeof(struct nat_src_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "nat_dst",// sugar@26
  .id = TABLE_nat_dst,// sugar@27
  .type = LOOKUP_EXACT,// sugar@28
  .key_size = 9,// sugar@29
  .val_size = sizeof(struct nat_dst_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "nat_twice",// sugar@26
  .id = TABLE_nat_twice,// sugar@27
  .type = LOOKUP_EXACT,// sugar@28
  .key_size = 15,// sugar@29
  .val_size = sizeof(struct nat_twice_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "nat_flow",// sugar@26
  .id = TABLE_nat_flow,// sugar@27
  .type = LOOKUP_TERNARY,// sugar@28
  .key_size = 15,// sugar@29
  .val_size = sizeof(struct nat_flow_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "nat_get_l4_infomation",// sugar@26
  .id = TABLE_nat_get_l4_infomation,// sugar@27
  .type = LOOKUP_EXACT,// sugar@28
  .key_size = 1,// sugar@29
  .val_size = sizeof(struct nat_get_l4_infomation_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "ipsg_permit_special",// sugar@26
  .id = TABLE_ipsg_permit_special,// sugar@27
  .type = LOOKUP_TERNARY,// sugar@28
  .key_size = 17,// sugar@29
  .val_size = sizeof(struct ipsg_permit_special_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "ipsg",// sugar@26
  .id = TABLE_ipsg,// sugar@27
  .type = LOOKUP_EXACT,// sugar@28
  .key_size = 12,// sugar@29
  .val_size = sizeof(struct ipsg_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "storm_control_tbl",// sugar@26
  .id = TABLE_storm_control_tbl,// sugar@27
  .type = LOOKUP_TERNARY,// sugar@28
  .key_size = 14,// sugar@29
  .val_size = sizeof(struct storm_control_tbl_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "port_vlan_to_vrf",// sugar@26
  .id = TABLE_port_vlan_to_vrf,// sugar@27
  .type = LOOKUP_EXACT,// sugar@28
  .key_size = 3,// sugar@29
  .val_size = sizeof(struct port_vlan_to_vrf_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "mac_learning",// sugar@26
  .id = TABLE_mac_learning,// sugar@27
  .type = LOOKUP_EXACT,// sugar@28
  .key_size = 8,// sugar@29
  .val_size = sizeof(struct mac_learning_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "routable",// sugar@26
  .id = TABLE_routable,// sugar@27
  .type = LOOKUP_EXACT,// sugar@28
  .key_size = 16,// sugar@29
  .val_size = sizeof(struct routable_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "unicast_routing",// sugar@26
  .id = TABLE_unicast_routing,// sugar@27
  .type = LOOKUP_EXACT,// sugar@28
  .key_size = 6,// sugar@29
  .val_size = sizeof(struct unicast_routing_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "switching",// sugar@26
  .id = TABLE_switching,// sugar@27
  .type = LOOKUP_EXACT,// sugar@28
  .key_size = 10,// sugar@29
  .val_size = sizeof(struct switching_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "multicast_routing",// sugar@26
  .id = TABLE_multicast_routing,// sugar@27
  .type = LOOKUP_LPM,// sugar@28
  .key_size = 4,// sugar@29
  .val_size = sizeof(struct multicast_routing_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 {// sugar@25
  .name= "igmp",// sugar@26
  .id = TABLE_igmp,// sugar@27
  .type = LOOKUP_LPM,// sugar@28
  .key_size = 7,// sugar@29
  .val_size = sizeof(struct igmp_action),// sugar@30
  .min_size = 0, //1024,// sugar@31
  .max_size = 255 //1024// sugar@32
 },// sugar@33
 };// sugar@34
 counter_t counter_config[NB_COUNTERS] = {// sugar@36
 };// sugar@51
 p4_register_t register_config[NB_REGISTERS] = {// sugar@53
 };// sugar@66
