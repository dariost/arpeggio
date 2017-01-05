/*
 * Copyright © [2016; 2017] | Dario Ostuni <dario.ostuni@gmail.com>
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
*/

#include "ImageManager.hpp"

ImageManager::ImageManager(shared_ptr<Logger> _log,
                           shared_ptr<ObjectManager> _obj_manager,
                           uint64_t _scale_factor,
                           uint32_t _num_cores,
                           bool _pixelated)
{
    log = _log;
    obj_manager = _obj_manager;
    scale_factor = _scale_factor;
    num_cores = _num_cores;
    pixelated = _pixelated;
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
    auto img = make_shared<Image>(log, obj_manager->getObject(path), scale_factor, pixelated);
    auto img2 = img;
    bucket[path] = img;
    bucket_mt.lock();
    pro.set_value(move(img2));
    futures.erase(path);
    bucket_mt.unlock();
    return img;
}
