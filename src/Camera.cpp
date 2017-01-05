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

#include "Camera.hpp"

Camera::Camera(shared_ptr<Logger> logger, double _real_width, double _real_height, double _height, double _pos_x, double _pos_y)
{
    log = logger;
    real_width = _real_width;
    real_height = _real_height;
    height = _height;
    pos_x = _pos_x;
    pos_y = _pos_y;
    width = height * real_width / real_height;
}

double Camera::getWidth()
{
    return width;
}

double Camera::getHeight()
{
    return height;
}

pair<double, double> Camera::getPoint(double x, double y)
{
    pair<double, double> tmp;
    x -= pos_x;
    y -= pos_y;
    tmp.first = 2.0 * x / width;
    tmp.second = 2.0 * y / height;
    return tmp;
}
