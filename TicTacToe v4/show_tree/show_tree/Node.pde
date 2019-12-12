class Node{
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
  
  public void show(){
    int h = getTreeHeight(this);
    show(this, 0, 0, 0);
  }
  
  public void show(Node n,int limg, float oldX, float oldY){
    int nb = getLeafCount(n);
    float x = limg + (largeur * (float)nb)/2.0f;
    float y = oldY + hauteur;
    n.posX = x;
    n.posY = y;
    if(n.parent != null){
      line(n.posX, n.posY, oldX, oldY);
    }
      
     for(int i = 0; i < n.children.size(); i++){
       Node child = n.children.get(i);
       nb = getLeafCount(child);
       show(child, limg, x, y + 20);
       limg += nb * largeur;
     }
     fill(255);
     ellipse(n.posX, n.posY, radius, radius);
     fill(0);
     text(n.play, n.posX - textWidth(n.play)/2, n.posY);
     text(n.winCount + "/" + n.visitCount, n.posX - textWidth(n.winCount + "/" + n.visitCount)/2 + 3, n.posY + 15);
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
    //println(n);
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
}
