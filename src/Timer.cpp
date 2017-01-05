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

#include "Timer.hpp"

Timer::Timer()
{
    reset();
}

void Timer::reset()
{
    _initial = chrono::high_resolution_clock::now();
    _paused = false;
    _bias = 0.0;
}

void Timer::pause()
{
    if(_paused)
        return;
    _paused = true;
    _circle = chrono::high_resolution_clock::now();
}

void Timer::unpause()
{
    if(!_paused)
        return;
    _paused = false;
    _bias -= chrono::duration<double>(std::chrono::high_resolution_clock::now() - _circle).count();
}

double Timer::getTime()
{
    double act_time = chrono::duration<double>(std::chrono::high_resolution_clock::now() - _initial).count();
    act_time += _bias;
    if(_paused)
        act_time -= chrono::duration<double>(std::chrono::high_resolution_clock::now() - _circle).count();
    return act_time;
}

void Timer::addBias(double b)
{
    _bias += b;
}
