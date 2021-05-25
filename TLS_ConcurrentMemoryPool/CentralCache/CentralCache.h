#ifndef MEMORYPOOL_CENTRALCACHE_H
#define MEMORYPOOL_CENTRALCACHE_H

#include "../Common/Common.h"

/*
进行资源的均衡，对于ThreadCache的某个资源过剩的时候，可以回收ThreadCache内部的的内存
从而可以分配给其他的ThreadCache
只有一个中心缓存，对于所有的线程来获取内存的时候都应该是一个中心缓存
所以对于中心缓存可以使用单例模式来进行创建中心缓存的类
对于中心缓存来说要加锁
*/

#endif //MEMORYPOOL_CENTRALCACHE_H
