# FdF
Fil de Fer se trata de um projeto da 42 e significa algo parecido com "grade de ferro" ou "wireframe", em francês.
<br></br>
<br></br>
[See english version](https://github.com/jou-code/fdf/README-EN.md)

Um programa que exibe a representação 3d de um mapa na perspectiva isométrica.

![image](https://github.com/jou-code/fdf/assets/145489056/d995fa86-1439-45b1-8833-91e1ea8e2bf4)

A partir de um arquivo que contém uma matriz de pontos com coordenadas (x, y, z) de cada ponto, devemos posicioná-los e ligá-los aos seus adjacentes para formar essa malha de fios. Usando uma pequena [biblioteca gráfica da 42](https://github.com/42Paris/minilibx-linux/), devemos renderizar pixel por pixel para gerar a imagem e exibi-la na tela.
<br></br>
<br></br>

## Como executar o projeto localmente
1. Cole esse comando no terminal para clonar e compilar:
   
  ``` bash
  git clone --recursive git@github.com:g-joana/fdf.git && cd fdf && make
  ```

2. Para executar digite o _binário_ + _mapa_. Exemplo:
  
  ``` bash
  ./fdf maps/mars.fdf
  ```
  _'./fdf maps/' + mapa escolhido_
