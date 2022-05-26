#include <bits/stdc++.h>
using namespace std;

int N, S, P, T;  // 神经元1e3、突触1e3、脉冲元1e3、输出时刻1e5
double st;  // 时间间隔
int R_N;
double u, v, a, b, c, d;
int r;
int s, t, D;
double w;

class sjy;
class tc;
class mcy;

sjy* s1[1007];  // 神经元
tc* s2[1007]; // 突触
mcy* s3[1007]; // 脉冲源

static unsigned long nxt = 1;
int myrand(void);

class tc { // 突触
public:
    int s, t;
    double w;
    int D;
    double* count;  // 脉冲累计
    int c; // 时刻指针位置

    tc(int _s, int _t, double _w, int _D);

    void recive();

    void update();

    void timenext();
};

class sjy { // 神经元
public:
    double u, v, a, b, c, d;
    int cnt;
    double Ik;
    tc* t[1007]; // 链接的突触
    int ct; // 突触数量
    sjy(double _v, double _u, double _a, double _b, double _c, double _d):u(_u), v(_v), a(_a), b(_b), c(_c), d(_d), cnt(0), ct(0), Ik(0) {
    }
    
    void update();

    void addtc(tc* atc);

    void send();
};

class mcy { // 脉冲源
public:
    int r;
    tc* t[1007]; // 链接的突触
    int ct; // 突触数量
    mcy(int _r): r(_r), ct(0) {

    }

    bool isSent() {
        if (r > myrand()) return true;
        else false;
    }

    void sent() {
        // 调用这个！！！！！！
        if (isSent())send();
    }

    void addtc(tc* atc) {
        t[ct++] = atc;
    }

    void send() {
        // 发生脉冲
        // printf("脉冲元发生脉冲\n");
        for (int i = 0; i < ct; ++i) {
            t[i]->recive();
        }
    }
};

tc::tc(int _s, int _t, double _w, int _D):s(_s), t(_t), w(_w), D(_D), c(0) {
    count = new double[D + 1];
    if (_s < N)
        s1[_s]->addtc(this);
    else s3[_s - N]->addtc(this);
}

void tc::recive() {
    // 收到脉冲
    // printf("突触 %d -> %d 收到脉冲\n", s, t);
    count[(c + D) % (D + 1)] += w;
}

void tc::update() {
    // 更新
    s1[t]->Ik += count[c];
    count[c] = 0;
}

void tc::timenext() {
    c = (c + 1) % (D + 1);
}

void sjy::update() {
    double uu, vv;
    vv = v + st * (0.04 * v * v + 5 *  v + 140 - u) + Ik;
    uu = u + st * a * (b * v - u);
    u = uu; v = vv;
    if (v >= 30) {
        send();
        v = c;
        u += d;
        cnt++;
    }
    // printf("更新后v为 %f\n", v);
    Ik = 0;
}

void sjy::addtc(tc* atc) {
    t[ct++] = atc;
}

void sjy::send() {
    // 发生脉冲
    // printf("神经元发生脉冲\n");
    for (int i = 0; i < ct; ++i) {
        t[i]->recive();
    }
}

/* RAND_MAX assumed to be 32767 */
int myrand(void) {
    nxt = nxt * 1103515245 + 12345;
    return((unsigned)(nxt/65536) % 32768);
}

int main(){

    // freopen("in.in", "r", stdin);
    // freopen("out.out", "w", stdout);

    cin >> N >> S >> P >> T;
    cin >> st;
    for (int i = N, j = 0; i > 0; ) {
        cin >> R_N >> v >> u >> a >> b >> c >> d;
        for (int k = 0; k < R_N; ++k) {
            s1[j++] = new sjy(v, u, a, b, c, d);
        }
        i -= R_N;
    }
    for (int i = 0; i < P; ++i) {
        cin >> r;
        s3[i] = new mcy(r);
    }
    for (int i = 0; i < S; ++i) {
        cin >> s >> t >> w >> D;
        s2[i] = new tc(s, t, w, D);
    }
    for (int tim = 1; tim <= T; tim++) {
        // printf("------ 当前时刻 %d --------\n", tim);
        for (int i = 0; i < P; ++i) {
            // printf("第 %d 个脉冲源\n", i);
            s3[i]->sent();
        }
        for (int i = 0; i < S; ++i) {
            // printf("第 %d 个突触\n", i);
            s2[i]->update();
        }
        for (int i = 0; i < N; ++i) {
            // printf("第 %d 个神经源\n", i);
            s1[i]->update();
        }
        for (int i = 0; i < S; ++i) {
            s2[i]->timenext();
        }
    }

    double ans1 = s1[0]->v, ans2 = s1[0]->v;
    int ans3 = s1[0]->cnt, ans4 = s1[0]->cnt;
    for (int i = 0; i < N; ++i) {
        ans1 = s1[i]->v > ans1 ? s1[i]->v : ans1;
        ans2 = s1[i]->v < ans2 ? s1[i]->v : ans2;
        ans3 = s1[i]->cnt > ans3 ? s1[i]->cnt : ans3;
        ans4 = s1[i]->cnt < ans4 ? s1[i]->cnt : ans4;
    }
    printf("%.3f %.3f\n", ans2, ans1);
    printf("%d %d", ans4, ans3);
    return 0;
}

/// 网上看到的满分解法

#include <bits/stdc++.h>

using namespace std;

static unsigned long nex = 1;

/* RAND_MAX assumed to be 32767 */
int myrand() {
    nex = nex * 1103515245 + 12345;
    return ((unsigned) (nex / 65536) % 32768);
}

int N, S, P, T;
double ct;
double maxv = -DBL_MAX;
double minv = DBL_MAX;
double v, u, a, b, c, d;
int maxtim = -INT_MAX;
int mintim = INT_MAX;
struct SJY {
    double v, u, a, b, c, d;
    int tim;
} sjy[1005];

double getww[1005][1005];
vector<int> G[2005];
struct TU {
    int s, t;
    double w;
    int D;
};
vector<TU> tu;
int r[1005];
int maxD=0;

int main() {
    int sjyn = 0;
    int RN;
    scanf("%d%d%d%d", &N, &S, &P, &T);
    scanf("%lf", &ct);
    while (true) {
        scanf("%d%lf%lf%lf%lf%lf%lf", &RN, &v, &u, &a, &b, &c, &d);
        while (RN--) {
            sjy[sjyn].v = v;
            sjy[sjyn].u = u;
            sjy[sjyn].a = a;
            sjy[sjyn].b = b;
            sjy[sjyn].c = c;
            sjy[sjyn].d = d;
            sjy[sjyn].tim = 0;
            sjyn++;
        }
        if (sjyn == N)
            break;
    }
    for (int i = 0; i < P; i++)
        scanf("%d", &r[i]);
    int s, t, D;
    double w;
    for (int i = 0; i < S; i++) {
        scanf("%d%d%lf%d", &s, &t, &w, &D);
        G[s].push_back(i);
        tu.push_back({s, t, w, D});
        if(D>maxD)
            maxD=D;
    }
    maxD++;
    for (int nowt = 1; nowt <= T; nowt++) {
        for (int j = 0; j < N; j++) {
            double v1 = sjy[j].v, u1 = sjy[j].u;
            sjy[j].v = v1 + ct * (0.04 * v1 * v1 + 5 * v1 + 140 - u1) + getww[nowt%maxD][j];
            sjy[j].u = u1 + ct * sjy[j].a * (sjy[j].b * v1 - u1);
            getww[nowt%maxD][j] = 0;
            if (sjy[j].v >= 30) {
                sjy[j].tim++;
                sjy[j].v = sjy[j].c;
                sjy[j].u += sjy[j].d;
                for (int ii = 0; ii < G[j].size(); ii++) {
                    TU tu1(tu[G[j][ii]]);
                    getww[(nowt+tu1.D)%maxD][tu1.t] += tu1.w;
                }
            }
        }

        for (int j = 0; j < P; j++) {
            if (r[j] > myrand()) {
                for (int ii = 0; ii < G[j + N].size(); ii++) {
                    TU tu1(tu[G[j + N][ii]]);
                    getww[(nowt+tu1.D)%maxD][tu1.t] += tu1.w;
                }
            }
        }
    }
    for(int j=0;j<N;j++){
        if (sjy[j].v > maxv)
            maxv = sjy[j].v;
        if (sjy[j].v < minv)
            minv = sjy[j].v;
        if (sjy[j].tim > maxtim)
            maxtim = sjy[j].tim;
        if (sjy[j].tim < mintim)
            mintim = sjy[j].tim;
    }
    printf("%.3f %.3f\n", minv, maxv);
    printf("%d %d", mintim, maxtim);

    return 0;
}