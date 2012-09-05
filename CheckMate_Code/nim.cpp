/**                                                                     **
 *  Copyright by Aikaterini Iliakopoulou  2012                             *
 *                                                                         *
 *   Author: Aikaterini Iliakopoulou <katerina.iliakopoulou@gmail.com>     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,  *
 *   MA 02110-1301, USA.                                                                                                     *
 *                                                                       *
 */                                                                       

/**
 * nim : includes functions that implement the way game of Nim
 *              is played
 * 
 * */



#include "nim.h"

using namespace std;

/**
	@brief constructor
**/
Nim::Nim(unsigned char a){
	root=a;
	#ifdef PRINT
	std::cout<<"Root is : "<<(int)root<<"\n";
	#endif
}

/**
	@brief evaluates a node by the board that it represents in the tree 
	       according to the rules of Nim
**/
void Nim::evaluateMove(treeNode * node){
	#ifdef PRINT
	std::cout<<"Going to evaluate node : "<<node->id<<"\n";
	#endif
	if(!(node->level%2)){
		node->weight=0;
		node->tempWeight=node->weight;
		if(node->parent!=NULL)
			if((node->tempWeight<node->parent->tempWeight)){
				node->parent->tempWeight=node->tempWeight;
				#ifdef PRINT
				std::cout<<"[NIM : "<<__LINE__<<"] Parent node : "<<node->parent->id<<" has now tempWeight : "<<node->parent->tempWeight<<"\n";
				#endif
			}
	}
	else{
		node->weight=1;
		node->tempWeight=node->weight;
		if(node->parent!=NULL)
			if((node->tempWeight>node->parent->tempWeight)){
				node->parent->tempWeight=node->tempWeight;
				#ifdef PRINT
				std::cout<<"[NIM : "<<__LINE__<<"] Parent node : "<<node->parent->id<<" has now tempWeight : "<<node->parent->tempWeight<<"\n";
				#endif
			}
	}
	
}

/**
	@brief adds a new move in the board of the game
**/
void Nim::reconstructBoard(std::vector<int> &curMoves,std::vector<unsigned char> &board,std::vector<unsigned char> &posBoard){
	
	posBoard=board;
	
	int x=curMoves[0];
	int y=curMoves[1];
	int z=curMoves[2];
	posBoard.insert(posBoard.begin()+x+1,y);
	posBoard.insert(posBoard.begin()+x+2,z);
	
	posBoard.erase(posBoard.begin()+x);
	
	
}

/**
	@brief Given a known board find all possible moves within one step 
	       in the game
**/
void Nim::findMoves(std::vector<unsigned char> &board,std::vector<std::vector<int> > &posBoards,int turn){
	
	int res;
	int elID;
	std::vector<int>oneMove;
	
	posBoards.clear();
	
	for(unsigned int i=0;i<board.size();i++){
		#ifdef PRINT
		std::cout<<"For element : "<<(int)board[i]<<" res is : ";
		#endif 
		res=board[i]/2;
		#ifdef PRINT
		std::cout<<res<<"\n";
		#endif
		if(res<1 || board[i]==2)
				continue;
			
		if(!(board[i]%2))
			res--;
			
		for(unsigned int j=1;j<=res;j++){
			
			oneMove.clear();
			
			
			oneMove.push_back(i);
			oneMove.push_back(j);
			oneMove.push_back((int)board[i]-j);
			#ifdef PRINT
			std::cout<<"New move has elements : ";
			for(unsigned int k=0;k<oneMove.size();k++)
				std::cout<<(int)oneMove[k]<<" ";
				
			std::cout<<"\n\n";
			#endif
			posBoards.push_back(oneMove);
		}		
	}
}

/**
	@brief is not used in the game of Nim
**/
bool Nim::quickEvaluate(std::vector<unsigned char> &board,std::vector<int> move,treeNode * node){
	
	return true;
	
} 


/**
	@brief prints the board
**/
void Nim::showBoard(std::vector<unsigned char> b){
	int s=b.size();
	cout<<"\n\n╔";
	for(int i=0;i<s-1;i++)
		cout<<"══╦";
	cout<<"══╗\n║";
	for(int i=0;i<s;i++){
		if(b[i]<10)
			cout<<" "<<(int)b[i]<<"║";
		else
			cout<<(int)b[i]<<"║";
	}
	cout<<"\n╚";
	for(int i=0;i<s-1;i++)
		cout<<"══╩";
	cout<<"══╝\n";
	cout<<"\n\n";	
}

/**
	@brief computes the board given a known move
**/
std::vector<unsigned char> Nim::createBoard(std::vector<int> move,std::vector<unsigned char> board){
	
	std::vector<unsigned char> newboard;
	if((unsigned int)move[0]>=board.size())
		return newboard;
	if (move[1]>move[2]){
		int t=move[1];
		move[1]=move[2];
		move[2]=t;
	}
	if (move[1]==move[2])
		return newboard;
	reconstructBoard(move,board,newboard);
	return newboard;
}


std::string Nim::getBoard(std::vector<unsigned char> b){
		return std::string("");
}
