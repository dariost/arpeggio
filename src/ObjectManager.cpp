#include "ObjectManager.hpp"

ObjectManager::ObjectManager(shared_ptr<Logger> logger, const string& path)
{
    log = logger;
    base_path = path;
}

shared_ptr<Object> ObjectManager::getObject(const string& file_name, bool encrypted)
{
    lock_guard<mutex> l(mt);
    string path = base_path + file_name;
    if(bucket.count(path) && !bucket[path].expired())
        return bucket[path].lock();
    auto obj = make_shared<Object>(log, path, encrypted);
    bucket[path] = obj;
    return obj;
}
