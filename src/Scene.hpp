#pragma once

#include "global.hpp"

#include "Actor.hpp"
#include "Camera.hpp"
#include "Config.hpp"
#include "ImageManager.hpp"
#include "Logger.hpp"
#include "ObjectManager.hpp"

class Scene
{
protected:
    class actor_data
    {
    public:
        double pos_x;
        double pos_y;
        shared_ptr<Actor> actor;
        void exec()
        {
            actor->exec(pos_x, pos_y);
        }
        void draw()
        {
            actor->draw();
        }
        actor_data(shared_ptr<Actor> _actor, double _pos_x, double _pos_y)
        {
            actor = _actor;
            pos_x = _pos_x;
            pos_y = _pos_y;
        }
        actor_data(const actor_data& o)
        {
            actor = o.actor;
            pos_x = o.pos_x;
            pos_y = o.pos_y;
        }
        actor_data()
        {
            pos_x = 0.0;
            pos_y = 0.0;
        }
        bool operator<(const actor_data& o) const
        {
            if(pos_y != o.pos_y)
                return pos_y < o.pos_y;
            return pos_x < o.pos_x;
        }
    };
    unordered_map<string, actor_data> actors;
    shared_ptr<Logger> log;
    shared_ptr<ImageManager> im;
    shared_ptr<ObjectManager> om;
    string name;
    shared_ptr<Config> conf;
    shared_ptr<Camera> camera;
    double render_priority;
    duk_context* js_ctx;
    double real_width;
    double real_height;

public:
    Scene(shared_ptr<Logger> logger,
          string _name,
          shared_ptr<Config> _conf,
          double _real_width,
          double _real_height,
          shared_ptr<ImageManager> _im,
          shared_ptr<ObjectManager> _om);
    ~Scene();
    void activateTextures(bool toggle = true);
    void draw();
    void exec();
    double getPriority();
};
