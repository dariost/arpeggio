#include "ImageManager.hpp"

ImageManager::ImageManager(shared_ptr<Logger> _log, shared_ptr<ObjectManager> _obj_manager, uint64_t _scale_factor)
{
    log = _log;
    obj_manager = _obj_manager;
    scale_factor = _scale_factor;
}

shared_ptr<Image> ImageManager::getImage(const string& path)
{
    if(bucket.count(path) && !bucket[path].expired())
        return bucket[path].lock();
    auto img = make_shared<Image>(log, obj_manager->getObject(path), scale_factor);
    bucket[path] = img;
    return img;
}
