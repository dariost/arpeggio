#pragma once

#include "global.hpp"

#include "Animation.hpp"
#include "Camera.hpp"
#include "Config.hpp"
#include "Drawable.hpp"
#include "Logger.hpp"

class Actor : public Drawable
{
protected:
    shared_ptr<Logger> log;
    shared_ptr<Config> conf;
    string name;
    unordered_map<string, shared_ptr<Animation>> act;
    unordered_map<string, double> custom_height;
    double main_height;
    string current_act;
    shared_ptr<ImageManager> im;
    shared_ptr<ObjectManager> om;
    shared_ptr<Camera> camera;

public:
    Actor(shared_ptr<Logger> logger,
          const string& _name,
          shared_ptr<Config> _conf,
          shared_ptr<ImageManager> _im,
          shared_ptr<ObjectManager> _om,
          shared_ptr<Camera> _camera);
    void activateTextures(bool toggle = true);
    void exec(double pos_x, double pos_y, double horiz_perc = 1.0, double vert_perc = 1.0);
    void draw();
    void changeAct(const string& new_act);
    double getWidth();
    double getHeight();
};
