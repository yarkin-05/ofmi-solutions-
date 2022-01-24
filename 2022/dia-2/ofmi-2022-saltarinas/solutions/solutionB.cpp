#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>

constexpr int intervalo_maximo = 16;
constexpr int maximo_sobrante = 720720;
constexpr int MOD = 1e9 + 7;

// Cantidad de cobayas que saltan cada i segundos
int tiempoSalto[intervalo_maximo + 1], tiempoGranVuelta;
unsigned long long saltosGranVuelta, sobrantes[maximo_sobrante + 1];
;

int lcm(int a, int b) { return a * b / std::__gcd(a, b); }

void calculaVueltaGrande() {
  tiempoGranVuelta = 1;
  for (int i = 1; i <= intervalo_maximo; i++) {
    if (tiempoSalto[i]) {
      tiempoGranVuelta = lcm(tiempoGranVuelta, i);
    }
  }
}

void calculaSaltosGranVuelta() {
  saltosGranVuelta = 0;
  for (int i = 1; i <= intervalo_maximo; i++) {
    saltosGranVuelta +=
        tiempoSalto[i] * ((unsigned long long)tiempoGranVuelta / i);
  }
}

unsigned long long sobrante(unsigned long long tiempo) {
  if (sobrantes[tiempo] != -1) {
    return sobrantes[tiempo];
  }
  unsigned long long cantidad_total_saltos = 0;
  for (int i = 1; i <= intervalo_maximo; i++) {
    // Contamos la cantidad de saltos que da una cobaya
    unsigned long long cantidad_saltos = tiempo / (unsigned long long)i;
    // Sumamos los saltos que hacen todas las cobayas de este tipo
    cantidad_total_saltos += cantidad_saltos * tiempoSalto[i];
  }
  return sobrantes[tiempo] = cantidad_total_saltos;
}

unsigned long long contarBrincos(unsigned long long tiempo) {
  unsigned long long a = tiempo / (unsigned long long)tiempoGranVuelta;
  unsigned long long resultado = a * saltosGranVuelta;
  if (__builtin_umulll_overflow(
          a, saltosGranVuelta,
          &resultado)) {  // equivalente a c = a * b; if (c se desbordó...) {
    return ULLONG_MAX;
  }
  return resultado + sobrante(tiempo % tiempoGranVuelta);
}

unsigned long long busquedaBinaria(unsigned long long inicio,
                                   unsigned long long final,
                                   unsigned long long m) {
  if (inicio == final) {
    return inicio;
  }
  unsigned long long mitad = (inicio + final) / 2;
  if (contarBrincos(mitad) >= m) {
    return busquedaBinaria(inicio, mitad, m);
  } else {
    return busquedaBinaria(mitad + 1, final, m);
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);

  int n, t, q, x;

  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::cin >> t;
    tiempoSalto[t]++;
  }

  calculaVueltaGrande();

  calculaSaltosGranVuelta();

  std::cin >> q >> x;

  memset(sobrantes, -1, sizeof(sobrantes));

  long long respuesta = 0;

  unsigned long long m = 0;

  for (int i = 0; i < q; i++) {
    m += x;
    respuesta =
        (respuesta + (busquedaBinaria(0, intervalo_maximo * m, m) % MOD)) % MOD;
  }

  std::cout << respuesta << "\n";

  return 0;
}
