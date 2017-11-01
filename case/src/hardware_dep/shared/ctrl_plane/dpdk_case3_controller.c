// Copyright 2016 Eotvos Lorand University, Budapest, Hungary
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "controller.h"
#include "messages.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>


controller c;

void fill_mac_learning_table(uint8_t smac[6], uint16_t vid) {
    // FIXME: The buffer size is changed to 4096 bytes to meet the demand for complex cache table match and action.
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_field_match_exact *exact1, *exact2; // TODO: replace to lpm

    printf("enter fill_mac_learning_table function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "mac_learning");

    exact1 = add_p4_field_match_exact(te, 4096);
    strcpy(exact1->header.name, "ethernet.src_mac");
    memcpy(exact1->bitmap, smac, 6);
    exact1->length = 6 * 8 + 0;

    exact2 = add_p4_field_match_exact(te, 4096);
    strcpy(exact2->header.name, "vlan.vid");
    memcpy(exact2->bitmap, &vid, 2);
    exact2->length = 2 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "nop");

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_exact(exact1);
    netconv_p4_field_match_exact(exact2);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, 4096);

}

void fill_routable_table(uint8_t vrf[2], uint8_t smac[6], uint8_t dmac[6], uint16_t vid, uint8_t lan) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap;
    struct p4_field_match_exact *exact0, *exact1, *exact2, *exact3; // TODO: replace to lpm

    printf("enter fill_routable_table function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "routable");

    exact0 = add_p4_field_match_exact(te, 4096);
    strcpy(exact0->header.name, "vrf_metadata.vrf");
    memcpy(exact0->bitmap, vrf, 2);
    exact0->length = 2 * 8 + 0;

    exact1 = add_p4_field_match_exact(te, 4096);
    strcpy(exact1->header.name, "ethernet.src_mac");
    memcpy(exact1->bitmap, smac, 6);
    exact1->length = 6 * 8 + 0;

    exact2 = add_p4_field_match_exact(te, 4096);
    strcpy(exact2->header.name, "ethernet.dst_mac");
    memcpy(exact2->bitmap, dmac, 6);
    exact2->length = 6 * 8 + 0;

    exact3 = add_p4_field_match_exact(te, 4096);
    strcpy(exact3->header.name, "vlan.vid");
    memcpy(exact3->bitmap, &vid, 2);
    exact3->length = 2 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "ucast");

    ap = add_p4_action_parameter(h, a, 4096);
    strcpy(ap->name, "lan");
    memcpy(ap->bitmap, &lan, 1);
    ap->length = 1 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_exact(exact0);
    netconv_p4_field_match_exact(exact1);
    netconv_p4_field_match_exact(exact2);
    netconv_p4_field_match_exact(exact3);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap);

    send_p4_msg(c, buffer, 4096);
}

void fill_unicast_routing_table(uint8_t vrf[2], uint8_t dip[4], uint8_t smac[6], uint8_t dmac[6]) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap1, *ap2;
    struct p4_field_match_exact *exact0, *exact1; // TODO: replace to lpm

    printf("enter fill_unicast_routing_table function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "unicast_routing");

    exact0 = add_p4_field_match_exact(te, 4096);
    strcpy(exact0->header.name, "vrf_metadata.vrf");
    memcpy(exact0->bitmap, vrf, 2);
    exact0->length = 2 * 8 + 0;

    exact1 = add_p4_field_match_exact(te, 4096);
    strcpy(exact1->header.name, "ip.dst_addr");
    memcpy(exact1->bitmap, dip, 4);
    exact1->length = 4 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "set_nhop");

    ap1 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap1->name, "src_mac");
    memcpy(ap1->bitmap, smac, 6);
    ap1->length = 6 * 8 + 0;

    ap2 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap2->name, "dst_mac");
    memcpy(ap2->bitmap, dmac, 6);
    ap2->length = 6 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_exact(exact0);
    netconv_p4_field_match_exact(exact1);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap1);
    netconv_p4_action_parameter(ap2);

    send_p4_msg(c, buffer, 4096);
}

void fill_switching_table(uint8_t vrf[2], uint8_t dmac[8], uint16_t vid, uint16_t port) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap;
    struct p4_field_match_exact *exact0, *exact1, *exact2; // TODO: replace to lpm

    printf("enter fill_switching_table function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "switching");

    exact0 = add_p4_field_match_exact(te, 4096);
    strcpy(exact0->header.name, "vrf_metadata.vrf");
    memcpy(exact0->bitmap, vrf, 2);
    exact0->length = 2 * 8 + 0;

    exact1 = add_p4_field_match_exact(te, 4096);
    strcpy(exact1->header.name, "ethernet.dst_mac");
    memcpy(exact1->bitmap, dmac, 6);
    exact1->length = 6 * 8 + 0;

    exact2 = add_p4_field_match_exact(te, 4096);
    strcpy(exact2->header.name, "vlan.vid");
    memcpy(exact2->bitmap, &vid, 2);
    exact2->length = 2 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "forwarding");

    ap = add_p4_action_parameter(h, a, 4096);
    strcpy(ap->name, "port");
    memcpy(ap->bitmap, &port, 2);
    ap->length = 2 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_exact(exact0);
    netconv_p4_field_match_exact(exact1);
    netconv_p4_field_match_exact(exact2);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap);

    send_p4_msg(c, buffer, 4096);
}

void fill_get_acl_features_table(uint8_t vrf[2], uint8_t vrf_mask[2], uint8_t sip[4], uint8_t sip_mask[4],
                                 uint8_t dip[4], uint8_t dip_mask[4],
                                 uint8_t e_mac, uint8_t e_vlan, uint8_t e_ipv4, uint8_t e_icmp,
                                 uint8_t e_tcp, uint8_t e_udp) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap1, *ap2, *ap3, *ap4, *ap5, *ap6;
    struct p4_field_match_ternary *ternary0, *ternary1, *ternary2; // TODO: replace to lpm

    printf("enter fill_get_acl_feature_table function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "get_acl_features");

    ternary0 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary0->header.name, "vrf_metadata.vrf");
    memcpy(ternary0->bitmap, vrf, 2);
    memcpy(ternary0->mask, vrf_mask, 2);
    ternary0->length = 2 * 8 + 0;

    ternary1 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary1->header.name, "ip.src_addr");
    memcpy(ternary1->bitmap, sip, 4);
    memcpy(ternary1->mask, sip_mask, 4);
    ternary1->length = 4 * 8 + 0;

    ternary2 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary2->header.name, "ip.dst_addr");
    memcpy(ternary2->bitmap, dip, 4);
    memcpy(ternary2->mask, dip_mask, 4);
    ternary2->length = 4 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "acl_feature");

    ap1 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap1->name, "enable_mac");
    memcpy(ap1->bitmap, &e_mac, 1);
    ap1->length = 1 * 8 + 0;

    ap2 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap2->name, "enable_vlan");
    memcpy(ap2->bitmap, &e_vlan, 1);
    ap2->length = 1 * 8 + 0;

    ap3 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap3->name, "enable_ipv4");
    memcpy(ap3->bitmap, &e_ipv4, 1);
    ap3->length = 1 * 8 + 0;

    ap4 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap4->name, "enable_icmp");
    memcpy(ap4->bitmap, &e_icmp, 1);
    ap4->length = 1 * 8 + 0;

    ap5 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap5->name, "enable_tcp");
    memcpy(ap5->bitmap, &e_tcp, 1);
    ap5->length = 1 * 8 + 0;

    ap6 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap6->name, "enable_udp");
    memcpy(ap6->bitmap, &e_udp, 1);
    ap6->length = 1 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_ternary(ternary0);
    netconv_p4_field_match_ternary(ternary1);
    netconv_p4_field_match_ternary(ternary2);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap1);
    netconv_p4_action_parameter(ap2);
    netconv_p4_action_parameter(ap3);
    netconv_p4_action_parameter(ap4);
    netconv_p4_action_parameter(ap5);
    netconv_p4_action_parameter(ap6);

    send_p4_msg(c, buffer, 4096);
}

void fill_mac_acl_table(uint8_t vrf[2], uint8_t vrf_mask[2], uint8_t smac[6], uint8_t smac_mask[6],
                        uint8_t dmac[6], uint8_t dmac_mask[6],
                        uint8_t eth_type[2], uint8_t eth_type_mask[2], uint16_t reason) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap;
    struct p4_field_match_ternary *ternary0, *ternary1, *ternary2, *ternary3; // TODO: replace to lpm

    printf("enter fill_mac_acl_table function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "mac_acl");

    ternary0 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary0->header.name, "vrf_metadata.vrf");
    memcpy(ternary0->bitmap, vrf, 2);
    memcpy(ternary0->mask, vrf_mask, 2);
    ternary0->length = 2 * 8 + 0;

    ternary1 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary1->header.name, "ethernet.src_mac");
    memcpy(ternary1->bitmap, smac, 6);
    memcpy(ternary1->mask, smac_mask, 6);
    ternary1->length = 6 * 8 + 0;

    ternary2 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary2->header.name, "ethernet.dst_mac");
    memcpy(ternary2->bitmap, dmac, 6);
    memcpy(ternary2->mask, dmac_mask, 6);
    ternary2->length = 6 * 8 + 0;

    ternary3 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary3->header.name, "ethernet.eth_type");
    memcpy(ternary3->bitmap, eth_type, 2);
    memcpy(ternary3->mask, eth_type_mask, 2);
    ternary3->length = 2 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "acl_permit");

    ap = add_p4_action_parameter(h, a, 4096);
    strcpy(ap->name, "reason");
    memcpy(ap->bitmap, &reason, 2);
    ap->length = 2 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_ternary(ternary0);
    netconv_p4_field_match_ternary(ternary1);
    netconv_p4_field_match_ternary(ternary2);
    netconv_p4_field_match_ternary(ternary3);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap);

    send_p4_msg(c, buffer, 4096);
}

void fill_ipv4_acl_table(uint8_t vrf[2], uint8_t vrf_mask[2], uint8_t sip[4], uint8_t sip_mask[4],
                         uint8_t dip[4], uint8_t dip_mask[4],
                         uint8_t ip_proto, uint8_t ip_proto_mask, uint16_t reason) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap;
    struct p4_field_match_ternary *ternary0, *ternary1, *ternary2, *ternary3; // TODO: replace to lpm

    printf("enter fill_ipv4_acl_table function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "ipv4_acl");

    ternary0 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary0->header.name, "vrf_metadata.vrf");
    memcpy(ternary0->bitmap, vrf, 2);
    memcpy(ternary0->mask, vrf_mask, 2);
    ternary0->length = 2 * 8 + 0;

    ternary1 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary1->header.name, "ip.src_addr");
    memcpy(ternary1->bitmap, sip, 4);
    memcpy(ternary1->mask, sip_mask, 4);
    ternary1->length = 4 * 8 + 0;

    ternary2 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary2->header.name, "ip.dst_addr");
    memcpy(ternary2->bitmap, dip, 4);
    memcpy(ternary2->mask, dip_mask, 4);
    ternary2->length = 4 * 8 + 0;

    ternary3 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary3->header.name, "ip.proto");
    memcpy(ternary3->bitmap, &ip_proto, 1);
    memcpy(ternary3->mask, &ip_proto_mask, 1);
    ternary3->length = 1 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "acl_permit");

    ap = add_p4_action_parameter(h, a, 4096);
    strcpy(ap->name, "reason");
    memcpy(ap->bitmap, &reason, 2);
    ap->length = 2 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_ternary(ternary0);
    netconv_p4_field_match_ternary(ternary1);
    netconv_p4_field_match_ternary(ternary2);
    netconv_p4_field_match_ternary(ternary3);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap);

    send_p4_msg(c, buffer, 4096);
}

void fill_tcp_acl_table(uint8_t vrf[2], uint8_t vrf_mask[2], uint8_t sport[2], uint8_t sport_mask[2],
                        uint8_t dport[2], uint8_t dport_mask[2],
                        uint8_t tcp_flags, uint8_t tcp_flags_mask, uint16_t reason) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap;
    struct p4_field_match_ternary *ternary0, *ternary1, *ternary2, *ternary3; // TODO: replace to lpm

    printf("enter fill_tcp_acl_table function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "tcp_acl");

    ternary0 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary0->header.name, "vrf_metadata.vrf");
    memcpy(ternary0->bitmap, vrf, 2);
    memcpy(ternary0->mask, vrf_mask, 2);
    ternary0->length = 2 * 8 + 0;

    ternary1 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary1->header.name, "tcp.src_port");
    memcpy(ternary1->bitmap, sport, 2);
    memcpy(ternary1->mask, sport_mask, 2);
    ternary1->length = 2 * 8 + 0;

    ternary2 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary2->header.name, "tcp.dst_port");
    memcpy(ternary2->bitmap, dport, 2);
    memcpy(ternary2->mask, dport_mask, 2);
    ternary2->length = 2 * 8 + 0;

    ternary3 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary3->header.name, "tcp.flags");
    memcpy(ternary3->bitmap, &tcp_flags, 1);
    memcpy(ternary3->mask, &tcp_flags_mask, 1);
    ternary3->length = 1 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "acl_permit");

    ap = add_p4_action_parameter(h, a, 4096);
    strcpy(ap->name, "reason");
    memcpy(ap->bitmap, &reason, 2);
    ap->length = 2 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_ternary(ternary0);
    netconv_p4_field_match_ternary(ternary1);
    netconv_p4_field_match_ternary(ternary2);
    netconv_p4_field_match_ternary(ternary3);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap);

    send_p4_msg(c, buffer, 4096);
}

void fill_udp_acl_table(uint8_t vrf[2], uint8_t vrf_mask[2], uint8_t sport[2], uint8_t sport_mask[2],
                        uint8_t dport[2], uint8_t dport_mask[2], uint16_t reason) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap;
    struct p4_field_match_ternary *ternary0, *ternary1, *ternary2; // TODO: replace to lpm

    printf("enter fill_udp_acl_table function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "udp_acl");

    ternary0 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary0->header.name, "vrf_metadata.vrf");
    memcpy(ternary0->bitmap, vrf, 2);
    memcpy(ternary0->mask, vrf_mask, 2);
    ternary0->length = 2 * 8 + 0;

    ternary1 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary1->header.name, "udp.src_port");
    memcpy(ternary1->bitmap, sport, 2);
    memcpy(ternary1->mask, sport_mask, 2);
    ternary1->length = 2 * 8 + 0;

    ternary2 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary2->header.name, "udp.dst_port");
    memcpy(ternary2->bitmap, dport, 2);
    memcpy(ternary2->mask, dport_mask, 2);
    ternary2->length = 2 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "acl_permit");

    ap = add_p4_action_parameter(h, a, 4096);
    strcpy(ap->name, "reason");
    memcpy(ap->bitmap, &reason, 2);
    ap->length = 2 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_ternary(ternary0);
    netconv_p4_field_match_ternary(ternary1);
    netconv_p4_field_match_ternary(ternary2);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap);

    send_p4_msg(c, buffer, 4096);
}

// FIXME: the interface of "fill_table" function lacks action_name, needs to be improved.
void fill_nat_get_l4_infomation_table_1(uint8_t ip_proto) {
    // FIXME: The buffer size is changed to 4096 bytes to meet the demand for complex cache table match and action.
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_field_match_exact *exact; // TODO: replace to lpm

    printf("enter fill_nat_get_l4_infomation_table.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "nat_get_l4_infomation");

    exact = add_p4_field_match_exact(te, 4096);
    strcpy(exact->header.name, "ip.proto");
    memcpy(exact->bitmap, &ip_proto, 1);
    exact->length = 1 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "get_tcp_information");

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_exact(exact);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, 4096);

}

void fill_nat_get_l4_infomation_table_2(uint8_t ip_proto) {
    // FIXME: The buffer size is changed to 4096 bytes to meet the demand for complex cache table match and action.
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_field_match_exact *exact; // TODO: replace to lpm

    printf("enter fill_nat_get_l4_infomation_table.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "nat_get_l4_infomation");

    exact = add_p4_field_match_exact(te, 4096);
    strcpy(exact->header.name, "ip.proto");
    memcpy(exact->bitmap, &ip_proto, 1);
    exact->length = 1 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "get_udp_information");

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_exact(exact);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, 4096);

}

void fill_nat_flow_table_1(uint8_t vrf[2], uint8_t vrf_mask[2], uint8_t sip[4], uint8_t sip_mask[4],
                           uint8_t dip[4], uint8_t dip_mask[4], uint8_t ip_proto,
                           uint8_t ip_proto_mask, uint8_t l4_sport[2], uint8_t l4_sport_mask[2], uint8_t l4_dport[2],
                           uint8_t l4_dport_mask[2], uint8_t addr[4], uint8_t port[2]) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap1, *ap2;
    struct p4_field_match_ternary *ternary0, *ternary1, *ternary2, *ternary3, *ternary4, *ternary5; // TODO: replace to lpm

    printf("enter fill_nat_flow_table_1 function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "nat_flow");

    ternary0 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary0->header.name, "vrf_metadata.vrf");
    memcpy(ternary0->bitmap, vrf, 2);
    memcpy(ternary0->mask, vrf_mask, 2);
    ternary0->length = 2 * 8 + 0;

    ternary1 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary1->header.name, "ip.src_addr");
    memcpy(ternary1->bitmap, sip, 4);
    memcpy(ternary1->mask, sip_mask, 4);
    ternary1->length = 4 * 8 + 0;

    ternary2 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary2->header.name, "ip.dst_addr");
    memcpy(ternary2->bitmap, dip, 4);
    memcpy(ternary2->mask, dip_mask, 4);
    ternary2->length = 4 * 8 + 0;

    ternary3 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary3->header.name, "ip.proto");
    memcpy(ternary3->bitmap, &ip_proto, 1);
    memcpy(ternary3->mask, &ip_proto_mask, 1);
    ternary3->length = 1 * 8 + 0;

    ternary4 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary4->header.name, "nat_metadata.l4_src_port");
    memcpy(ternary4->bitmap, l4_sport, 2);
    memcpy(ternary4->mask, l4_sport_mask, 2);
    ternary4->length = 2 * 8 + 0;

    ternary5 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary5->header.name, "nat_metadata.l4_dst_port");
    memcpy(ternary5->bitmap, l4_dport, 2);
    memcpy(ternary5->mask, l4_dport_mask, 2);
    ternary5->length = 2 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "rewrite_tcp_src");

    ap1 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap1->name, "addr");
    memcpy(ap1->bitmap, addr, 4);
    ap1->length = 4 * 8 + 0;

    ap2 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap2->name, "port");
    memcpy(ap2->bitmap, port, 2);
    ap2->length = 2 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_ternary(ternary0);
    netconv_p4_field_match_ternary(ternary1);
    netconv_p4_field_match_ternary(ternary2);
    netconv_p4_field_match_ternary(ternary3);
    netconv_p4_field_match_ternary(ternary4);
    netconv_p4_field_match_ternary(ternary5);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap1);
    netconv_p4_action_parameter(ap2);

    send_p4_msg(c, buffer, 4096);
}

void fill_nat_flow_table_2(uint8_t vrf[2], uint8_t vrf_mask[2], uint8_t sip[4], uint8_t sip_mask[4],
                           uint8_t dip[4], uint8_t dip_mask[4], uint8_t ip_proto,
                           uint8_t ip_proto_mask, uint8_t l4_sport[2], uint8_t l4_sport_mask[2], uint8_t l4_dport[2],
                           uint8_t l4_dport_mask[2], uint8_t addr[4], uint8_t port[2]) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap1, *ap2;
    struct p4_field_match_ternary *ternary0, *ternary1, *ternary2, *ternary3, *ternary4, *ternary5; // TODO: replace to lpm

    printf("enter fill_nat_flow_table_2 function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "nat_flow");

    ternary0 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary0->header.name, "vrf_metadata.vrf");
    memcpy(ternary0->bitmap, vrf, 2);
    memcpy(ternary0->mask, vrf_mask, 2);
    ternary0->length = 2 * 8 + 0;

    ternary1 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary1->header.name, "ip.src_addr");
    memcpy(ternary1->bitmap, sip, 4);
    memcpy(ternary1->mask, sip_mask, 4);
    ternary1->length = 4 * 8 + 0;

    ternary2 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary2->header.name, "ip.dst_addr");
    memcpy(ternary2->bitmap, dip, 4);
    memcpy(ternary2->mask, dip_mask, 4);
    ternary2->length = 4 * 8 + 0;

    ternary3 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary3->header.name, "ip.proto");
    memcpy(ternary3->bitmap, &ip_proto, 1);
    memcpy(ternary3->mask, &ip_proto_mask, 1);
    ternary3->length = 1 * 8 + 0;

    ternary4 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary4->header.name, "nat_metadata.l4_src_port");
    memcpy(ternary4->bitmap, l4_sport, 2);
    memcpy(ternary4->mask, l4_sport_mask, 2);
    ternary4->length = 2 * 8 + 0;

    ternary5 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary5->header.name, "nat_metadata.l4_dst_port");
    memcpy(ternary5->bitmap, l4_dport, 2);
    memcpy(ternary5->mask, l4_dport_mask, 2);
    ternary5->length = 2 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "rewrite_udp_src");

    ap1 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap1->name, "addr");
    memcpy(ap1->bitmap, addr, 4);
    ap1->length = 4 * 8 + 0;

    ap2 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap2->name, "port");
    memcpy(ap2->bitmap, port, 2);
    ap2->length = 2 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_ternary(ternary0);
    netconv_p4_field_match_ternary(ternary1);
    netconv_p4_field_match_ternary(ternary2);
    netconv_p4_field_match_ternary(ternary3);
    netconv_p4_field_match_ternary(ternary4);
    netconv_p4_field_match_ternary(ternary5);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap1);
    netconv_p4_action_parameter(ap2);

    send_p4_msg(c, buffer, 4096);
}

void fill_ipsg_permit_special_table(uint8_t sip[4], uint8_t sip_mask[4], uint8_t dip[4], uint8_t dip_mask[4], uint8_t ip_proto,
                           uint8_t ip_proto_mask, uint8_t tcp_sport[2], uint8_t tcp_sport_mask[2], uint8_t tcp_dport[2],
                           uint8_t tcp_dport_mask[2], uint8_t udp_sport[2], uint8_t udp_sport_mask[2],
                           uint8_t udp_dport[2], uint8_t udp_dport_mask[2]) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_field_match_ternary *ternary1, *ternary2, *ternary3, *ternary4, *ternary5,
                                  *ternary6, *ternary7; // TODO: replace to lpm

    printf("enter fill_ipsg_permit_special function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "ipsg_permit_special");

    ternary1 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary1->header.name, "ip.src_addr");
    memcpy(ternary1->bitmap, sip, 4);
    memcpy(ternary1->mask, sip_mask, 4);
    ternary1->length = 4 * 8 + 0;

    ternary2 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary2->header.name, "ip.dst_addr");
    memcpy(ternary2->bitmap, dip, 4);
    memcpy(ternary2->mask, dip_mask, 4);
    ternary2->length = 4 * 8 + 0;

    ternary3 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary3->header.name, "ip.proto");
    memcpy(ternary3->bitmap, &ip_proto, 1);
    memcpy(ternary3->mask, &ip_proto_mask, 1);
    ternary3->length = 1 * 8 + 0;

    ternary4 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary4->header.name, "tcp.src_port");
    memcpy(ternary4->bitmap, tcp_sport, 2);
    memcpy(ternary4->mask, tcp_sport_mask, 2);
    ternary4->length = 2 * 8 + 0;

    ternary5 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary5->header.name, "tcp.dst_port");
    memcpy(ternary5->bitmap, tcp_dport, 2);
    memcpy(ternary5->mask, tcp_dport_mask, 2);
    ternary5->length = 2 * 8 + 0;

    ternary6 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary6->header.name, "udp.src_port");
    memcpy(ternary6->bitmap, udp_sport, 2);
    memcpy(ternary6->mask, udp_sport_mask, 2);
    ternary6->length = 2 * 8 + 0;

    ternary7 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary7->header.name, "udp.dst_port");
    memcpy(ternary7->bitmap, udp_dport, 2);
    memcpy(ternary7->mask, udp_dport_mask, 2);
    ternary7->length = 2 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "nop");

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_ternary(ternary1);
    netconv_p4_field_match_ternary(ternary2);
    netconv_p4_field_match_ternary(ternary3);
    netconv_p4_field_match_ternary(ternary4);
    netconv_p4_field_match_ternary(ternary5);
    netconv_p4_field_match_ternary(ternary6);
    netconv_p4_field_match_ternary(ternary7);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, 4096);
}

void fill_storm_control_tbl_table(uint8_t iport[2], uint8_t iport_mask[2], uint8_t dmac[6], uint8_t dmac_mask[6],
                                  uint8_t eth_type[2], uint8_t eth_type_mask[2], uint8_t dip[4], uint8_t dip_mask[6],
                                  uint16_t index) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap;
    struct p4_field_match_ternary *ternary1, *ternary2, *ternary3, *ternary4; // TODO: replace to lpm

    printf("enter fill_storm_control_tbl_table function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "storm_control_tbl");

    ternary1 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary1->header.name, "standard_metadata.ingress_port");
    memcpy(ternary1->bitmap, iport, 2);
    memcpy(ternary1->mask, iport_mask, 2);
    ternary1->length = 2 * 8 + 0;

    ternary2 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary2->header.name, "ethernet.dst_mac");
    memcpy(ternary2->bitmap, dmac, 6);
    memcpy(ternary2->mask, dmac_mask, 6);
    ternary2->length = 6 * 8 + 0;

    ternary3 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary3->header.name, "ethernet.eth_type");
    memcpy(ternary3->bitmap, eth_type, 2);
    memcpy(ternary3->mask, eth_type_mask, 2);
    ternary3->length = 2 * 8 + 0;

    ternary4 = add_p4_field_match_ternary(te, 4096);
    strcpy(ternary4->header.name, "ip.dst_addr");
    memcpy(ternary4->bitmap, dip, 4);
    memcpy(ternary4->mask, dip_mask, 4);
    ternary4->length = 4 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "set_storm_control_meter");

    ap = add_p4_action_parameter(h, a, 4096);
    strcpy(ap->name, "meter_idx");
    memcpy(ap->bitmap, &index, 2);
    ap->length = 2 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_ternary(ternary1);
    netconv_p4_field_match_ternary(ternary2);
    netconv_p4_field_match_ternary(ternary3);
    netconv_p4_field_match_ternary(ternary4);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap);

    send_p4_msg(c, buffer, 4096);
}

void fill_port_vlan_to_vrf_table(uint8_t iport[2], uint8_t vid[2], uint16_t vrf) {
    // FIXME: The buffer size is changed to 4096 bytes to meet the demand for complex cache table match and action.
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap;
    struct p4_field_match_exact *exact1, *exact2; // TODO: replace to lpm

    printf("enter fill_port_vlan_to_vrf_table function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "port_vlan_to_vrf");

    exact1 = add_p4_field_match_exact(te, 4096);
    strcpy(exact1->header.name, "standard_metadata.ingress_port");
    memcpy(exact1->bitmap, iport, 2);
    exact1->length = 2 * 8 + 0;

    exact2 = add_p4_field_match_exact(te, 4096);
    strcpy(exact2->header.name, "vlan.vid");
    memcpy(exact2->bitmap, vid, 2);
    exact2->length = 2 * 8 + 0;

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "set_vrf");

    ap = add_p4_action_parameter(h, a, 4096);
    strcpy(ap->name, "vrf");
    memcpy(ap->bitmap, &vrf, 2);
    ap->length = 2 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_exact(exact1);
    netconv_p4_field_match_exact(exact2);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap);

    send_p4_msg(c, buffer, 4096);
}

void set_default_action_mac_acl() {
    char buffer[4096];
    struct p4_header* h;
    struct p4_set_default_action* sda;
    struct p4_action* a;

    printf("Generate set_default_action message for table mac_acl\n");

    h = create_p4_header(buffer, 0, sizeof(buffer));

    sda = create_p4_set_default_action(buffer,0,sizeof(buffer));
    strcpy(sda->table_name, "mac_acl");

    a = &(sda->action);
    strcpy(a->description.name, "nop");

    netconv_p4_header(h);
    netconv_p4_set_default_action(sda);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, sizeof(buffer));
}

void set_default_action_ipv4_acl() {
    char buffer[4096];
    struct p4_header* h;
    struct p4_set_default_action* sda;
    struct p4_action* a;

    printf("Generate set_default_action message for table ipv4_acl\n");

    h = create_p4_header(buffer, 0, sizeof(buffer));

    sda = create_p4_set_default_action(buffer,0,sizeof(buffer));
    strcpy(sda->table_name, "ipv4_acl");

    a = &(sda->action);
    strcpy(a->description.name, "nop");

    netconv_p4_header(h);
    netconv_p4_set_default_action(sda);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, sizeof(buffer));
}

void set_default_action_udp_acl() {
    char buffer[4096];
    struct p4_header* h;
    struct p4_set_default_action* sda;
    struct p4_action* a;

    printf("Generate set_default_action message for table udp_acl\n");

    h = create_p4_header(buffer, 0, sizeof(buffer));

    sda = create_p4_set_default_action(buffer,0,sizeof(buffer));
    strcpy(sda->table_name, "udp_acl");

    a = &(sda->action);
    strcpy(a->description.name, "nop");

    netconv_p4_header(h);
    netconv_p4_set_default_action(sda);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, sizeof(buffer));
}

void set_default_action_tcp_acl() {
    char buffer[4096];
    struct p4_header* h;
    struct p4_set_default_action* sda;
    struct p4_action* a;

    printf("Generate set_default_action message for table tcp_acl\n");

    h = create_p4_header(buffer, 0, sizeof(buffer));

    sda = create_p4_set_default_action(buffer,0,sizeof(buffer));
    strcpy(sda->table_name, "tcp_acl");

    a = &(sda->action);
    strcpy(a->description.name, "nop");

    netconv_p4_header(h);
    netconv_p4_set_default_action(sda);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, sizeof(buffer));
}

void set_default_action_nat_src() {
    char buffer[4096];
    struct p4_header* h;
    struct p4_set_default_action* sda;
    struct p4_action* a;

    printf("Generate set_default_action message for table nat_src\n");

    h = create_p4_header(buffer, 0, sizeof(buffer));

    sda = create_p4_set_default_action(buffer,0,sizeof(buffer));
    strcpy(sda->table_name, "nat_src");

    a = &(sda->action);
    strcpy(a->description.name, "on_miss");

    netconv_p4_header(h);
    netconv_p4_set_default_action(sda);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, sizeof(buffer));
}

void set_default_action_nat_dst() {
    char buffer[4096];
    struct p4_header* h;
    struct p4_set_default_action* sda;
    struct p4_action* a;

    printf("Generate set_default_action message for table nat_dst\n");

    h = create_p4_header(buffer, 0, sizeof(buffer));

    sda = create_p4_set_default_action(buffer,0,sizeof(buffer));
    strcpy(sda->table_name, "nat_dst");

    a = &(sda->action);
    strcpy(a->description.name, "on_miss");

    netconv_p4_header(h);
    netconv_p4_set_default_action(sda);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, sizeof(buffer));
}

void set_default_action_nat_twice() {
    char buffer[4096];
    struct p4_header* h;
    struct p4_set_default_action* sda;
    struct p4_action* a;

    printf("Generate set_default_action message for table nat_twice\n");

    h = create_p4_header(buffer, 0, sizeof(buffer));

    sda = create_p4_set_default_action(buffer,0,sizeof(buffer));
    strcpy(sda->table_name, "nat_twice");

    a = &(sda->action);
    strcpy(a->description.name, "on_miss");

    netconv_p4_header(h);
    netconv_p4_set_default_action(sda);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, sizeof(buffer));
}

void set_default_action_nat_flow() {
    char buffer[4096];
    struct p4_header* h;
    struct p4_set_default_action* sda;
    struct p4_action* a;

    printf("Generate set_default_action message for table nat_flow\n");

    h = create_p4_header(buffer, 0, sizeof(buffer));

    sda = create_p4_set_default_action(buffer,0,sizeof(buffer));
    strcpy(sda->table_name, "nat_flow");

    a = &(sda->action);
    strcpy(a->description.name, "nop");

    netconv_p4_header(h);
    netconv_p4_set_default_action(sda);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, sizeof(buffer));
}

void set_default_action_nat_get_l4_infomation() {
    char buffer[4096];
    struct p4_header* h;
    struct p4_set_default_action* sda;
    struct p4_action* a;

    printf("Generate set_default_action message for table nat_get_l4_infomation\n");

    h = create_p4_header(buffer, 0, sizeof(buffer));

    sda = create_p4_set_default_action(buffer,0,sizeof(buffer));
    strcpy(sda->table_name, "nat_get_l4_infomation");

    a = &(sda->action);
    strcpy(a->description.name, "disable_nat");

    netconv_p4_header(h);
    netconv_p4_set_default_action(sda);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, sizeof(buffer));
}

void set_default_action_ipsg() {
    char buffer[4096];
    struct p4_header* h;
    struct p4_set_default_action* sda;
    struct p4_action* a;

    printf("Generate set_default_action message for table ipsg\n");

    h = create_p4_header(buffer, 0, sizeof(buffer));

    sda = create_p4_set_default_action(buffer,0,sizeof(buffer));
    strcpy(sda->table_name, "ipsg");

    a = &(sda->action);
    strcpy(a->description.name, "on_miss");

    netconv_p4_header(h);
    netconv_p4_set_default_action(sda);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, sizeof(buffer));
}

void set_default_action_ipsg_permit_special() {
    char buffer[4096];
    struct p4_header* h;
    struct p4_set_default_action* sda;
    struct p4_action* a;

    printf("Generate set_default_action message for table ipsg_permit_special.\n");

    h = create_p4_header(buffer, 0, sizeof(buffer));

    sda = create_p4_set_default_action(buffer,0,sizeof(buffer));
    strcpy(sda->table_name, "ipsg_permit_special");

    a = &(sda->action);
    strcpy(a->description.name, "ipsg_miss");

    netconv_p4_header(h);
    netconv_p4_set_default_action(sda);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, sizeof(buffer));
}

void dhf(void *b) {
    printf("Unknown digest received\n");
}

void init_simple() {
    uint8_t zero_mac[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t mac_1[6] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x01};
    uint8_t mac_2[6] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x02};
    uint8_t mac_3[6] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x11};
    uint8_t mac_4[6] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x12};

    uint8_t mac_1_r[6] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x80};
    uint8_t mac_2_r[6] = {0x02, 0x00, 0x00, 0x00, 0x00, 0x80};
    uint8_t mac_3_r[6] = {0x11, 0x00, 0x00, 0x00, 0x00, 0x80};
    uint8_t mac_4_r[6] = {0x12, 0x00, 0x00, 0x00, 0x00, 0x80};

    uint8_t zero_ip[4] = {0, 0, 0, 0};
    uint8_t ip_1[4] = {192, 168, 0, 2};
    uint8_t ip_2[4] = {192, 168, 1, 2};
    // uint8_t gw_1[4] = {192, 168, 0, 1};
    uint8_t gw_2[4] = {192, 168, 1, 1};
    uint8_t gw_2_r[4] = {1, 1, 168, 192};

    uint8_t zero_mask_1[2] = {0x00, 0x00};
    uint8_t mask_1[2] = {0xFF, 0xFF};
    uint8_t zero_mask_2[4] = {0x00, 0x00, 0x00, 0x00};
    uint8_t mask_2[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    uint8_t zero_mask_3[4] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t mask_3[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    uint8_t zero_eth_type[2] = {0x00, 0x00};
    uint8_t eth_type[2] = {0x08, 0x00};
    uint8_t port_num[2] = {0x1f, 0x40};
    uint8_t port_num_r[2] = {0x40, 0x1f};
    uint8_t zero_port_num[2] = {0x00, 0x00};

    uint8_t vrf[2] = {0x00, 0x00};
    uint8_t vid[2] = {0x00, 0x00};

    fill_mac_learning_table(mac_2, 0);
    fill_mac_learning_table(mac_4, 0);

    fill_routable_table(vrf, mac_2, mac_1, 0, 0);
    fill_routable_table(vrf, mac_4, mac_3, 0, 0);

    fill_unicast_routing_table(vrf, ip_2, mac_3, mac_4);
    fill_unicast_routing_table(vrf, ip_1, mac_1, mac_2);

    fill_switching_table(vrf, mac_2, 0, 0);
    fill_switching_table(vrf, mac_4, 0, 1);

    fill_get_acl_features_table(vrf, mask_1, ip_1, mask_2, ip_2, mask_2, 1, 1, 1, 1, 1, 1);
    fill_get_acl_features_table(vrf, mask_1, ip_2, mask_2, ip_1, mask_2, 1, 1, 1, 1, 1, 1);

    fill_mac_acl_table(vrf, mask_1, mac_2, mask_3, mac_4, mask_3, eth_type, mask_1, 1);
    fill_mac_acl_table(vrf, mask_1, mac_4, mask_3, mac_2, mask_3, eth_type, mask_1, 1);

    fill_ipv4_acl_table(vrf, mask_1, ip_1, mask_2, ip_2, mask_2, 0, 0, 1);
    fill_ipv4_acl_table(vrf, mask_1, ip_2, mask_2, ip_1, mask_2, 0, 0, 1);

    fill_tcp_acl_table(vrf, mask_1, port_num, mask_1, port_num, mask_1, 0, 0, 1);

    fill_udp_acl_table(vrf, mask_1, port_num, mask_1, port_num, mask_1, 1);

    set_default_action_mac_acl();
    set_default_action_ipv4_acl();
    set_default_action_udp_acl();
    set_default_action_tcp_acl();

    set_default_action_nat_src();
    set_default_action_nat_dst();
    set_default_action_nat_twice();
    set_default_action_nat_flow();
    set_default_action_nat_get_l4_infomation();
    set_default_action_ipsg();
    set_default_action_ipsg_permit_special();

    fill_nat_get_l4_infomation_table_1(6); // related to tcp
    fill_nat_get_l4_infomation_table_2(17); // related to udp

    // FIXME: When adding match part of an entry, follow the big-end
    // FIXME: When adding action parameter of an entry, >4 bytes follow the big-end, <4 bytes follow the small end.
    // related to tcp
    fill_nat_flow_table_1(vrf, mask_1, ip_1, mask_2, ip_2, mask_2, 0x06, 0xFF, port_num, mask_1, port_num, mask_1, gw_2_r, port_num_r);

    // related to udp
    fill_nat_flow_table_2(vrf, mask_1, ip_1, mask_2, ip_2, mask_2, 0x11, 0xFF, port_num, mask_1, port_num, mask_1, gw_2_r, port_num_r);

    fill_port_vlan_to_vrf_table(vrf, vid, 0);

    fill_ipsg_permit_special_table(ip_1, mask_2, ip_2, mask_2, 0x11, 0xFF, zero_port_num, zero_mask_1,
                                   zero_port_num, zero_mask_1, zero_port_num, zero_mask_1, zero_port_num, zero_mask_1);

    fill_storm_control_tbl_table(zero_port_num, mask_1, zero_mac, zero_mask_3, zero_eth_type, zero_mask_1,
                                 zero_ip, zero_mask_2, 0);
}

int main() {
    printf("Create and configure controller...\n");
    c = create_controller_with_init(11111, 3, dhf, init_simple);

    printf("Launching controller's main loop...\n");
    execute_controller(c);

    printf("Destroy controller\n");
    destroy_controller(c);

    return 0;
}

