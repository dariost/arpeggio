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

#include "Logger.hpp"
#include "Object.hpp"
#include "Texture.hpp"

class Image
{
protected:
    shared_ptr<Logger> log;
    string path;
    uint32_t width;
    uint32_t height;
    vector<uint8_t> data;
    shared_ptr<Texture> texture;
    bool pixelated;

public:
    Image(shared_ptr<Logger> logger, shared_ptr<Object> obj, uint32_t scale_factor, bool _pixelated);
    uint32_t getWidth();
    uint32_t getHeight();
    void* getData();
    string getName();
    bool isTextureActive();
    void activateTexture(bool toggle = true);
    void bindTexture();
};
