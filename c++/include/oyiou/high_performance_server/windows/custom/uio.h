//
// Created by leever on 2023/3/11.
//

#ifndef C_UIO_H
#define C_UIO_H

#include "high_performance_server.h"

struct iovec{
    void *iov_base; /* Pointer to data. */
    size_t iov_len; /* Length of data. */
};
/*实现类似于writev功能*/
static long writev(SOCKET socket , struct iovec *iov , int count)
{
    long totallen ,tlen = -1;
    while(count)
    {
        tlen = send(socket, (const char*)iov->iov_base,iov->iov_len,0);
        if(tlen < 0)
            return totallen;
        totallen+=tlen;
        iov++;
        count--;
    }
}
int readv(int handle, struct iovec *iov, int count) {

    long r, t = 0;
    while (count) {

        r = read(handle, iov->iov_base, iov->iov_len);
        if (r < 0)
            return r;
        t += r;
        iov++;
        count--;

    }
}
#endif //C_UIO_H
