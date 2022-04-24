/* 为响应分配内存，大小为1字节的消息类型，
加上2字节的有效载荷长度，
加上有效载荷，加上填充物*/
unsigned int payload;
unsigned int padding = 16; /*使用最小的填充物 */

//  先从类型字段读取
hbtype = *p++; /*这条指令之后，指针p将指向payload_length字段*/

//  从请求包的payload_length字段中读取
n2s(p, payload); /* 函数n2s(p, payload)从指针p中读出16位，
                * 并将该值存储在INT变量 "payload "中。*/

pl = p; // pl 指向有效载荷内容的开头
if (hbtype == TLS1_HB_REQUEST)
{
    unsigned char *buffer, *bp;
    int r;
    /* 为响应分配内存，大小为1字节的消息类型，
    加上2字节的有效载荷长度，加上有效载荷，加上填充物 */

    buffer = OPENSSL_malloc(1 + 2 + payload + padding);
    bp = buffer;

    // 输入响应类型、长度和复制有效载荷
    *bp++ = TLS1_HB_RESPONSE;
    s2n(payload, bp);
    // 复制有效载荷
    memcpy(bp, pl, payload);
    /*pl是指向有效载荷内容开头的指针*/
    bp += payload;
    // 随机填充
    RAND_pseudo_bytes(bp, padding);
    //这个函数将从缓冲区复制3+payload+padding的字节，并将它们放入心跳响应包，以发回给请求客户端。
    OPENSSL_free(buffer);
    r = ssl3_write_bytes(s, TLS1_RT_HEARTBEAT, buffer, 3 + payload + padding);
}