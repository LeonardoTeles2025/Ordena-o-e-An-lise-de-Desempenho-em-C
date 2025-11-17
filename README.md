# Ordena-o-e-An-lise-de-Desempenho-em-C
README.md — PROJETO DE ORDENAÇÃO (Bubble Sort)

1. Entrada A (RGM): 
  - O usuário informa seu RGM (8 dígitos).  
  - Cada dígito é convertido para inteiro.  
  - O vetor é ordenado com Bubble Sort.  
  - São registrados tempo e número de passos (operações-chave).
A saída final é exibida em formato **CSV**, permitindo importar em Excel, Python, R, etc.

Entrada B (Benchmark):  
   - Geração de vetores aleatórios nos tamanhos N = 100, 1.000, 10.000.  
   - Cada vetor é ordenado com Bubble Sort.  
   - São registradas métricas de desempenho.  
   - Cada caso é executado 5 vezes, calculando a média.

 
Bubble Sort foi escolhido porque:

1. É extremamente simples de implementar.
2. Sua lógica facilita a contagem de passos.
3. É útil para fins didáticos na comparação entre custos teóricos e experimentais.
4. Mostra claramente problemas de escalabilidade em entradas grandes.
Como este trabalho solicita somente Bubble Sort, a escolha foi intencional para demonstrar limites computacionais.

--Como compilar e executar

    No terminal, dentro da pasta do projeto:

gcc -O1 -std=c11 src/*.c -o ordena

    --O tempo é medido usando:

clock_t t0 = clock();
...
tempo_ms = (clock() - t0) * 1000.0 / CLOCKS_PER_SEC;

   --Saída em Formato CSV

Estrutura da saída:

metodo,N,caso,passos,tempo_ms

   --Conclusão

O Bubble Sort cumpre seu papel didático, mas é ineficiente para tamanhos reais.
O estudo demonstra claramente por que algoritmos quadráticos não escalam bem.
