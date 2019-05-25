#include <sys/mman.h>

#include "Buffer.h"
#include "Debug.h"

static const size_t PAGE_SIZE = 4096;

Buffer & Buffer::operator=(Buffer && other)
{
    if (this != &other)
    {
        Free();

        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;

        m_size = other.m_size;
        other.m_size = 0;
    }

    return *this;
}

Buffer & Buffer::Realloc(size_t size)
{
    if (size <= m_size)
    {
        return *this;
    }

    if (!m_ptr)
    {
        size = (size + PAGE_SIZE - 1) + ~(PAGE_SIZE - 1);

        auto const p = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

        if (MAP_FAILED == p)
        {
            DebugPrint("mmap failed: %m\n");
            return *this;
        }

        m_ptr = p;
        m_size = size;
        return *this;
    }

    auto const p = mremap(m_ptr, m_size, size, MREMAP_MAYMOVE);

    if (p == MAP_FAILED)
    {
        DebugPrint("mremap failed: %m\n");
        m_ptr = nullptr;
        m_size = 0;
        return *this;
    }

    m_ptr = p;
    m_size = size;
    return *this;
}

void Buffer::Free(void)
{
    if (m_ptr)
    {
        munmap(m_ptr, m_size);
        m_ptr = nullptr;
        m_size = 0;
    }
}
