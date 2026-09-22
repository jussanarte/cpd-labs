# Lab 3 — Análise de Desempenho OpenMP

Laboratório 3 de CPD: **profiling** e optimização de programas OpenMP com o **Intel VTune Profiler** (análises de *Hotspots* e *Threading*), usando três implementações de multiplicação de matrizes.

## 📜 Enunciado (resumo)

- **Objectivos**: analisar e optimizar o desempenho de programas OpenMP; *profiling* com **Intel VTune Profiler**.
- **Hotspots**: compilar com `-g`, executar amostragem (*sampling*) em modo utilizador e identificar as secções de código que consomem mais tempo (Bottom-Up, Flame Graph).
- **Threading**: analisar `mult-sync.c`, `mult-redux.c` e `mult-good.c`, medindo o *overhead* das directivas OpenMP, o ponto de sincronização e a eficiência de utilização da CPU.
- **Requisito**: símbolos de debug do `libgomp` para o VTune identificar correctamente as directivas (apêndice do enunciado).

## Programas

Multiplicação de matrizes `N x N` (N = 1000) com três estratégias de paralelização:

| Ficheiro | Estratégia |
|----------|------------|
| `mult-sync.c` | Sincronização exagerada (`single`/`barrier` por elemento) — ponto de sincronização caro |
| `mult-redux.c` | Região paralela e `reduction` criadas dentro do loop interior |
| `mult-good.c` | Uma única directiva `parallel for` no loop exterior — implementação eficiente |

## Compilar

```bash
make
```

Gera os executáveis `mult-sync`, `mult-redux` e `mult-good`.

## Executar / analisar

```bash
./mult-sync
./mult-redux
./mult-good
```

Compilar com `-g` e executar a análise no **Intel VTune** (GUI: `vtune-gui`; CLI: `vtune -collect threading ./mult-sync`) para comparar as três implementações — tempo efectivo, ponto de sincronização e desequilíbrio de carga.

## Notas

- `mult-good.c` não inicializa a matriz `C` após `malloc`; para resultados correctos deve ser usada `calloc` ou `memset` antes do cálculo.
- A análise *Threading* do VTune exige símbolos de debug do `libgomp` (ver apêndice do enunciado).