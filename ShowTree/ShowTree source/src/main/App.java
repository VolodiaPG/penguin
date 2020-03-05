package main;

import java.io.File;

import node.Node;
import processing.core.PApplet;


public class App extends PApplet{
	
	private File treeLogPath;
	private float radius = 50;
	private float hauteur = 50;
	private float largeur = 80;
	private String[] lines;
	private Node node;
	private Node rootNode;
	private float scale;
	private float tX;
	private float tY;
	
	
	public void settings() {
		size(1200, 800);
	}
	
	public void setup() {
		selectInput("Select a file to process:", "fileSelected");
	}
	
	public void fileSelected(File selection) {
		  if (selection == null) {
		    println("Window was closed or the user hit cancel.");
		    exit();
		  } else {
		    treeLogPath = selection;
		    lines = loadStrings(treeLogPath.getAbsolutePath());
			generateNodes();
			
		  }
		}
	
	public void draw() {
		if(rootNode != null) {
			beginRecord(SVG, "logSVG.svg");
			background(220);
			scale(scale);
			translate(tX*1/scale, tY*1/scale);
			show(rootNode, 0,0,0);
			endRecord();
			launch("logSVG.svg");
			exit();
		}
	}
	
	public void generateNodes() {
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
		scale = width/(largeur * rootNode.getLeafCount(rootNode) + 1);
		tX = width/(largeur * rootNode.getLeafCount(rootNode) + 1);
		tY = height/(rootNode.getTreeHeight(rootNode) + 1);
	}
	
	public void show(Node n, int limg, float oldX, float oldY){
	    int nb = n.getLeafCount(n);
	    float x = limg + (largeur * (float)nb)/2.0f;
	    float y = oldY + hauteur;
	    n.setPosX(x);
	    n.setPosY(y);
	    if(n.getParent() != null){
	      line(n.getPosX(), n.getPosY(), oldX, oldY);
	    }
	      
	     for(int i = 0; i < n.getChildren().size(); i++){
	       Node child = n.getChildren().get(i);
	       nb = n.getLeafCount(child);
	       show(child, limg, x, y + 20);
	       limg += nb * largeur;
	     }
	     fill(255);
	     ellipse(n.getPosX(), n.getPosY(), radius, radius);
	     fill(0);
	     text(n.getPlay(), n.getPosX() - textWidth(n.getPlay())/2, n.getPosY());
	     text(n.getWinCount() + "/" + n.getVisitCount(), n.getPosX() - textWidth(n.getWinCount() + "/" + n.getVisitCount())/2 + 3, n.getPosY() + 15);
	  }
	
	public static void main(String[] args) {
		PApplet.main("main.App");
	}
}
