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

class Timer
{
protected:
    chrono::time_point<std::chrono::high_resolution_clock> _initial;
    chrono::time_point<std::chrono::high_resolution_clock> _circle;
    bool _paused;
    double _bias;

public:
    Timer();
    void reset();
    void pause();
    void unpause();
    double getTime();
    void addBias(double b);
};
