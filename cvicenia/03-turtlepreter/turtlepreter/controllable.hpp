
#ifndef TURTLEPRETER_CONTROLLABLE_HPP
#define TURTLEPRETER_CONTROLLABLE_HPP

#include <libfriimgui/image.hpp>
#include <string>

namespace turtlepreter {

class Controllable {
public:
    
    explicit Controllable(const std::string& imgPath);
    Controllable(const std::string& imgPath, float centerX, float centerY);

    virtual ~Controllable() = default;

    virtual void draw(const friimgui::Region& region);
    virtual void reset();
    friimgui::Transformation& getTransformation();

protected:
    friimgui::Transformation m_transformation; 
    friimgui::Image m_image;                  
    ImVec2 m_initPos{0.f, 0.f};
    float m_initAngle{0.f};
};

} // namespace turtlepreter

#endif
