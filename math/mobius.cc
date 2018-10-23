void sieve() {
    fill(isPrime, isPrime + maxn, 1);
    mu[1] = 1, num = 0;
    for (int i = 2; i < maxn; ++i) {
        if (isPrime[i]) primes[num++] = i, mu[i] = -1;
        static int d;
        for (int j = 0; j < num && (d = i * primes[j]) < maxn; ++j) {
            isPrime[d] = false;
            if (i % primes[j] == 0) {
                mu[d] = 0;
                break;
            } else mu[d] = -mu[i];
        }
    }
}