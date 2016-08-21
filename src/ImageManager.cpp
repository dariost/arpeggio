#include "ImageManager.hpp"

ImageManager::ImageManager(shared_ptr<Logger> _log,
                           shared_ptr<ObjectManager> _obj_manager,
                           uint64_t _scale_factor,
                           uint32_t _num_cores)
{
    log = _log;
    obj_manager = _obj_manager;
    scale_factor = _scale_factor;
    num_cores = _num_cores;
}

uint32_t ImageManager::getNumCores()
{
    return num_cores;
}

shared_ptr<Image> ImageManager::getImage(const string& path)
{
    bucket_mt.lock();
    if(bucket.count(path) && !bucket[path].expired())
    {
        auto tmp_ptr = bucket[path].lock();
        bucket_mt.unlock();
        return tmp_ptr;
    }
    if(futures.count(path))
    {
        shared_future<shared_ptr<Image>> f = futures[path];
        bucket_mt.unlock();
        log->check(f.valid(), true, Logger::Level::CRITICAL, "Deadlock while reading image \"", path, "\"");
        return f.get();
    }
    promise<shared_ptr<Image>> pro;
    shared_future<shared_ptr<Image>> fut(pro.get_future());
    futures[path] = fut;
    bucket_mt.unlock();
    auto img = make_shared<Image>(log, obj_manager->getObject(path), scale_factor);
    auto img2 = img;
    bucket[path] = img;
    bucket_mt.lock();
    pro.set_value(move(img2));
    futures.erase(path);
    bucket_mt.unlock();
    return img;
}
