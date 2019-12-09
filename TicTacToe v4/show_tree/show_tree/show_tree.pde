import java.util.regex.Pattern;
import java.util.regex.PatternSyntaxException;
import java.util.regex.Matcher;

import processing.pdf.*;
String[] lines;

float radius = 50;
float hauteur = 50;
float largeur = 200;
float tX = 0;
float tY = 0;
float originX;
float originY;
float startX = 0;
float startY = 0;
boolean record = false;
float scale = 1;

//Pattern pattern = Pattern.compile("(\\d*);(\\d*);(\\d*);(\\d*)");
PGraphicsPDF pdf;
Node node;
Node rootNode;

String url = "../../tree0";

void setup(){
  size(1200, 800);
  lines = loadStrings(url + ".txt");
  pdf = (PGraphicsPDF) createGraphics(width, height, PDF, url + ".pdf");
  for(int i = 0; i < lines.length; i++){
    String[] words = lines[i].split(";");
    String pos = words[0];
    String play = words[1];
    String win = words[2];
    String visit = words[3];
    if(pos.equals("0")){
      rootNode = new Node(pos, play, win, visit, null);
      node = rootNode;
    }else{
      if(Integer.parseInt(pos) == Integer.parseInt(node.getPos()) + 1){
        Node newNode = new Node(pos, play, win, visit, node);
        node.putChild(newNode);
        node = newNode;
      }else{
        int start = Integer.parseInt(node.getPos());
        for(int j = 0; j < start - Integer.parseInt(pos) + 1; j++){
          node = node.getParent();
        }
        Node newNode = new Node(pos, play, win, visit, node);
        node.putChild(newNode);
        node = newNode;
      }
    }
  }
  //largeur = rootNode.getLeafCount(rootNode)*50;
  largeur = 80;
  scale = width/(largeur * rootNode.getLeafCount(rootNode) + 1);
  hauteur = height/(rootNode.getTreeHeight(rootNode) + 1);
 // hauteur = 30;
  //println(rootNode.getDepth(rootNode));
  //println(rootNode.getCousinsCount(1,2));
  //println(rootNode.getLeafCount(rootNode));
  //noLoop();
  tX = width/(largeur * rootNode.getLeafCount(rootNode) + 1);
  tY = height/(rootNode.getTreeHeight(rootNode) + 1);
}

void draw(){
  background(204);
  if(record)
    beginRecord(pdf);
  scale(scale);
  pushMatrix();
  //translate(mouseX*1/scale - originX, mouseY*1/scale - originY);
  translate(tX*1/scale, tY*1/scale);
  rootNode.show();
  if(record){
    endRecord();
    record = false;
    println("yolo");
  }
  popMatrix();
}

void mouseWheel(MouseEvent event) {
  float e = event.getCount();
  if(e > 0)
    scale += 0.05;
  else
    scale -= 0.05;
}
/*
void mouseMoved(){
  tX = mouseX;
  tY = mouseY;
}
/*
void mouseReleased(){
  startX = mouseX;
  startY = mouseY;
}
*/
/*
void mousePressed(){
  originX = 2*mouseX;
  originY = mouseY;
}

void mouseDragged(){
  originX = 2*mouseX;
  originY = mouseY;
}
*/
void mouseReleased(){
  
}

void keyPressed(){
  float moveFactor = 10*1/scale;
  if(keyCode == LEFT){
    tX += moveFactor;
  }else if(keyCode == RIGHT){
    tX -= moveFactor;
  }else if(keyCode == UP){
    tY += moveFactor;
  }else if(keyCode == DOWN){
    tY -= moveFactor;
  }else if(key == 'r'){
    record = true;
  }
}
