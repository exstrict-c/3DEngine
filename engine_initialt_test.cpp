#include<iostream>
#include<vector>
#include <cmath>
#include <cstdlib>
#define eps 1e-6

using namespace std;

class Point3D
{
    public:
        int x;
        int y;
        int z;
        Point2D& shadowing(){
            static Point2D p2d;
            p2d.x=x;p2d.y=y;
            return p2d;
        }
};

class Point2D
{
    public:
        float x;
        float y;
};

class hexahedron
{
    public:
        Point3D points[8];
        vector<vector<int>> faces={
            {0,1,2,3},
            {4,5,6,7},
            {0,1,5,4},
            {3,2,6,7},
            {0,3,7,4},
            {1,2,6,5}
        };
        //给正方形录入各点数据
        void init()
        {
            for(int i=0;i<8;i++) {
                cin>>points[i].x>>points[i].y;
            }
            return;
        }

        void FrameRendering()
        {
            for(int i=0;i<2;i++) {
                
            }
        }
};





vector<vector<int>> RENDER(50,vector<int>(50,0));

bool isInRender(int x,int y)
{
    if(x<50 && x>=0 && y>0 && y<50) {
        return true;
    }else {
        return false;
    }
}

void LineGenerate(Point2D a,Point2D b,vector<vector<int>>&render)
{
    if (fabs(a.x - b.x) < eps) {
        // 竖线单独处理
        Point2D pen = a;
        float dy = (b.y > a.y) ? 1.0f : -1.0f;
        while (fabs(b.y - pen.y) >= eps) {
            
            int x = (int)floor(pen.x);
            int y = (int)floor(pen.y);
            if (x >= 0 && x < 50 && y >= 0 && y < 50) {
                render[x][y] = 1;
            }
            pen.y += dy;
        }
        return;
    }
    //一般情况
    Point2D pen=a;
    float dx=(a.x<b.x)?1.0f:-1.0f;          //每次移动x的距离
    float dy=fabs(a.y-b.y)/fabs(a.x-b.x);   //每次移动y的距离


    while (fabs(b.x - pen.x) >= eps) {

        int x_tmp=(int)floor(pen.x);    //取整让render读取
        int y_tmp=(int)floor(pen.y);

        //判断是否在渲染范围内
        if(isInRender(x_tmp,y_tmp)) {
            render[x_tmp][y_tmp]=1;
        }
        //画笔移动
        pen.x+=dx;  
        pen.y+=dy;
    }

    //处理终点
    int x_tmp=(int)floor(b.x);
    int y_tmp=(int)floor(b.y);

    if(isInRender(x_tmp,y_tmp)) {
        render[x_tmp][y_tmp]=1;
    }
}

void render_output()
{
    for(int y=0;y<50;y++) {
        for(int x=0;x<50;x++) {
            if(RENDER[x][y]) {
                cout<<"*";
            }else {
                cout<<" ";
            }
        }
        cout<<endl;
    }
}












int main()
{
    vector<vector<int>>& render=RENDER;
    Point2D p1,p2;
    cin>>p1.x>>p1.y;
    cin>>p2.x>>p2.y;
    LineGenerate(p1,p2,render);
    render_output();
    system("pause");
    return 0;
}