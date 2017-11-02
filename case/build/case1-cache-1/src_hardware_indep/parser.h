 #ifndef __HEADER_INFO_H__// sugar@95
 #define __HEADER_INFO_H__// sugar@96

 #define MODIFIED 1// sugar@98

 typedef struct parsed_fields_s {// sugar@100
 uint32_t field_instance_vlan_vid;// sugar@104
 uint8_t attr_field_instance_vlan_vid;// sugar@105
 } parsed_fields_t;// sugar@106
 
 #define HEADER_INSTANCE_COUNT 11// sugar@108
 #define HEADER_STACK_COUNT 0// sugar@109
 #define FIELD_INSTANCE_COUNT 70// sugar@110
 
 enum header_stack_e {
  header_stack_
};

// sugar@112
 enum header_instance_e {
  header_instance_standard_metadata,
  header_instance_ethernet,
  header_instance_ip,
  header_instance_tcp,
  header_instance_arp,
  header_instance_icmp,
  header_instance_udp,
  header_instance_vlan,
  header_instance_acl_metadata,
  header_instance_intrinsic_metadata,
  header_instance_route_metadata
};

// sugar@113
 enum field_instance_e {
  field_instance_standard_metadata_ingress_port,
  field_instance_standard_metadata_packet_length,
  field_instance_standard_metadata_egress_spec,
  field_instance_standard_metadata_egress_port,
  field_instance_standard_metadata_egress_instance,
  field_instance_standard_metadata_instance_type,
  field_instance_standard_metadata_clone_spec,
  field_instance_standard_metadata__padding,
  field_instance_ethernet_dst_mac,
  field_instance_ethernet_src_mac,
  field_instance_ethernet_eth_type,
  field_instance_ip_ver,
  field_instance_ip_ihl,
  field_instance_ip_diff_serv,
  field_instance_ip_tot_len,
  field_instance_ip_id,
  field_instance_ip_flags,
  field_instance_ip_frag_offset,
  field_instance_ip_ttl,
  field_instance_ip_proto,
  field_instance_ip_checksum,
  field_instance_ip_src_addr,
  field_instance_ip_dst_addr,
  field_instance_tcp_src_port,
  field_instance_tcp_dst_port,
  field_instance_tcp_seq_no,
  field_instance_tcp_ack_no,
  field_instance_tcp_offset,
  field_instance_tcp_res,
  field_instance_tcp_flags,
  field_instance_tcp_window,
  field_instance_tcp_checksum,
  field_instance_tcp_urgent_ptr,
  field_instance_arp_hw_type,
  field_instance_arp_proto_type,
  field_instance_arp_hw_addr_len,
  field_instance_arp_proto_addr_len,
  field_instance_arp_opcode,
  field_instance_arp_src_hw_addr,
  field_instance_arp_src_proto_addr,
  field_instance_arp_dst_hw_mac,
  field_instance_arp_dst_proto_addr,
  field_instance_icmp_msg_type,
  field_instance_icmp_code,
  field_instance_icmp_checksum,
  field_instance_udp_src_port,
  field_instance_udp_dst_port,
  field_instance_udp_length_,
  field_instance_udp_checksum,
  field_instance_vlan_pcp,
  field_instance_vlan_cfi,
  field_instance_vlan_vid,
  field_instance_vlan_eth_type,
  field_instance_acl_metadata_enable_mac_acl,
  field_instance_acl_metadata_enable_vlan_acl,
  field_instance_acl_metadata_enable_ipv4_acl,
  field_instance_acl_metadata_enable_icmp_acl,
  field_instance_acl_metadata_enable_tcp_acl,
  field_instance_acl_metadata_enable_udp_acl,
  field_instance_acl_metadata_padding,
  field_instance_acl_metadata_acl_op,
  field_instance_acl_metadata_acl_reason,
  field_instance_intrinsic_metadata_ingress_global_timestamp,
  field_instance_intrinsic_metadata_lf_field_list,
  field_instance_intrinsic_metadata_mcast_grp,
  field_instance_intrinsic_metadata_egress_rid,
  field_instance_intrinsic_metadata_resubmit_flag,
  field_instance_intrinsic_metadata_recirculate_flag,
  field_instance_route_metadata_route,
  field_instance_route_metadata_lan
};

// sugar@114
 typedef enum header_instance_e header_instance_t;// sugar@115
 typedef enum field_instance_e field_instance_t;// sugar@116
 static const int header_instance_byte_width[HEADER_INSTANCE_COUNT] = {
  20 /* header_instance_standard_metadata */,
  14 /* header_instance_ethernet */,
  20 /* header_instance_ip */,
  20 /* header_instance_tcp */,
  28 /* header_instance_arp */,
  4 /* header_instance_icmp */,
  8 /* header_instance_udp */,
  4 /* header_instance_vlan */,
  3 /* header_instance_acl_metadata */,
  13 /* header_instance_intrinsic_metadata */,
  1 /* header_instance_route_metadata */
};

// sugar@117
 static const int header_instance_is_metadata[HEADER_INSTANCE_COUNT] = {
  1 /* header_instance_standard_metadata */,
  0 /* header_instance_ethernet */,
  0 /* header_instance_ip */,
  0 /* header_instance_tcp */,
  0 /* header_instance_arp */,
  0 /* header_instance_icmp */,
  0 /* header_instance_udp */,
  0 /* header_instance_vlan */,
  1 /* header_instance_acl_metadata */,
  1 /* header_instance_intrinsic_metadata */,
  1 /* header_instance_route_metadata */
};

// sugar@118
 static const int header_instance_var_width_field[HEADER_INSTANCE_COUNT] = {
  -1 /* fixed-width header */ /* header_instance_standard_metadata */,
  -1 /* fixed-width header */ /* header_instance_ethernet */,
  -1 /* fixed-width header */ /* header_instance_ip */,
  -1 /* fixed-width header */ /* header_instance_tcp */,
  -1 /* fixed-width header */ /* header_instance_arp */,
  -1 /* fixed-width header */ /* header_instance_icmp */,
  -1 /* fixed-width header */ /* header_instance_udp */,
  -1 /* fixed-width header */ /* header_instance_vlan */,
  -1 /* fixed-width header */ /* header_instance_acl_metadata */,
  -1 /* fixed-width header */ /* header_instance_intrinsic_metadata */,
  -1 /* fixed-width header */ /* header_instance_route_metadata */
};

// sugar@119
 static const int field_instance_bit_width[FIELD_INSTANCE_COUNT] = {
  9 /* field_instance_standard_metadata_ingress_port */,
  32 /* field_instance_standard_metadata_packet_length */,
  9 /* field_instance_standard_metadata_egress_spec */,
  9 /* field_instance_standard_metadata_egress_port */,
  32 /* field_instance_standard_metadata_egress_instance */,
  32 /* field_instance_standard_metadata_instance_type */,
  32 /* field_instance_standard_metadata_clone_spec */,
  5 /* field_instance_standard_metadata__padding */,
  48 /* field_instance_ethernet_dst_mac */,
  48 /* field_instance_ethernet_src_mac */,
  16 /* field_instance_ethernet_eth_type */,
  4 /* field_instance_ip_ver */,
  4 /* field_instance_ip_ihl */,
  8 /* field_instance_ip_diff_serv */,
  16 /* field_instance_ip_tot_len */,
  16 /* field_instance_ip_id */,
  3 /* field_instance_ip_flags */,
  13 /* field_instance_ip_frag_offset */,
  8 /* field_instance_ip_ttl */,
  8 /* field_instance_ip_proto */,
  16 /* field_instance_ip_checksum */,
  32 /* field_instance_ip_src_addr */,
  32 /* field_instance_ip_dst_addr */,
  16 /* field_instance_tcp_src_port */,
  16 /* field_instance_tcp_dst_port */,
  32 /* field_instance_tcp_seq_no */,
  32 /* field_instance_tcp_ack_no */,
  4 /* field_instance_tcp_offset */,
  4 /* field_instance_tcp_res */,
  8 /* field_instance_tcp_flags */,
  16 /* field_instance_tcp_window */,
  16 /* field_instance_tcp_checksum */,
  16 /* field_instance_tcp_urgent_ptr */,
  16 /* field_instance_arp_hw_type */,
  16 /* field_instance_arp_proto_type */,
  8 /* field_instance_arp_hw_addr_len */,
  8 /* field_instance_arp_proto_addr_len */,
  16 /* field_instance_arp_opcode */,
  48 /* field_instance_arp_src_hw_addr */,
  32 /* field_instance_arp_src_proto_addr */,
  48 /* field_instance_arp_dst_hw_mac */,
  32 /* field_instance_arp_dst_proto_addr */,
  8 /* field_instance_icmp_msg_type */,
  8 /* field_instance_icmp_code */,
  16 /* field_instance_icmp_checksum */,
  16 /* field_instance_udp_src_port */,
  16 /* field_instance_udp_dst_port */,
  16 /* field_instance_udp_length_ */,
  16 /* field_instance_udp_checksum */,
  3 /* field_instance_vlan_pcp */,
  1 /* field_instance_vlan_cfi */,
  12 /* field_instance_vlan_vid */,
  16 /* field_instance_vlan_eth_type */,
  1 /* field_instance_acl_metadata_enable_mac_acl */,
  1 /* field_instance_acl_metadata_enable_vlan_acl */,
  1 /* field_instance_acl_metadata_enable_ipv4_acl */,
  1 /* field_instance_acl_metadata_enable_icmp_acl */,
  1 /* field_instance_acl_metadata_enable_tcp_acl */,
  1 /* field_instance_acl_metadata_enable_udp_acl */,
  2 /* field_instance_acl_metadata_padding */,
  4 /* field_instance_acl_metadata_acl_op */,
  12 /* field_instance_acl_metadata_acl_reason */,
  48 /* field_instance_intrinsic_metadata_ingress_global_timestamp */,
  8 /* field_instance_intrinsic_metadata_lf_field_list */,
  16 /* field_instance_intrinsic_metadata_mcast_grp */,
  16 /* field_instance_intrinsic_metadata_egress_rid */,
  8 /* field_instance_intrinsic_metadata_resubmit_flag */,
  8 /* field_instance_intrinsic_metadata_recirculate_flag */,
  4 /* field_instance_route_metadata_route */,
  4 /* field_instance_route_metadata_lan */
};

// sugar@120
 static const int field_instance_bit_offset[FIELD_INSTANCE_COUNT] = {
  0 /* field_instance_standard_metadata_ingress_port */,
  1 /* field_instance_standard_metadata_packet_length */,
  1 /* field_instance_standard_metadata_egress_spec */,
  2 /* field_instance_standard_metadata_egress_port */,
  3 /* field_instance_standard_metadata_egress_instance */,
  3 /* field_instance_standard_metadata_instance_type */,
  3 /* field_instance_standard_metadata_clone_spec */,
  3 /* field_instance_standard_metadata__padding */,
  0 /* field_instance_ethernet_dst_mac */,
  0 /* field_instance_ethernet_src_mac */,
  0 /* field_instance_ethernet_eth_type */,
  0 /* field_instance_ip_ver */,
  4 /* field_instance_ip_ihl */,
  0 /* field_instance_ip_diff_serv */,
  0 /* field_instance_ip_tot_len */,
  0 /* field_instance_ip_id */,
  0 /* field_instance_ip_flags */,
  3 /* field_instance_ip_frag_offset */,
  0 /* field_instance_ip_ttl */,
  0 /* field_instance_ip_proto */,
  0 /* field_instance_ip_checksum */,
  0 /* field_instance_ip_src_addr */,
  0 /* field_instance_ip_dst_addr */,
  0 /* field_instance_tcp_src_port */,
  0 /* field_instance_tcp_dst_port */,
  0 /* field_instance_tcp_seq_no */,
  0 /* field_instance_tcp_ack_no */,
  0 /* field_instance_tcp_offset */,
  4 /* field_instance_tcp_res */,
  0 /* field_instance_tcp_flags */,
  0 /* field_instance_tcp_window */,
  0 /* field_instance_tcp_checksum */,
  0 /* field_instance_tcp_urgent_ptr */,
  0 /* field_instance_arp_hw_type */,
  0 /* field_instance_arp_proto_type */,
  0 /* field_instance_arp_hw_addr_len */,
  0 /* field_instance_arp_proto_addr_len */,
  0 /* field_instance_arp_opcode */,
  0 /* field_instance_arp_src_hw_addr */,
  0 /* field_instance_arp_src_proto_addr */,
  0 /* field_instance_arp_dst_hw_mac */,
  0 /* field_instance_arp_dst_proto_addr */,
  0 /* field_instance_icmp_msg_type */,
  0 /* field_instance_icmp_code */,
  0 /* field_instance_icmp_checksum */,
  0 /* field_instance_udp_src_port */,
  0 /* field_instance_udp_dst_port */,
  0 /* field_instance_udp_length_ */,
  0 /* field_instance_udp_checksum */,
  0 /* field_instance_vlan_pcp */,
  3 /* field_instance_vlan_cfi */,
  4 /* field_instance_vlan_vid */,
  0 /* field_instance_vlan_eth_type */,
  0 /* field_instance_acl_metadata_enable_mac_acl */,
  1 /* field_instance_acl_metadata_enable_vlan_acl */,
  2 /* field_instance_acl_metadata_enable_ipv4_acl */,
  3 /* field_instance_acl_metadata_enable_icmp_acl */,
  4 /* field_instance_acl_metadata_enable_tcp_acl */,
  5 /* field_instance_acl_metadata_enable_udp_acl */,
  6 /* field_instance_acl_metadata_padding */,
  0 /* field_instance_acl_metadata_acl_op */,
  4 /* field_instance_acl_metadata_acl_reason */,
  0 /* field_instance_intrinsic_metadata_ingress_global_timestamp */,
  0 /* field_instance_intrinsic_metadata_lf_field_list */,
  0 /* field_instance_intrinsic_metadata_mcast_grp */,
  0 /* field_instance_intrinsic_metadata_egress_rid */,
  0 /* field_instance_intrinsic_metadata_resubmit_flag */,
  0 /* field_instance_intrinsic_metadata_recirculate_flag */,
  0 /* field_instance_route_metadata_route */,
  4 /* field_instance_route_metadata_lan */
};

// sugar@121
 static const int field_instance_byte_offset_hdr[FIELD_INSTANCE_COUNT] = {
  0 /* field_instance_standard_metadata_ingress_port */,
  1 /* field_instance_standard_metadata_packet_length */,
  5 /* field_instance_standard_metadata_egress_spec */,
  6 /* field_instance_standard_metadata_egress_port */,
  7 /* field_instance_standard_metadata_egress_instance */,
  11 /* field_instance_standard_metadata_instance_type */,
  15 /* field_instance_standard_metadata_clone_spec */,
  19 /* field_instance_standard_metadata__padding */,
  0 /* field_instance_ethernet_dst_mac */,
  6 /* field_instance_ethernet_src_mac */,
  12 /* field_instance_ethernet_eth_type */,
  0 /* field_instance_ip_ver */,
  0 /* field_instance_ip_ihl */,
  1 /* field_instance_ip_diff_serv */,
  2 /* field_instance_ip_tot_len */,
  4 /* field_instance_ip_id */,
  6 /* field_instance_ip_flags */,
  6 /* field_instance_ip_frag_offset */,
  8 /* field_instance_ip_ttl */,
  9 /* field_instance_ip_proto */,
  10 /* field_instance_ip_checksum */,
  12 /* field_instance_ip_src_addr */,
  16 /* field_instance_ip_dst_addr */,
  0 /* field_instance_tcp_src_port */,
  2 /* field_instance_tcp_dst_port */,
  4 /* field_instance_tcp_seq_no */,
  8 /* field_instance_tcp_ack_no */,
  12 /* field_instance_tcp_offset */,
  12 /* field_instance_tcp_res */,
  13 /* field_instance_tcp_flags */,
  14 /* field_instance_tcp_window */,
  16 /* field_instance_tcp_checksum */,
  18 /* field_instance_tcp_urgent_ptr */,
  0 /* field_instance_arp_hw_type */,
  2 /* field_instance_arp_proto_type */,
  4 /* field_instance_arp_hw_addr_len */,
  5 /* field_instance_arp_proto_addr_len */,
  6 /* field_instance_arp_opcode */,
  8 /* field_instance_arp_src_hw_addr */,
  14 /* field_instance_arp_src_proto_addr */,
  18 /* field_instance_arp_dst_hw_mac */,
  24 /* field_instance_arp_dst_proto_addr */,
  0 /* field_instance_icmp_msg_type */,
  1 /* field_instance_icmp_code */,
  2 /* field_instance_icmp_checksum */,
  0 /* field_instance_udp_src_port */,
  2 /* field_instance_udp_dst_port */,
  4 /* field_instance_udp_length_ */,
  6 /* field_instance_udp_checksum */,
  0 /* field_instance_vlan_pcp */,
  0 /* field_instance_vlan_cfi */,
  0 /* field_instance_vlan_vid */,
  2 /* field_instance_vlan_eth_type */,
  0 /* field_instance_acl_metadata_enable_mac_acl */,
  0 /* field_instance_acl_metadata_enable_vlan_acl */,
  0 /* field_instance_acl_metadata_enable_ipv4_acl */,
  0 /* field_instance_acl_metadata_enable_icmp_acl */,
  0 /* field_instance_acl_metadata_enable_tcp_acl */,
  0 /* field_instance_acl_metadata_enable_udp_acl */,
  0 /* field_instance_acl_metadata_padding */,
  1 /* field_instance_acl_metadata_acl_op */,
  1 /* field_instance_acl_metadata_acl_reason */,
  0 /* field_instance_intrinsic_metadata_ingress_global_timestamp */,
  6 /* field_instance_intrinsic_metadata_lf_field_list */,
  7 /* field_instance_intrinsic_metadata_mcast_grp */,
  9 /* field_instance_intrinsic_metadata_egress_rid */,
  11 /* field_instance_intrinsic_metadata_resubmit_flag */,
  12 /* field_instance_intrinsic_metadata_recirculate_flag */,
  0 /* field_instance_route_metadata_route */,
  0 /* field_instance_route_metadata_lan */
};

// sugar@122
 static const uint32_t field_instance_mask[FIELD_INSTANCE_COUNT] = {
  0x80ff /* field_instance_standard_metadata_ingress_port */,
  0x0 /* field_instance_standard_metadata_packet_length */,
  0xc07f /* field_instance_standard_metadata_egress_spec */,
  0xe03f /* field_instance_standard_metadata_egress_port */,
  0x0 /* field_instance_standard_metadata_egress_instance */,
  0x0 /* field_instance_standard_metadata_instance_type */,
  0x0 /* field_instance_standard_metadata_clone_spec */,
  0x1f /* field_instance_standard_metadata__padding */,
  0x0 /* field_instance_ethernet_dst_mac */,
  0x0 /* field_instance_ethernet_src_mac */,
  0xffff /* field_instance_ethernet_eth_type */,
  0xf0 /* field_instance_ip_ver */,
  0xf /* field_instance_ip_ihl */,
  0xff /* field_instance_ip_diff_serv */,
  0xffff /* field_instance_ip_tot_len */,
  0xffff /* field_instance_ip_id */,
  0xe0 /* field_instance_ip_flags */,
  0xff1f /* field_instance_ip_frag_offset */,
  0xff /* field_instance_ip_ttl */,
  0xff /* field_instance_ip_proto */,
  0xffff /* field_instance_ip_checksum */,
  0xffffffff /* field_instance_ip_src_addr */,
  0xffffffff /* field_instance_ip_dst_addr */,
  0xffff /* field_instance_tcp_src_port */,
  0xffff /* field_instance_tcp_dst_port */,
  0xffffffff /* field_instance_tcp_seq_no */,
  0xffffffff /* field_instance_tcp_ack_no */,
  0xf0 /* field_instance_tcp_offset */,
  0xf /* field_instance_tcp_res */,
  0xff /* field_instance_tcp_flags */,
  0xffff /* field_instance_tcp_window */,
  0xffff /* field_instance_tcp_checksum */,
  0xffff /* field_instance_tcp_urgent_ptr */,
  0xffff /* field_instance_arp_hw_type */,
  0xffff /* field_instance_arp_proto_type */,
  0xff /* field_instance_arp_hw_addr_len */,
  0xff /* field_instance_arp_proto_addr_len */,
  0xffff /* field_instance_arp_opcode */,
  0x0 /* field_instance_arp_src_hw_addr */,
  0xffffffff /* field_instance_arp_src_proto_addr */,
  0x0 /* field_instance_arp_dst_hw_mac */,
  0xffffffff /* field_instance_arp_dst_proto_addr */,
  0xff /* field_instance_icmp_msg_type */,
  0xff /* field_instance_icmp_code */,
  0xffff /* field_instance_icmp_checksum */,
  0xffff /* field_instance_udp_src_port */,
  0xffff /* field_instance_udp_dst_port */,
  0xffff /* field_instance_udp_length_ */,
  0xffff /* field_instance_udp_checksum */,
  0xe0 /* field_instance_vlan_pcp */,
  0x10 /* field_instance_vlan_cfi */,
  0xff0f /* field_instance_vlan_vid */,
  0xffff /* field_instance_vlan_eth_type */,
  0x80 /* field_instance_acl_metadata_enable_mac_acl */,
  0x40 /* field_instance_acl_metadata_enable_vlan_acl */,
  0x20 /* field_instance_acl_metadata_enable_ipv4_acl */,
  0x10 /* field_instance_acl_metadata_enable_icmp_acl */,
  0x8 /* field_instance_acl_metadata_enable_tcp_acl */,
  0x4 /* field_instance_acl_metadata_enable_udp_acl */,
  0x3 /* field_instance_acl_metadata_padding */,
  0xf0 /* field_instance_acl_metadata_acl_op */,
  0xff0f /* field_instance_acl_metadata_acl_reason */,
  0x0 /* field_instance_intrinsic_metadata_ingress_global_timestamp */,
  0xff /* field_instance_intrinsic_metadata_lf_field_list */,
  0xffff /* field_instance_intrinsic_metadata_mcast_grp */,
  0xffff /* field_instance_intrinsic_metadata_egress_rid */,
  0xff /* field_instance_intrinsic_metadata_resubmit_flag */,
  0xff /* field_instance_intrinsic_metadata_recirculate_flag */,
  0xf0 /* field_instance_route_metadata_route */,
  0xf /* field_instance_route_metadata_lan */
};

// sugar@123
 static const header_instance_t field_instance_header[FIELD_INSTANCE_COUNT] = {
  header_instance_standard_metadata /* field_instance_standard_metadata_ingress_port */,
  header_instance_standard_metadata /* field_instance_standard_metadata_packet_length */,
  header_instance_standard_metadata /* field_instance_standard_metadata_egress_spec */,
  header_instance_standard_metadata /* field_instance_standard_metadata_egress_port */,
  header_instance_standard_metadata /* field_instance_standard_metadata_egress_instance */,
  header_instance_standard_metadata /* field_instance_standard_metadata_instance_type */,
  header_instance_standard_metadata /* field_instance_standard_metadata_clone_spec */,
  header_instance_standard_metadata /* field_instance_standard_metadata__padding */,
  header_instance_ethernet /* field_instance_ethernet_dst_mac */,
  header_instance_ethernet /* field_instance_ethernet_src_mac */,
  header_instance_ethernet /* field_instance_ethernet_eth_type */,
  header_instance_ip /* field_instance_ip_ver */,
  header_instance_ip /* field_instance_ip_ihl */,
  header_instance_ip /* field_instance_ip_diff_serv */,
  header_instance_ip /* field_instance_ip_tot_len */,
  header_instance_ip /* field_instance_ip_id */,
  header_instance_ip /* field_instance_ip_flags */,
  header_instance_ip /* field_instance_ip_frag_offset */,
  header_instance_ip /* field_instance_ip_ttl */,
  header_instance_ip /* field_instance_ip_proto */,
  header_instance_ip /* field_instance_ip_checksum */,
  header_instance_ip /* field_instance_ip_src_addr */,
  header_instance_ip /* field_instance_ip_dst_addr */,
  header_instance_tcp /* field_instance_tcp_src_port */,
  header_instance_tcp /* field_instance_tcp_dst_port */,
  header_instance_tcp /* field_instance_tcp_seq_no */,
  header_instance_tcp /* field_instance_tcp_ack_no */,
  header_instance_tcp /* field_instance_tcp_offset */,
  header_instance_tcp /* field_instance_tcp_res */,
  header_instance_tcp /* field_instance_tcp_flags */,
  header_instance_tcp /* field_instance_tcp_window */,
  header_instance_tcp /* field_instance_tcp_checksum */,
  header_instance_tcp /* field_instance_tcp_urgent_ptr */,
  header_instance_arp /* field_instance_arp_hw_type */,
  header_instance_arp /* field_instance_arp_proto_type */,
  header_instance_arp /* field_instance_arp_hw_addr_len */,
  header_instance_arp /* field_instance_arp_proto_addr_len */,
  header_instance_arp /* field_instance_arp_opcode */,
  header_instance_arp /* field_instance_arp_src_hw_addr */,
  header_instance_arp /* field_instance_arp_src_proto_addr */,
  header_instance_arp /* field_instance_arp_dst_hw_mac */,
  header_instance_arp /* field_instance_arp_dst_proto_addr */,
  header_instance_icmp /* field_instance_icmp_msg_type */,
  header_instance_icmp /* field_instance_icmp_code */,
  header_instance_icmp /* field_instance_icmp_checksum */,
  header_instance_udp /* field_instance_udp_src_port */,
  header_instance_udp /* field_instance_udp_dst_port */,
  header_instance_udp /* field_instance_udp_length_ */,
  header_instance_udp /* field_instance_udp_checksum */,
  header_instance_vlan /* field_instance_vlan_pcp */,
  header_instance_vlan /* field_instance_vlan_cfi */,
  header_instance_vlan /* field_instance_vlan_vid */,
  header_instance_vlan /* field_instance_vlan_eth_type */,
  header_instance_acl_metadata /* field_instance_acl_metadata_enable_mac_acl */,
  header_instance_acl_metadata /* field_instance_acl_metadata_enable_vlan_acl */,
  header_instance_acl_metadata /* field_instance_acl_metadata_enable_ipv4_acl */,
  header_instance_acl_metadata /* field_instance_acl_metadata_enable_icmp_acl */,
  header_instance_acl_metadata /* field_instance_acl_metadata_enable_tcp_acl */,
  header_instance_acl_metadata /* field_instance_acl_metadata_enable_udp_acl */,
  header_instance_acl_metadata /* field_instance_acl_metadata_padding */,
  header_instance_acl_metadata /* field_instance_acl_metadata_acl_op */,
  header_instance_acl_metadata /* field_instance_acl_metadata_acl_reason */,
  header_instance_intrinsic_metadata /* field_instance_intrinsic_metadata_ingress_global_timestamp */,
  header_instance_intrinsic_metadata /* field_instance_intrinsic_metadata_lf_field_list */,
  header_instance_intrinsic_metadata /* field_instance_intrinsic_metadata_mcast_grp */,
  header_instance_intrinsic_metadata /* field_instance_intrinsic_metadata_egress_rid */,
  header_instance_intrinsic_metadata /* field_instance_intrinsic_metadata_resubmit_flag */,
  header_instance_intrinsic_metadata /* field_instance_intrinsic_metadata_recirculate_flag */,
  header_instance_route_metadata /* field_instance_route_metadata_route */,
  header_instance_route_metadata /* field_instance_route_metadata_lan */
};

// sugar@124
 
 static const header_instance_t header_stack_elements[HEADER_STACK_COUNT][10] = {
  
};

// sugar@126
 static const unsigned header_stack_size[HEADER_STACK_COUNT] = {
  
};

// sugar@127
 typedef enum header_stack_e header_stack_t;// sugar@128
 
 #endif // __HEADER_INFO_H__// sugar@130
