 #include <stdlib.h>// sugar@20
 #include <string.h>// sugar@21
 #include "dpdk_lib.h"// sugar@22
 #include "actions.h"// sugar@23
 
 extern void parse_packet(packet_descriptor_t* pd, lookup_table_t** tables);// sugar@25

 extern void increase_counter (int counterid, int index);// sugar@27

 void apply_table_mac_acl(packet_descriptor_t* pd, lookup_table_t** tables);// sugar@30
 void apply_table_ipv4_acl(packet_descriptor_t* pd, lookup_table_t** tables);// sugar@30
 void apply_table_tcp_acl(packet_descriptor_t* pd, lookup_table_t** tables);// sugar@30
 void apply_table_udp_acl(packet_descriptor_t* pd, lookup_table_t** tables);// sugar@30
 void apply_table_get_acl_features(packet_descriptor_t* pd, lookup_table_t** tables);// sugar@30
 void apply_table_mac_learning(packet_descriptor_t* pd, lookup_table_t** tables);// sugar@30
 void apply_table_routable(packet_descriptor_t* pd, lookup_table_t** tables);// sugar@30
 void apply_table_unicast_routing(packet_descriptor_t* pd, lookup_table_t** tables);// sugar@30
 void apply_table_switching(packet_descriptor_t* pd, lookup_table_t** tables);// sugar@30
 void apply_table_multicast_routing(packet_descriptor_t* pd, lookup_table_t** tables);// sugar@30
 void apply_table_igmp(packet_descriptor_t* pd, lookup_table_t** tables);// sugar@30

 uint8_t reverse_buffer[14];// sugar@34
 void table_mac_acl_key(packet_descriptor_t* pd, uint8_t* key) {// sugar@43
 EXTRACT_BYTEBUF(pd, field_instance_ethernet_src_mac, key)// sugar@53
 key += 6;// sugar@54
 EXTRACT_BYTEBUF(pd, field_instance_ethernet_dst_mac, key)// sugar@53
 key += 6;// sugar@54
 EXTRACT_INT32_BITS(pd, field_instance_ethernet_eth_type, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 }// sugar@62

 void table_ipv4_acl_key(packet_descriptor_t* pd, uint8_t* key) {// sugar@43
 EXTRACT_INT32_BITS(pd, field_instance_ip_src_addr, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 EXTRACT_INT32_BITS(pd, field_instance_ip_dst_addr, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 EXTRACT_INT32_BITS(pd, field_instance_ip_proto, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 }// sugar@62

 void table_tcp_acl_key(packet_descriptor_t* pd, uint8_t* key) {// sugar@43
 EXTRACT_INT32_BITS(pd, field_instance_tcp_src_port, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 EXTRACT_INT32_BITS(pd, field_instance_tcp_dst_port, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 EXTRACT_INT32_BITS(pd, field_instance_tcp_flags, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 }// sugar@62

 void table_udp_acl_key(packet_descriptor_t* pd, uint8_t* key) {// sugar@43
 EXTRACT_INT32_BITS(pd, field_instance_udp_src_port, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 EXTRACT_INT32_BITS(pd, field_instance_udp_dst_port, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 }// sugar@62

 void table_get_acl_features_key(packet_descriptor_t* pd, uint8_t* key) {// sugar@43
 EXTRACT_INT32_BITS(pd, field_instance_ip_src_addr, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 EXTRACT_INT32_BITS(pd, field_instance_ip_dst_addr, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 }// sugar@62

 void table_mac_learning_key(packet_descriptor_t* pd, uint8_t* key) {// sugar@43
 EXTRACT_BYTEBUF(pd, field_instance_ethernet_src_mac, key)// sugar@53
 key += 6;// sugar@54
 EXTRACT_INT32_BITS(pd, field_instance_vlan_vid, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 }// sugar@62

 void table_routable_key(packet_descriptor_t* pd, uint8_t* key) {// sugar@43
 EXTRACT_BYTEBUF(pd, field_instance_ethernet_src_mac, key)// sugar@53
 key += 6;// sugar@54
 EXTRACT_BYTEBUF(pd, field_instance_ethernet_dst_mac, key)// sugar@53
 key += 6;// sugar@54
 EXTRACT_INT32_BITS(pd, field_instance_vlan_vid, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 }// sugar@62

 void table_unicast_routing_key(packet_descriptor_t* pd, uint8_t* key) {// sugar@43
 EXTRACT_INT32_BITS(pd, field_instance_ip_dst_addr, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 }// sugar@62

 void table_switching_key(packet_descriptor_t* pd, uint8_t* key) {// sugar@43
 EXTRACT_BYTEBUF(pd, field_instance_ethernet_dst_mac, key)// sugar@53
 key += 6;// sugar@54
 EXTRACT_INT32_BITS(pd, field_instance_vlan_vid, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 }// sugar@62

 void table_multicast_routing_key(packet_descriptor_t* pd, uint8_t* key) {// sugar@43
 EXTRACT_INT32_BITS(pd, field_instance_ip_dst_addr, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 key -= 4;// sugar@58
 int c, d;// sugar@59
 for(c = 3, d = 0; c >= 0; c--, d++) *(reverse_buffer+d) = *(key+c);// sugar@60
 for(c = 0; c < 4; c++) *(key+c) = *(reverse_buffer+c);// sugar@61
 }// sugar@62

 void table_igmp_key(packet_descriptor_t* pd, uint8_t* key) {// sugar@43
 EXTRACT_INT32_BITS(pd, field_instance_vlan_vid, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 EXTRACT_INT32_BITS(pd, field_instance_standard_metadata_ingress_port, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 EXTRACT_INT32_BITS(pd, field_instance_ip_dst_addr, *(uint32_t*)key)// sugar@49
 key += sizeof(uint32_t);// sugar@50
 key -= 7;// sugar@58
 int c, d;// sugar@59
 for(c = 6, d = 0; c >= 0; c--, d++) *(reverse_buffer+d) = *(key+c);// sugar@60
 for(c = 0; c < 7; c++) *(key+c) = *(reverse_buffer+c);// sugar@61
 }// sugar@62

 void apply_table_mac_acl(packet_descriptor_t* pd, lookup_table_t** tables)// sugar@68
 {// sugar@69
     debug("  :::: EXECUTING TABLE mac_acl\n");// sugar@70
     uint8_t* key[14];// sugar@71
     table_mac_acl_key(pd, (uint8_t*)key);// sugar@72
     uint8_t* value = ternary_lookup(tables[TABLE_mac_acl], (uint8_t*)key);// sugar@73
     struct mac_acl_action* res = (struct mac_acl_action*)value;// sugar@74
     int index; (void)index;// sugar@75
     if(res != NULL) {// sugar@78
       index = *(int*)(value+sizeof(struct mac_acl_action));// sugar@79
     }// sugar@82
     if(res == NULL) {// sugar@85
       debug("    :: NO RESULT, NO DEFAULT ACTION.\n");// sugar@86
     } else {// sugar@87
       switch (res->action_id) {// sugar@88
         case action_acl_alert:// sugar@90
           debug("    :: EXECUTING ACTION acl_alert...\n");// sugar@91
           action_code_acl_alert(pd, tables, res->acl_alert_params);// sugar@93
           break;// sugar@96
         case action_acl_permit:// sugar@90
           debug("    :: EXECUTING ACTION acl_permit...\n");// sugar@91
           action_code_acl_permit(pd, tables, res->acl_permit_params);// sugar@93
           break;// sugar@96
         case action_acl_drop:// sugar@90
           debug("    :: EXECUTING ACTION acl_drop...\n");// sugar@91
           action_code_acl_drop(pd, tables, res->acl_drop_params);// sugar@93
           break;// sugar@96
         case action_nop:// sugar@90
           debug("    :: EXECUTING ACTION nop...\n");// sugar@91
           action_code_nop(pd, tables);// sugar@95
           break;// sugar@96
       }// sugar@97
     }// sugar@98
     if (res != NULL) {// sugar@110
       switch (res->action_id) {// sugar@111
         case action_acl_alert:// sugar@113
           if (pd->headers[header_instance_ip].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_ipv4_acl))==(1)) { return apply_table_ipv4_acl(pd, tables); } else { if (pd->headers[header_instance_tcp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_tcp_acl))==(1)) { return apply_table_tcp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if (pd->headers[header_instance_udp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_udp_acl))==(1)) { return apply_table_udp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } }// sugar@114
           break;// sugar@115
         case action_acl_permit:// sugar@113
           if (pd->headers[header_instance_ip].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_ipv4_acl))==(1)) { return apply_table_ipv4_acl(pd, tables); } else { if (pd->headers[header_instance_tcp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_tcp_acl))==(1)) { return apply_table_tcp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if (pd->headers[header_instance_udp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_udp_acl))==(1)) { return apply_table_udp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } }// sugar@114
           break;// sugar@115
         case action_acl_drop:// sugar@113
           if (pd->headers[header_instance_ip].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_ipv4_acl))==(1)) { return apply_table_ipv4_acl(pd, tables); } else { if (pd->headers[header_instance_tcp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_tcp_acl))==(1)) { return apply_table_tcp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if (pd->headers[header_instance_udp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_udp_acl))==(1)) { return apply_table_udp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } }// sugar@114
           break;// sugar@115
         case action_nop:// sugar@113
           if (pd->headers[header_instance_ip].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_ipv4_acl))==(1)) { return apply_table_ipv4_acl(pd, tables); } else { if (pd->headers[header_instance_tcp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_tcp_acl))==(1)) { return apply_table_tcp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if (pd->headers[header_instance_udp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_udp_acl))==(1)) { return apply_table_udp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } }// sugar@114
           break;// sugar@115
       }// sugar@116
     } else {// sugar@117
       debug("    :: IGNORING PACKET.\n");// sugar@118
       return;// sugar@119
     }// sugar@120
 }// sugar@121

 void apply_table_ipv4_acl(packet_descriptor_t* pd, lookup_table_t** tables)// sugar@68
 {// sugar@69
     debug("  :::: EXECUTING TABLE ipv4_acl\n");// sugar@70
     uint8_t* key[9];// sugar@71
     table_ipv4_acl_key(pd, (uint8_t*)key);// sugar@72
     uint8_t* value = ternary_lookup(tables[TABLE_ipv4_acl], (uint8_t*)key);// sugar@73
     struct ipv4_acl_action* res = (struct ipv4_acl_action*)value;// sugar@74
     int index; (void)index;// sugar@75
     if(res != NULL) {// sugar@78
       index = *(int*)(value+sizeof(struct ipv4_acl_action));// sugar@79
     }// sugar@82
     if(res == NULL) {// sugar@85
       debug("    :: NO RESULT, NO DEFAULT ACTION.\n");// sugar@86
     } else {// sugar@87
       switch (res->action_id) {// sugar@88
         case action_acl_permit:// sugar@90
           debug("    :: EXECUTING ACTION acl_permit...\n");// sugar@91
           action_code_acl_permit(pd, tables, res->acl_permit_params);// sugar@93
           break;// sugar@96
         case action_acl_alert:// sugar@90
           debug("    :: EXECUTING ACTION acl_alert...\n");// sugar@91
           action_code_acl_alert(pd, tables, res->acl_alert_params);// sugar@93
           break;// sugar@96
         case action_acl_drop:// sugar@90
           debug("    :: EXECUTING ACTION acl_drop...\n");// sugar@91
           action_code_acl_drop(pd, tables, res->acl_drop_params);// sugar@93
           break;// sugar@96
         case action_nop:// sugar@90
           debug("    :: EXECUTING ACTION nop...\n");// sugar@91
           action_code_nop(pd, tables);// sugar@95
           break;// sugar@96
       }// sugar@97
     }// sugar@98
     if (res != NULL) {// sugar@110
       switch (res->action_id) {// sugar@111
         case action_acl_permit:// sugar@113
           if (pd->headers[header_instance_tcp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_tcp_acl))==(1)) { return apply_table_tcp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if (pd->headers[header_instance_udp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_udp_acl))==(1)) { return apply_table_udp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } }// sugar@114
           break;// sugar@115
         case action_acl_alert:// sugar@113
           if (pd->headers[header_instance_tcp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_tcp_acl))==(1)) { return apply_table_tcp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if (pd->headers[header_instance_udp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_udp_acl))==(1)) { return apply_table_udp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } }// sugar@114
           break;// sugar@115
         case action_acl_drop:// sugar@113
           if (pd->headers[header_instance_tcp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_tcp_acl))==(1)) { return apply_table_tcp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if (pd->headers[header_instance_udp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_udp_acl))==(1)) { return apply_table_udp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } }// sugar@114
           break;// sugar@115
         case action_nop:// sugar@113
           if (pd->headers[header_instance_tcp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_tcp_acl))==(1)) { return apply_table_tcp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if (pd->headers[header_instance_udp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_udp_acl))==(1)) { return apply_table_udp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } }// sugar@114
           break;// sugar@115
       }// sugar@116
     } else {// sugar@117
       debug("    :: IGNORING PACKET.\n");// sugar@118
       return;// sugar@119
     }// sugar@120
 }// sugar@121

 void apply_table_tcp_acl(packet_descriptor_t* pd, lookup_table_t** tables)// sugar@68
 {// sugar@69
     debug("  :::: EXECUTING TABLE tcp_acl\n");// sugar@70
     uint8_t* key[5];// sugar@71
     table_tcp_acl_key(pd, (uint8_t*)key);// sugar@72
     uint8_t* value = ternary_lookup(tables[TABLE_tcp_acl], (uint8_t*)key);// sugar@73
     struct tcp_acl_action* res = (struct tcp_acl_action*)value;// sugar@74
     int index; (void)index;// sugar@75
     if(res != NULL) {// sugar@78
       index = *(int*)(value+sizeof(struct tcp_acl_action));// sugar@79
     }// sugar@82
     if(res == NULL) {// sugar@85
       debug("    :: NO RESULT, NO DEFAULT ACTION.\n");// sugar@86
     } else {// sugar@87
       switch (res->action_id) {// sugar@88
         case action_acl_permit:// sugar@90
           debug("    :: EXECUTING ACTION acl_permit...\n");// sugar@91
           action_code_acl_permit(pd, tables, res->acl_permit_params);// sugar@93
           break;// sugar@96
         case action_acl_alert:// sugar@90
           debug("    :: EXECUTING ACTION acl_alert...\n");// sugar@91
           action_code_acl_alert(pd, tables, res->acl_alert_params);// sugar@93
           break;// sugar@96
         case action_acl_drop:// sugar@90
           debug("    :: EXECUTING ACTION acl_drop...\n");// sugar@91
           action_code_acl_drop(pd, tables, res->acl_drop_params);// sugar@93
           break;// sugar@96
         case action_nop:// sugar@90
           debug("    :: EXECUTING ACTION nop...\n");// sugar@91
           action_code_nop(pd, tables);// sugar@95
           break;// sugar@96
       }// sugar@97
     }// sugar@98
     if (res != NULL) {// sugar@110
       switch (res->action_id) {// sugar@111
         case action_acl_permit:// sugar@113
           if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  }// sugar@114
           break;// sugar@115
         case action_acl_alert:// sugar@113
           if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  }// sugar@114
           break;// sugar@115
         case action_acl_drop:// sugar@113
           if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  }// sugar@114
           break;// sugar@115
         case action_nop:// sugar@113
           if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  }// sugar@114
           break;// sugar@115
       }// sugar@116
     } else {// sugar@117
       debug("    :: IGNORING PACKET.\n");// sugar@118
       return;// sugar@119
     }// sugar@120
 }// sugar@121

 void apply_table_udp_acl(packet_descriptor_t* pd, lookup_table_t** tables)// sugar@68
 {// sugar@69
     debug("  :::: EXECUTING TABLE udp_acl\n");// sugar@70
     uint8_t* key[4];// sugar@71
     table_udp_acl_key(pd, (uint8_t*)key);// sugar@72
     uint8_t* value = ternary_lookup(tables[TABLE_udp_acl], (uint8_t*)key);// sugar@73
     struct udp_acl_action* res = (struct udp_acl_action*)value;// sugar@74
     int index; (void)index;// sugar@75
     if(res != NULL) {// sugar@78
       index = *(int*)(value+sizeof(struct udp_acl_action));// sugar@79
     }// sugar@82
     if(res == NULL) {// sugar@85
       debug("    :: NO RESULT, NO DEFAULT ACTION.\n");// sugar@86
     } else {// sugar@87
       switch (res->action_id) {// sugar@88
         case action_acl_permit:// sugar@90
           debug("    :: EXECUTING ACTION acl_permit...\n");// sugar@91
           action_code_acl_permit(pd, tables, res->acl_permit_params);// sugar@93
           break;// sugar@96
         case action_acl_alert:// sugar@90
           debug("    :: EXECUTING ACTION acl_alert...\n");// sugar@91
           action_code_acl_alert(pd, tables, res->acl_alert_params);// sugar@93
           break;// sugar@96
         case action_acl_drop:// sugar@90
           debug("    :: EXECUTING ACTION acl_drop...\n");// sugar@91
           action_code_acl_drop(pd, tables, res->acl_drop_params);// sugar@93
           break;// sugar@96
         case action_nop:// sugar@90
           debug("    :: EXECUTING ACTION nop...\n");// sugar@91
           action_code_nop(pd, tables);// sugar@95
           break;// sugar@96
       }// sugar@97
     }// sugar@98
     if (res != NULL) {// sugar@110
       switch (res->action_id) {// sugar@111
         case action_acl_permit:// sugar@113
           if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  }// sugar@114
           break;// sugar@115
         case action_acl_alert:// sugar@113
           if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  }// sugar@114
           break;// sugar@115
         case action_acl_drop:// sugar@113
           if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  }// sugar@114
           break;// sugar@115
         case action_nop:// sugar@113
           if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  }// sugar@114
           break;// sugar@115
       }// sugar@116
     } else {// sugar@117
       debug("    :: IGNORING PACKET.\n");// sugar@118
       return;// sugar@119
     }// sugar@120
 }// sugar@121

 void apply_table_get_acl_features(packet_descriptor_t* pd, lookup_table_t** tables)// sugar@68
 {// sugar@69
     debug("  :::: EXECUTING TABLE get_acl_features\n");// sugar@70
     uint8_t* key[8];// sugar@71
     table_get_acl_features_key(pd, (uint8_t*)key);// sugar@72
     uint8_t* value = ternary_lookup(tables[TABLE_get_acl_features], (uint8_t*)key);// sugar@73
     struct get_acl_features_action* res = (struct get_acl_features_action*)value;// sugar@74
     int index; (void)index;// sugar@75
     if(res != NULL) {// sugar@78
       index = *(int*)(value+sizeof(struct get_acl_features_action));// sugar@79
     }// sugar@82
     if(res == NULL) {// sugar@85
       debug("    :: NO RESULT, NO DEFAULT ACTION.\n");// sugar@86
     } else {// sugar@87
       switch (res->action_id) {// sugar@88
         case action_acl_feature:// sugar@90
           debug("    :: EXECUTING ACTION acl_feature...\n");// sugar@91
           action_code_acl_feature(pd, tables, res->acl_feature_params);// sugar@93
           break;// sugar@96
       }// sugar@97
     }// sugar@98
     if (res != NULL) {// sugar@110
       switch (res->action_id) {// sugar@111
         case action_acl_feature:// sugar@113
           if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_mac_acl))==(1)) { return apply_table_mac_acl(pd, tables); } else { if (pd->headers[header_instance_ip].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_ipv4_acl))==(1)) { return apply_table_ipv4_acl(pd, tables); } else { if (pd->headers[header_instance_tcp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_tcp_acl))==(1)) { return apply_table_tcp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if (pd->headers[header_instance_udp].pointer != NULL) { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_enable_udp_acl))==(1)) { return apply_table_udp_acl(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } } } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } }// sugar@114
           break;// sugar@115
       }// sugar@116
     } else {// sugar@117
       debug("    :: IGNORING PACKET.\n");// sugar@118
       return;// sugar@119
     }// sugar@120
 }// sugar@121

 void apply_table_mac_learning(packet_descriptor_t* pd, lookup_table_t** tables)// sugar@68
 {// sugar@69
     debug("  :::: EXECUTING TABLE mac_learning\n");// sugar@70
     uint8_t* key[8];// sugar@71
     table_mac_learning_key(pd, (uint8_t*)key);// sugar@72
     uint8_t* value = exact_lookup(tables[TABLE_mac_learning], (uint8_t*)key);// sugar@73
     struct mac_learning_action* res = (struct mac_learning_action*)value;// sugar@74
     int index; (void)index;// sugar@75
     if(res != NULL) {// sugar@78
       index = *(int*)(value+sizeof(struct mac_learning_action));// sugar@79
     }// sugar@82
     if(res == NULL) {// sugar@85
       debug("    :: NO RESULT, NO DEFAULT ACTION.\n");// sugar@86
     } else {// sugar@87
       switch (res->action_id) {// sugar@88
         case action_learning:// sugar@90
           debug("    :: EXECUTING ACTION learning...\n");// sugar@91
           action_code_learning(pd, tables);// sugar@95
           break;// sugar@96
         case action_nop:// sugar@90
           debug("    :: EXECUTING ACTION nop...\n");// sugar@91
           action_code_nop(pd, tables);// sugar@95
           break;// sugar@96
       }// sugar@97
     }// sugar@98
     if (res != NULL) {// sugar@110
       switch (res->action_id) {// sugar@111
         case action_learning:// sugar@113
           return apply_table_routable(pd, tables);// sugar@114
           break;// sugar@115
         case action_nop:// sugar@113
           return apply_table_routable(pd, tables);// sugar@114
           break;// sugar@115
       }// sugar@116
     } else {// sugar@117
       debug("    :: IGNORING PACKET.\n");// sugar@118
       return;// sugar@119
     }// sugar@120
 }// sugar@121

 void apply_table_routable(packet_descriptor_t* pd, lookup_table_t** tables)// sugar@68
 {// sugar@69
     debug("  :::: EXECUTING TABLE routable\n");// sugar@70
     uint8_t* key[14];// sugar@71
     table_routable_key(pd, (uint8_t*)key);// sugar@72
     uint8_t* value = exact_lookup(tables[TABLE_routable], (uint8_t*)key);// sugar@73
     struct routable_action* res = (struct routable_action*)value;// sugar@74
     int index; (void)index;// sugar@75
     if(res != NULL) {// sugar@78
       index = *(int*)(value+sizeof(struct routable_action));// sugar@79
     }// sugar@82
     if(res == NULL) {// sugar@85
       debug("    :: NO RESULT, NO DEFAULT ACTION.\n");// sugar@86
     } else {// sugar@87
       switch (res->action_id) {// sugar@88
         case action_ucast:// sugar@90
           debug("    :: EXECUTING ACTION ucast...\n");// sugar@91
           action_code_ucast(pd, tables, res->ucast_params);// sugar@93
           break;// sugar@96
         case action_mcast:// sugar@90
           debug("    :: EXECUTING ACTION mcast...\n");// sugar@91
           action_code_mcast(pd, tables);// sugar@95
           break;// sugar@96
       }// sugar@97
     }// sugar@98
     if (res != NULL) {// sugar@110
       switch (res->action_id) {// sugar@111
         case action_ucast:// sugar@113
           if ((GET_INT32_AUTO(pd, field_instance_route_metadata_route))==(1)) { return apply_table_multicast_routing(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_route_metadata_route))==(2)) { if ((GET_INT32_AUTO(pd, field_instance_route_metadata_lan))!=(1)) { return apply_table_unicast_routing(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else {  } }// sugar@114
           break;// sugar@115
         case action_mcast:// sugar@113
           if ((GET_INT32_AUTO(pd, field_instance_route_metadata_route))==(1)) { return apply_table_multicast_routing(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_route_metadata_route))==(2)) { if ((GET_INT32_AUTO(pd, field_instance_route_metadata_lan))!=(1)) { return apply_table_unicast_routing(pd, tables); } else { if ((GET_INT32_AUTO(pd, field_instance_acl_metadata_acl_op))==(0)) { return apply_table_switching(pd, tables); } else {  } } } else {  } }// sugar@114
           break;// sugar@115
       }// sugar@116
     } else {// sugar@117
       debug("    :: IGNORING PACKET.\n");// sugar@118
       return;// sugar@119
     }// sugar@120
 }// sugar@121

 void apply_table_unicast_routing(packet_descriptor_t* pd, lookup_table_t** tables)// sugar@68
 {// sugar@69
     debug("  :::: EXECUTING TABLE unicast_routing\n");// sugar@70
     uint8_t* key[4];// sugar@71
     table_unicast_routing_key(pd, (uint8_t*)key);// sugar@72
     uint8_t* value = exact_lookup(tables[TABLE_unicast_routing], (uint8_t*)key);// sugar@73
     struct unicast_routing_action* res = (struct unicast_routing_action*)value;// sugar@74
     int index; (void)index;// sugar@75
     if(res != NULL) {// sugar@78
       index = *(int*)(value+sizeof(struct unicast_routing_action));// sugar@79
     }// sugar@82
     if(res == NULL) {// sugar@85
       debug("    :: NO RESULT, NO DEFAULT ACTION.\n");// sugar@86
     } else {// sugar@87
       switch (res->action_id) {// sugar@88
         case action_set_nhop:// sugar@90
           debug("    :: EXECUTING ACTION set_nhop...\n");// sugar@91
           action_code_set_nhop(pd, tables, res->set_nhop_params);// sugar@93
           break;// sugar@96
         case action_set_nhop_with_vlan:// sugar@90
           debug("    :: EXECUTING ACTION set_nhop_with_vlan...\n");// sugar@91
           action_code_set_nhop_with_vlan(pd, tables, res->set_nhop_with_vlan_params);// sugar@93
           break;// sugar@96
       }// sugar@97
     }// sugar@98
     if (res != NULL) {// sugar@110
       switch (res->action_id) {// sugar@111
         case action_set_nhop:// sugar@113
           return apply_table_get_acl_features(pd, tables);// sugar@114
           break;// sugar@115
         case action_set_nhop_with_vlan:// sugar@113
           return apply_table_get_acl_features(pd, tables);// sugar@114
           break;// sugar@115
       }// sugar@116
     } else {// sugar@117
       debug("    :: IGNORING PACKET.\n");// sugar@118
       return;// sugar@119
     }// sugar@120
 }// sugar@121

 void apply_table_switching(packet_descriptor_t* pd, lookup_table_t** tables)// sugar@68
 {// sugar@69
     debug("  :::: EXECUTING TABLE switching\n");// sugar@70
     uint8_t* key[8];// sugar@71
     table_switching_key(pd, (uint8_t*)key);// sugar@72
     uint8_t* value = exact_lookup(tables[TABLE_switching], (uint8_t*)key);// sugar@73
     struct switching_action* res = (struct switching_action*)value;// sugar@74
     int index; (void)index;// sugar@75
     if(res != NULL) {// sugar@78
       index = *(int*)(value+sizeof(struct switching_action));// sugar@79
     }// sugar@82
     if(res == NULL) {// sugar@85
       debug("    :: NO RESULT, NO DEFAULT ACTION.\n");// sugar@86
     } else {// sugar@87
       switch (res->action_id) {// sugar@88
         case action_forwarding:// sugar@90
           debug("    :: EXECUTING ACTION forwarding...\n");// sugar@91
           action_code_forwarding(pd, tables, res->forwarding_params);// sugar@93
           break;// sugar@96
       }// sugar@97
     }// sugar@98
     if (res != NULL) {// sugar@110
       switch (res->action_id) {// sugar@111
         case action_forwarding:// sugar@113
           // sugar@114
           break;// sugar@115
       }// sugar@116
     } else {// sugar@117
       debug("    :: IGNORING PACKET.\n");// sugar@118
       return;// sugar@119
     }// sugar@120
 }// sugar@121

 void apply_table_multicast_routing(packet_descriptor_t* pd, lookup_table_t** tables)// sugar@68
 {// sugar@69
     debug("  :::: EXECUTING TABLE multicast_routing\n");// sugar@70
     uint8_t* key[4];// sugar@71
     table_multicast_routing_key(pd, (uint8_t*)key);// sugar@72
     uint8_t* value = lpm_lookup(tables[TABLE_multicast_routing], (uint8_t*)key);// sugar@73
     struct multicast_routing_action* res = (struct multicast_routing_action*)value;// sugar@74
     int index; (void)index;// sugar@75
     if(res != NULL) {// sugar@78
       index = *(int*)(value+sizeof(struct multicast_routing_action));// sugar@79
     }// sugar@82
     if(res == NULL) {// sugar@85
       debug("    :: NO RESULT, NO DEFAULT ACTION.\n");// sugar@86
     } else {// sugar@87
       switch (res->action_id) {// sugar@88
         case action_set_multicast:// sugar@90
           debug("    :: EXECUTING ACTION set_multicast...\n");// sugar@91
           action_code_set_multicast(pd, tables, res->set_multicast_params);// sugar@93
           break;// sugar@96
       }// sugar@97
     }// sugar@98
     if (res != NULL) {// sugar@110
       switch (res->action_id) {// sugar@111
         case action_set_multicast:// sugar@113
           return apply_table_igmp(pd, tables);// sugar@114
           break;// sugar@115
       }// sugar@116
     } else {// sugar@117
       debug("    :: IGNORING PACKET.\n");// sugar@118
       return;// sugar@119
     }// sugar@120
 }// sugar@121

 void apply_table_igmp(packet_descriptor_t* pd, lookup_table_t** tables)// sugar@68
 {// sugar@69
     debug("  :::: EXECUTING TABLE igmp\n");// sugar@70
     uint8_t* key[7];// sugar@71
     table_igmp_key(pd, (uint8_t*)key);// sugar@72
     uint8_t* value = lpm_lookup(tables[TABLE_igmp], (uint8_t*)key);// sugar@73
     struct igmp_action* res = (struct igmp_action*)value;// sugar@74
     int index; (void)index;// sugar@75
     if(res != NULL) {// sugar@78
       index = *(int*)(value+sizeof(struct igmp_action));// sugar@79
     }// sugar@82
     if(res == NULL) {// sugar@85
       debug("    :: NO RESULT, NO DEFAULT ACTION.\n");// sugar@86
     } else {// sugar@87
       switch (res->action_id) {// sugar@88
         case action_set_multicast:// sugar@90
           debug("    :: EXECUTING ACTION set_multicast...\n");// sugar@91
           action_code_set_multicast(pd, tables, res->set_multicast_params);// sugar@93
           break;// sugar@96
       }// sugar@97
     }// sugar@98
     if (res != NULL) {// sugar@110
       switch (res->action_id) {// sugar@111
         case action_set_multicast:// sugar@113
           // sugar@114
           break;// sugar@115
       }// sugar@116
     } else {// sugar@117
       debug("    :: IGNORING PACKET.\n");// sugar@118
       return;// sugar@119
     }// sugar@120
 }// sugar@121


 uint16_t csum16_add(uint16_t num1, uint16_t num2) {// sugar@125
     if(num1 == 0) return num2;// sugar@126
     uint32_t tmp_num = num1 + num2;// sugar@127
     while(tmp_num > 0xffff)// sugar@128
         tmp_num = ((tmp_num & 0xffff0000) >> 16) + (tmp_num & 0xffff);// sugar@129
     return (uint16_t)tmp_num;// sugar@130
 }// sugar@131

 void reset_headers(packet_descriptor_t* packet_desc) {// sugar@229
 memset(packet_desc->headers[header_instance_standard_metadata].pointer, 0, header_info(header_instance_standard_metadata).bytewidth * sizeof(uint8_t));// sugar@233
 packet_desc->headers[header_instance_ethernet].pointer = NULL;// sugar@235
 packet_desc->headers[header_instance_ip].pointer = NULL;// sugar@235
 packet_desc->headers[header_instance_tcp].pointer = NULL;// sugar@235
 packet_desc->headers[header_instance_arp].pointer = NULL;// sugar@235
 packet_desc->headers[header_instance_icmp].pointer = NULL;// sugar@235
 packet_desc->headers[header_instance_udp].pointer = NULL;// sugar@235
 packet_desc->headers[header_instance_vlan].pointer = NULL;// sugar@235
 memset(packet_desc->headers[header_instance_acl_metadata].pointer, 0, header_info(header_instance_acl_metadata).bytewidth * sizeof(uint8_t));// sugar@233
 memset(packet_desc->headers[header_instance_intrinsic_metadata].pointer, 0, header_info(header_instance_intrinsic_metadata).bytewidth * sizeof(uint8_t));// sugar@233
 memset(packet_desc->headers[header_instance_route_metadata].pointer, 0, header_info(header_instance_route_metadata).bytewidth * sizeof(uint8_t));// sugar@233
 }// sugar@236
 void init_headers(packet_descriptor_t* packet_desc) {// sugar@237
 packet_desc->headers[header_instance_standard_metadata] = (header_descriptor_t) { .type = header_instance_standard_metadata, .length = header_info(header_instance_standard_metadata).bytewidth,// sugar@241
                               .pointer = malloc(header_info(header_instance_standard_metadata).bytewidth * sizeof(uint8_t)),// sugar@242
                               .var_width_field_bitwidth = 0 };// sugar@243
 packet_desc->headers[header_instance_ethernet] = (header_descriptor_t) { .type = header_instance_ethernet, .length = header_info(header_instance_ethernet).bytewidth, .pointer = NULL,// sugar@245
                               .var_width_field_bitwidth = 0 };// sugar@246
 packet_desc->headers[header_instance_ip] = (header_descriptor_t) { .type = header_instance_ip, .length = header_info(header_instance_ip).bytewidth, .pointer = NULL,// sugar@245
                               .var_width_field_bitwidth = 0 };// sugar@246
 packet_desc->headers[header_instance_tcp] = (header_descriptor_t) { .type = header_instance_tcp, .length = header_info(header_instance_tcp).bytewidth, .pointer = NULL,// sugar@245
                               .var_width_field_bitwidth = 0 };// sugar@246
 packet_desc->headers[header_instance_arp] = (header_descriptor_t) { .type = header_instance_arp, .length = header_info(header_instance_arp).bytewidth, .pointer = NULL,// sugar@245
                               .var_width_field_bitwidth = 0 };// sugar@246
 packet_desc->headers[header_instance_icmp] = (header_descriptor_t) { .type = header_instance_icmp, .length = header_info(header_instance_icmp).bytewidth, .pointer = NULL,// sugar@245
                               .var_width_field_bitwidth = 0 };// sugar@246
 packet_desc->headers[header_instance_udp] = (header_descriptor_t) { .type = header_instance_udp, .length = header_info(header_instance_udp).bytewidth, .pointer = NULL,// sugar@245
                               .var_width_field_bitwidth = 0 };// sugar@246
 packet_desc->headers[header_instance_vlan] = (header_descriptor_t) { .type = header_instance_vlan, .length = header_info(header_instance_vlan).bytewidth, .pointer = NULL,// sugar@245
                               .var_width_field_bitwidth = 0 };// sugar@246
 packet_desc->headers[header_instance_acl_metadata] = (header_descriptor_t) { .type = header_instance_acl_metadata, .length = header_info(header_instance_acl_metadata).bytewidth,// sugar@241
                               .pointer = malloc(header_info(header_instance_acl_metadata).bytewidth * sizeof(uint8_t)),// sugar@242
                               .var_width_field_bitwidth = 0 };// sugar@243
 packet_desc->headers[header_instance_intrinsic_metadata] = (header_descriptor_t) { .type = header_instance_intrinsic_metadata, .length = header_info(header_instance_intrinsic_metadata).bytewidth,// sugar@241
                               .pointer = malloc(header_info(header_instance_intrinsic_metadata).bytewidth * sizeof(uint8_t)),// sugar@242
                               .var_width_field_bitwidth = 0 };// sugar@243
 packet_desc->headers[header_instance_route_metadata] = (header_descriptor_t) { .type = header_instance_route_metadata, .length = header_info(header_instance_route_metadata).bytewidth,// sugar@241
                               .pointer = malloc(header_info(header_instance_route_metadata).bytewidth * sizeof(uint8_t)),// sugar@242
                               .var_width_field_bitwidth = 0 };// sugar@243
 }// sugar@247


 void init_keyless_tables() {// sugar@255
 }// sugar@263

 void init_dataplane(packet_descriptor_t* pd, lookup_table_t** tables) {// sugar@265
     init_headers(pd);// sugar@266
     reset_headers(pd);// sugar@267
     init_keyless_tables();// sugar@268
     pd->dropped=0;// sugar@269
 }// sugar@270

 void update_packet(packet_descriptor_t* pd) {// sugar@273
     uint32_t value32, res32;// sugar@274
     (void)value32, (void)res32;// sugar@275
 if(pd->fields.attr_field_instance_vlan_vid == MODIFIED) {// sugar@280
     value32 = pd->fields.field_instance_vlan_vid;// sugar@281
     MODIFY_INT32_INT32_AUTO(pd, field_instance_vlan_vid, value32)// sugar@282
 }// sugar@283

 }// sugar@296


 int verify_packet(packet_descriptor_t* pd) {// sugar@300
   uint32_t value32;// sugar@301
   return 0;// sugar@317
 }// sugar@318

 
 void handle_packet(packet_descriptor_t* pd, lookup_table_t** tables)// sugar@322
 {// sugar@323
     int value32;// sugar@324
     EXTRACT_INT32_BITS(pd, field_instance_standard_metadata_ingress_port, value32)// sugar@325
     debug("### HANDLING PACKET ARRIVING AT PORT %" PRIu32 "...\n", value32);// sugar@326
     parse_packet(pd, tables);// sugar@327
     update_packet(pd);// sugar@328
 }// sugar@329
