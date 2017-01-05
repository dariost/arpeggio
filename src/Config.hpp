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

class Config
{
protected:
    shared_ptr<Logger> log;
    string name;
    string relative_name;
    json internal;

public:
    Config(shared_ptr<Logger> logger, const string& debug_name = "(default)", const string& rn = "NULL");
    string getRelativeName();
    string getName();
    void parseConfig(const string& config);
    void parseConfig(shared_ptr<Object> config);
    string getConfig();
    template <typename T>
    T get(const string& obj_name, const T& default_value = T())
    {
        log->check(internal.is_object(),
                   true,
                   Logger::Level::CRITICAL,
                   "Error while reading \"",
                   obj_name,
                   "\" from \"",
                   name,
                   "\": not an object");
        T tmp;
        try
        {
            tmp = internal[obj_name].get<T>();
        }
        catch(exception& e)
        {
            log->log(
                Logger::Level::DEBUG, "Cannot read \"", obj_name, "\" from \"", name, "\": ", e.what(), "; using default value");
            return default_value;
        }
        return tmp;
    }
    vector<json> getv(const string& obj_name);
    json get_json(const string& obj_name);
    template <typename T>
    void set(const string& obj_name, const T& value = T())
    {
        try
        {
            internal[obj_name] = value;
        }
        catch(exception& e)
        {
            log->log(Logger::Level::CRITICAL, "Cannot write property \"", obj_name, "\" in config \"", name, "\": ", e.what());
        }
    }
};
