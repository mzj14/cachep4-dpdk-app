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
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_field_match_exact *exact1, *exact2; // TODO: replace to lpm

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

void fill_routable_table(uint8_t smac[6], uint8_t dmac[6], uint16_t vid, uint8_t lan) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap;
    struct p4_field_match_exact *exact1, *exact2, *exact3; // TODO: replace to lpm

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "routable");

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
    netconv_p4_field_match_exact(exact1);
    netconv_p4_field_match_exact(exact2);
    netconv_p4_field_match_exact(exact3);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap);

    send_p4_msg(c, buffer, 4096);
}

void fill_unicast_routing_table(uint8_t dip[4], uint8_t smac[6], uint8_t dmac[6]) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap1, *ap2;
    struct p4_field_match_exact *exact; // TODO: replace to lpm

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "unicast_routing");

    exact = add_p4_field_match_exact(te, 4096);
    strcpy(exact->header.name, "ip.dst_addr");
    memcpy(exact->bitmap, dip, 4);
    exact->length = 4 * 8 + 0;

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
    netconv_p4_field_match_exact(exact);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap1);
    netconv_p4_action_parameter(ap2);

    send_p4_msg(c, buffer, 4096);
}

void fill_switching_table(uint8_t dmac[4], uint16_t vid, uint16_t port) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap;
    struct p4_field_match_exact *exact1, *exact2; // TODO: replace to lpm

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "switching");

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
    netconv_p4_field_match_exact(exact1);
    netconv_p4_field_match_exact(exact2);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap);

    send_p4_msg(c, buffer, 4096);
}

void fill_cache_table(uint16_t iport, uint8_t smac_1[6], uint8_t dmac_1[6], uint8_t dip[4], uint16_t vid_1,
                       uint16_t eport, uint8_t smac_2[6], uint8_t dmac_2[6], uint16_t vid_2, uint16_t grp) {
    char buffer[4096]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap1, *ap2, *ap3, *ap4, *ap5;
    struct p4_field_match_exact *exact1, *exact2, *exact3, *exact4, *exact5; // TODO: replace to lpm

    // printf("enter fill_cache_table function.\n");

    h = create_p4_header(buffer, 0, 4096);
    te = create_p4_add_table_entry(buffer, 0, 4096);
    strcpy(te->table_name, "cache");

    // printf("you know 1.\n");

    exact1 = add_p4_field_match_exact(te, 4096);
    strcpy(exact1->header.name, "standard_metadata.ingress_port");
    memcpy(exact1->bitmap, &iport, 2);
    exact1->length = 2 * 8 + 0;

    // printf("you know 2.\n");

    exact2 = add_p4_field_match_exact(te, 4096);
    strcpy(exact2->header.name, "ethernet.src_mac");
    memcpy(exact2->bitmap, smac_1, 6);
    exact2->length = 6 * 8 + 0;

    // printf("you know 3.\n");

    exact3 = add_p4_field_match_exact(te, 4096);
    strcpy(exact3->header.name, "ethernet.dst_mac");
    memcpy(exact3->bitmap, dmac_1, 6);
    exact3->length = 6 * 8 + 0;

    // printf("you know 4.\n");

    exact4 = add_p4_field_match_exact(te, 4096);
    strcpy(exact4->header.name, "ip.dst_addr");
    memcpy(exact4->bitmap, dip, 4);
    exact4->length = 4 * 8 + 0;

    // printf("you know 5.\n");


    exact5 = add_p4_field_match_exact(te, 4096);
    // printf("you know 5.1\n");
    strcpy(exact5->header.name, "vlan.vid");
    // printf("you know 5.2\n");
    memcpy(exact5->bitmap, &vid_1, 2);
    // printf("you know 5.3\n");
    exact5->length = 2 * 8 + 0;

    // printf("you know 6.\n");

    a = add_p4_action(h, 4096);
    strcpy(a->description.name, "cache_action");

    // printf("you know 7.\n");

    ap1 = add_p4_action_parameter(h, a, 4096);
    // printf("you know 7.1\n");
    strcpy(ap1->name, "port");
    // printf("you know 7.2\n");
    memcpy(ap1->bitmap, &eport, 2);
    // printf("you know 7.3");
    ap1->length = 2 * 8 + 0;

    // printf("you know 8.\n");

    ap2 = add_p4_action_parameter(h, a, 4096);
    // printf("you know 8.1\n");
    strcpy(ap2->name, "src_mac");
    // printf("you know 8.2\n");
    memcpy(ap2->bitmap, smac_2, 6);
    ap2->length = 6 * 8 + 0;

    // printf("you know 9.\n");

    ap3 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap3->name, "dst_mac");
    memcpy(ap3->bitmap, dmac_2, 6);
    ap3->length = 6 * 8 + 0;

    // printf("you know 10.\n");

    ap4 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap4->name, "vid");
    memcpy(ap4->bitmap, &vid_2, 2);
    ap4->length = 2 * 8 + 0;

    // printf("you know 11.\n");

    ap5 = add_p4_action_parameter(h, a, 4096);
    strcpy(ap5->name, "grp");
    memcpy(ap5->bitmap, &grp, 2);
    ap5->length = 2 * 8 + 0;

    // printf("you know 1.\n");

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_exact(exact1);
    netconv_p4_field_match_exact(exact2);
    netconv_p4_field_match_exact(exact3);
    netconv_p4_field_match_exact(exact4);
    netconv_p4_field_match_exact(exact5);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap1);
    netconv_p4_action_parameter(ap2);
    netconv_p4_action_parameter(ap3);
    netconv_p4_action_parameter(ap4);
    netconv_p4_action_parameter(ap5);

    printf("begin to send p4 msg for cache table.\n");

    send_p4_msg(c, buffer, 4096);
}

void dhf(void *b) {
    printf("Unknown digest received\n");
}

void init_simple() {
    uint8_t mac_1[6] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x01};
    uint8_t mac_2[6] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x02};
    uint8_t mac_3[6] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x11};
    uint8_t mac_4[6] = {0x80, 0x00, 0x00, 0x00, 0x00, 0x12};

    uint8_t ip_1[4] = {192, 168, 0, 2};
    uint8_t ip_2[4] = {192, 168, 1, 2};

    fill_cache_table(0, mac_2, mac_1, ip_2, 0, 1, mac_3, mac_4, 0, 0);
    fill_cache_table(1, mac_4, mac_3, ip_1, 0, 0, mac_1, mac_2, 0, 0);

    fill_mac_learning_table(mac_2, 0);
    fill_mac_learning_table(mac_4, 0);

    fill_routable_table(mac_2, mac_1, 0, 0);
    fill_routable_table(mac_4, mac_3, 0, 0);

    fill_unicast_routing_table(ip_2, mac_3, mac_4);
    fill_unicast_routing_table(ip_1, mac_1, mac_2);

    fill_switching_table(mac_2, 0, 0);
    fill_switching_table(mac_4, 0, 1);
}

int main() {
    printf("Create and configure controller...\n");
    c = create_controller_with_init(11110, 3, dhf, init_simple);

    printf("Launching controller's main loop...\n");
    execute_controller(c);

    printf("Destroy controller\n");
    destroy_controller(c);

    return 0;
}

