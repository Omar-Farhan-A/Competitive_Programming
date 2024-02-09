const int N=1e6+6;
bool is_prime[N];
void sieve() {  // O(N) ~= O(N*log(log(N)))
    fill(is_prime, is_prime + N, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p < N; p++) {
        if (is_prime[p]) {
            for (int m = p * p; m < N; m += p) {
                is_prime[m] = false;
            }
        }
    }
}