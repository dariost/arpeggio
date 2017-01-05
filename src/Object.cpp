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

#include "Object.hpp"

Object::Object(shared_ptr<Logger> logger, const string& file_name, const string& rn, bool encrypted)
{
    log = logger;
    name = file_name;
    relative_name = rn;
    (void)encrypted;
    log->check(encrypted, false, Logger::Level::CRITICAL, "File encryption is not implemented yet");
    errno = 0;
    FILE* in = fopen(name.c_str(), "rb");
    log->check(!in, false, Logger::Level::CRITICAL, "Cannot open \"", name, "\": ", strerror(errno));
    uint8_t buffer[4096];
    while(!feof(in))
    {
        size_t ret = fread(buffer, 1, 4096, in);
        if(ret == 0)
            break;
        data.insert(data.end(), buffer, buffer + ret);
    }
    fclose(in);
    data.push_back(0);
}

size_t Object::getSize()
{
    return data.size() - 1;
}

void* Object::getData()
{
    return data.data();
}

const char* Object::getString()
{
    return (const char*)data.data();
}

string Object::getName()
{
    return name;
}

string Object::getRelativeName()
{
    return relative_name;
}
