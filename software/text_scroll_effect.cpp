#include "text_scroll_effect.h"
#include "ascii_table.h"

namespace effects
{

TextScroll::TextScroll()
    : BaseEffect("Text Scroll", "")
    , m_string("DANCUBE")
    , m_pos(0.0f)
    , m_scrollrate(0.1f)
{

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

}

} // namespace effects
