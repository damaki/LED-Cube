#include "rain_effect.h"
#include <QSlider>

#define MIN_DECAY_RATE (0.005f)
#define MAX_DECAY_RATE (0.1f)

#define MIN_FALL_RATE (0.001f)
#define MAX_FALL_RATE (1.0f)

namespace effects
{

Rain::Rain()
    : BaseEffect("Rain", ":/forms/rain_effect_ctrl.ui")
    , m_counter(0)
    , m_pDecaySlider(NULL)
    , m_pFallRateSlider(NULL)
    , m_pSpawnRateSlider(NULL)
{
    m_decay_rate = 0.01f;
    m_fall_rate = 0.15f;

    m_pDecaySlider = m_pCtrls->findChild<QSlider*>("slider_decayRate");
    m_pFallRateSlider = m_pCtrls->findChild<QSlider*>("slider_fallRate");
    m_pSpawnRateSlider = m_pCtrls->findChild<QSlider*>("slider_spawnRate");

    connect(m_pDecaySlider, SIGNAL(valueChanged(int)), this, SLOT(set_decay_rate(int)));
    connect(m_pFallRateSlider, SIGNAL(valueChanged(int)), this, SLOT(set_fall_rate(int)));
    connect(m_pSpawnRateSlider, SIGNAL(valueChanged(int)), this, SLOT(set_spawn_rate(int)));

    int slider_diff = m_pDecaySlider->maximum() - m_pDecaySlider->minimum();
    m_pDecaySlider->setValue((m_decay_rate - MIN_DECAY_RATE)*slider_diff);

    slider_diff = m_pFallRateSlider->maximum() - m_pFallRateSlider->minimum();
    m_pFallRateSlider->setValue((m_fall_rate - MIN_FALL_RATE)*slider_diff);
}

Rain::~Rain()
{

}

void Rain::start()
{
    memset(m_cube, 0, sizeof(m_cube));
    srand(10);
}

void Rain::stop()
{

}

void Rain::update(boost::asio::serial_port &port)
{
    // Make existing drops fall & decay
    for (uint8_t x = 0; x < CUBE_SIZE; ++x)
    {
        for (uint8_t z = 0; z < CUBE_SIZE; ++z)
        {
            for (std::list<RainDrop>::iterator iter = m_drops[x][z].begin();
                 iter != m_drops[x][z].end();)
            {
                // Decay brightness
                iter->brightness -= m_decay_rate;
                iter->height     -= m_fall_rate;

                if (iter->height <= 0.0f)
                    iter->height = 0.0f;

                /* Delete the drop when it's dimmed completely */
                if (iter->brightness <= 0.0f)
                    iter = m_drops[x][z].erase(iter);
                else
                    ++iter;
            }

        }
    }

    // Make a new drop at the top layer somewhere
    uint8_t new_x = rand() % 8;
    uint8_t new_z = rand() % 8;
    float new_brightness = 0.5f + (static_cast<float>(rand() % 256)/512);

    m_drops[new_x][new_z].push_back(RainDrop(7.0f, new_brightness));

    // Calculate the cube
    memset(m_cube, 0, sizeof(m_cube));
    for (uint8_t x = 0; x < CUBE_SIZE; ++x)
    {
        for (uint8_t z = 0; z < CUBE_SIZE; ++z)
        {
            for (std::list<RainDrop>::const_iterator iter = m_drops[x][z].begin();
                 iter != m_drops[x][z].end();
                 ++iter)
            {
                const uint8_t y = static_cast<uint8_t>(iter->height + 0.5f);
                m_cube[x][y][z] += iter->brightness;
            }
        }
    }

    send(port);
}

void Rain::set_decay_rate(int rate)
{
    m_decay_rate = MIN_DECAY_RATE + (((float)rate/m_pDecaySlider->maximum())*(MAX_DECAY_RATE - MIN_DECAY_RATE));
}

void Rain::set_spawn_rate(int rate)
{
    //TODO: set_spawn_rate
}

void Rain::set_fall_rate(int rate)
{
    m_fall_rate = MIN_FALL_RATE + (((float)rate/m_pFallRateSlider->maximum())*(MAX_FALL_RATE - MIN_FALL_RATE));
}

} // namespace effects
