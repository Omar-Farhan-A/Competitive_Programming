const int N = 5e5 + 10;
vector<int> d[N];
char mob[N];
bool prime[N];

void moebius() {
    memset(mob, 1, sizeof mob);
    memset(prime + 2, 1, sizeof(prime) - 2);
    mob[0] = 0;
    mob[2] = -1;
    for (int i = 4; i < N; i += 2) {
        mob[i] *= (i & 3) ? -1 : 0;
        prime[i] = 0;
    }
    for (int i = 3; i < N; i += 2)
        if (prime[i]) {
            mob[i] = -1;
            for (int j = 2 * i; j < N; j += i) {
                mob[j] *= j % (1LL * i * i) ? -1 : 0;
                prime[j] = 0;
            }
        }
    for (int i = 2; i < N; i++) {
        if (mob[i] == 0)continue;
        for (int j = i; j < N; j += i)d[j].push_back(i);
    }
}
