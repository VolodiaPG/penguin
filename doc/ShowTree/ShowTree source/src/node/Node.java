package node;

import java.util.ArrayList;

public class Node {
	private String pos;
	  private String play;
	  private String winCount;
	  private String visitCount;
	  private Node parent = null;
	  private ArrayList<Node> children;
	  
	  private float posX = 0;
	  private float posY = 0;
	  
	  
	  public Node(String pos, String play,String wc, String vc, Node parent){
	    this.pos = pos;
	    this.play = play;
	    winCount = wc;
	    visitCount = vc;
	    this.parent = parent;
	    children = new ArrayList<Node>();
	  }
	  
	  public void putChild(Node n){
	    children.add(n);
	  }
	  
	  public String getPos(){
	    return pos;
	  }
	  
	  public Node getParent(){
	    return parent;
	  }
	  
	  public void setPosX(float posX){
	    this.posX = posX;
	  }
	  
	  public void setPosY(float posY){
	    this.posY = posY;
	  }
	  
	  public float getPosX() {
		  return posX;
	  }
	  
	  public float getPosY() {
		  return posY;
	  }
	  
	  public int getLeafCount(Node n){
	    int count = 0;
	    if(n.children.size() == 0){
	      return 1;
	    }
	    for(Node child : n.children){
	      count += getLeafCount(child);
	    }
	    return count;
	  }
	  
	  public int getBrotherCount(Node node){
	    if(node.getParent() == null)
	      return 0;
	    return node.parent.children.size();
	  }
	  
	  public int getCousinsCount(int nodeHeight, int treeHeight){
	    Node rootNode = this;
	    while(rootNode.getParent() != null){
	      rootNode = rootNode.getParent();
	    }
	    return getCousinsCount(rootNode, nodeHeight, treeHeight);
	  }
	  
	  public int getCousinsCount(Node node, int nodeHeight, int treeHeight){
	    int count = 0;
	    if(treeHeight - getDepth(node) == nodeHeight){
	      return 1;
	    }
	    for(Node child : node.children){
	      count += getCousinsCount(child, nodeHeight, treeHeight);
	    }
	    return count;
	  }
	  
	  public int getDepth(Node n){
	    int count = 0;
	    while(n.getParent() != null){
	      n = n.getParent();
	      count ++;
	    }
	    return count;
	  }
	  
	  public int getTreeHeight(Node n){
	    if(n.children.size() == 0){
	      return 1;
	    }
	    int maxSize = 0;
	    for(int i = 0; i < n.children.size(); i++){
	      int h = 1 + getTreeHeight(n.children.get(i));
	      if(h > maxSize){
	        maxSize = h;
	      }
	    }
	    return maxSize;
	  }
	  
	  public ArrayList<Node> getChildren(){
	    return children;
	  }
	  
	  public String toString(){
	    return pos + "," + play + "," + winCount + "," + visitCount;
	  }
	  
	  public String getPlay() {
		  return play;
	  }
	  
	  public String getWinCount() {
		  return winCount;
	  }
	  
	  public String getVisitCount() {
		  return visitCount;
	  }
}
