#define  _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <typeinfo>
#include <iostream>
#include <cstdlib>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <cmath>
#include <cstring>
#include <vector>
#include <iomanip>
using namespace std;
using namespace cv;

void to_raw(int* input, int out_width, int out_height, unsigned char* output) {
    int count = 0;
    for (int row = 0; row < out_height; row++) {
        for (int column = 0; column < out_width; column++) {
            *(output + count) = *(input + row * out_width + column);
            count = count + 1;
        }
    }
}

void mat2array(Mat input, int* output) {
    int m = input.rows, n = input.cols;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            *(output + i * n + j) = input.at<uchar>(i, j);
        }
    }
}

int path(Mat input, int beginX, int beginY, int endX, int endY, int* output) {
    int m = input.rows, n = input.cols;
    //cout << m << "  " << n << endl;
    typedef pair<int, int> PII; //定義pair包含兩個int型別的數值
    //double* enhancement = new double[in_width * in_height];
    PII* q = new PII[m * n];  //儲存可以走的節點
    PII* prevv = new PII[m * n]; //儲存上一個節點的矩陣
    int* map = new int[m * n]; //地圖
    int* d = new int[m * n]; //儲存與出發點路徑長的矩陣
    for (int i = 0; i < m * n; i++)
        d[i] = -1;

    //int beginX, beginY; //定義起始點
    //int endX, endY;     //定義終點
    vector<int> ansX, ansY; //紀錄最短路徑的x,y

    mat2array(input, map);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i * n + j] >= 128) {
                map[i * n + j] = 0;
            }
            else {
                map[i * n + j] = 1;
            }
        }
    }

    //cin >> beginX ;
    //cin >> beginY;
    //cin >> endX; 
    //cin >> endY;
    int hh = 0, tt = 0;  //定義隊頭及游標
    
    q[0] = { beginX - 1, beginY - 1 }; //初始化
    
    //memset(d, -1, sizeof d); //初始化儲存與出發點路徑長的矩陣，設為-1
    d[(beginX - 1) * n + (beginY - 1)] = 0; //初始化起點
    
    int dx[8] = { -1, 0, 1, 0, -1, -1, 1, 1 }, dy[8] = { 0, 1, 0, -1, 1, -1, -1, 1 };//定義可以走的方向 dx, dy ，分别代表上、下、左、右、右上、左上、左下、右下八個方向
    //cout << map[300 * n + 447] << endl;
    //cout << d[300 * n + 447] << endl;
    //cout << m << endl;
    //cout << n << endl;
    while (hh <= tt){  //當隊頭小於游標時
        auto t = q[hh++];  //取上一個節點作為隊頭
        //cout << t.first << "  " << t.second << endl;
        for (int i = 0; i < 8; i++){
            int x = t.first + dx[i], y = t.second + dy[i]; //依照上、下、左、右、右上、左上、左下、右下八個方向判斷是否可以走
            if (x >= 0 && x < m && y >= 0 && y < n && map[x * n + y] == 0 && d[x * n + y] == -1) {
                d[x * n + y] = d[(t.first) * n + (t.second)] + 1; //如果可以走且沒走過，矩陣d需紀錄
                prevv[x * n + y] = t;    //並記錄上一個位置，方便我們找出最短路徑
                //cout << prevv[x * n + y].first << "  " << prevv[x * n + y].second << endl;
                q[++tt] = { x, y };  //記錄下可以走的x, y
                //cout << setw(5) << x;
                //cout << setw(5) << y;
                //cout << setw(5) << t.first;
                //cout << setw(5) << t.second << endl;
            }
        }
    }
    //cout << "  fghgfh "  << endl;
    int x = endX - 1, y = endY - 1;
    ansX.push_back(x);
    ansY.push_back(y);
    auto t = prevv[x * n + y];
    x = t.first, y = t.second;
    while (x || y){ //未到起始點
        ansX.push_back(x);//將最短路徑的x, y座標由後找回來，並從ansX, ansY的最後開始放
        ansY.push_back(y);
        auto t = prevv[x * n + y];
        x = t.first, y = t.second;
        //cout << t.first << "   " << t.second << endl;
    }
    ansX.push_back(beginX - 1);
    ansY.push_back(beginY - 1);
    int short_path = d[(endX - 1) * n + (endY - 1)];
    if (short_path == -1) {
        printf("從(%d,%d) 到 (%d, %d)無路徑\n", beginX, beginY, endX, endY);
        short_path = 0;
    }
    else {
        printf("從(%d,%d) 到 (%d, %d)的最短路徑長度為：%d\n", beginX, beginY, endX, endY, short_path);
    }
    //cout << "最短路徑為：" <<endl;
    map[(beginX - 1) * n + (beginY - 1)] = 2;
    for (int i = ansX.size() - 1; i >= 0; i--){
        *(output + ansX[i] * n + ansY[i]) = 2;
        /*
        if (i)
            cout << "(" << ansX[i] + 1 << "," << ansY[i] + 1 << ")" << "->";
        else
            cout << "(" << ansX[i] + 1 << "," << ansY[i] + 1 << ")";*/
    }
    /*
    cout << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << map[i * n + j];
            if (j == 9)
                cout << endl;
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i * n + j] == 0) {
                map[i * n + j] = 255;
            }
            else if(map[i * n + j] == 2){
                map[i * n + j] = 127;
            }
            else {
                map[i * n + j] = 0;
            }
        }
    }
    unsigned char* img_save = new unsigned char[m * n];
    to_raw(map, n, m, img_save);
    Mat saveimg(m, n, CV_8UC1, img_save);
    imwrite("map_path.png", saveimg);*/
    delete[] q;
    delete[] prevv;
    delete[] map;
    delete[] d;
    
    return short_path;
}

void navigation(Mat input, vector<int>& pathX, vector<int>& pathY, int people_car) {
    int m = input.rows, n = input.cols;
    if (people_car == 0) {
        int sum_path = 0;
        int* map = new int[m * n];
        int* output = new int[m * n];
        mat2array(input, map);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (map[i * n + j] >= 128) {
                    *(output + i * n + j) = 0;
                }
                else {
                    *(output + i * n + j) = 1;
                }
            }
        }
        for (int i = 0; i < pathX.size() - 1; i++) {
            int short_path;
            int beginX = pathX[i];
            int beginY = pathY[i];
            int endX = pathX[i + 1];
            int endY = pathY[i + 1];
            short_path = path(input, beginX, beginY, endX, endY, output);
            sum_path = sum_path + short_path;
            
        }
        cout << "總距離為:" << sum_path << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (output[i * n + j] == 0) {
                    output[i * n + j] = 80;
                }
                else if (output[i * n + j] == 2) {
                    output[i * n + j] = 255;
                }
                else {
                    output[i * n + j] = 0;
                }
            }
        }
        unsigned char* img_save = new unsigned char[m * n];
        to_raw(output, n, m, img_save);
        Mat saveimg(m, n, CV_8UC1, img_save);
        imwrite("map_path.png", saveimg);
        delete[] img_save;
        delete[] output;
    }
    else if (people_car == 1) {
        Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
        Mat open;
        morphologyEx(input, open, MORPH_OPEN, kernel);
        imwrite("map_open.png", open);
        int sum_path = 0;
        int* map = new int[m * n];
        int* output = new int[m * n];
        mat2array(input, map);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (map[i * n + j] >= 128) {
                    *(output + i * n + j) = 0;
                }
                else {
                    *(output + i * n + j) = 1;
                }
            }
        }
        for (int i = 0; i < pathX.size() - 1; i++) {
            int short_path;
            int beginX = pathX[i];
            int beginY = pathY[i];
            int endX = pathX[i + 1];
            int endY = pathY[i + 1];
            short_path = path(open, beginX, beginY, endX, endY, output);
            sum_path = sum_path + short_path;  
        }
        cout << "總距離為:" << sum_path << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (output[i * n + j] == 0) {
                    output[i * n + j] = 80;
                }
                else if (output[i * n + j] == 2) {
                    output[i * n + j] = 255;
                }
                else {
                    output[i * n + j] = 0;
                }
            }
        }
        unsigned char* img_save = new unsigned char[m * n];
        to_raw(output, n, m, img_save);
        Mat saveimg(m, n, CV_8UC1, img_save);
        imwrite("map_path.png", saveimg);
        delete[] img_save;
        delete[] output;
    }
    else {
        cout << "input Error ! ! !" << endl;
    }
}
 
int main(){
    Mat img = imread("map1.png",IMREAD_GRAYSCALE);
    if (img.empty()) {
        puts("Loading File Error!");
        system("PAUSE");
        exit(0);
    }
    int X, Y; //定義路徑點
    vector<int> pathX, pathY; //定義整個路徑
    int i = 0;
    int people_car;
    cout << "輸入行人使用(0)或車輛使用(1):";
    cin >> people_car;
    while (1) {
        cout << "輸入座標X、Y，直到輸入-1為止" << endl;
        cin >> X;
        if (X == -1)
            break;
        else
            pathX.push_back(X);
        cin >> Y;
        pathY.push_back(Y);
        i++;
    }
    clock_t start, end;
    start = clock();
    navigation(img, pathX, pathY, people_car);
    end = clock();
    cout << "執行時間: " << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;
    /*
    while (1) {
        path(img);
        
    }*/
}
