#include "wave_effect.h"
#include "math.h"

namespace effects
{

Wave::Wave()
    : BaseEffect("Wave", "")
    , m_speed(0.2f)
    , m_pos(0.0f)
    , m_size(1.0f)
    , m_height(3.5f)
{
    // Nothing to do
}

Wave::~Wave()
{

}

void Wave::start()
{

}

void Wave::stop()
{

}

void Wave::update(boost::asio::serial_port &port)
{
    memset(m_cube, 0, sizeof(m_cube));

    for (uint8_t x = 0; x < CUBE_SIZE; ++x)
    {
        for (uint8_t y = 0; y < CUBE_SIZE; ++y)
        {
            const float pos = sin(m_pos + (x*m_size))*m_height;

            for (uint8_t z = 0; z < CUBE_SIZE; ++z)
                m_cube[x][(int)(m_height + pos + 0.5f)][z] = 1.0f;
        }
    }

    m_pos += m_speed;

    send(port);
}

} // namespace effects
