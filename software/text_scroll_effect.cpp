#include "text_scroll_effect.h"
#include "ascii_table.h"

#define MIN_SPEED (0.05f)
#define MAX_SPEED (3.0f)

namespace effects
{

TextScroll::TextScroll()
    : BaseEffect("Text Scroll", ":/forms/text_scroll_effect_ctrl.ui")
    , m_string("")
    , m_pos(0.0f)
    , m_scrollrate(0.5f)
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

        // Draw face 3
        for (uint8_t x = 0; x < CUBE_SIZE; ++x)
        {
            const int32_t char_col_offset = (m_pos - x) - (CUBE_SIZE*2);

            if ((char_col_offset >= 0) * (char_col_offset < (m_string.size()*CUBE_SIZE)))
            {
                const int32_t char_index = m_string[char_col_offset/8].toAscii();

                for (uint8_t y = 0;y < CUBE_SIZE; ++y)
                {
                    const int32_t char_row_offset = (CUBE_SIZE - 1) - y;

                    m_cube[(CUBE_SIZE - 1) - x][y][7] = g_ascii_table[char_index][char_row_offset][char_col_offset % CUBE_SIZE];
                }
            }
        }

        // Draw face 2
        for (uint8_t z = 0; z < CUBE_SIZE; ++z)
        {
            const int32_t char_col_offset = (m_pos - z) - CUBE_SIZE;

            if ((char_col_offset >= 0) * (char_col_offset < (m_string.size()*CUBE_SIZE)))
            {
                const int32_t char_index = m_string[char_col_offset/8].toAscii();

                for (uint8_t y = 0;y < CUBE_SIZE; ++y)
                {
                    const int32_t char_row_offset = (CUBE_SIZE - 1) - y;

                    m_cube[7][y][z] = g_ascii_table[char_index][char_row_offset][char_col_offset % CUBE_SIZE];
                }
            }
        }

        // Draw face 1
        for (uint8_t x = 0; x < CUBE_SIZE; ++x)
        {
            const int32_t char_col_offset = m_pos - x;

            if ((char_col_offset >= 0) * (char_col_offset < (m_string.size()*CUBE_SIZE)))
            {
                const int32_t char_index = m_string[char_col_offset/8].toAscii();

                for (uint8_t y = 0;y < CUBE_SIZE; ++y)
                {
                    const int32_t char_row_offset = (CUBE_SIZE - 1) - y;

                    m_cube[x][y][0] = g_ascii_table[char_index][char_row_offset][char_col_offset % CUBE_SIZE];
                }
            }
        }
    }

    // Advance the string position
    m_pos += m_scrollrate;

    if (m_pos > (m_string.size()*CUBE_SIZE + 24)) // +24 to give the text time to go around the whole cube
    {
        m_pos = 0.0f;
    }

    send(port);
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
