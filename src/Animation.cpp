#include "Animation.hpp"

#include "GLDebug.hpp"

double Animation::getAspectRatio()
{
    return aspect_ratio;
}

Animation::Animation(shared_ptr<Logger> logger,
                     shared_ptr<Config> desc,
                     shared_ptr<ImageManager> image_manager,
                     const string& _name)
{
    log = logger;
    name = _name;
    fps = 1.0;
    data = {-1.0, -1.0, 0.0, 1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0};
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
#ifdef USE_GLDEBUG
    string debug_name = "\"" + name + "\"";
    fpObjectLabel(GL_VERTEX_ARRAY, vao, debug_name.size(), debug_name.data());
    fpObjectLabel(GL_BUFFER, vbo, debug_name.size(), debug_name.data());
#endif
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // End OpenGL stuff
    setFPS(desc->get("fps", 1.0));
    auto num_frames = desc->get("num_frames", 1UL);
    string frames = name + string("/") + desc->get<string>("frames", "image.png");
    string tmp = desc->getRelativeName();
    while(tmp.back() != '/' && tmp.back() != '\\')
    {
        tmp.pop_back();
    }
    frames = tmp + frames;
    uint32_t num_cores = image_manager->getNumCores();
    vector<string> frame_names;
    char* buffer = (char*)malloc(2 << 16);
    log->check(!buffer, false, Logger::Level::CRITICAL, "Out of memory while creating animation \"", name, "\"");
    for(unsigned int i = 0; i < num_frames; i++)
    {
        memset(buffer, 0, 2 << 16);
#ifdef _MSC_VER
        sprintf(buffer, frames.c_str(), i);
#else
        snprintf(buffer, 2 << 16, frames.c_str(), i);
#endif
        frame_names.emplace_back(buffer);
    }
    free(buffer);
    reverse(frame_names.begin(), frame_names.end());
    vector<shared_ptr<Image>> image_data(num_frames);
    vector<pair<future<shared_ptr<Image>>, size_t>> futures;
    size_t frames_processed = 0;
    while(frames_processed < num_frames)
    {
        while(futures.size() < num_cores && frame_names.size())
        {
            futures.push_back(make_pair(async(launch::async,
                                              [](shared_ptr<ImageManager> im, string ss) -> auto { return im->getImage(ss); },
                                              image_manager,
                                              frame_names.back()),
                                        num_frames - frame_names.size()));
            frame_names.pop_back();
        }
        for(int i = 0; i < (int)futures.size(); i++)
        {
            auto status = futures[i].first.wait_for(chrono::microseconds(1));
            if(status == future_status::ready)
            {
                image_data[futures[i].second] = futures[i].first.get();
                frames_processed++;
                swap(futures[i], futures.back());
                futures.pop_back();
                i--;
            }
        }
    }
    setFrames(image_data);
}

void Animation::updateData(const array<GLfloat, 16>& d)
{
    data = d;
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(GLfloat), data.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

array<GLfloat, 16> Animation::getData()
{
    return data;
}

void Animation::draw()
{
    frame[getActualFrameNumber()]->bindTexture();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Animation::~Animation()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Animation::setFrames(const vector<shared_ptr<Image>>& v)
{
    log->check(v.size() > 0, true, Logger::Level::CRITICAL, "Trying to feed animation \"", name, "\" with 0 frames");
    aspect_ratio = double(v[0]->getWidth()) / double(v[0]->getHeight());
    for(size_t i = 1; i < v.size(); i++)
    {
        log->check(v[i]->getWidth(),
                   v[i - 1]->getWidth(),
                   Logger::Level::CRITICAL,
                   "In animation \"",
                   name,
                   "\" there is a frame size mismatch");
        log->check(v[i]->getHeight(),
                   v[i - 1]->getHeight(),
                   Logger::Level::CRITICAL,
                   "In animation \"",
                   name,
                   "\" there is a frame size mismatch");
    }
    frame = v;
}

void Animation::setFPS(double f)
{
    log->check(f > 0.0, true, Logger::Level::CRITICAL, "Trying to set non positive FPS in animation \"", name, "\"");
    fps = f;
}

size_t Animation::getActualFrameNumber()
{
    log->check(frame.size() > 0, true, Logger::Level::CRITICAL, "Trying to use empty animation \"", name, "\"");
    return size_t(timer.getTime() / (1.0 / fps)) % frame.size();
}

void Animation::activateTextures(bool toggle)
{
    for(auto& i : frame)
    {
        i->activateTexture(toggle);
    }
}
