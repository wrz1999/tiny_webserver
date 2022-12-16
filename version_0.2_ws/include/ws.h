#ifndef WS_H_
#define WS_H_
//小端
typedef struct _ws_ophdr {
    unsigned char opcode: 4,
            rsv3: 1,
            rsv2: 1,
            rsv1: 1,
            fin: 1;
    unsigned char payload_len: 7,
            mask: 1;
} ws_ophdr;

typedef struct _ws_ophdr126 {
    unsigned short payload_len;
    char mask_key[4];
} ws_ophdr126;

typedef struct _ws_ophdr127 {
    long long payload_len;
    char mask_key[4];
} ws_ophdr127;
#endif