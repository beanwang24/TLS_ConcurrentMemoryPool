#include "CentralCache.h"
#include "../PageCache/PageCache.h"

CentralCache CentralCache::_inst;

Span* CentralCache::GetOneSpan(SpanList& spanlist, size_t byte_size)
{
    Span* span = spanlist.Begin();
    while (span != spanlist.End())//当前找到一个span
    {
        if (span->_list != nullptr)
            return span;
        else
            span = span->_next;
    }

    // 走到这儿，说明前面没有获取到span,都是空的，到下一层pagecache获取span
    Span* newspan = PageCache::GetInstence()->NewSpan(SizeClass::NumMovePage(byte_size));
    // 将span页切分成需要的对象并链接起来
    char* cur = (char*)(newspan->_pageid << PAGE_SHIFT);
    char* end = cur + (newspan->_npage << PAGE_SHIFT);
    newspan->_list = cur;
    newspan->_objsize = byte_size;

    while (cur + byte_size < end)
    {
        char* next = cur + byte_size;
        NEXT_OBJ(cur) = next;
        cur = next;
    }
    NEXT_OBJ(cur) = nullptr;

    spanlist.PushFront(newspan);

    return newspan;
}