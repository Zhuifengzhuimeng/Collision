//getchar()需判断是否为eof或'\n'。
//while(cin.getline(s,length))可以成立，到末位自会break。另外实际输入的字符为length-1。
//在前一个cin后立刻getline会得到一个空行，这是因为cin不处理换行符。请使用cin.ignore(0x7fffffff,'\n')，无视之前的换行符。
//%0xd == 前导零#include <iostream>
//map如果访问了未包含的key，会自动创建一个。
//两个iterator不可以用大于／小于号比较。
//链表在用iterator遍历时，如果erase了元素，原来的iterator就不可用了，若要继续遍历必须使用it=list.erase(...)语句重置iterator（删除后就不用++it了）。
//cin.peek()观测输入的第一个字符（返回char） cin.peek() == '\n' 判断输入了换行符
//unsigned int 1<<32及以上为什么等于3520 / 3504？
//memset是按字节赋值的！对int数组a用memset(a, 1, sizeof(a))会导致数组a中的值变为0x0101！！
//dijkstra（以及其他图论的题）的时候小心输入数据有重边：1 2 3\n1 2 4\n应该取1 2 3
//sprintf()要保证char足够大（别忘了\0），否则写地址就会写到之前的变量里。

//void my_sort(void * base, size_t length, size_t width, int (* _Nonnull)(const void *, const void *));

#include <iostream>
//#include <cmath>
//#include <cstdlib>
#include <cstring>
//#include <fstream>
//#include <iomanip>
//#include <string>
// *** STL - algorithm *** //
//#include <algorithm>
// *** STL - continer *** //
//#include <deque>
//#include <list>
//#include <map>
#include <queue>
//#include <stack>
//#include <vector>
// *** OpenGL *** //
//#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
//#include <GLUT/glut.h>

//#ifndef MATH_PI
// #define MATH_PI 3.141592653589793
//#endif
#define MAX_LEN 7000000
//#define MAX_ROADS 100010
//#define INF 0xffffffff
// ****** bored with 'for(foo; foo; foo)' ****** //
//#define FIN(i,N) for(i=0;i<(N);++i)
//#define FIN1(i,N) for(i=1;i<=(N);++i)
//#define FINM(i,N) for(i=((N)-1);i>=0;--i)
//#define FINM1(i,N) for(i=(N);i>=1;--i)
// ****** count the code's execution time ****** //
//#define INITICK clock_t ___START___, ___END___, ___DUR___
//#define TICK ___START___ = clock()
//#define COUNT(str) ___END___ = clock(); ___DUR___ = ___END___ - ___START___; printf(#str" used %f ms\n",(double)___DUR___/CLOCKS_PER_SEC * 1000)

using namespace std;
//typedef long long int ll;

struct state {
    char chr[8];
    int count;
    state() {}
    state(char *c, int i): count(i) { memcpy(chr, c, sizeof(char) * 8); }
};

int main() {
    bool states[MAX_LEN] = {0};
    queue<state> que;
    int st, en, temp, t = -1; scanf("%d%d", &st, &en);
    if (st == en) { printf("0\n"); return 0; }
    // the first digit is position of the cursor (1 to 6)
    char s[8], cur[8], tmp[8];
    sprintf(s, "%d", st + 1000000);
    
    que.push(state(s, 0));
    states[st + 1000000] = true;
    while (!que.empty()) {
        memcpy(cur, que.front().chr, sizeof(char) * 8);
        memcpy(tmp, cur, sizeof(char) * 8);
        t = que.front().count + 1;
        // swap0
        if (cur[0] - '1') {
            memcpy(tmp, cur, sizeof(char) * 8);
            tmp[cur[0] - '0'] = cur[1]; tmp[1] = cur[cur[0] - '0'];
            temp = atoi(tmp);
            if (temp % 1000000 == en) break;
            if (!states[temp]) {
                states[temp] = true;
                que.push(state(tmp, t));
            }
        }
        // swap1
        if (cur[0] - '6') {
            memcpy(tmp, cur, sizeof(char) * 8);
            tmp[cur[0] - '0'] = cur[6];
            tmp[6] = cur[cur[0] - '0'];
            temp = atoi(tmp);
            if (temp % 1000000 == en) break;
            if (!states[temp]) {
                states[temp] = true;
                que.push(state(tmp, t));
            }
        }
        // up
        if (cur[cur[0] - '0'] - '9') {
            memcpy(tmp, cur, sizeof(char) * 8);
            ++tmp[cur[0] - '0'];
            temp = atoi(tmp);
            if (temp % 1000000 == en) break;
            if (!states[temp]) {
                states[temp] = true;
                que.push(state(tmp, t));
            }
        }
        // down
        if (cur[cur[0] - '0'] - '0') {
            memcpy(tmp, cur, sizeof(char) * 8);
            --tmp[cur[0] - '0'];
            temp = atoi(tmp);
            if (temp % 1000000 == en) break;
            if (!states[temp]) {
                states[temp] = true;
                que.push(state(tmp, t));
            }
        }
        // left
        if (cur[0] - '1') {
            memcpy(tmp, cur, sizeof(char) * 8);
            --tmp[0];
            temp = atoi(tmp);
            if (!states[temp]) {
                states[temp] = true;
                que.push(state(tmp, t));
            }
        }
        // right
        if (cur[0] - '6') {
            memcpy(tmp, cur, sizeof(char) * 8);
            ++tmp[0];
            temp = atoi(tmp);
            if (!states[temp]) {
                states[temp] = true;
                que.push(state(tmp, t));
            }
        }
        que.pop();
    }
    printf("%d\n", t);
}
/*
const GLfloat vertex_list[][3] = {
    0.5,0.5,0.5,
    0.5,0.5,-0.5,
    0.5,-0.5,0.5,
    0.5,-0.5,-0.5,
    -0.5,0.5,0.5,
    -0.5,0.5,-0.5,
    -0.5,-0.5,0.5,
    -0.5,-0.5,-0.5
};
const GLint index_list[][4] ={
     7, 5, 1, 3,
     7, 6, 4, 5,
     7, 3, 2, 6,
     6, 2, 0, 4,
     3, 1, 0, 2,
     5, 4, 0, 1
};

double angel = 0;

void update(double dur) { angel += (dur * MATH_PI); }

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1.0);
    
    gluLookAt(cos(angel), sin(angel), 0, 0, 0, 0, 0, 0, 1);
    glBegin(GL_QUADS);
    int i, j;
    FIN(i, 6) {
        FIN(j, 4) {
            glVertex3fv(vertex_list[index_list[i][j]]);
        }
    }
    glEnd();
    glFlush();
    
}

int main(int argc, char* argv[]) {
    clock_t start, end, dur;
    start = clock();
    glutInit(&argc, argv);
    end = clock(); dur = end - start; start = clock();
    
    update(dur / (double)CLOCKS_PER_SEC);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("第一个OpenGL程序");
    glutDisplayFunc(&display);
    glutMainLoop();
}
*/
/*
#define pi 3.1415926
bool mouseisdown=false;
bool loopr=false;
int mx,my;
int ry=30;
int rx=30;
void timer(int p)
{
    ry-=5;
    glutPostRedisplay();                 //marks the current window as needing to be redisplayed.
    if (loopr)
        glutTimerFunc(200,timer,0);
}
void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {    mouseisdown=true; loopr=false;}
        else
            mouseisdown=false;
    }
    if (button== GLUT_RIGHT_BUTTON)
        if(state == GLUT_DOWN)
        {loopr=true; glutTimerFunc(200,timer,0);}
    
}
void motion(int x, int y)
{
    if(mouseisdown==true)
    {
        ry+=x-mx;
        rx+=y-my;
        mx=x;
        my=y;
        glutPostRedisplay();
    }
}
void special(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_LEFT:
            ry-=5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            ry+=5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            rx+=5;
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            rx-=5;
            glutPostRedisplay();
            break;
    }
}
void display()
{
    
    float red[3]={1,0,0};
    float blue[3]={0,1,0};
    float green[3]={0,0,1};
    float yellow[3]={1,1,0};
    
    
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(ry,0,1,0);
    glRotatef(rx,1,0,0);
    glColor3fv(green);
    glutWireTeapot(0.5);
    glFlush();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE| GLUT_RGBA);
    glutInitWindowSize (400, 400);
    glutInitWindowPosition(100,100);
    glutCreateWindow ("A TEAPOT");
    
    glutDisplayFunc (display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutSpecialFunc(special);
    glutMainLoop();
    return 0;
}
*/


/*
 map<string, int> a, b;
 void init() {
 a["one"] = 1; a["two"] = 2; a["three"] = 3; a["four"] = 4; a["five"] = 5; a["six"] = 6;
    a["seven"] = 7; a["eight"] = 8; a["nine"] = 9; a["ten"] = 10; a["eleven"] = 11; a["twelve"] = 12;
    a["thirteen"] = 13; a["fourteen"] = 14; a["fifteen"] = 15; a["sixteen"] = 16; a["seventeen"] = 17;
    a["eighteen"] = 18; a["nineteen"] = 19; a["twenty"] = 20; a["thirty"] = 30; a["forty"] = 40;
    a["fifty"] = 50; a["sixty"] = 60; a["seventy"] = 70; a["eighty"] = 80; a["ninty"] = 90;
    
    b["negative"] = -1; b["hundred"] = 100; b["thousand"] = 1000; b["million"] = 1000000;
}

int main() {
    string t, r;
    int rst, tmp, ma;
    char c[MAX_LEN];
    bool neg = false;
    init();
    while (cin.getline(c, MAX_LEN)) {
        rst = tmp = ma = 0; t = r = ""; neg = false;
        t = c;
        while (t.find(" ") != string::npos) {
            r = t.substr(0, t.find(" "));
            if (r.length()) {
                if (b[r] == -1) neg = true; else {
                    if (a[r]) tmp += a[r]; else if (b[r]) {
                        if (b[r] >= ma) { // "=" is illegal in fact, eg. two hundred three hundred
                            
                        }
                        tmp *= b[r]; rst += tmp; tmp = 0;
                    }
                }
                t = t.substr(t.find(" ") + 1);
            }
        }
        if (t.length()) {
            if (a[t]) tmp += a[t]; else if (b[t]) {
                tmp *= b[t]; rst += tmp; tmp = 0;
            }
            rst += tmp;
        }
        if (strlen(c)) cout << (neg ? -rst : rst) << endl;
    }
}
*/
/*
 struct p {
 int des; // destination
 int dis; // distance
 };
 
 p path[MAX_LEN][MAX_LEN];
 int MinPos[MAX_LEN];
 int n;
 */
/*
 int my_cmp(const void *a, const void *b) {
 int m = ((p*)a)->dis; int n = ((p*)b)->dis;
 // throw 0s behind
 if (!m) return 1;
 if (!n) return -1;
 return (m - n);
 }
 
 // find the min positive number(and its index) in an array
 p findMinPos(p path[][MAX_LEN], int begin) {
 p tmp[MAX_LEN], rst;
 memcpy(&tmp, path + begin, sizeof(p) * MAX_LEN);
 qsort(tmp, MAX_LEN, sizeof(p), my_cmp);
 rst.des = tmp[0].des; rst.dis = tmp[0].dis; // still can be 0
 return rst;
 }
 */
/*
 int main() {
 int i, j, k, dis, curVill = 0, rst = 0, Amin = inf, Bmin = inf;
 char cur, vill;
 p minV, minS;
 while (cin >> n) {
 if (!n) break;
 memset(path, 0, sizeof(path)); memset(MinPos, 0, sizeof(MinPos));
 curVill = rst = 0; Amin = Bmin = inf;
 FIN(i, n - 1) {
 cin >> cur >> k;
 while (k--) {
 cin >> vill >> dis;
 p tmp; tmp.des = vill - 'A'; tmp.dis = dis;
 path[cur - 'A'][vill - 'A'] = tmp;
 tmp.des = cur - 'A';
 path[vill - 'A'][cur - 'A'] = tmp;
 }
 }
 FIN(i, n - 1) {
 MinPos[curVill] |= (1 << 16);
 minV.des = 0; minV.dis = inf;
 FIN(j, n) {
 if (MinPos[j] & (1 << 16)) {
 for (int k = 0; k < n; k++) {
 if (!path[j][k].dis || MinPos[k] & (1 << 16)) continue;
 if (path[j][k].dis < minV.dis) {
 minV.dis = minS.dis = path[j][k].dis;
 minV.des = k; curVill = j;
 }
 }
 }
 }
 rst += minV.dis;
 path[curVill][minV.des].dis = path[minV.des][curVill].dis = 0;
 curVill = minV.des;
 }
 cout << rst << endl;
 }
 
 }
 */

/*
 #define STK_OV "stack overflow!"
 #define LEN_ZERO "length of the array == 0!"
 #define INDEX_OFR "index of the array out of range!"
 #define FIND_1_IN_0 "cannot find 1 because the input == 0!"
 
 using namespace std;
 typedef long long int ll;
 
 const unsigned int bits_of_int = __SIZEOF_INT__ * 8;
 
 class BitArray {
 protected:
 bool neg = false;
 unsigned int len;
 unsigned int int_count;
 unsigned int *bits;
 public:
 
 BitArray operator -(const BitArray);
 
 BitArray(unsigned int length) {
 if (!length) throw LEN_ZERO;
 this->int_count = (length + (bits_of_int - 1)) / bits_of_int;
 this->bits = new unsigned int[this->int_count]();
 this->len = length;
 //memset(this->bits, 0, this->int_count * __SIZEOF_INT__);
 //int i;
 //FIN(i, int_count) {
 //    bits[i] = 0;
 //}
 }
 
 BitArray(const BitArray &source):int_count(source.int_count) {
 bits = new unsigned int[int_count]();
 len = source.len;
 //memcpy(bits, &source.bits, sizeof(source.bits));
 int i;
 FIN(i, int_count) {
 bits[i] = source.bits[i];
 }
 }
 
 void init(unsigned int length) {
 if (!length) throw LEN_ZERO;
        this->int_count = (length + (bits_of_int - 1)) / bits_of_int;
        this->bits = new unsigned int[this->int_count]();
        this->len = length;
        memset(this->bits, 0, this->int_count * __SIZEOF_INT__);
    }
 
    void setBit(unsigned int index, unsigned int value) {
        if (index >= this->len) throw INDEX_OFR;
        if (value) {
            this->bits[index / bits_of_int] |= 1 << (index % bits_of_int);
        } else {
            this->bits[index / bits_of_int] &= ~(1 << (index % bits_of_int));
        }
    }
 
    unsigned int getBit(unsigned int index) const {
        if (index >= this->len) throw INDEX_OFR;
        if (this->bits[index / bits_of_int] & (1 << (index % bits_of_int))) {
            return 1;
        } else {
            return 0;
        }
    }
    
    unsigned int length() {
        return this->len;
    }
    
    void clear() {
        delete[] bits;
        len = 0;
        int_count = 0;
    }
    
    ~BitArray() {
        clear();
    }
    
    BitArray* operator =(ll num) {
        int i, zero = ~0;
        if (num < 0) this->neg = true;
        //memset(this->bits, 0, this->int_count * __SIZEOF_INT__);
        FIN(i, this->int_count) {
            this->bits[i] = num & (zero);
            num >>= bits_of_int;
            if (!num) break;
        }
        return this;
    }
    
    const BitArray &operator =(const BitArray &num) {
        if (&num == this) return *this;
        delete[] bits;
        neg = num.neg;
        len = num.len;
        int_count = num.int_count;
        bits = new unsigned int[int_count]();
        //memcpy(this->bits, &num.bits, sizeof(num.bits));
        int i;
        FIN(i, len) {
            setBit(i, num.getBit(i));
        }
        return *this;
    }
    
    const BitArray &copy(const BitArray &num, bool expand = false,
                         unsigned int destIndex = 0, unsigned int sourceIndex = 0,
                         unsigned int length = 0) {
        //if (&num == this) return *this;
        if (!length) length = num.len;
        if (sourceIndex + length > num.len) throw INDEX_OFR;
        if (expand && this->len - destIndex < length) {
            //delete[] bits;
            //len = num.len;
            //int_count = num.int_count;
            //bits = new unsigned int[int_count]();
            this->resize(destIndex + length);
        }
        //memcpy(this->bits, &num.bits, sizeof(num.bits));
        int i;
        //FIN(i, len) {
        //    if (i >= num.len) {
        //        setBit(i, 0);
        //    } else {
        //        setBit(i, num.getBit(i));
        //    }
        //}
        FIN(i, length) {
            if (i + destIndex >= this->len) break;
            this->setBit(i + destIndex, num.getBit(i + sourceIndex));
        }
        this->neg = num.neg;
        return *this;
    }
    
    unsigned int bitScan(bool reverse = false) { // find the highest / lowest 1's position
        unsigned int pos, i, tmp;
        if (reverse) {
            FINM(i, this->int_count) {
                if (!this->bits[i]) continue;
                tmp = this->bits[i];
                __asm {
                    bsr eax, tmp;
                    mov pos, eax;
                }
                return (pos + i * bits_of_int);
            }
        } else {
            FIN(i, this->int_count) {
                if (!this->bits[i]) continue;
                tmp = this->bits[i];
                __asm {
                    bsf eax, tmp;
                    mov pos, eax;
                }
                return (pos + i * bits_of_int);
            }
        }
        throw FIND_1_IN_0; // *this == 0
    }
    
    BitArray* resize(unsigned length) { // do not expand even if length < this->len
        BitArray tmp(length);
        int i;
        FIN(i, length) {
            if (len <= i) {
                tmp.setBit(i, 0);
            } else {
                tmp.setBit(i, this->getBit(i));
            }
        }
        delete[] bits;
        len = tmp.len;
        int_count = tmp.int_count;
        bits = new unsigned int[int_count]();
        FIN(i, length) {
            this->setBit(i, tmp.getBit(i));
        }
        return this;
    }
    
    BitArray &operator ~() {
        this->neg = !this->neg;
        return *this;
    }
    
    bool operator ==(unsigned int target) const {
        if (this->neg) return false;
        int i;
        FIN1(i, this->int_count - 1) {
            if (this->bits[i]) return false;
        }
        return (this->bits[0] == target);
    }
    
    bool operator ==(const BitArray& target) const {
        if (this->neg != target.neg) return false;
        if (len != target.len) return false;
        int i;
        FIN(i, len) {
            if (getBit(i) ^ target.getBit(i)) return false;
        }
        return true;
    }
    
    bool operator !=(unsigned int target) const {
        return !(*this == target);
    }
    
    bool operator !=(const BitArray& target) const {
        return !(*this == target);
    }
    
    bool operator !() const {
        return (*this == 0);
    }
    
    unsigned int operator [](unsigned int index) const {
        return getBit(index);
    }
    
    BitArray operator +(const BitArray &num) {
        unsigned int len = max(this->len, num.len) + 1;
        int i;
        int8_t c = 0; // carry flag, using 1 byte to store the flags
        //bool c = false;
        BitArray tmp1(len), tmp2(len);
        tmp1 = tmp1.copy(*this); tmp2 = tmp2.copy(num);
        FIN(i, tmp1.int_count) {
            unsigned int a = tmp1.bits[i], b = tmp2.bits[i];
            if (c & 1) { // carry
                __asm {
                    mov eax, a;
                    mov ebx, b;
                    stc;             // carry flag = 1
                    adc eax, ebx;
                    mov a, eax;
                    lahf;            // lahf will effect the result????
                    mov c, ah;
                }
            } else {
                __asm {
                    mov eax, a;
                    mov ebx, b;
                    clc;              // carry flag = 0
                    adc eax, ebx;
                    mov a, eax;
                    lahf;             // mov ah, flags
                    mov c, ah;
                }
            }
            tmp1.bits[i] = a;
            */
            /*
             ======bug====== the determination of carring or not remains bugs.
            if (c) {
                c = false;
                if (a == 4294963295) c = true;
                ++a;
                tmp1.bits[i] = a;
            }
            if ((a & b) >= (1 << 31)) c = true; else c = false;
            while (a && b) {
                tmp1.bits[i] = a ^ b;
                tmp2.bits[i] = a & b;
                a = tmp1.bits[i]; b = tmp2.bits[i] << 1;
            }
            tmp1.bits[i] = (a | b);
            */
            /*
        }
        if (c & 1) throw STK_OV;
        //tmp1 != 0 !!!!!!
        tmp1 = *tmp1.resize(tmp1.bitScan(true) + 1);
        *this = tmp1;
        return *this;
    }
    
    BitArray operator -(const BitArray &num) {
        if (this->neg != num.neg) return ~(~(*this) + num);
        unsigned int len = max(this->len, num.len) + 1;
        int i;
        int8_t c = 0; // carry flag, using 1 byte to store the flags
        //bool c = false;
        BitArray tmp1(len), tmp2(len);
        tmp1 = tmp1.copy(*this); tmp2 = tmp2.copy(num);
        FIN(i, tmp1.int_count) {
            unsigned int a = tmp1.bits[i], b = tmp2.bits[i];
            if (c & 1) { // carry
                __asm {
                    mov eax, a;
                    mov ebx, b;
                    stc;             // carry flag = 1
                    adc eax, ebx;
                    mov a, eax;
                    lahf;            // lahf will effect the result????
                    mov c, ah;
                }
            } else {
                __asm {
                    mov eax, a;
                    mov ebx, b;
                    clc;              // carry flag = 0
                    adc eax, ebx;
                    mov a, eax;
                    lahf;             // mov ah, flags
                    mov c, ah;
                }
            }
            tmp1.bits[i] = a;
            */
            /*
             ======bug====== the determination of carring or not remains bugs.
             if (c) {
             c = false;
             if (a == 4294963295) c = true;
             ++a;
             tmp1.bits[i] = a;
             }
             if ((a & b) >= (1 << 31)) c = true; else c = false;
             while (a && b) {
             tmp1.bits[i] = a ^ b;
             tmp2.bits[i] = a & b;
             a = tmp1.bits[i]; b = tmp2.bits[i] << 1;
             }
             tmp1.bits[i] = (a | b);
             */
            /*
        }
        if (c & 1) throw STK_OV;
        //tmp1 != 0 !!!!!!
        tmp1 = *tmp1.resize(tmp1.bitScan(true) + 1);
        *this = tmp1;
        return *this;
    }
    
    BitArray &operator *(const BitArray &num) {
        if (!(*this) || !num) {
            BitArray zero(1);
            *this = zero;
            return *this;
        }
        if (this->len == 1 && this->len == num.len) {
            BitArray rst(1);
            rst.setBit(0, 1); // now *this != 0 && num != 0
            *this = rst;
            return *this;
        }
        unsigned int len = max(this->len, num.len);
        int i;
        
        BitArray tmpa(len), tmpb(len);
        tmpa = tmpa.copy(*this); tmpb = tmpb.copy(num);
        BitArray tmp1(len >> 1), tmp2(len >> 1),
            tmp3(len - (len >> 1)), tmp4(len - (len >> 1)), rst(len << 1);
        tmp1 = tmp1.copy(tmpa); tmp2 = tmp2.copy(tmpb);
        tmp3 = tmp3.copy(tmpa, false, 0, len >> 1); tmp4 = tmp4.copy(tmpb, false, 0, len >> 1);
        rst = rst.copy(tmp1 * tmp2);
        rst = rst.copy(tmp1 * tmp4 + tmp2 * tmp3, false, len >> 1);
        rst = rst.copy(tmp3 * tmp4, false, len >> 1 << 1);
        return *this;
    }
    
    void printBin() const {
        int i;
        FINM(i, this->len) {
            printf("%u", getBit(i));
        }
        printf("\n");
    }
    
    void printDec() const { // bug
        int i;
        FINM(i, this->int_count) {
            printf("%u ", this->bits[i]);
        }
        printf("\n");
    }
};

int main() {
    try {
        BitArray b(64);
        b = 102030405060708090;
        BitArray c(64);
        c = 908070605040302010;
        c = b + c;
        c.printBin(); c.printDec();
    } catch(string dscpt) {
        cout << dscpt << endl;
    }
}
*/
