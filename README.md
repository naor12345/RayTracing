# RayTracing
一种全局光照的实现。

## 各类说明
- Vec：向量
- Ray：光线，由一点和一方向向量确定
- Geometry：几何体，抽象类
- Plane：平面（无限延展），由过平面一点和平面法向量确定
- RecPlane：平面（矩形范围）
- sphere：球，由球心和半径确定
- CylinderInf：柱面（无限长）
- Cylinder：柱面（有限）
- Polyhedron：六面体
- Union：用于描述场景
- IntersectResult：用于求光线与物体的交点

## 渲染结果如图
![Aaron Swartz](https://github.com/naor12345/RayTracing/raw/master/image.JPG)
