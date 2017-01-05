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
