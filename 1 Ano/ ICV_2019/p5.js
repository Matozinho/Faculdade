//=================Variáveis Globais====================//
let canvas, Cwidth = 1200, Cheight = 800; //variáveis sobre o canvas
let colunas, linhas, tamanho; //variáveis para resolução do canvas (Quantidade de quadrados)
let Xpontos = [2], Ypontos = [2]; //para guardar as coordenadas dos pontos
let counter = 0;
let lastLine

colunas = document.getElementById("input_col");

let Draw = "line_1" //valor inicial do radio Button

//======================================================//

function setup() {
  canvas = createCanvas(Cwidth, Cheight);
  canvas.parent('canvas') //linka o canvas à div no html
  
  tamanho = Cwidth / colunas.value; //define o tamanho dos quadrados
  linhas = Cheight / tamanho; //define a quantidade de linhas a serem desenhadas
  lastLine = Cheight - tamanho*Math.trunc(linhas); //desenhar as colunas até a útima linha, não até o final do canvas
  let i;

  for(i=0; i<=colunas.value; i++)
  {
    
    line(i*tamanho, 0, i*tamanho, Cheight-lastLine)
  }

  for(i=0; i<=linhas; i++) //desenha as linhas no canvas
    line(0, i*tamanho, Cwidth, i*tamanho)
}

function draw() {
  canvas.mousePressed(redirect);
}


//valida o numero de colunas
function redefineCol(){
  counter = 0;
  colunas = document.getElementById("input_col");
  let i;

  canvas.clear();

  tamanho = Cwidth / colunas.value; //define o tamanho dos quadrados
  linhas = Cheight / tamanho; //define a quantidade de linhas a serem desenhadas
  lastLine = Cheight - tamanho*Math.trunc(linhas); //desenhar as colunas até a útima linha, não até o final do canvas

  for(i=0; i<=colunas.value; i++)
  {
    line(i*tamanho, 0, i*tamanho, Cheight-lastLine)
  }

  for(i=0; i<=linhas; i++) //desenha as linhas no canvas
    line(0, i*tamanho, Cwidth, i*tamanho)
}

//value do Radio Button, para o tipo do desenho
function selectedValue(typeDraw) {
  Draw = typeDraw;
  redefineCol();
};

function redirect(){
  if(counter < 2 && mouseY < Cheight-lastLine) 
  {   
    //define qual o quadrado a partir das coordenadas
    Xpontos[counter] = Math.trunc(mouseX / tamanho);
    Ypontos[counter] = Math.trunc(mouseY / tamanho);

    //pinta o quadrado referente à coordenada
    fill('black');
    rect((Xpontos[counter] * tamanho), (Ypontos[counter] * tamanho), tamanho);

    if(counter == 1)
    {
      if(Draw == "line_1")
        drawLine_1();
  
      else if(Draw == "line_2")
        drawLine_2();
      
      else if(Draw == "circle")
        drawCircle();
      
      else
        drawElipse();
    }
    counter++;
  }
};

function drawLine_1(){
  let dy = Ypontos[1] - Ypontos[0]; //y2 - y1
  let dx = Xpontos[1] - Xpontos[0]; //x2 - x1
  let m = dy / dx;
  let x, y = Ypontos[0];

  for(x = Xpontos[0]; x <= Xpontos[1]; x++){
    fill('black');
    rect(x * tamanho, Math.round(y) * tamanho, tamanho);
    y += m;
  }
};

function drawLine_2(){
  let a = Ypontos[1] - Ypontos[0]; //y2 - y1
  let b = Xpontos[0] - Xpontos[1]; //x1 - x2
  let V = 2 * a + b; //valor inicial de V
  let incrE = 2 * a; //mover para E
  let incrNE = 2 * (a + b); // Mover para NE
  let x = Xpontos[0], y = Ypontos[0];
  
  while(x < Xpontos[1]){
    console.log(V);
    if (V <= 0)
      V += incrE //escolhe E
    else{ //escolher NE
      V += incrNE;
      ++y;
    }
    ++x;
    fill('black');
    rect(x * tamanho, y * tamanho, tamanho);
  }
};

function drawCircle(){
  console.log("drawCircle");
};

function drawElipse(){
  console.log("DrawElipse");
};
