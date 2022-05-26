# --------------------测试用，提交前请注释掉----------------------

# import sys

# sys.stdin = open('in3.dat', 'r')
# sys.stdout = open('out3.dat', 'w')

# -------------------------------------------------------------
from collections import deque

class Random():
    def __init__(self) -> None:
        self.next = 1

    def myrand(self):
        self.next = (self.next * 1103515245 + 12345) % (2 ** 64)
        return (self.next // 65536) % 32768

class neural():
    def __init__(self, v, u, a, b, c, d, dt) -> None:
        self.v, self.u, self.a, self.b, self.c, self.d, self.dt = v, u, a, b, c, d, dt
        self.Ik = 0
        self.out_connect = list()
        self.cnt = 0
    
    def update(self):
        self.v, self.u = self.v + self.dt * (0.04 * self.v ** 2 + 5 * self.v + 140 - self.u) + self.Ik, self.u + self.dt * self.a * (self.b * self.v - self.u)
        if self.v >= 30:
            self.launch()
            self.v, self.u = self.c, self.u + self.d
        self.Ik = 0
    
    def receve(self, w):
        self.Ik += w

    def launch(self):
        for c in self.out_connect:
            c.receve()
        self.cnt += 1

class source():
    def __init__(self, r):
        self.r = r
        self.out_connect = list()
    
    def update(self, rand):
        if self.r > rand:
            self.launch()
    
    def launch(self):
        for c in self.out_connect:
            c.receve()

class connect():
    def __init__(self, s, t, w, D) -> None:
        self.s, self.t, self.w, self.Delay = s, t, w, D
        self.signal = deque([0 for _ in range(D)], maxlen=D)
        self.cur = 0
    
    def receve(self):
        self.cur += 1

    def launch(self, s):
        self.t.receve(self.w * s)
    
    def update(self):
        c = self.signal.popleft()
        if c > 0:
            self.launch(c)

    def clear(self):
        self.signal.append(self.cur)
        self.cur = 0

def main():
    rand = Random()
    N, S, P, T = map(int, input().split())
    dt = float(input())
    cnt = N
    network = list()
    conn = list()
    while cnt:
        # neural
        RN, v, u, a, b, c, d = map(float, input().split())
        RN = int(RN)
        cnt -= RN
        for _ in range(RN):
            network.append(neural(v, u, a, b, c, d, dt))
    for _ in range(P):
        # source
        r = int(input())
        network.append(source(r))
    for _ in range(S):
        # connect
        s, t, w, D = input().split()
        s, t, D = map(int, (s, t, D,))
        w = float(w)
        c = connect(s, network[t], w, D)
        conn.append(c)
        network[s].out_connect.append(c)
    for _ in range(T):
        for i in range(N, N + P):
            network[i].update(rand.myrand())
        for c in conn:
            c.update()
        for i in range(N):
            network[i].update()
        for c in conn:
            c.clear()
    print("{:.3f} {:.3f}".format(round(min(network[i].v for i in range(N)), 3), round(max(network[i].v for i in range(N)), 3)))
    print("{} {}".format(min(network[i].cnt for i in range(N)), max(network[i].cnt for i in range(N))))

# --------------------测试用，提交前请注释掉----------------------
        
main()
# main()

# ---------------------------------------------------------------