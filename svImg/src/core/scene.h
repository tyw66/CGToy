#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "shape.h"

class Scene
{
public:
    Scene();

    std::vector<tyw::Shape *> m_objs; /**< 场景包含的物体*/

    void add(tyw::Shape *obj){
        m_objs.push_back(obj);
    }



};

#endif // SCENE_H
