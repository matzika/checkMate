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
 * tree : includes all functions that construct and edit the tree of game
 * 
 * */



#include "tree.h"

using namespace std;



std::string getRandomColor(){
	std::string color="#";
	for(unsigned int i=0;i<6;i++){
		char c=rand()%16;
		switch(c){
			case 0: color+='0'; break;
			case 1: color+='1'; break;	
			case 2: color+='2'; break;	
			case 3: color+='3'; break;	
			case 4: color+='4'; break;	
			case 5: color+='5'; break;	
			case 6: color+='6'; break;	
			case 7: color+='7'; break;	
			case 8: color+='8'; break;	
			case 9: color+='9'; break;	
			case 10: color+='a'; break;	
			case 11: color+='b'; break;	
			case 12: color+='c'; break;	
			case 13: color+='d'; break;	
			case 14: color+='e'; break;	
			case 15: color+='f'; break;	
		}
	}
	return color;
}



/**
	@brief constructor of class treeNode
**/
treeNode::treeNode(int level){
	
	this->level=level;
	weight=100000000.0;
	if(level%2)
		tempWeight=1000000.0;
	else
		tempWeight=-1000000.0;
	isVisited=false; 
	isChecked=false;
	isToBeExpanded=true;
	id=ID; 
	ID++;
	
}


/**
	@brief returns a node given its id in the tree
**/
treeNode * treeNode::returnNodeWithId(int id){
	treeNode *t;
	for(unsigned int i=0;i<children.size();i++){
		if(children[i]->id==id)
			return children[i];
		else{
			t=children[i]->returnNodeWithId(id);
			if(t!=NULL)
				return t;
		}
	}
	return NULL;
}



/**
	@brief finds the node in the tree that has not been checked yet
	       by the algorithm in order to be extended
**/
treeNode * treeNode::findLeftmostEmpty(void){
	treeNode *runner;
	#ifdef PRINT
	std::cout<<"Node : "<<this->id<<" and has  :"<<children.size()<<" children \n";
	#endif
	for(unsigned int i=0;i<children.size();i++){
		#ifdef PRINT
		std::cout<<"Node : "<<children[i]->id<<"\n";
		#endif
		if(children[i]->weight>1000000.0){
			#ifdef PRINT
			std::cout<<"Node "<<children[i]->id<<" has unchanged weight :\n";
			#endif
			if(!children[i]->isVisited && !children[i]->isChecked){
				#ifdef PRINT
				std::cout<<"Node "<<children[i]->id<<" is not visited\n"; 
				#endif
				children[i]->isChecked=true;
				return children[i];
			}
			
			runner=children[i]->findLeftmostEmpty();
			if(runner!=NULL){
				#ifdef PRINT
				std::cout<<"Node :"<<runner->id<<" is checked\n";
				#endif
				return runner; 
			}
		}
	}
	return NULL;
}


/**
	@brief finds the next node in the same level that is to be expanded
**/
treeNode * treeNode::findNextLeftChild(void){
	treeNode * runner;
	
	for(unsigned int i=0;i<children.size();i++){
		#ifdef PRINT
		cout<<"Examining child : "<<children[i]->id<<"\n";
		#endif
		if(!children[i]->isVisited){
				#ifdef PRINT
				cout<<"It is a node to expand!\n";
				#endif
				return children[i];
		}
		
		runner=children[i]->findNextLeftChild();
		if(runner!=NULL){
			return runner; 
		}
	}
	#ifdef PRINT
	cout<<"No node found\n";
	#endif
	return NULL;
}


/**
	@brief checks if all nodes have been assigned weights
**/
bool treeNode::checkIfAllHaveWeights(void){
	
	for(unsigned int i=0;i<children.size();i++){
		if(children[i]->weight>10000)
			return false;
			
	}
	return true;
}


/**
	@brief finds the node in the tree that corresponds to a certain move
**/
treeNode * treeNode::getNextBoard(std::vector<unsigned char> board){
	int index=-1;
	bool found;
	for(unsigned int i=0;i<children.size();i++){
		found=true;
		for(unsigned int j=0;j<children[i]->board.size();j++){
			if(children[i]->board[j]!=board[j]){
				found=false;
				break;
			}	
		}
		if(!found) continue;
		index=i;
	}
			
			
	if(index==-1)
		return NULL;
	
	return children[index];
	
}


/**
	@brief finds the node that constitutes the best move for computer 
	       to play according to the weights of the nodes in current
	       level
**/
treeNode * treeNode::getBestMove(void){
	int max=-100000;
	int index=-1;
	#ifdef PRINT
	cout<<"Choosing best move for node : "<<id<<"\nChildren";
	
	for (unsigned k=0;k<children.size();k++)
		cout<<"[id="<<children[k]->id<<" w="<<children[k]->weight<<"] ";
	cout<<"\n";
	#endif
	for(unsigned int i=0;i<children.size();i++){
		if(children[i]->weight<1000 && children[i]->weight>-1000 && children[i]->weight > max){
			#ifdef PRINT
			cout<<"Child : "<<children[i]->id<<" has weight : "<<children[i]->weight<<"\n";
			cout<<"---max is : "<<max<<"\n";
			#endif
			max=children[i]->weight;
			#ifdef PRINT
			cout<<"---now max is : "<<max<<"\n";
			#endif
			index=i;
		}
	}
	if(index==-1)
		return NULL;
		
	return children[index];
}


/**
	@brief checks if all children of a node are checked by the algorithm
	       of expansion
**/
bool treeNode::checkIfAllVisited(void){
	for(unsigned int i=0;i<this->children.size();i++){
		#ifdef PRINT
		std::cout<<"Checking node : "<<this->children[i]->id<<"if visited\n";
		#endif
		if(!this->children[i]->isVisited || this->children[i]->weight>1000000.0){
			#ifdef PRINT
			std::cout<<"Node : "<<this->children[i]->id<<" is not visited!!\n";
			#endif
			return false;
		}
	}
			
	return true;
	
}


/**
	@brief initializes the weights of the nodes in the tree
**/
void treeNode::reinitializeWeights(void){
	isVisited=false;
	weight=100000000.0;
	if(level%2)
		tempWeight=1000000.0;
	else
		tempWeight=-1000000.0;
		
	for(unsigned int i=0;i<children.size();i++)
		children[i]->reinitializeWeights();
	
	
}


/**
	@brief deletes children of a node in the tree
**/
void treeNode::deleteChildren(){
	
	if(this->parent==NULL)
		return;
		
	treeNode *runner;
	runner=this;
	
	
	while(runner->children.size()>0)	
		runner=runner->children[0];
	
	
	
	while(this->children.size()>0){
		if (runner->children.size()==(0)){
			runner=runner->parent;
			#ifdef PRINT
			cout<<"Goint to delete node with id : "<<runner->children[0]->id<<" \n";
			#endif
			delete runner->children[0];
			runner->children.erase(runner->children.begin());
		}
		else{
			runner=runner->children[0];
			
		}
	}

}



/**
	@brief implements alpha beta pruning algorithm
**/
void treeNode::alphaBetaPrunning(){
	treeNode * q = new treeNode;
	q=this;
	bool eliminate=false;
	
	if(q==NULL)
		return;
	#ifdef PRINT
	cout<<"------------PRUNING------------\n";
	#endif
	while(q->parent != NULL){
		if(!(q->parent->level%2) && q->parent->tempWeight>-1000 && q->tempWeight<q->parent->tempWeight){
			#ifdef PRINT
			std::cout<<"Node : "<<q->id<<" has tempWeight : "<<q->tempWeight<<"\n";
			std::cout<<"His father ,node : "<<q->parent->id<<" has tempWeight : "<<q->parent->tempWeight<<"\n";
			std::cout<<"Level of father is MAX\n";
			#endif
			eliminate=true;
			break;
		}
		else if((q->parent->level%2) && q->parent->tempWeight<1000 && q->tempWeight>q->parent->tempWeight){
			#ifdef PRINT
			std::cout<<"Node : "<<q->id<<" has tempWeight : "<<q->tempWeight<<"\n";
			std::cout<<"His father ,node : "<<q->parent->id<<" has tempWeight : "<<q->parent->tempWeight<<"\n";
			std::cout<<"Level of father is MIN\n";
			#endif
			eliminate=true;
			break;
		}
		q=q->parent;
	}
	if(eliminate){
		#ifdef PRINT
		std::cout<<"Node for elimination is : "<<q->id<<"\n";
		#endif
		for(unsigned int i=0;i<q->children.size();i++){
			if((q->children[i]->tempWeight < -1000) || (q->children[i]->tempWeight > 1000)){
				#ifdef PRINT
				std::cout<<"FOUND EXTRA NODE : NODE %"<<q->children[i]->id<<" - ELIMINATE IT\n";
				#endif
				q->children[i]->isVisited=true;
				q->children[i]->weight=-1000000;
				//this->children.erase(this->children.begin()+i);
				//this->children[i]->isVisited=true;
				//i--;
			}
		}
		#ifdef PRINT
		std::cout<<"Now node : "<<q->id<<"has "<<q->children.size()<<" children \n";
		#endif
	}
	
	
}


/**
	@brief returns the elements of node in the tree as strings
**/
std::string treeNode::getStringElements(void){
	std::string s="";
	std::stringstream out2;
	out2 << id;
	s+=out2.str()+" : ";
	if(level%2)
		s+=" min ";
	else
		s+=" Max ";
	
	s+="\\n";
	
	
	
	//------------------------------------------------//
	
	int b=sqrt(board.size());
	for (unsigned int i=0;i<board.size();i++){
		if(i%b==0)
			s+="\\n";
		std::stringstream out;

		out << (int)board[i];
		s+=out.str();
		if(i!=(board.size()-1))
			s+=" ";
	}
	s+="\\n w=";
	std::stringstream out3;
	out3 << weight;
	s+=out3.str();
	s+=" , tw=";
	std::stringstream out4;
	out4<< tempWeight;
	s+=out4.str();
	if(isVisited)
		s+=" V";
	s+="";
	return s;
}


/**
	@brief function is used for drawing the tree 
**/
void treeNode::fixGraphConnections(Graph &g,int d){
	g.addNode(id,getStringElements());
	
	if(parent!=NULL){
		g.makeNeighbor(parent->id,id);
		
	}
	if(level>=d) return;
	for(unsigned int i=0;i<children.size();i++)
		children[i]->fixGraphConnections(g,d);
}


/**
	@brief constructor of class Tree
**/
Tree::Tree(unsigned char number){
	root = new treeNode(0);
	root->board.push_back(number);
	root->parent=NULL;
	
}	


/**
	@brief constructor of class Tree
**/
Tree::Tree(std::vector<unsigned char> board){
	root = new treeNode(0);
	root->board=board;
	root->parent=NULL;
	
}

void Tree::fixGraph(Graph &g){
	root->fixGraphConnections(g,100000);
}


/**
	@brief computes the sum of all nodes in the tree
**/
long Tree::sumAllNodesInTree(void){
	
	long sum=1;
	std::vector<treeNode *>currCheck;
	std::vector<treeNode *>nextCheck;
	
	currCheck=root->children;
	sum+=currCheck.size();
	
	while(currCheck.size()>0){
		
		for(unsigned int i=0;i<currCheck.size();i++){
			for(unsigned int j=0;j<currCheck[i]->children.size();j++)
				nextCheck.push_back(currCheck[i]->children[j]);
				
			sum+=currCheck[i]->children.size();
			
		}
		currCheck.swap(nextCheck);
		nextCheck.clear();
	}
	return sum;
}


/**
	@brief prints the tree
**/
void Tree::printTree(){
	
	std::vector<treeNode *>currCheck;
	std::vector<treeNode *>nextCheck;
	
	currCheck.push_back(root);
	std::cout<<"----------PRINTING TREE-----------------\n";
	while(currCheck.size()>0){
		for(unsigned int i=0;i<currCheck.size();i++){
			std::cout<<"Node [L="<<currCheck[i]->level<<"]: "<<currCheck[i]->id<<" has weight : "<<currCheck[i]->weight<<" and tw="<<currCheck[i]->tempWeight<<"\n";
			std::cout<<"Its children are : \n";
			for(unsigned int j=0;j<currCheck[i]->children.size();j++){
				std::cout<<"Node : "<<currCheck[i]->children[j]->id<<"\n";
				nextCheck.push_back(currCheck[i]->children[j]);
			}
		}
		currCheck.swap(nextCheck);
		nextCheck.clear();
	}
	
	
}


treeNode * Tree::returnNodeWithId(int id){
	return root->returnNodeWithId(id);
}


/**
	@brief creates the tree that is to be drawn
**/
void Tree::createGraph(std::string name){
	Graph graphTree;
	fixGraph(graphTree);
	
	graphTree.drawGraph("graphs/"+name,true,false);
}

/**
	@brief creates the tree that is to be drawn
**/
void Tree::createGraph(treeNode *start,std::string name,int d){
	Graph graphTree;
	start->fixGraphConnections(graphTree,d+start->level);
	graphTree.drawGraph("graphs/"+name,true,false);
}

/**
	@brief deletes all children of a node except the one that is given
	       as an argument
**/
void treeNode::destroyChildrenExcept(treeNode * ex){
	treeNode *runner;
	runner=this;
	bool foundPre=false;
	bool found=false;
	while(runner->children.size()>0){
		if(runner->children[0]==ex){
			if(runner->children.size()==1){
				return;
			}
			found=true;
			runner=runner->children[1];
		}
		else
			runner=runner->children[0];
	}
	
	
	while(this->children.size()!=1){
		if (runner->children.size()==(0+found*(runner==this))){
			runner=runner->parent;
			delete runner->children[0+found*(runner==this)];
			runner->children.erase(runner->children.begin()+found*(runner==this));
		}
		else{
			runner=runner->children[0+found*(runner==this)];
			if(runner==ex){
				runner=runner->parent;
				found=true;
			}
		}
	}
}

/**
	@brief deletes the tree of the game
**/

void Tree::freeTree(treeNode *bias){
	if(bias->id==0)
		return;
	
	treeNode * father=bias->parent;
	father->destroyChildrenExcept(bias);
	
	#ifdef GRAPHS
	createGraph("tree_after_.png");
	#endif
	
	treeNode * grandfather=father->parent;
	grandfather->destroyChildrenExcept(father);
	
	#ifdef GRAPHS
	createGraph("tree_after_2.png");
	#endif
}
