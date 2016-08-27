#pragma once

#include "global.hpp"

#include "Image.hpp"
#include "Logger.hpp"
#include "ObjectManager.hpp"

class ImageManager
{
protected:
    shared_ptr<Logger> log;
    shared_ptr<ObjectManager> obj_manager;
    uint64_t scale_factor;
    unordered_map<string, weak_ptr<Image>> bucket;
    mutex bucket_mt;
    unordered_map<string, shared_future<shared_ptr<Image>>> futures;
    uint32_t num_cores;
    bool pixelated;

public:
    ImageManager(shared_ptr<Logger> _log,
                 shared_ptr<ObjectManager> _obj_manager,
                 uint64_t _scale_factor,
                 uint32_t _num_cores,
                 bool _pixelated);
    shared_ptr<Image> getImage(const string& path);
    uint32_t getNumCores();
};
