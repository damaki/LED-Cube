#ifndef RAIN_EFFECT_H
#define RAIN_EFFECT_H
#include "effect_base.h"
#include <list>

namespace effects
{

struct RainDrop
{
    float height;
    float brightness;

    RainDrop(float _height, float _brightness)
        : height(_height), brightness(_brightness)
    {}
};

class Rain : public BaseEffect
{
    Q_OBJECT
public:
    Rain();
    virtual ~Rain();

    virtual void start();
    virtual void stop();

    virtual void update(boost::asio::serial_port &port);

private slots:
    void set_decay_rate(int rate);
    void set_spawn_rate(int rate);
    void set_fall_rate(int rate);

private:
    uint32_t m_counter;
    float m_decay_rate;
    float m_fall_rate;
    float m_spawn_rate;
    float m_spawn_counter;

    std::list<RainDrop> m_drops[CUBE_SIZE][CUBE_SIZE];

    QSlider *m_pDecaySlider;
    QSlider *m_pFallRateSlider;
    QSlider *m_pSpawnRateSlider;
};

} // namespace effects

#endif // RAIN_EFFECT_H
