#include "mcts.hpp"

Mcts::Mcts(Board * b, int p)
{
    board = b;
    player = p;
}

int Mcts::findNextMove()
{
    Node rootNode(board, player);
    //Node rootNode(board, (player+1)%2);
    int i = 0;
    while(i < 10000 && !rootNode.isVisited()){

        Node * promisingNode = selectPromisingNode(&rootNode);
        if(promisingNode != nullptr){
            //if(promisingNode->getStatus() == IN_PROGRESS && promisingNode->getVisitCount() != 0)
            if(promisingNode->getStatus() == IN_PROGRESS)
            {
                promisingNode->generateChildren();
            }
            Node * nodeToExplore = promisingNode;
            if(nodeToExplore->getChildrenSize() != 0)
            {
                nodeToExplore = promisingNode->getRandomChild();
            }
            int result = nodeToExplore->doRandomPlayout();
            backpropagate(result, nodeToExplore);
        }
        i++;
    }
    printTree(&rootNode, 0);
    int nextMove = 0;
    if(rootNode.isVisited())
    {
        Node * bestChild = rootNode.getBestChildByValue();
        nextMove = bestChild->getMovePosition();
    }else
    {
        Node * bestChild = rootNode.getBestChildByValueBis();
        nextMove = bestChild->getMovePosition();
    }
    return nextMove;
}

Node * Mcts::selectPromisingNode(Node * node)
{
    if(node->getChildrenSize() == 0)
    {
        return node;
    }
    Node * res = node->getBestChildByUct();
    if(res != nullptr)
        return selectPromisingNode(res);
    else
        return res;
}

void Mcts::backpropagate(int result, Node * node)
{
    while(node != nullptr)
    {
        if(node->getStatus() != IN_PROGRESS)
        {
            node->setVisited(true);
        }
        if(node->getChildrenSize() != 0)
        {
            node->setVisited(true);
            for(Node * child : *(node->getChildren()))
            {
                if(!child->isVisited())
                {
                    node->setVisited(false);
                }
            }
        }
        int nodePlayer = node->getPlayer();
        if(result == nodePlayer)
        {
            node->incrWinCount(10);
        }else if(result == FULL)
        {
            node->incrWinCount(1);
        }else if(result == (nodePlayer + 1)%2)
        {
            node->incrWinCount(0);
        }
        //std::cout<<node->getWinCount();
        node->incrVisitCount(1);
        node = node->getParent();
    }
}

void Mcts::showTree(Node * node)
{
    showTree(node, 0);
    std::cout<<std::endl;
}

void Mcts::showTree(Node * node, int pos)
{
    std::cout<<pos;
    for(int i = 0; i < pos; i++)
        std::cout<<"   ";
    if(node->getChildren()->size() == 0)
    {
        std::cout<<"("<<node->getMovePosition()<<","<<node->getWinCount()<<","<<node->getVisitCount()<<")"<<std::endl;
    }else
    {
        std::cout<<"("<<node->getMovePosition()<<","<<node->getWinCount()<<","<<node->getVisitCount()<<")"<<std::endl;
        for(Node * child : *(node->getChildren()))
        {
            showTree(child, pos + 1);
        }
    }
}

void Mcts::printTree(Node * node, int num)
{
   //std::cout<<std::to_string(num)<<std::endl;
    std::ofstream flux("tree"+std::to_string(num)+".txt");
    if(flux)
        printTree(node, 0, &flux);

}

void Mcts::printTree(Node * node, int pos, std::ofstream * flux)
{
    *flux<<pos<<";";
    if(node->getChildren()->size() == 0)
    {
        *flux<<node->getMovePosition()<<";"<<node->getWinCount()<<";"<<node->getVisitCount()<<";"<<node->isVisited()<<std::endl;
    }else
    {
        *flux<<node->getMovePosition()<<";"<<node->getWinCount()<<";"<<node->getVisitCount()<<";"<<node->isVisited()<<";"<<node->getStatus()<<std::endl;
        for(Node * child : *(node->getChildren()))
        {
            printTree(child, pos + 1, flux);
        }
    }
}

