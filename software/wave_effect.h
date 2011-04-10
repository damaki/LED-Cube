#ifndef WAVE_EFFECT_H
#define WAVE_EFFECT_H
#include "effect_base.h"

namespace effects
{

class Wave : public BaseEffect
{
public:
    Wave();
    ~Wave();

    virtual void start();
    virtual void stop();

    virtual void update(boost::asio::serial_port &port);

private:
    float m_speed;
    float m_pos;
    float m_size;
    float m_height;
};

} // namespace effects

#endif // WAVE_EFFECT_H
