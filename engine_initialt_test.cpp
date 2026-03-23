#include<iostream>
#include<vector>
#include <cmath>
#include <cstdlib>
#include <windows.h>
#define eps 1e-6

using namespace std;

vector<vector<int>> RENDER(50,vector<int>(50,0));

class Point2D
{
    public:
        float x;
        float y;
        Point2D(float xt=0,float yt=0)
        {
            x=xt;y=yt;
        }
        
        void rendering(vector<vector<int>>&render)
        {
            int xt=(int)floor(x);
            int yt=(int)floor(y);
            render[xt][yt]=1;
        }

        void circleRendering(int r);
};

class Point3D
{
    public:
        float x;
        float y;
        float z;
        Point2D shadowing() {
            return Point2D(x, y);
        }       
};



class Hexahedron
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
        vector<vector<int>> edges = {
            {0,1}, {1,2}, {2,3}, {3,0}, 
            {4,5}, {5,6}, {6,7}, {7,4}, 
            {0,4}, {1,5}, {2,6}, {3,7}  
        };
        
        void init()
        {
            for(int i=0;i<8;i++) {
                cin>>points[i].x>>points[i].y>>points[i].z;
            }
            return;
        }
        void FrameRendering(vector<vector<int>>&render);
        
};

// void render_output(vector<vector<int>>& render) {
//     // 清屏（Windows）
//     system("cls");

//     // 控制台句柄
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//     for (int y = 0; y < 50; y++) {
//         for (int x = 0; x < 50; x++) {
//             if (render[y][x] == 1) {
//                 // 白色小方块 = 真正像素效果
//                 SetConsoleTextAttribute(hConsole, 0x0F);
//                 cout << "#";
//             } else {
//                 // 空格占位，保持画布大小
//                 cout << " ";
//             }
//         }
//         cout << endl;
//     }

//     // 恢复颜色
//     SetConsoleTextAttribute(hConsole, 0x07);
// }

void render_output(vector<vector<int>>& render)
{
    for(int i=0;i<50;i++) {
        for(int j=0;j<50;j++) {
            if(render[i][j]==1) {
                cout<<'#';
            }else {
                cout<<' ';            
            }
        }
        cout<<endl;
    }
    return;
}

void debugCommand(int i) 
{
    cout<<"第"<<i<<"次渲染"<<endl;
    render_output(RENDER);
    cout<<endl<<endl;
    return;
}


bool isInRender(Point2D p)
{
    int xt=(int)floor(p.x);
    int yt=(int)floor(p.y);
    
    if(xt<50 && xt>=0 && yt>=0 && yt<50) {
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
        
            if (isInRender(pen)) {
                pen.rendering(render);
            }
            pen.y += dy;
        }
        b.rendering(render);
        return;
    }
    //一般情况
    Point2D pen=a;
    float dx=(a.x<b.x)?1.0f:-1.0f;          //每次移动x的距离
    float dy=fabs(a.y-b.y)/fabs(a.x-b.x);   //每次移动y的距离


    while (fabs(b.x - pen.x) >= eps) {

        //判断是否在渲染范围内
        if(isInRender(pen)) {
            pen.rendering(render);
        }
        //画笔移动
        pen.x+=dx;  
        pen.y+=dy;
    }

    //处理终点
    if(isInRender(pen)) {
        b.rendering(render);
    }
}



void Hexahedron::FrameRendering(vector<vector<int>>&render)
{
    // 遍历所有棱边绘制
    for (auto& edge : edges) {

        Point2D a = points[edge[0]].shadowing();
        Point2D b = points[edge[1]].shadowing();
        if (isInRender(a) && isInRender(b)) {
            LineGenerate(a, b, render);
        }
        // 每画一条边输出一次画布（调试用，可删除）
        // render_output(render);
    }  
}

void putpixel(int x,int y,vector<vector<int>>& render)
{
    render[x][y]=1;
    return;
}   

void Point2D::circleRendering(int r)
{
    int dx=0;
    int dy=r;
    int i=1;

    while(dx<dy) {
        float ym=(float)dy-0.5;
        if((float)ym*ym+dx*dx-r*r>eps) {
            dy-=1;
        }

        putpixel(x+dx,y+dy,RENDER);
        putpixel(x+dx,y-dy,RENDER);
        putpixel(x-dx,y+dy,RENDER);
        putpixel(x-dx,y-dy,RENDER);
        putpixel(x+dy,y+dx,RENDER);
        putpixel(x+dy,y-dx,RENDER);
        putpixel(x-dy,y+dx,RENDER);
        putpixel(x-dy,y-dx,RENDER);
        // debugCommand(i);

        dx+=1;i++;
    }
}


int main()
{
    // Hexahedron cube;
    // cube.init();
    // cube.FrameRendering(RENDER);
    // cout<<cube.points[cube.faces[0][1]].shadowing().x<<' '<<cube.points[cube.faces[0][1]].shadowing().y<<endl;
    // cout<<cube.points[cube.faces[0][(1+1)%4]].shadowing().x<<' '<<cube.points[cube.faces[0][(1+1)%4]].shadowing().y;

    system("chcp 65001");
    Point2D pt(0,0);
    int r;
    cin>>pt.x>>pt.y>>r;
    pt.circleRendering(r);

    cout<<"最终渲染"<<endl;
    render_output(RENDER);
    system("pause");

    // Point2D a,b;
    // cin>>a.x>>a.y;
    // cin>>b.x>>b.y;
    // LineGenerate(a,b,RENDER);
    // render_output();
    

    return 0;
}