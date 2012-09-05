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
 * fourinarow : includes functions that implement the way game Four In A Row
 *              is played
 * 
 * */

#include "fourinarow.h"

using namespace std;

/**
	@brief constructor
**/

FourInRow::FourInRow(int size){
	this->size=size;
	gain2=1;
	gain3=50;
	gain4=100;
	
	loss2=1;
	loss3=50;
	loss4=100;
}

/**
	@brief Given a known board find all possible moves within one step 
	       in the game
**/

void FourInRow::findMoves(std::vector<unsigned char> &board,std::vector<std::vector<int> > &posBoards,int turn){
	unsigned int side=sqrt(board.size());
	
	std::vector<int>temp;
	for(unsigned int i=0;i<side;i++){
		for(unsigned int j=0;j<side;j++){
			if(i==0){
				if(board[i*side+j]==2){
					if(turn%2){
						temp.push_back(0);
						temp.push_back(i);
						temp.push_back(j);
						posBoards.push_back(temp);
						temp.clear();
					}
					else{
						temp.push_back(1);
						temp.push_back(i);
						temp.push_back(j);
						posBoards.push_back(temp);
						temp.clear();
					}
				}
			}
			if(board[i*side+j]!=2 && board[(i+1)*side+j]==2){
				if(turn%2){
					temp.push_back(0);
					temp.push_back(i+1);
					temp.push_back(j);
					posBoards.push_back(temp);
					temp.clear();
				}
				else{
					temp.push_back(1);
					temp.push_back(i+1);
					temp.push_back(j);
					posBoards.push_back(temp);
					temp.clear();
				}
			}
		}
	}
	
}

/**
	@brief evaluates a node by the board that it represents in the tree 
	       according to the rules of Four In A Row
**/

void FourInRow::evaluateMove(treeNode * node){
	int ii,jj;
	int twoC=0,threeC=0,twoR=0,threeR=0;
	int count;
	
	#ifdef PRINT
	std::cout<<"I examine node : "<<node->id<<"\n";
	#endif
	/**Check Horizontal**/
	for(int i=0;i<size;i++){
		jj=0;
		count=0;
		while(jj<size){
			if((unsigned int)(i*size+jj)<node->board.size()){
				if(node->board[i*size+jj]==1)
					count++;
				else if (count>0){
					if(count==2){
						twoC++;
						count=0;
					}
					else if(count==3){
						threeC++;
						count=0;
					}
					else
						count=0;
				}
			}
			jj++;
		}
		if(count==2)
			twoC++;
		if(count==3)
			threeC++;
	}
	
	/**Check Vertical**/
	for(int i=0;i<size;i++){
		ii=0;
		count=0;
		while(ii<size){
			if((unsigned int)(ii*size+i)<node->board.size()){
				if(node->board[ii*size+i]==1)
					count++;
				else if (count>0){
					if(count==2){
						twoC++;
						count=0;
					}
					else if(count==3){
						threeC++;
						count=0;
					}
					else
						count=0;
				}
			}
			ii++;
		}
		if(count==2)
			twoC++;
		if(count==3)
			threeC++;
	}
	
	/**Check Diagonal**/
	for(int i=0;i<size;i++){
		ii=0;
		jj=0;
		count=0;
		while(ii<size && jj<size){
			if((unsigned int)((i+ii)*size+jj)<node->board.size()){
				if(node->board[(i+ii)*size+jj]==1)
					count++;
				else if (count>0){
					if(count==2){
						twoC++;
						count=0;
					}
					else if(count==3){
						threeC++;
						count=0;
					}
					else
						count=0;
				}
			}
			ii++;
			jj++;
		}
		if(count==2)
			twoC++;
		if(count==3)
			threeC++;
		
	}
	for(int i=0;i<size;i++){
		ii=0;
		jj=1+i;
		count=0;
		while(ii<size && jj<size){
			if((unsigned int)((i+ii)*size+jj)<node->board.size()){
				if(node->board[(i+ii)*size+jj]==1)
					count++;
				else if (count>0){
					if(count==2){
						twoC++;
						count=0;
					}
					else if(count==3){
						threeC++;
						count=0;
					}
					else
						count=0;
				}
			}
			ii++;
			jj++;
		}
		if(count==2)
			twoC++;
		if(count==3)
			threeC++;
	}
	
	for(int i=0;i<size;i++){
		ii=0;
		jj=size-1;
		count=0;
		while(ii<size && jj>=0){
			if((unsigned int)((i+ii)*size+jj)<node->board.size() && ((i+ii)*size+jj)>0){
				if(node->board[(i+ii)*size+jj]==1)
					count++;
				else if (count>0){
					if(count==2){
						twoC++;
						count=0;
					}
					else if(count==3){
						threeC++;
						count=0;
					}
					else
						count=0;
				}
			}	
			ii++;
			jj--;
		}
		if(count==2)
			twoC++;
		if(count==3)
			threeC++;
	}
	
	for(int i=0;i<size;i++){
		ii=0;
		jj=size-2-i;
		count=0;
		while(ii<size && jj>=0){
			if((unsigned int)(ii*size+jj)<node->board.size() && (ii*size+jj)>0){
				if(node->board[(ii*size+jj)]==1)
					count++;
				else if (count>0){
					if(count==2){
						twoC++;
						count=0;
					}
					else if(count==3){
						threeC++;
						count=0;
					}
					else
						count=0;
				}
			}	
			ii++;
			jj--;
		}
		if(count==2)
			twoC++;
		if(count==3)
			threeC++;
		
	}
	//Checking opponent
	
	/**Check Horizontal**/
	for(int i=0;i<size;i++){
		jj=0;
		count=0;
		while(jj<size){
			if((unsigned int)(i*size+jj)<node->board.size()){
				if(node->board[i*size+jj]==0)
					count++;
				else if (count>0){
					if(count==2){
						twoR++;
						count=0;
					}
					else if(count==3){
						threeR++;
						count=0;
					}
					else
						count=0;
				}
			}
			jj++;
		}
		if(count==2)
			twoR++;
		if(count==3)
			threeR++;
	}
	
	/**Check Vertical**/
	for(int i=0;i<size;i++){
		ii=0;
		count=0;
		while(ii<size){
			if((unsigned int)(ii*size+i)<node->board.size()){
				if(node->board[ii*size+i]==0)
					count++;
				else if (count>0){
					if(count==2){
						twoR++;
						count=0;
					}
					else if(count==3){
						threeR++;
						count=0;
					}
					else
						count=0;
				}
			}
			ii++;
		}
		if(count==2)
			twoR++;
		if(count==3)
			threeR++;
	}
	
	/**Check Diagonal**/
	for(int i=0;i<size;i++){
		ii=0;
		jj=0;
		count=0;
		while(ii<size && jj<size){
			if((unsigned int)((i+ii)*size+jj)<node->board.size()){
				if(node->board[(i+ii)*size+jj]==0)
					count++;
				else if (count>0){
					if(count==2){
						twoR++;
						count=0;
					}
					else if(count==3){
						threeR++;
						count=0;
					}
					else
						count=0;
				}
			}
			ii++;
			jj++;
		}
		if(count==2)
			twoR++;
		if(count==3)
			threeR++;
		
	}
	for(int i=0;i<size;i++){
		ii=0;
		jj=1+i;
		count=0;
		while(ii<size && jj<size){
			if((unsigned int)((i+ii)*size+jj)<node->board.size()){
				if(node->board[(i+ii)*size+jj]==0)
					count++;
				else if (count>0){
					if(count==2){
						twoR++;
						count=0;
					}
					else if(count==3){
						threeR++;
						count=0;
					}
					else
						count=0;
				}
			}
			ii++;
			jj++;
		}
		if(count==2)
			twoR++;
		if(count==3)
			threeR++;
	}
	
	for(int i=0;i<size;i++){
		ii=0;
		jj=size-1;
		count=0;
		while(ii<size && jj>=0){
			if((unsigned int)((i+ii)*size+jj)<node->board.size() && ((i+ii)*size+jj)>0){
				if(node->board[(i+ii)*size+jj]==0)
					count++;
				else if (count>0){
					if(count==2){
						twoR++;
						count=0;
					}
					else if(count==3){
						threeR++;
						count=0;
					}
					else
						count=0;
				}
			}	
			ii++;
			jj--;
		}
		if(count==2)
			twoR++;
		if(count==3)
			threeR++;
	}
	
	for(int i=0;i<size;i++){
		ii=0;
		jj=size-2-i;
		count=0;
		while(ii<size && jj>=0){
			if((unsigned int)(ii*size+jj)<node->board.size() && (ii*size+jj)>0){
				if(node->board[(ii*size+jj)]==0)
					count++;
				else if (count>0){
					if(count==2){
						twoR++;
						count=0;
					}
					else if(count==3){
						threeR++;
						count=0;
					}
					else
						count=0;
				}
			}	
			ii++;
			jj--;
		}
		if(count==2)
			twoR++;
		if(count==3)
			threeR++;
		
	}
	#ifdef PRINT
	std::cout<<"twoC : "<<twoC<<" threeC : "<<threeC<<" twoR : "<<twoR<<" threeR : "<<threeR<<"\n";
	#endif
	node->weight= (twoC*gain2 + threeC*gain3) - (twoR*loss2 + threeR*loss3);
	node->tempWeight=node->weight;
	if(node->parent!=NULL){
		if(!(node->parent->level%2) && (node->tempWeight>node->parent->tempWeight))
			node->parent->tempWeight=node->tempWeight;
		else if((node->parent->level%2) && (node->tempWeight<node->parent->tempWeight))
			node->parent->tempWeight=node->tempWeight;
	}
	#ifdef PRINT	
	std::cout<<"Finally node : "<<node->id<<"has weight : "<<node->weight<<"\n";
	#endif
}

/**
	@brief adds a new move in the board of the game
**/

void FourInRow::reconstructBoard(std::vector<int> &curMoves,std::vector<unsigned char> &board,std::vector<unsigned char> &posBoard){
	
	posBoard=board;
	posBoard[curMoves[1]*size+curMoves[2]]=curMoves[0]; 
	
}

/**
	@brief prints the board
**/
void FourInRow::showBoard(std::vector<unsigned char> b){
	int s=sqrt(b.size());
	cout<<"\n\n╔";
	
	for(int i=0;i<s-1;i++){
		cout<<"═══╦";
	}
	cout<<"═══╗\n";
	for(int i=0;i<s;i++){
		cout<<"║ ";
		for(int j=0;j<s;j++){
			if(b[s*(s-1-i)+j]!=2)
				cout<<(int)b[s*(s-1-i)+j]<<" ║ ";
			else
				cout<<"  ║ ";
		}
		if(i<=(s-2)){
			cout<<"\n╠";
			for(int j=0;j<s-1;j++){
				cout<<"═══╬";
			}
			cout<<"═══╣";
		}
		cout<<"\n";
	}

	cout<<"╚";
	for(int i=0;i<s-1;i++)
		cout<<"═══╩";
	cout<<"═══╝\n";
	for(int i=0;i<s;i++){
		cout<<"  "<<i<<" ";
	}
	cout<<"\n\n";	
}

/**
	@brief prints the board 
**/
std::string FourInRow::getBoard(std::vector<unsigned char> b){
	std::string ret;
	int s=sqrt(b.size());
	ret+="╔";
	
	for(int i=0;i<s-1;i++){
		ret+="═══╦";
	}
	ret+="═══╗\n";
	for(int i=0;i<s;i++){
		ret+="║ ";
		for(int j=0;j<s;j++){
			if(b[s*i+j]!=2)
				ret+=(int)b[s*i+j]+" ║ ";
			else
				ret+="  ║ ";
		}
		if(i<=(s-2)){
			ret+="\n╠";
			for(int j=0;j<s-1;j++){
				ret+="═══╬";
			}
			ret+="═══╣";
		}
		ret+="\n";
	}

	ret+="╚";
	for(int i=0;i<s-1;i++)
		ret+="═══╩";
	ret+="═══╝";
	return ret;
}

/**
	@brief checks if a node in the tree corresponds to a board that has
	       four checkers in a row
**/
bool FourInRow::quickEvaluate(std::vector<unsigned char> &board,std::vector<int> move,treeNode * node){
	unsigned char x=move[1];
	unsigned char y=move[2];
	unsigned char player=move[0];
	
	int ii,jj;
	int gmax=0;
	int count;
	
	#ifdef PRINT
	std::cout<<"I examine node : "<<node->id<<"\n";
	#endif
	/**Check Horizontal**/
	for(int i=0;i<size;i++){
		jj=0;
		count=0;
		while(jj<size){
			if((unsigned int)(i*size+jj)<node->board.size()){
				if(node->board[i*size+jj]==player)
					count++;
				else if (count>0){
					count=0;
				}
				if(count==4){
					gmax++;
					break;
				}
			}
			jj++;
		}
		
	}
	
	/**Check Vertical**/
	for(int i=0;i<size;i++){
		ii=0;
		count=0;
		while(ii<size){
			if((unsigned int)(ii*size+i)<node->board.size()){
				if(node->board[ii*size+i]==player)
					count++;
				else if (count>0){
					count=0;
				}
				if(count==4){
					gmax++;
					break;
				}
			}
			ii++;
		}
		
	}
	
	/**Check Diagonal**/
	for(int i=0;i<size;i++){
		ii=0;
		jj=0;
		count=0;
		while(ii<size && jj<size){
			if((unsigned int)((i+ii)*size+jj)<node->board.size()){
				if(node->board[(i+ii)*size+jj]==player)
					count++;
				else if (count>0){
					count=0;
				}
				if(count==4){
					gmax++;
					break;
				}
			}
			ii++;
			jj++;
		}
		
	}
	for(int i=0;i<size;i++){
		ii=0;
		jj=1+i;
		count=0;
		while(ii<size && jj<size){
			if((unsigned int)((ii)*size+jj)<node->board.size()){
				if(node->board[(ii)*size+jj]==player)
					count++;
				else if (count>0){
					count=0;
				}
				if(count==4){
					gmax++;
					break;
				}
			}
			ii++;
			jj++;
		}
		
	}
	
	for(int i=0;i<size;i++){
		ii=0;
		jj=size-1;
		count=0;
		while(ii<size && jj>=0){
			if((unsigned int)((i+ii)*size+jj)<node->board.size() && ((i+ii)*size+jj)>0){
				if(node->board[(i+ii)*size+jj]==player)
					count++;
				else if (count>0){	
					count=0;
				}
				if(count==4){
					gmax++;
					break;
				}
			}	
			ii++;
			jj--;
		}
		
	}
	
	for(int i=0;i<size;i++){
		ii=0;
		jj=size-2-i;
		count=0;
		while(ii<size && jj>=0){
			if((unsigned int)(ii*size+jj)<node->board.size() && (ii*size+jj)>0){
				if(node->board[(ii*size+jj)]==player)
					count++;
				else if (count>0){
					count=0;
				}
				if(count==4){
					gmax++;
					break;
				}
			}	
			ii++;
			jj--;
		}
		
	}

	
	if(gmax>0){
		
		node->weight=gain4*(move[0]==1) + (-loss4)*(move[0]==0);
		node->tempWeight=node->weight;
		#ifdef PRINT	
		std::cout<<"Node : "<<node->id<<" is a terminal node! He has weight : "<<node->weight<<"\n";
		#endif
		if(node->parent!=NULL){
			if(!(node->parent->level%2) && (node->tempWeight>node->parent->tempWeight)){
				node->parent->tempWeight=node->tempWeight;
				#ifdef PRINT	
				std::cout<<"Node : "<<node->parent->id<<" is the parent of a terminal node! He has tempWeight : "<<node->parent->tempWeight<<"\n";
				#endif
			}
			else if((node->parent->level%2) && (node->tempWeight<node->parent->tempWeight)){
				node->parent->tempWeight=node->tempWeight;
				#ifdef PRINT	
				std::cout<<"Node : "<<node->parent->id<<" is the parent of a terminal node! He has tempWeight : "<<node->parent->tempWeight<<"\n";
				#endif
			}
		}
		return false;
	}
	
	return true;
	
}

/**
	@brief computes the board given a known move
**/
std::vector<unsigned char> FourInRow::createBoard(std::vector<int> move,std::vector<unsigned char> board){
	
	std::vector<int> fullMove;
	std::vector<unsigned char> newboard;
	fullMove.push_back(0);
	fullMove.push_back(0);
	fullMove.push_back(move[0]);
	for(unsigned int i=0;i<size;i++){
		if(board[i*size+move[0]]==2){
			fullMove[1]=i;
			break;
		}
	}
	reconstructBoard(fullMove,board,newboard);
	return newboard;
}
