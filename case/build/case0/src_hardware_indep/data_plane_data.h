#ifndef __DATA_PLANE_DATA_H__// sugar@14
#define __DATA_PLANE_DATA_H__// sugar@15

#include "parser.h"// sugar@17

#define NB_TABLES 6// sugar@19

enum table_names {// sugar@21
    TABLE_mac_learning,// sugar@23
    TABLE_routable,// sugar@23
    TABLE_unicast_routing,// sugar@23
    TABLE_switching,// sugar@23
    TABLE_multicast_routing,// sugar@23
    TABLE_igmp,// sugar@23
    TABLE_// sugar@24
};// sugar@25

#define NB_COUNTERS 0// sugar@27

enum counter_names {// sugar@29
    COUNTER_// sugar@32
};// sugar@33

#define NB_REGISTERS 0// sugar@35

enum register_names {// sugar@37
    REGISTER_// sugar@40
};// sugar@41

#endif // __DATA_PLANE_DATA_H__// sugar@43
