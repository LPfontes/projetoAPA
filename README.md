
## Instruções de Compilação

Na raiz do projeto execute o comando no terminal:

make


## Instruções de Execução


Para executar uma instância basta passar o caminho como argumento no terminal:
  

./build/prog <caminho_do_arquivo>
  

Para executar todas as instancias e calcular o gap bas executar sem argumentos:
  

./build/prog


## Organização do projeto


./input - Instâncias de teste.

./include - Arquivos de cabeçalho.

./src - Implementações do código.


		
## Principais Arquivos:
	
### Algoritmo guloso:
		
LowerCost 
A classe LowerCost implementa um algoritmo guloso do vizinho mais próximo, utilizando uma matriz de adjacência ordenada para selecionar a próxima estação com o menor custo que ainda não tenha sido visitada, garantindo que a capacidade do caminhão não seja ultrapassada e que a carga não se torne negativa.
RouteStep
A classe RouteStep representa um movimento na rota construída, armazenando as informações relevantes de um trecho entre duas estações, como o ID da estação de origem, o ID da estação de destino, a carga, o custo e o custo acumulado até aquele ponto.
		
### VND: 

./src/VND.cpp - A lógica de execução do VND utilizando os algoritmos de vizinhança descritos  a seguir.

#### Algoritmos de vizinhança:
	
Swap - ./src/swap.cpp - Implementado conforme demonstrado na vídeo aula, realiza as permutações em cada rota.
		
2-Opt - ./src/TwoOpt.cpp - Também implementado conforme demonstrado na vídeo aula. Realiza as trocas em cada rota. 

Swap2 - ./src/swap2.cpp - Implementado conforme demonstrado na vídeo aula, com a modificação que permite não apenas trocar nós dentro de uma mesma rota, mas também realizar permutações entre diferentes rotas.
