/**
 * @brief 颜色类
 * @author tyw
 * @date 2018/09/25
 */
class Color
{
public:
    unsigned int r,g,b;

    Color(){}

    Color(unsigned int value)
        :r(value),g(value),b(value) { }

    Color(unsigned int r_, unsigned int g_, unsigned int b_)
        :r(r_),g(g_),b(b_) { }

    void set(unsigned int value_){
        r = value_; g = value_; b = value_;
    }
    void set(unsigned int r_, unsigned int g_, unsigned int b_){
        r = r_; g = g_; b = b_;
    }

};

