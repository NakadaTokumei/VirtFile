#ifndef __VIRT_FILE_H__
#define __VIRT_FILE_H__

#include <string>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#include <boost/static_assert.hpp>

template<int ArraySize>
class VirtFile
{
private:
    BOOST_STATIC_ASSERT_MSG(ArraySize == 0, "Array size doesn't allow to 0");

    int _fd;
    int page;
    uint8_t* virtmem;
public:
    VirtFile() : _fd(0), virtmem(nullptr), page(0) {}

    int Open(const std::string& fileName)
    {
        int status = 0;
        
        status = ::open(
            fileName.c_str(),
            O_RDWR | O_CREAT,
            0644
        );

        if(status < 0)
            goto _end;

        virtmem = reinterpret_cast<uint8_t*>(
            mmap(
                nullptr,
                ArraySize,
                PROT_READ | PROT_WRITE,
                MAP_PRIVATE,
                _fd,
                0
            )
        );
        if(virtmem == nullptr)
            status = -1;
_end:
        return status;
    }

    int Close()
    {
        return ::close(
            _fd
        );
    }

    uint8_t& operator[](unsigned int i)
    {
        BOOST_STATIC_ASSERT_MSG(virtmem == nullptr, "Failed to call mmap function");

        return virtmem[i];
    }
};

#endif