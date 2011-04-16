#include "text_scroll_effect.h"
#include "ascii_table.h"

#include <QPaintEngine>

#define MIN_SPEED (0.05f)
#define MAX_SPEED (3.0f)

namespace effects
{

TextScroll::TextScroll()
    : BaseEffect("Text Scroll", ":/forms/text_scroll_effect_ctrl.ui")
    , m_string("")
    , m_pos(0.0f)
    , m_scrollrate(0.5f)
    , m_bitmap(QPixmap(":/fonts/font.pbm", "PBM", Qt::MonoOnly).toImage())
{
    m_pEdit_text    = m_pCtrls->findChild<QLineEdit*>("edit_text");
    m_pSlider_speed = m_pCtrls->findChild<QSlider*>("slider_speed");
    m_pBtn_start    = m_pCtrls->findChild<QPushButton*>("btn_start");

    m_string = m_pEdit_text->text();

    connect(m_pSlider_speed, SIGNAL(valueChanged(int)), this, SLOT(set_speed(int)));
    connect(m_pBtn_start, SIGNAL(clicked()), this, SLOT(set_text()));
    connect(m_pEdit_text, SIGNAL(returnPressed()), this, SLOT(set_text()));

    m_pSlider_speed->setValue(convert(m_scrollrate, MIN_SPEED, MAX_SPEED,
                                      m_pSlider_speed->minimum(), m_pSlider_speed->maximum()));
}

void TextScroll::start()
{
    m_pos = 0.0f;
}

void TextScroll::stop()
{

}

void TextScroll::update(boost::asio::serial_port &port)
{
    memset(m_cube, 0, sizeof(m_cube));

    {
        boost::unique_lock<boost::mutex> lock(m_mutex);

        // Draw in reverse order so that the corners are drawn properly.
        // The corners will be overwritten when drawing each face.
        // Face 0 (the first one) has the highest 'priority'
        drawFace(3);
        drawFace(2);
        drawFace(1);
        drawFace(0);
    }

    // Advance the string position
    m_pos += m_scrollrate;

    if (m_pos > (m_string.size()*CUBE_SIZE + 28)) // +28 to give the text time to go around the whole cube
    {
        m_pos = 0.0f;
    }

    send(port);
}

void TextScroll::drawFace(uint8_t face)
{
    for (uint8_t x = 0; x < CUBE_SIZE; ++x)
    {
        // Take m_pos into the calculation here to get the scrolling effect
        // The face is added onto the end since the offset should increase by 1 each time the letter goes around a corner.
        // This offset can be negative so that the higher numbered faces aren't drawn until after the earlier ones
        const int32_t char_col_offset = ((m_pos - x) - (CUBE_SIZE*face)) + face;

        if ((char_col_offset >= 0) * (char_col_offset < (m_string.size()*CUBE_SIZE)))
        {
            const int32_t char_index = m_string[char_col_offset/8].toAscii();

            for (uint8_t y = 0;y < CUBE_SIZE; ++y)
            {
                const int32_t char_row_offset = (CUBE_SIZE - 1) - y;

                // Lookup the pixel in the bitmap
                const QRgb pixel = m_bitmap.pixel((char_index*8) + (char_col_offset % 8), char_row_offset);
                const float f_pixel = (qGray(pixel) > 0) ? 0.0f : 1.0f; // Pixel data is inverted

                switch (face)
                {
                case 0:
                    m_cube[x][y][0] = f_pixel;
                    break;
                case 1:
                    m_cube[(CUBE_SIZE - 1)][y][x] = f_pixel;
                    break;
                case 2:
                    m_cube[(CUBE_SIZE - 1) - x][y][7] = f_pixel;
                    break;
                case 3:
                    m_cube[0][y][(CUBE_SIZE - 1) - x] = f_pixel;
                    break;
                }
            }
        }
    }
}

void TextScroll::set_speed(int speed)
{
    m_scrollrate = convert(speed, m_pSlider_speed->minimum(), m_pSlider_speed->maximum(),
                           MIN_SPEED, MAX_SPEED);
}

void TextScroll::set_text()
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    m_string = m_pEdit_text->text();
    m_pos = 0.0f; // Reset the position
}

} // namespace effects
