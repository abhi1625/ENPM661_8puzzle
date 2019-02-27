/*"""
ENPM661 Spring 2019: Planning for Autonomous Robots
Project1: 8Puzzle Solver using Breadth First Search

Author(s):
Abhinav Modi (abhi1625@terpmail.umd.edu)
Masters of Engineering in Robotics,
University of Maryland, College Park
"""*/

#ifndef PUZZLE_H
#define PUZZLE_H
#include<stdio.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<string.h>
using namespace std;

struct node {
    int state[9];
    int id=0;
    int parentid=0;
    int cost=0;
    int posBlank=0;
};
class Solvepuzzle {
    vector<node> Nodes;
    node node_init, Goal_Node;
    int* goal_state;
    vector<int> Path;

    public :

    Solvepuzzle(){
        cout<<1<<"\n";
        int start[9] = {7,0,8,5,3,1,4,2,6};   //Column Wise
        int end[9] = {1, 4, 7, 2, 5, 8, 3, 6, 0};
        for(int i=0; i<9; i++){
            node_init.state[i]=start[i];
        }
        node_init.id = 0;
        node_init.parentid = 0;
        node_init.cost = 0;
        node_init.posBlank = 2;
        Nodes.push_back(node_init);
        for(int i=0; i<9; i++){
            Goal_Node.state[i]=end[i];
        }
        Goal_Node.posBlank = 9;
    }

    Solvepuzzle(int* start){
        int end[9] = {1, 4, 7, 2, 5, 8, 3, 6, 0};
        for(int i=0; i<9; i++){
            node_init.state[i]=start[i];

            if(start[i] == 0){
                node_init.posBlank = i+1;
            }
        }

        node_init.id = 0;
        node_init.parentid = 0;
        node_init.cost = 0;
        Nodes.push_back(node_init);

        for(int i=0; i<9; i++){
            Goal_Node.state[i]=end[i];
            if(end[i] == 0){
                Goal_Node.posBlank = i+1;
            }
        }

        cout<<Nodes.size()<<"\n";
    }

    Solvepuzzle(int* start, int* end){
        for(int i=0; i<9; i++){
            node_init.state[i]=start[i];
            if(start[i] == 0){
                node_init.posBlank = i+1;
            }
        }

        node_init.id = 0;
        node_init.parentid = 0;
        node_init.cost = 0;
        Nodes.push_back(node_init);

        for(int i=0; i<9; i++){
            Goal_Node.state[i]=end[i];
            if(end[i] == 0){
                Goal_Node.posBlank = i+1;
            }
        }
    }

    node moveUp(int currentid){
        node next;
        int c = Nodes[currentid].posBlank;
        for(int i=0; i<9; i++){
            next.state[i]=Nodes[currentid].state[i];
        }
        next.state[c-1] = next.state[c-2];
        next.state[c-2] = 0;
        next.id = Nodes.size();
        next.parentid = currentid;
        next.posBlank = c-1;
        next.cost = Nodes[currentid].cost + 1;
        return next;
    }
    node moveDown(int currentid){
        node next;
        int c = Nodes[currentid].posBlank;
        for(int i=0; i<9; i++){
            next.state[i]=Nodes[currentid].state[i];
        }
        next.state[c-1] = next.state[c];
        next.state[c] = 0;
        next.id = Nodes.size();
        next.parentid = currentid;
        next.posBlank = c+1;
        next.cost = Nodes[currentid].cost + 1;
        return next;
    }
    node moveLeft(int currentid){
        node next;
        int c = Nodes[currentid].posBlank;
        for(int i=0; i<9; i++){
            next.state[i]=Nodes[currentid].state[i];
        }
        next.state[c-1] = next.state[(c-4)];
        next.state[c-4] = 0;
        next.id = Nodes.size();
        next.parentid = currentid;
        next.posBlank = c-3;
        next.cost = Nodes[currentid].cost + 1;
        return next;
    }
    node moveRight(int currentid){
        int c = Nodes[currentid].posBlank;
        node next;
        for(int i=0; i<9; i++){
            next.state[i]=Nodes[currentid].state[i];
        }
        next.state[c-1] = next.state[(c+2)];
        next.state[c+2] = 0;
        next.id = Nodes.size();
        next.parentid = currentid;
        next.posBlank = c+3;
        next.cost = Nodes[currentid].cost + 1;
        return next;
    }
    bool bsearch(){
        bool ret;
        vector<int> parentids;
        vector<int> childids;

        parentids.push_back(Nodes[0].id);

        bool flag = true;
        while(flag){
            for(int i=0; i<parentids.size(); i++){
                int m,n;
                int currentid = parentids[i];
                int c = Nodes[parentids[i]].posBlank;
                int p = Nodes[Nodes[parentids[i]].parentid].posBlank;

                if(c%3==0){
                    m = 3;
                    n = c/3;
                }
                else{
                    m = c%3;
                    n = (c/3) + 1;
                }

                if(c==Goal_Node.posBlank){
                    if(checkForGoal(currentid)){
                        Goal_Node.id = currentid;
                        Goal_Node.cost = Nodes[currentid].cost;
                        Goal_Node.parentid = Nodes[currentid].parentid;
                        ret = true;
                        flag = false;
                        break;
                    }
                }
                if((m-1>0) && (c-1!=p)){                           //UP
                    node next = moveUp(currentid);
                    if(checkUnique(next)){

                        childids.push_back(next.id);
                        Nodes.push_back(next);
                    }
                    else{
                    }
                }
                if((m+1<4) && (c+1!=p)){                          //Down
                    node next = moveDown(currentid);
                    if(checkUnique(next)){
                        childids.push_back(next.id);
                        Nodes.push_back(next);
                    }
                }
                if((n-1>0) && (c-3!=p)){                          //Left
                    node next = moveLeft(currentid);
                    if(checkUnique(next)){
                        childids.push_back(next.id);
                        Nodes.push_back(next);
                    }
                }
                if((n+1<4) && (c+3!=p)){                         //Right
                    node next = moveRight(currentid);
                    if(checkUnique(next)){
                        childids.push_back(next.id);
                        Nodes.push_back(next);
                    }
                }
            }
            parentids = childids;

            cout<<"Number of parents"<<"\t"<< childids.size()<<"\t";
            if(parentids.size()==0 || childids.empty()){
                printf("\n Goal can't be reached. Total nodes searched = %lu \n Quitting program \n",Nodes.size());
                ret = false;
                flag = false;
            }
            childids.clear();
            cout<<"Total Nodes searched"<<"\t"<<Nodes.size()<<"\n";
        }
        return ret;
    }

    bool checkForGoal(int currentid){
        for(int i=0; i<9; i++){
            if(Nodes[currentid].state[i] == Goal_Node.state[i]){
                continue;
            }
            else{
                return false;
            }
        }
        return true;
    }

    void nextNode(int parentid,int currentid){
        int c = Nodes[currentid].posBlank;
        int p = Nodes[parentid].posBlank;
        if(c==9){
            if(checkForGoal(currentid)){
                return;
            }
        }
        if((((c-1)%3)!=0) && (c-1!=p)){
            node next = moveUp(currentid);
            Nodes.push_back(next);
            nextNode(currentid, next.id);
        }
        if((((c+1)%3)!=1) && (c+1!=p)){
            node next = moveDown(currentid);
            Nodes.push_back(next);
            nextNode(currentid, next.id);
        }
        if(((c/3)-1!=0) && (c-3!=p)){
            node next = moveLeft(currentid);
            Nodes.push_back(next);
            nextNode(currentid, next.id);
        }
        if(((c/3)+1!=4) && (c+3!=p)){
            node next = moveRight(currentid);
            Nodes.push_back(next);
            nextNode(currentid, next.id);
        }

    }

    void printNode(int nodeid){
        printf("Node State : ");
        for(int i=0; i<9; i++){
            printf(" %d ",Nodes[nodeid].state[i]);
        }
        printf("; Node ID : %d ; Node Parent : %d ; Cost2Come : %d \n",Nodes[nodeid].id,Nodes[nodeid].parentid,Nodes[nodeid].cost);
    }

    bool checkUnique(node child){
        int c = 0;
        for(int i=0;i<Nodes.size();i++){
            c = 0;
            for(int j=0;j<9;j++){
                if(Nodes[i].state[j]==child.state[j]){
                    c+=1;
                    continue;
                }
            }
            if(c == 9){
                return false;
            }
        }
        return true;
    }

    void printPath(){
        int currentid = Goal_Node.id;
        while(true){
            Path.push_back(currentid);
            if(currentid == 0){break;}
            currentid = Nodes[currentid].parentid;
        }
        reverse(Path.begin(), Path.end());
        for(int i=0; i< Path.size();i++){
            printNode(Path[i]);
        }
    }

    void txtGen(){
        ofstream Pathfile ("nodePath.txt");
        ofstream Nodesfile ("Nodes.txt");
        ofstream NodesInfofile ("NodeInfo.txt");
        for(int i=0; i< Path.size();i++){
            for(int j=0; j<9; j++){
                Pathfile << "\t"<<Nodes[Path[i]].state[j];
            }
            Pathfile << "\n";
        }
        for(int i=0; i< Nodes.size();i++){
            for(int j=0; j<9; j++){
                Nodesfile << "\t"<<Nodes[i].state[j];
            }
            Nodesfile << "\n";
            NodesInfofile << "\t"<<Nodes[i].id<<"\t"<<Nodes[i].parentid<<"\t"<<Nodes[i].cost<<"\n";
        }
    }
};

class Solvable{
public:
  bool isSolvable(int* state){
        int invcount = 0;
        int arr[9];
        int j;
        for(int j = 0;j<3;j++){
            for(int i=0; i<3; i++){
                arr[i + j*3] = state[j + i*3];
            }
        }
        for(int i=0;i<9-1;i++){
            for(int j=i+1;j<9;j++){
                if(arr[j] && arr[i] && arr[i]>arr[j]){
                invcount++;
                }
            }
        }
        return (invcount%2 == 0);
    }
};

#endif
