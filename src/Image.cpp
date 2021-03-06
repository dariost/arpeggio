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

#include "Image.hpp"

Image::Image(shared_ptr<Logger> logger, shared_ptr<Object> obj, uint32_t scale_factor, bool _pixelated)
{
    log = logger;
    pixelated = _pixelated;
    path = obj->getName();
    SDL_RWops* rwops = SDL_RWFromConstMem(obj->getData(), obj->getSize());
    log->check(!rwops, false, Logger::Level::CRITICAL, "Cannot get a pointer to \"", path, "\": ", SDL_GetError());
    SDL_Surface* raw_surf = IMG_Load_RW(rwops, 0);
    SDL_Surface* surf;
    log->check(!raw_surf, false, Logger::Level::CRITICAL, "Cannot open image \"", path, "\": ", IMG_GetError());
    if(raw_surf->format->format == SDL_PIXELFORMAT_ABGR8888)
        surf = raw_surf;
    else
        surf = SDL_ConvertSurfaceFormat(raw_surf, SDL_PIXELFORMAT_ABGR8888, 0);
    log->check(!surf, false, Logger::Level::CRITICAL, "Cannot convert image \"", path, "\": ", SDL_GetError());
    log->check(surf->w <= ARPEGGIO_MAX_TEXTURE_SIZE, true, Logger::Level::CRITICAL, "Image \"", path, "\" width is too large");
    log->check(surf->h <= ARPEGGIO_MAX_TEXTURE_SIZE, true, Logger::Level::CRITICAL, "Image \"", path, "\" height is too large");
    log->check(surf->w & 0x0F, 0, Logger::Level::CRITICAL, "Image \"", path, "\" width is not a multiple of 16");
    log->check(surf->h & 0x0F, 0, Logger::Level::CRITICAL, "Image \"", path, "\" height is not a multiple of 16");
    uint8_t* p_data = (uint8_t*)surf->pixels;
    vector<uint8_t> raw_data;
    for(uint32_t y = 0; y < (uint32_t)surf->h; y++)
    {
        for(uint32_t x = 0; x < (uint32_t)surf->w; x++)
        {
            for(uint32_t c = 0; c < 4; c++)
            {
                raw_data.push_back(p_data[y * surf->pitch + x * 4 + c]);
            }
        }
    }
    uint32_t current_width = surf->w;
    uint32_t current_height = surf->h;
    if(surf != raw_surf)
        SDL_FreeSurface(surf);
    SDL_FreeSurface(raw_surf);
    SDL_RWclose(rwops);
    for(uint32_t i = 1; i < scale_factor; i *= 2)
    {
        vector<uint8_t> tmp_data;
        for(uint32_t y = 0; y < current_height; y += 2)
        {
            for(uint32_t x = 0; x < current_width; x += 2)
            {
                for(uint32_t c = 0; c < 4; c++)
                {
                    uint16_t sum = 0;
                    sum += raw_data[y * current_width * 4 + x * 4 + c];
                    sum += raw_data[(y + 1) * current_width * 4 + x * 4 + c];
                    sum += raw_data[y * current_width * 4 + (x + 1) * 4 + c];
                    sum += raw_data[(y + 1) * current_width * 4 + (x + 1) * 4 + c];
                    tmp_data.push_back(sum / 4);
                }
            }
        }
        raw_data = tmp_data;
        current_width /= 2;
        current_height /= 2;
    }
    width = current_width;
    height = current_height;
    data = raw_data;
}

uint32_t Image::getWidth()
{
    return width;
}

uint32_t Image::getHeight()
{
    return height;
}

void* Image::getData()
{
    return data.data();
}

string Image::getName()
{
    return path;
}

bool Image::isTextureActive()
{
    return bool(texture);
}

void Image::activateTexture(bool toggle)
{
    if((toggle && isTextureActive()) || (!toggle && !isTextureActive()))
        return;
    if(toggle)
        texture = make_shared<Texture>(log, width, height, data, path, pixelated);
    else
        texture.reset();
}

void Image::bindTexture()
{
    log->check(isTextureActive(), true, Logger::Level::CRITICAL, "Trying to bind \"", path, "\" while not in VRAM");
    texture->bind();
}
