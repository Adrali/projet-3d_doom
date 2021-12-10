#include "camera.h"

void Camera::actualiseVueMatrix(){
    QVector3D playerPos = p->getPlayerPosition();
    vue.setToIdentity();
    vue.rotate(-1*p->getPlayerAngle(),QVector3D(0,1,0));
    vue.translate(-1*p->getPlayerPosition());

}
