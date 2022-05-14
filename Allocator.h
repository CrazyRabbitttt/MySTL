/*
*Create by SGX, 5.14
*/

#ifndef _ALLOC_
#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>


namespace SS
{

    template<class T>
    inline T* _allocate(ptrdiff_t size, T*) {   
        std::set_new_handler(0);
        T *tmp = (T*)(::operator new((size_t)(size * sizeof(T))));          //都是调用::operator new
        if (tmp == 0) {
            std::cerr << "out of memory" << std::endl;
            exit(1);
        }
        return tmp;
    }

    template<class T>
    inline void _deallocate(T *buffer) {            //从指针开始的地方进行删除
        ::operator delete(buffer);
    }

    template<class T1, class T2>
    inline void _construct(T1 *p, const T2& value) {
        new (p) T1(value);
    }


    template<class T>
    inline void _destory(T *ptr) {
        ptr->~T();
    }


    template<class T>
    class allocator{
    public:
        typedef T           value_type;
        typedef T*          pointer;
        typedef const T*    const_pointer;
        typedef T&          reference;
        typedef const T&    const_reference;
        typedef size_t      size_type;
        typedef ptrdiff_t   difference_type;            //8字节

        //rebind allocator of type U,内部进行了一个嵌套

        template<class U>
        struct rebind{
            typedef allocator<U> other;
        };
        pointer allocate(size_type n, const void * hint = 0) {
            return _allocate((difference_type)n, (pointer)0);
        }
        
        void deallocate(pointer p, size_type n) {
            _deallocate(p);
        }

        void construct(pointer p, const T& value) {
            _construct(p, value);
        }

        void destory(pointer p) {
            _destory(p);
        }

        const_pointer const_address(const_reference x) {
            return (const_pointer)&x;           //返回地址
        }

        size_type max_size() const {
            return size_type(UINT_MAX/sizeof(T));
        }
    };
};


#define _ALLOC_

#endif