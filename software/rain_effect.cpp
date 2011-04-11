#include "rain_effect.h"
#include <QSlider>

#define MIN_DECAY_RATE (0.005f)
#define MAX_DECAY_RATE (0.1f)

#define MIN_FALL_RATE (0.001f)
#define MAX_FALL_RATE (1.0f)

#define MIN_SPAWN_RATE (0.1f)
#define MAX_SPAWN_RATE (10.0f)

namespace effects
{

Rain::Rain()
    : BaseEffect("Rain", ":/forms/rain_effect_ctrl.ui")
    , m_counter(0)
    , m_pDecaySlider(NULL)
    , m_pFallRateSlider(NULL)
    , m_pSpawnRateSlider(NULL)
    , m_spawn_rate(1.0f)
    , m_spawn_counter(0.0f)
{
    m_decay_rate = 0.01f;
    m_fall_rate = 0.15f;

    m_pDecaySlider = m_pCtrls->findChild<QSlider*>("slider_decayRate");
    m_pFallRateSlider = m_pCtrls->findChild<QSlider*>("slider_fallRate");
    m_pSpawnRateSlider = m_pCtrls->findChild<QSlider*>("slider_spawnRate");

    connect(m_pDecaySlider, SIGNAL(valueChanged(int)), this, SLOT(set_decay_rate(int)));
    connect(m_pFallRateSlider, SIGNAL(valueChanged(int)), this, SLOT(set_fall_rate(int)));
    connect(m_pSpawnRateSlider, SIGNAL(valueChanged(int)), this, SLOT(set_spawn_rate(int)));

    m_pDecaySlider->setValue(convert(m_decay_rate, MIN_DECAY_RATE, MAX_DECAY_RATE,
                                     m_pDecaySlider->minimum(), m_pDecaySlider->maximum()));

    m_pFallRateSlider->setValue(convert(m_fall_rate, MIN_FALL_RATE, MAX_FALL_RATE,
                                        m_pFallRateSlider->minimum(), m_pFallRateSlider->maximum()));

    m_pSpawnRateSlider->setValue(convert(m_spawn_rate, MIN_SPAWN_RATE, MAX_SPAWN_RATE,
                                         m_pSpawnRateSlider->minimum(), m_pSpawnRateSlider->maximum()));
}

Rain::~Rain()
{

}

void Rain::start()
{
    memset(m_cube, 0, sizeof(m_cube));

    // Delete any existing raindrops
    for (uint8_t x = 0; x < CUBE_SIZE; ++x)
        for (uint8_t y = 0;y < CUBE_SIZE; ++y)
            m_drops[x][y].clear();

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

    // Make new drops
    m_spawn_counter += m_spawn_rate;
    const uint32_t num_drops_to_spawn = static_cast<uint32_t>(m_spawn_counter);
    m_spawn_counter -= num_drops_to_spawn;

    for (uint32_t i = 0; i < num_drops_to_spawn; ++i)
    {
        const uint32_t new_x = rand() % 8;
        const uint32_t new_y = rand() % 8;
        float new_brightness = 0.5f + (static_cast<float>(rand() % 256)/512); // Random brightness at least 50% brightness

        m_drops[new_x][new_y].push_back(RainDrop(7.0f, new_brightness));
    }

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
    m_decay_rate = convert(rate, m_pDecaySlider->minimum(), m_pDecaySlider->maximum(),
                           MIN_DECAY_RATE, MAX_DECAY_RATE);
}

void Rain::set_spawn_rate(int rate)
{
    m_spawn_rate = convert(rate, m_pSpawnRateSlider->minimum(), m_pSpawnRateSlider->maximum(),
                           MIN_SPAWN_RATE, MAX_SPAWN_RATE);
}

void Rain::set_fall_rate(int rate)
{
    m_fall_rate = convert(rate, m_pFallRateSlider->minimum(), m_pFallRateSlider->maximum(),
                          MIN_FALL_RATE, MAX_FALL_RATE);
}

} // namespace effects
