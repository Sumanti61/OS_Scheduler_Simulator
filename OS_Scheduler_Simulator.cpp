#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct P {
    int id, at, bt, pr, ct, tat, wt, rt;
};

void print(vector<P> &p) {
    float wt = 0, tat = 0;
    cout << "\nID AT BT CT TAT WT\n";
    for (auto x : p) {
        cout << x.id << "  " << x.at << "  " << x.bt << "  "
             << x.ct << "  " << x.tat << "   " << x.wt << "\n";
        wt += x.wt;
        tat += x.tat;
    }
    cout << "Avg WT = " << wt / p.size();
    cout << "\nAvg TAT = " << tat / p.size() << "\n";
}

/* FCFS */
void FCFS(vector<P> p) {
    int t = 0;
    cout << "\nGantt: ";
    for (auto &x : p) {
        t = max(t, x.at);
        cout << "P" << x.id << " ";
        t += x.bt;
        x.ct = t;
        x.tat = x.ct - x.at;
        x.wt = x.tat - x.bt;
    }
    print(p);
}

/* SJF */
void SJF(vector<P> p) {
    int n = p.size(), done = 0, t = 0;
    vector<int> v(n, 0);
    cout << "\nGantt: ";
    while (done < n) {
        int i = -1, mn = INT_MAX;
        for (int j = 0; j < n; j++)
            if (!v[j] && p[j].at <= t && p[j].bt < mn)
                mn = p[j].bt, i = j;

        if (i == -1) { t++; continue; }

        cout << "P" << p[i].id << " ";
        t += p[i].bt;
        p[i].ct = t;
        p[i].tat = t - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        v[i] = 1; done++;
    }
    print(p);
}

/* Priority */
void PRIORITY(vector<P> p) {
    int n = p.size(), done = 0, t = 0;
    vector<int> v(n, 0);
    cout << "\nGantt: ";
    while (done < n) {
        int i = -1, best = INT_MAX;
        for (int j = 0; j < n; j++)
            if (!v[j] && p[j].at <= t && p[j].pr < best)
                best = p[j].pr, i = j;

        if (i == -1) { t++; continue; }

        cout << "P" << p[i].id << " ";
        t += p[i].bt;
        p[i].ct = t;
        p[i].tat = t - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        v[i] = 1; done++;
    }
    print(p);
}

/* Round Robin */
void RR(vector<P> p, int q) {
    int t = 0, done = 0, n = p.size();
    for (auto &x : p) x.rt = x.bt;

    cout << "\nGantt: ";
    while (done < n) {
        bool exec = false;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= t && p[i].rt > 0) {
                exec = true;
                cout << "P" << p[i].id << " ";
                int x = min(q, p[i].rt);
                p[i].rt -= x;
                t += x;
                if (p[i].rt == 0) {
                    done++;
                    p[i].ct = t;
                    p[i].tat = t - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                }
            }
        }
        if (!exec) t++;
    }
    print(p);
}

/* SRTF */
void SRTF(vector<P> p) {
    int n = p.size(), done = 0, t = 0;
    for (auto &x : p) x.rt = x.bt;

    cout << "\nGantt: ";
    while (done < n) {
        int i = -1, mn = INT_MAX;
        for (int j = 0; j < n; j++)
            if (p[j].at <= t && p[j].rt > 0 && p[j].rt < mn)
                mn = p[j].rt, i = j;

        if (i == -1) { t++; continue; }

        cout << "P" << p[i].id << " ";
        p[i].rt--; t++;
        if (p[i].rt == 0) {
            done++;
            p[i].ct = t;
            p[i].tat = t - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
        }
    }
    print(p);
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<P> p(n);
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "AT BT Priority for P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt >> p[i].pr;
    }

    int ch;
    cout << "\n1.FCFS 2.SJF 3.Priority 4.RR 5.SRTF\nChoose: ";
    cin >> ch;

    if (ch == 1) FCFS(p);
    else if (ch == 2) SJF(p);
    else if (ch == 3) PRIORITY(p);
    else if (ch == 4) {
        int q;
        cout << "Time Quantum: ";
        cin >> q;
        RR(p, q);
    }
    else if (ch == 5) SRTF(p);

    return 0;
}
