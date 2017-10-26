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
    char buffer[2048]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_field_match_exact *exact1, *exact2; // TODO: replace to lpm

    h = create_p4_header(buffer, 0, 2048);
    te = create_p4_add_table_entry(buffer, 0, 2048);
    strcpy(te->table_name, "mac_learning");

    exact1 = add_p4_field_match_exact(te, 2048);
    strcpy(exact1->header.name, "ethernet.src_mac");
    memcpy(exact1->bitmap, smac, 6);
    exact1->length = 6 * 8 + 0;

    exact2 = add_p4_field_match_exact(te, 2048);
    strcpy(exact2->header.name, "vlan.vid");
    memcpy(exact2->bitmap, &vid, 2);
    exact2->length = 2 * 8 + 0;

    a = add_p4_action(h, 2048);
    strcpy(a->description.name, "nop");

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_exact(exact1);
    netconv_p4_field_match_exact(exact2);
    netconv_p4_action(a);

    send_p4_msg(c, buffer, 2048);

}

void fill_routable_table(uint8_t smac[6], uint8_t dmac[6], uint16_t vid, uint8_t lan) {
    char buffer[2048]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap;
    struct p4_field_match_exact *exact1, *exact2, *exact3; // TODO: replace to lpm

    h = create_p4_header(buffer, 0, 2048);
    te = create_p4_add_table_entry(buffer, 0, 2048);
    strcpy(te->table_name, "routable");

    exact1 = add_p4_field_match_exact(te, 2048);
    strcpy(exact1->header.name, "ethernet.src_mac");
    memcpy(exact1->bitmap, smac, 6);
    exact1->length = 6 * 8 + 0;

    exact2 = add_p4_field_match_exact(te, 2048);
    strcpy(exact2->header.name, "ethernet.dst_mac");
    memcpy(exact2->bitmap, dmac, 6);
    exact2->length = 6 * 8 + 0;

    exact3 = add_p4_field_match_exact(te, 2048);
    strcpy(exact3->header.name, "vlan.vid");
    memcpy(exact3->bitmap, &vid, 2);
    exact3->length = 2 * 8 + 0;

    a = add_p4_action(h, 2048);
    strcpy(a->description.name, "ucast");

    ap = add_p4_action_parameter(h, a, 2048);
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

    send_p4_msg(c, buffer, 2048);
}

void fill_unicast_routing_table(uint8_t dip[4], uint8_t smac[6], uint8_t dmac[6]) {
    char buffer[2048]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap1, *ap2;
    struct p4_field_match_exact *exact; // TODO: replace to lpm

    h = create_p4_header(buffer, 0, 2048);
    te = create_p4_add_table_entry(buffer, 0, 2048);
    strcpy(te->table_name, "unicast_routing");

    exact = add_p4_field_match_exact(te, 2048);
    strcpy(exact->header.name, "ip.dst_addr");
    memcpy(exact->bitmap, dip, 4);
    exact->length = 4 * 8 + 0;

    a = add_p4_action(h, 2048);
    strcpy(a->description.name, "set_nhop");

    ap1 = add_p4_action_parameter(h, a, 2048);
    strcpy(ap1->name, "src_mac");
    memcpy(ap1->bitmap, smac, 6);
    ap1->length = 6 * 8 + 0;

    ap2 = add_p4_action_parameter(h, a, 2048);
    strcpy(ap2->name, "dst_mac");
    memcpy(ap2->bitmap, dmac, 6);
    ap2->length = 6 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_exact(exact);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap1);
    netconv_p4_action_parameter(ap2);

    send_p4_msg(c, buffer, 2048);
}

void fill_switching_table(uint8_t dmac[4], uint16_t vid, uint8_t port) {
    char buffer[2048]; /* TODO: ugly */
    struct p4_header *h;
    struct p4_add_table_entry *te;
    struct p4_action *a;
    struct p4_action_parameter *ap;
    struct p4_field_match_exact *exact1, *exact2; // TODO: replace to lpm

    h = create_p4_header(buffer, 0, 2048);
    te = create_p4_add_table_entry(buffer, 0, 2048);
    strcpy(te->table_name, "switching");

    exact1 = add_p4_field_match_exact(te, 2048);
    strcpy(exact1->header.name, "ethernet.dst_mac");
    memcpy(exact1->bitmap, dmac, 6);
    exact1->length = 6 * 8 + 0;

    exact2 = add_p4_field_match_exact(te, 2048);
    strcpy(exact2->header.name, "vlan.vid");
    memcpy(exact2->bitmap, &vid, 2);
    exact2->length = 2 * 8 + 0;

    a = add_p4_action(h, 2048);
    strcpy(a->description.name, "forwarding");

    ap = add_p4_action_parameter(h, a, 2048);
    strcpy(ap->name, "port");
    ap->bitmap[0] = 0;
    ap->bitmap[1] = port;
    ap->length = 2 * 8 + 0;

    netconv_p4_header(h);
    netconv_p4_add_table_entry(te);
    netconv_p4_field_match_exact(exact1);
    netconv_p4_field_match_exact(exact2);
    netconv_p4_action(a);
    netconv_p4_action_parameter(ap);

    send_p4_msg(c, buffer, 2048);
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
    c = create_controller_with_init(11111, 3, dhf, init_simple);

    printf("Launching controller's main loop...\n");
    execute_controller(c);

    printf("Destroy controller\n");
    destroy_controller(c);

    return 0;
}

