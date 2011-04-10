#ifndef TEXT_SCROLL_EFFECT_H
#define TEXT_SCROLL_EFFECT_H
#include "effect_base.h"
#include <QString>

namespace effects
{

class TextScroll : public BaseEffect
{
    Q_OBJECT
public:
    TextScroll();

    virtual void start();
    virtual void stop();

    virtual void update(boost::asio::serial_port &port);

private:
    QString m_string;
    float m_pos;
    float m_scrollrate;
};

} // namespace effects

#endif // TEXT_SCROLL_EFFECT_H
