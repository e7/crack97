#ifndef __CRACK97_SINGLETON_H__
#define __CRACK97_SINGLETON_H__


using std::map;
using std::string;


namespace e7 {
namespace common {
class singleton_mng
{
public:
    int append(string const &name, void *p)
    {
        if (singleton_objs.end() != this->singleton_objs.find(name)) {
            return -1;
        }

        this->singleton_objs[name] = p;

        return 0;
    }

    void *get_instance(string const &name)
    {
        if (singleton_objs.end() == this->singleton_objs.find(name)) {
            return NULL;
        }

        return this->singleton_objs[name];
    }

private:
    void *operator new(size_t size);
    void operator delete(void *p);
    void *operator new[](size_t size);
    void operator delete[](void *p);

private:
    map<string, void *> singleton_objs;
};
}
}


// 全局变量
namespace crack97 {
    extern e7::common::singleton_mng g_singleton_mng;
}
#endif // __CRACK97_SINGLETON_H__
