
/*"""
ENPM661 Spring 2019: Planning for Autonomous Robots
Project1: 8Puzzle Solver using Breadth First Search

Author(s):
Abhinav Modi (abhi1625@terpmail.umd.edu)
Masters of Engineering in Robotics,
University of Maryland, College Park
"""*/

#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"puzzle.h"
using namespace std;


int main(int argc, char* argv[])
{
    bool err = false;
    if(argc == 1 || argc == 2){
        Solvepuzzle game;
        if(game.bsearch()){
            game.printPath();
        }
        game.txtGen();
        system("./matlab_run.sh");
    }
    else if(argc == 3){
        int len1 = strlen(argv[2]);
        int start[9];
        if(len1!=9){
            printf("Too many or too few elements in start state vector. Execute command again%d",len1);
        }
        else{
            char* st = argv[2];
            for(int i=0;i<9;i++){
                start[i] = st[i] - 48;
            }
            for(int i=0; i<9;i++){
                for(int j=i+1;j<9;j++){
                    if(start[i]==start[j]){
                        err = true;
                        break;
                    }
                }
            }
            if(err){
                printf("Invalid State");
            }
            else{
              Solvable test;
              if(test.isSolvable(start)){
                cout << "Solvable"<<endl;

                Solvepuzzle game(start);
                if(game.bsearch()){
                    game.printPath();
                }
                game.txtGen();
                system("./matlab_run.sh");
              }
              else{
                cout<<"Not Solvable"<<endl;
              }
            }
        }
    }
    else if(argc == 4){
        int len1 = strlen(argv[2]);
        int len2 = strlen(argv[3]);
        int start[9], end[9];
        if(len1!=9){
            printf("Too many or too few elements in start state vector. Execute command again%d",len1);
        }
        else if(len2!=9){
            printf("Too many or too few elements in goal state vector. Execute command again");
        }
        else{
            char* st = argv[2];
            char* en = argv[3];
            for(int i=0;i<9;i++){
                start[i] = st[i] - 48;
                end[i] = en[i] - 48;
            }
            for(int i=0; i<9;i++){
                for(int j=i+1;j<9;j++){
                    if((start[i]==start[j]) || (end[i] == end[j])){
                        err = true;
                        break;
                    }
                }
            }
            if(err){
                printf("Invalid State");
            }
            else{


                Solvepuzzle game(start,end);
                if(game.bsearch()){
                    game.printPath();
                }
                game.txtGen();
                system("./matlab_run.sh");

            }
        }
    }
    return 0;
}
