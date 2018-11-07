#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "shape.h"

class Scene
{
public:
    Scene();

    std::vector<tyw::Shape *> m_objs; /**< 场景包含的物体*/

    /**
     * @brief sampling
     * @param x
     * @param y
     * @param mx
     * @param my
     * @param time
     * @return
     */
    Color& sampling(double x, double y, double mx, double my, int time);


};

#endif // SCENE_H
