#include <iostream>

#include "mcts.hpp"
#include "board.hpp"
using namespace std;

int main()
{
    srand(time(NULL));
    Board b;
    Mcts ai(&b, PLAYER_O);
    int playerPos;
    while(b.status() == IN_PROGRESS)
    {
        system("cls");
        b.show();
        if(b.status() == IN_PROGRESS)
        {
            do
            {
                cin >> playerPos;
                playerPos = playerPos - 1;
            }while(!b.isPosValid(playerPos));
            b.play(playerPos);
        }
        system("cls");
        b.show();
        if(b.status() == IN_PROGRESS)
        {
            int pos = ai.findNextMove();
            b.play(pos);
        }

    }
    system("cls");
    b.show();
    int result = b.getResult();
    switch(result)
    {
    case PLAYER_X:
        cout<<"X WON !"<<endl;
        break;
    case PLAYER_O:
        cout<<"O WON !"<<endl;
        break;
    case FULL:
        cout<<"DRAW !"<<endl;
        break;
    }
    return 0;
}

/*
int main()
{
    srand(time(NULL));
    Board b;
    Node n(&b, PLAYER_X);
    int result = 0;
    n.generateChildren();
    cout<<"-----------------------"<<endl;
    Node * c = n.getChildren()->at(0);
    c->generateChildren();
    cout<<"-----------------------"<<endl;
    Node * c2 = c->getChildren()->at(0);
    c2->generateChildren();
    cout<<"-----------------------"<<endl;
    Node * c3 = c2->getChildren()->at(0);
    c3->generateChildren();
    cout<<"-----------------------"<<endl;
    Node * c4 = c3->getChildren()->at(0);
    c4->generateChildren();

    for(int i = 0; i < 1; i++)
    {
        for(Node *child: *(n.getChildren()))
        {
            result = child->doRandomPlayout();
            cout<<child->getStatus()<<endl;
            cout<<"-----------------------"<<endl;
        }

    }
    return 0;
}
*/
