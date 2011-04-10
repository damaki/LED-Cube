#include "ball_effect.h"
#include <math.h>

#define MIN_BALL_SIZE (0.1f)
#define MAX_BALL_SIZE (3.0f)

#define MIN_BALL_SPEED (0.05f)
#define MAX_BALL_SPEED (3.0f)

namespace effects
{

Ball::Ball()
    : BaseEffect("Ball", ":/forms/ball_effect_ctrl.ui")
{
    m_ball.pos.setX(3.5f);
    m_ball.pos.setY(3.5f);
    m_ball.pos.setX(3.5f);

    m_ball.size = 1.0f;

    m_ball.direction.setX(rand());
    m_ball.direction.setY(rand());
    m_ball.direction.setZ(rand());
    m_ball.direction.normalize();

    m_ball.speed = 0.5f;

    m_pSlider_size = m_pCtrls->findChild<QSlider*>("slider_size");
    m_pSlider_speed = m_pCtrls->findChild<QSlider*>("slider_speed");

    connect(m_pSlider_speed, SIGNAL(valueChanged(int)), this, SLOT(set_speed(int)));
    connect(m_pSlider_size, SIGNAL(valueChanged(int)), this, SLOT(set_size(int)));

    int slider_diff = m_pSlider_size->maximum() - m_pSlider_size->minimum();
    m_pSlider_size->setValue(((m_ball.size - MIN_BALL_SIZE)*slider_diff)/(MAX_BALL_SIZE - MIN_BALL_SIZE));

    slider_diff = m_pSlider_speed->maximum() - m_pSlider_speed->minimum();
    m_pSlider_speed->setValue(((m_ball.speed - MIN_BALL_SPEED)*slider_diff)/(MAX_BALL_SPEED - MIN_BALL_SPEED));
}

Ball::~Ball()
{

}

void Ball::start()
{
    memset(m_cube, 0, sizeof(m_cube));

    m_ball.pos.setX(3.5f);
    m_ball.pos.setY(3.5f);
    m_ball.pos.setX(3.5f);

    m_ball.direction.setX(rand());
    m_ball.direction.setY(rand());
    m_ball.direction.setZ(rand());
    m_ball.direction.normalize();
}

void Ball::stop()
{

}

void Ball::update(boost::asio::serial_port &port)
{
    // Draw the cube
    for (uint8_t x = 0; x < CUBE_SIZE; ++x)
    {
        for (uint8_t y = 0;y < CUBE_SIZE; ++y)
        {
            for (uint8_t z = 0; z < CUBE_SIZE; ++z)
            {
                const float x_diff = m_ball.pos.x() - x;
                const float y_diff = m_ball.pos.y() - y;
                const float z_diff = m_ball.pos.z() - z;

                const float x_sq = x_diff*x_diff;
                const float y_sq = y_diff*y_diff;
                const float z_sq = z_diff*z_diff;

                const float distance = 1.0f/sqrt(x_sq + y_sq + z_sq);

                // Set the brightness based on the distance to the cube
                // Exponentially decrease the brightness as distance increases
                m_cube[x][y][z] = distance*m_ball.size;
            }
        }
    }

    // Update position based on velocity
    m_ball.pos += m_ball.direction*m_ball.speed;

    // Bounds checking on the axes - keep the ball within the cube
    if (m_ball.pos.x() > 7.0f)
    {
        m_ball.pos.setX(7.0f - (m_ball.pos.x() - 7.0f));
        m_ball.direction.setX(-m_ball.direction.x());   // Reverse X axis direction
    }
    else if (m_ball.pos.x() < 0.0f)
    {
        m_ball.pos.setX(-m_ball.pos.x());
        m_ball.direction.setX(-m_ball.direction.x());   // Reverse X axis direction
    }

    if (m_ball.pos.y() > 7.0f)
    {
        m_ball.pos.setY(7.0f - (m_ball.pos.y() - 7.0f));
        m_ball.direction.setY(-m_ball.direction.y());   // Reverse Y axis direction
    }
    else if (m_ball.pos.y() < 0.0f)
    {
        m_ball.pos.setY(-m_ball.pos.y());
        m_ball.direction.setY(-m_ball.direction.y());   // Reverse Y axis direction
    }

    if (m_ball.pos.z() > 7.0f)
    {
        m_ball.pos.setZ(7.0f - (m_ball.pos.z() - 7.0f));
        m_ball.direction.setZ(-m_ball.direction.z());   // Reverse Y axis direction
    }
    else if (m_ball.pos.z() < 0.0f)
    {
        m_ball.pos.setZ(-m_ball.pos.z());
        m_ball.direction.setZ(-m_ball.direction.z());   // Reverse Y axis direction
    }

    send(port);
}

void Ball::set_speed(int speed)
{
    m_ball.speed = MIN_BALL_SPEED + ((float)speed/m_pSlider_speed->maximum())*(MAX_BALL_SPEED - MIN_BALL_SPEED);
}

void Ball::set_size(int size)
{
    m_ball.size = MIN_BALL_SIZE + ((float)size/m_pSlider_size->maximum())*(MAX_BALL_SIZE - MIN_BALL_SIZE);
}

} // namespace effects
