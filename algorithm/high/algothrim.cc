#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;
class ProPaint{
    private:
        int line;    // 行
        int col;     // 列
        vector<vector<int> > Rebostatus;   //机器人
        list<vector<vector<int> > *> finalstatus;   //最后
        vector<vector<int> > thingStatus;   //受到监视的情况
        int curNum;                         // 当前机器人个数
        int minNum;                         // 最小的机器人数目
        static int table[6][3];             //监视情况 
        int leftSize;
    public:
        ProPaint(int l, int c)
            :line(l), col(c), curNum(0), minNum(32767), leftSize(col*line)
        {
            Rebostatus.resize(line);
            thingStatus.resize(line);
            for (int i=0; i<line; ++i) {
                Rebostatus[i].resize(col, 0);
                thingStatus[i].resize(col, 0);
            }
        }
        ~ProPaint() {
            destory();
        }
        void destory();
        void startLocate(int i, int j);
        void showEnd() const;
        void changeStatus(int i, int j);
        void retuStatus(int i, int j);
        void findNonuse(int &i, int &j);
        void ForR(int i, int j);
        void ForQ(int i, int j);
        void ForP(int i, int j);
        int bound(int i, int j);
        bool checkPos(int x, int y) {
            if (x >= 0 && y >= 0 && x < line && y < col) return true;
            else return false;
        }
};
void ProPaint::destory() {
    list<vector<vector<int> > *>::iterator it = finalstatus.begin();
    for (; it!=finalstatus.end();++it) {
        delete *it;
    }
    finalstatus.clear();
}
int ProPaint::bound(int i, int j) {
    int addNum = leftSize/5;
    return curNum+addNum;
}
int ProPaint::table[6][3] = {
        {0,0,0},
        {0,0,0},
        {0,0,-1},
        {0,-1,0},
        {0,0,1},
        {0,1,0}
        };
void ProPaint::showEnd() const {
    cout << "the min num is " << minNum << endl;
    list<vector<vector<int> > *>::const_iterator it = finalstatus.begin();
    for (;it != finalstatus.end(); ++it) {
        cout << "case " << endl;
        for (int i=0; i<line; ++i) {
            for (int j=0; j<col; ++j) {
                cout << ((*it)->operator[](i)).operator[](j) << " ";
            }
            cout << endl;
        }
    }
    cout << endl;
}
void ProPaint::ForP(int i, int j) {
    if (!checkPos(i+1, j)) return;
    changeStatus(i+1, j);    //改变状态，  Rebostatus, thingStatus
    startLocate(i, j);       //
    retuStatus(i+1, j);
}
void ProPaint::ForQ(int i, int j) {
    changeStatus(i, j);
    startLocate(i ,j);
    retuStatus(i, j);
}
void ProPaint::ForR(int i, int j) {
    if (!checkPos(i, j+1)) return;
    changeStatus(i, j+1);
    startLocate(i, j);
    retuStatus(i, j+1);
}
void ProPaint::findNonuse(int &i, int &j) {
    while (thingStatus[i][j] !=0) {
        ++j;
        if (j == col) {
            ++i;
            j=0;
        }
        if (i == line) return;
    }
}
void ProPaint::startLocate(int i, int j) {
    findNonuse(i, j);   // 寻找没有被监事的
    if (i >= line) {    //一次结束
        if (curNum <= minNum) {
            vector<vector<int> > *p = new vector<vector<int> >;
            p->resize(line);
            for (int i=0; i<line; ++i) {
                p->operator[](i).resize(col);
                std::copy(Rebostatus[i].begin(), 
                          Rebostatus[i].end(),
                          p->operator[](i).begin());
            }
            if (curNum < minNum) 
            {
                destory();
                minNum = curNum;
            }
            finalstatus.push_back(p);
        }
        return;
    }
    if (bound(i, j) > minNum) return;
    ForP(i, j);       //先进行p
    ForQ(i, j);       // Q
    ForR(i, j);       // R
}
void ProPaint::changeStatus(int i, int j) {
    Rebostatus[i][j] = 1;
    ++curNum;
    for (int k=1; k<6; ++k) {
        int Posx = i+table[k][1];
        int Posy = j+table[k][2];
        if (checkPos(Posx, Posy)) {
            if (thingStatus[Posx][Posy] == 0) 
                --leftSize;
            ++thingStatus[Posx][Posy];
        }
    }
}
void ProPaint::retuStatus(int i, int j) {
    Rebostatus[i][j] = 0;
    --curNum;
    for (int k=1; k<6; ++k) {
        int Posx = i+table[k][1];
        int Posy = j+table[k][2];
        if (checkPos(Posx, Posy)) {
            --thingStatus[Posx][Posy];
            if (thingStatus[Posx][Posy] == 0) {
                ++leftSize;
            }
        }
   }
}
int main () {
    cout << "please input the size : ";
    int first, second;
    cin >> first >> second;
    if (first == 0 || second == 0) return -1;
    ProPaint paint(first, second);
    paint.startLocate(0, 0);
    paint.showEnd();
    return 0;
}
