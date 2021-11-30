#include "triangle.h"

triangle::triangle()
{

}
triangle::triangle(QVector3D t1_,QVector3D t2_,QVector3D t3_) : t1(t1_),t2(t2_),t3(t3_){
    normal = QVector3D::crossProduct(t2-t1,t3-t1);
    normal.normalize();
}
bool triangle::PointInTriangle(QVector3D p) {
  // Lets define some local variables, we can change these
  // without affecting the references passed in
  QVector3D a = t1;
  QVector3D b = t2;
  QVector3D c = t3;

  // Move the triangle so that the point becomes the
  // triangles origin
  a -= p;
  b -= p;
  c -=p;

  // The point should be moved too, so they are both
  // relative, but because we don't use p in the
  // equation anymore, we don't need it!
  // p -= p;

  // Compute the normal vectors for triangles:
  // u = normal of PBC
  // v = normal of PCA
  // w = normal of PAB

  QVector3D u = QVector3D::crossProduct(b, c);
  QVector3D v = QVector3D::crossProduct(c, a);
  QVector3D w = QVector3D::crossProduct(a, b);

  // Test to see if the normals are facing
  // the same direction, return false if not
  if (QVector3D::dotProduct(u, v) < 0.0f) {
      return false;
  }
  if (QVector3D::dotProduct(u, w) < 0.0f) {
      return false;
  }

  // All normals facing the same way, return true
  return true;
}

double triangle::hauteurPoint(QVector3D v){
    QVector4D plan(normal,0.0);
    plan[3] = -(plan.x()*t1.x()+plan.y()*t1.y()+plan.z()*t1.z());
    float t=plan[0]*v.x()+plan[1]*v.y()+plan[2]*v.z()+plan[3];
    QVector3D newPoint = v + t*QVector3D(0,-1,0);
    if(PointInTriangle(newPoint))
        return t;
    else
        return std::numeric_limits<double>::infinity();
}
