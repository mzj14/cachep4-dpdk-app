#include "dataplane.h"// sugar@18
#include "actions.h"// sugar@19
#include "data_plane_data.h"// sugar@20

lookup_table_t table_config[NB_TABLES] = {// sugar@22
        {// sugar@25
                .name= "mac_acl",// sugar@26
                .id = TABLE_mac_acl,// sugar@27
                .type = LOOKUP_TERNARY,// sugar@28
                .key_size = 14,// sugar@29
                .val_size = sizeof(struct mac_acl_action),// sugar@30
                .min_size = 0, //None,// sugar@31
                .max_size = 255 //None// sugar@32
        },// sugar@33
        {// sugar@25
                .name= "ipv4_acl",// sugar@26
                .id = TABLE_ipv4_acl,// sugar@27
                .type = LOOKUP_TERNARY,// sugar@28
                .key_size = 9,// sugar@29
                .val_size = sizeof(struct ipv4_acl_action),// sugar@30
                .min_size = 0, //None,// sugar@31
                .max_size = 255 //None// sugar@32
        },// sugar@33
        {// sugar@25
                .name= "tcp_acl",// sugar@26
                .id = TABLE_tcp_acl,// sugar@27
                .type = LOOKUP_TERNARY,// sugar@28
                .key_size = 5,// sugar@29
                .val_size = sizeof(struct tcp_acl_action),// sugar@30
                .min_size = 0, //None,// sugar@31
                .max_size = 255 //None// sugar@32
        },// sugar@33
        {// sugar@25
                .name= "udp_acl",// sugar@26
                .id = TABLE_udp_acl,// sugar@27
                .type = LOOKUP_TERNARY,// sugar@28
                .key_size = 4,// sugar@29
                .val_size = sizeof(struct udp_acl_action),// sugar@30
                .min_size = 0, //None,// sugar@31
                .max_size = 255 //None// sugar@32
        },// sugar@33
        {// sugar@25
                .name= "get_acl_features",// sugar@26
                .id = TABLE_get_acl_features,// sugar@27
                .type = LOOKUP_TERNARY,// sugar@28
                .key_size = 8,// sugar@29
                .val_size = sizeof(struct get_acl_features_action),// sugar@30
                .min_size = 0, //None,// sugar@31
                .max_size = 255 //None// sugar@32
        },// sugar@33
        {// sugar@25
                .name= "cache",// sugar@26
                .id = TABLE_cache,// sugar@27
                .type = LOOKUP_EXACT,// sugar@28
                .key_size = 34,// sugar@29
                .val_size = sizeof(struct cache_action),// sugar@30
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
                .key_size = 14,// sugar@29
                .val_size = sizeof(struct routable_action),// sugar@30
                .min_size = 0, //1024,// sugar@31
                .max_size = 255 //1024// sugar@32
        },// sugar@33
        {// sugar@25
                .name= "unicast_routing",// sugar@26
                .id = TABLE_unicast_routing,// sugar@27
                .type = LOOKUP_EXACT,// sugar@28
                .key_size = 4,// sugar@29
                .val_size = sizeof(struct unicast_routing_action),// sugar@30
                .min_size = 0, //1024,// sugar@31
                .max_size = 255 //1024// sugar@32
        },// sugar@33
        {// sugar@25
                .name= "switching",// sugar@26
                .id = TABLE_switching,// sugar@27
                .type = LOOKUP_EXACT,// sugar@28
                .key_size = 8,// sugar@29
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
