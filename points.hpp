#include<iostream>
#include<vector>

class Point2D
{
    public:
        float x;
        float y;
        Point2D(float xt=0,float yt=0);
        void rendering(std::vector<std::vector<int>>&render);
        void circleRendering(int r);
};

class Point3D
{
    public:
        float x;
        float y;
        float z;
        Point3D(int xt,int yt,int zt);
        Point2D shadowing(); 
};