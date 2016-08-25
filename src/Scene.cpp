#include "Scene.hpp"

Scene::Scene(shared_ptr<Logger> logger, string _name, shared_ptr<Config> _conf)
{
    log = logger;
    name = _name;
    conf = _conf;
}

void Scene::activateTextures(bool toggle)
{
    (void)toggle;
}

void Scene::draw()
{
}

void Scene::exec()
{
}

double Scene::getPriority()
{
    return conf->get("render_priority", 0.0);
}
