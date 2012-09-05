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
 * Play : includes functions that implement the basic way the abstract 
 *        game plays either in a serial or a parallel way
 * 
 * */

#include "nim.h"
#include "fourinarow.h"

using namespace std;

int treeNode::ID=0;

/**
	@brief turns an integer to a string
**/
std::string numToString(int num){
	std::stringstream out;
	out << num;
	return out.str();
}

/**
	@brief finds the node with the minimum weight among a node's children
	       and returns that minimum weight
**/
float chooseMin(treeNode * node){
	float min=1000000000.0;
	for(unsigned int i=0;i<node->children.size();i++)
		if(node->children[i]->weight<min && !(node->children[i]->weight>1000) && !(node->children[i]->weight<-1000))
			min=node->children[i]->weight;
			
	return min;
}

/**
	@brief finds the node with the maximum weight among a node's children
	       and returns that maximum weight
**/
float chooseMax(treeNode * node){
	float max=-10000000.0;
	for(unsigned int i=0;i<node->children.size();i++){
		if(node->children[i]->weight>max && !(node->children[i]->weight>1000) && !(node->children[i]->weight<-1000)){
			max=node->children[i]->weight;
		}
	}
	return max;
}
/**
	@brief traverses the tree upside down and applies min-max algorithm
		   and alpha-beta pruning algorithm in order to assign weights
		   to the nodes
**/
void reverseTraversing(treeNode * node,int checkNode){
	#ifdef PRINT
	cout<<"["<<__LINE__<<"] Called reversedTraversing for node : "<<node->id<<"\n";
	#endif
	
	if(node->id==checkNode){
		return;
	}
	
	if(node->parent->children.size()>1){
		if(!node->parent->checkIfAllHaveWeights())
			node->alphaBetaPrunning();
		if(node->parent->checkIfAllHaveWeights()){
			if(!(node->parent->level%2)){
				node->parent->weight=chooseMax(node->parent);
				node->parent->tempWeight=node->parent->weight;
				
				if(node->parent->parent!=NULL)
					if((node->parent->tempWeight<node->parent->parent->tempWeight)){
						node->parent->parent->tempWeight=node->parent->tempWeight;
						#ifdef PRINT
						cout<<"["<<__LINE__<<"]RV MAX : Node : "<<node->parent->parent->id<<" has now tempWeight : "<<node->parent->parent->tempWeight<<"\n";
						#endif
					}
						
				#ifdef PRINT
				cout<<"["<<__LINE__<<"]MAX : Node: "<<node->parent->id<<" has now weight : "<<node->parent->weight<<"\n";
				#endif
			}
			else{
				
				node->parent->weight=chooseMin(node->parent);
				node->parent->tempWeight=node->parent->weight;
				
				if(node->parent->parent!=NULL)
					if((node->parent->tempWeight>node->parent->parent->tempWeight)){
						node->parent->parent->tempWeight=node->parent->tempWeight;
						#ifdef PRINT
						cout<<"["<<__LINE__<<"]RV MAX : Node : "<<node->parent->parent->id<<" has now tempWeight : "<<node->parent->parent->tempWeight<<"\n";
						#endif
					}
					
				#ifdef PRINT
				cout<<"["<<__LINE__<<"]MIN : Node: "<<node->parent->id<<" has now weight : "<<node->parent->weight<<"\n";
				#endif
			}
			
			if(node->parent->parent==NULL){

				return;
			}
			if(node->parent->tempWeight==1000000.0 || node->parent->tempWeight==-1000000.0)
				return;
				
			reverseTraversing(node->parent,checkNode);
		}
		
	}
	else{

		node->parent->weight=node->weight;
		node->parent->tempWeight=node->tempWeight;
		#ifdef PRINT
		cout<<"["<<__LINE__<<"]Parent Node of node : "<<node->id<<" has now weight : "<<node->parent->weight<<"\n";
		cout<<"["<<__LINE__<<"]And tempWeight : "<<node->parent->tempWeight<<"\n";
		#endif
		if(node->parent->parent==NULL){
			return;
		}
		if((node->parent->parent->level%2) && (node->parent->tempWeight<1000) &&(node->parent->tempWeight>-1000) && (node->parent->tempWeight<node->parent->parent->tempWeight)){
			node->parent->parent->tempWeight=node->parent->tempWeight;
			#ifdef PRINT
			cout<<"["<<__LINE__<<"]Parent Node of node : "<<node->parent->id<<" has now tempWeight : "<<node->parent->parent->tempWeight<<"\n";
			#endif
		}
		else if(!(node->parent->parent->level%2) && (node->parent->tempWeight<1000) &&(node->parent->tempWeight>-1000) &&(node->parent->tempWeight>node->parent->parent->tempWeight)){
			node->parent->parent->tempWeight=node->parent->tempWeight;
			#ifdef PRINT
			cout<<"["<<__LINE__<<"]Parent Node of node : "<<node->parent->id<<" has now tempWeight : "<<node->parent->parent->tempWeight<<"\n";
			#endif
		}
		
		reverseTraversing(node->parent,checkNode);
	}
	
}

/**
	@brief initializes the board of the game
**/
void initializeBoard(std::vector<unsigned char> &board,int size){
	for(unsigned int i=0;i<size;i++){
		for(unsigned int j=0;j<size;j++){
			board.push_back(2);
			
		}
	}
	
}

/**
	@brief function for serial algorithm that constructs the tree of game
**/

void play(Game * g,treeNode * qStart,int depth,Tree *t,int serial=1){
	bool found=false;
	int currDepth=qStart->level;
	int startID;
	treeNode * qNext = new treeNode;
	treeNode * qLimit = new treeNode;
	std::vector<std::vector<int> >newBoards;
	std::vector<unsigned char> posBoard;
	
	qLimit=qStart;
	startID=qLimit->id;
	
	if(serial){
		t->freeTree(qStart);
		qStart->deleteChildren();
		#ifdef PRINT
		cout<<"Finished trimming\n";
		#endif 
	}
	qStart->children.clear();
	qStart->isVisited=false; 
	
	
	while(qStart!=NULL){
		found=false;
		treeNode * qNew;
	
		if(!qStart->isVisited){
			qStart->isVisited=true;
			#ifdef PRINT
			cout<<"["<<__LINE__<<"]Possible moves for node : "<<qStart->id<<" are : \n";
			#endif
			g->findMoves(qStart->board,newBoards,qStart->level);
			for(unsigned int i=0;i<newBoards.size();i++){
				qNew = new treeNode(qStart->level+1);
				g->reconstructBoard(newBoards[i],qStart->board,posBoard);
				qNew->board=posBoard;
				qNew->parent=qStart;
				qStart->children.push_back(qNew);
				
				/**------ PRINTS-------**/
				//~ cout<<"Possible board "<<i+1<<"\n";
				//~ g->showBoard(posBoard);
				/**------ PRINTS-------**/
				
				qStart->children[qStart->children.size()-1]->isToBeExpanded=g->quickEvaluate(qStart->board,newBoards[i],qStart->children[qStart->children.size()-1]);

				#ifdef PRINT
				cout<<"["<<__LINE__<<"][Node : "<<qStart->children[qStart->children.size()-1]->id<<"]STATE IS : "<<qStart->children[qStart->children.size()-1]->isToBeExpanded<<"\n";
				if(!qStart->children[qStart->children.size()-1]->isToBeExpanded)
					cout<<"["<<__LINE__<<"] Node : "<<qStart->children[qStart->children.size()-1]->id<<" is a terminal node\n";
					g->showBoard(qStart->children[qStart->children.size()-1]->board);
				#endif
				
				#ifdef GRAPHS
				t->createGraph("tree_node_"+numToString(qStart->id)+".png");
				#endif
			}
			#ifdef PRINT
			cout<<"-------------------------------------\n";
			cout<<"["<<__LINE__<<"]Made "<<newBoards.size()<<" children\n";
			#endif
			newBoards.clear();
		}
		if(qStart->children.size()==0 || !qStart->isToBeExpanded){
				#ifdef PRINT
				cout<<"["<<__LINE__<<"]Node : "<<qStart->id<<" has no children so i need to evaluate him\n";
				#endif
				//~ if(qStart->isToBeExpanded)
					g->evaluateMove(qStart);
				reverseTraversing(qStart,startID);
				qStart->isToBeExpanded=false;
				
				#ifdef GRAPHS
				t->createGraph("tree_node_"+numToString(qStart->id)+"_no_childs.png");
				#endif
		}
		#ifdef PRINT
		cout<<"["<<__LINE__<<"]CurrDepth : "<<currDepth<<"\n";
		cout<<"["<<__LINE__<<"]Depth is : "<<depth<<"\n";
		#endif
		for(unsigned int i=0;i<qStart->children.size();i++){
			#ifdef PRINT
			cout<<"["<<__LINE__<<"]Checking child : "<<qStart->children[i]->id<<" of parent node : "<<qStart->id<<"\n";
			cout<<"["<<__LINE__<<"]Child is visited : "<<qStart->children[i]->isVisited<<"\n";
			cout<<"["<<__LINE__<<"]Child is to be expanded : "<<qStart->children[i]->isToBeExpanded<<"\n";
			cout<<"["<<__LINE__<<"]Child has depth : "<<qStart->level<<"\n";
			#endif
			if(!(qStart->children[i]->isVisited) && (qStart->children[i]->level<currDepth+depth) && (qStart->children[i]->isToBeExpanded)){
				#ifdef PRINT
				cout<<"["<<__LINE__<<"]Setting child  : "<<qStart->children[i]->id<<" as the new qStart\n";
				#endif
				qStart=qStart->children[i];
				found=true;
				break;
			}
			if(!(qStart->children[i]->level<currDepth+depth) && !(qStart->children[i]->isVisited)){
				#ifdef PRINT
				cout<<"["<<__LINE__<<"]Child : "<<qStart->children[i]->id<<" cannot be expanded so i will evaluate it\n";
				#endif
				//~ if(qStart->children[i]->isToBeExpanded)
					g->evaluateMove(qStart->children[i]);
				reverseTraversing(qStart->children[i],startID);
				
				#ifdef GRAPHS
				t->createGraph("tree_node_"+numToString(qStart->id)+"_"+numToString(qStart->children[i]->id)+"_depth_eval.png");
				#endif
			}
		}
		if(found)
			continue;
			
		if(qStart==qLimit && qStart->checkIfAllVisited())
			break;
		
		
		qStart=qStart->parent;
		
		
	}
	
	
}

/**
	@brief thread that extends a node in the tree of game by computing 
	       its children and its children children and so on
**/
void * playThread(void * data){
	#ifdef PRINT
	cout<<"Running thread function\n";
	#endif
	threadInput * nodes;
	treeNode * chosenElement;
	nodes = (threadInput *) data;
	float maxWeight=-1000000.0;
	#ifdef PRINT
	cout<<"Thread has id : "<<nodes -> threadID<<" \n" ;
	#endif
	int id = nodes -> threadID;
	int currDepth = nodes -> ndepth;
	Game * tg = nodes -> ng;
	Tree * tt = nodes -> nt;
	
	#ifdef PRINT
	cout<<"[Thread : "<<id<<"] nodes.size() = "<<nodes->nodes.size()<<"\n";
	
	for(unsigned int i=0;i<nodes->nodes.size();i++)
		cout<<"[Thread : "<<id<<"] element : "<<i<<" has id : "<<nodes->nodes[i]->id<<"\n";
	#endif
	
	for(unsigned int i=0;i<nodes->nodes.size();i++){
		treeNode * el = nodes->nodes[i];
		play(tg,el,currDepth,tt,0);
		if(el->tempWeight>maxWeight){
			maxWeight=el->tempWeight;
			chosenElement=el;
		}
		
	}
	#ifdef PRINT
	cout<<" [Thread : "<<id<<"] has chosen element : "<<chosenElement->id<<"\n";
	#endif
}

/**
	@brief function for parallel algorithm that constructs the tree of game
**/
void playParallel(Game * g,treeNode * qStart,int depth,Tree *t,int numberOfThreads){

	bool found=false;
	int currDepth=qStart->level;
	int startID;
	treeNode * qLimit;
	treeNode * qNew;
	std::vector<std::vector<int> >newBoards;
	std::vector<unsigned char> posBoard;
	
	pthread_t *pthreads;
	pthreads = (pthread_t *)malloc(numberOfThreads*sizeof(pthread_t));
	
	qLimit=qStart;
	startID=qLimit->id;
	
	std::vector<treeNode * >currCheck;
	std::vector<treeNode * >nextCheck;
	
	t->freeTree(qStart);
	qStart->deleteChildren();
	qStart->reinitializeWeights();
	#ifdef PRINT
	cout<<"Finished trimming\n";
	#endif
	qStart->isVisited=false; 
	
	currCheck.push_back(qStart);
	
	while(currCheck.size()<numberOfThreads){
		#ifdef PRINT
		cout<<"CurrCheck has elements :  \n";
		for(unsigned int i=0;i<currCheck.size();i++)
			cout<<" "<<currCheck[i]->id<<" ";
			
		cout<<"\n";
		#endif
		if(currCheck.size()==0)
			break;
		for(unsigned int a=0;a<currCheck.size();a++){
			if(!currCheck[a]->isVisited){
				currCheck[a]->isVisited=true;
				#ifdef PRINT
				cout<<"["<<__LINE__<<"]Possible moves for node : "<<currCheck[a]->id<<" are : \n";
				#endif
				g->findMoves(currCheck[a]->board,newBoards,currCheck[a]->level);
				for(unsigned int i=0;i<newBoards.size();i++){
					qNew = new treeNode(currCheck[a]->level+1);
					g->reconstructBoard(newBoards[i],currCheck[a]->board,posBoard);
					qNew->board=posBoard;
					qNew->parent=currCheck[a];
					currCheck[a]->children.push_back(qNew);
					
					currCheck[a]->children[currCheck[a]->children.size()-1]->isToBeExpanded=g->quickEvaluate(currCheck[a]->board,newBoards[i],currCheck[a]->children[currCheck[a]->children.size()-1]);

					#ifdef PRINT
					cout<<"["<<__LINE__<<"][Node : "<<currCheck[a]->children[currCheck[a]->children.size()-1]->id<<"]STATE IS : "<<currCheck[a]->children[currCheck[a]->children.size()-1]->isToBeExpanded<<"\n";
					if(!currCheck[a]->children[currCheck[a]->children.size()-1]->isToBeExpanded)
						cout<<"["<<__LINE__<<"] Node : "<<currCheck[a]->children[currCheck[a]->children.size()-1]->id<<" is a terminal node\n";
						g->showBoard(currCheck[a]->children[currCheck[a]->children.size()-1]->board);
					#endif
					
					#ifdef GRAPHS
					t->createGraph("tree_node_"+numToString(currCheck[a]->id)+".png");
					#endif
					
					
				}
				#ifdef PRINT
				cout<<"-------------------------------------\n";
				cout<<"["<<__LINE__<<"]Made "<<newBoards.size()<<" children\n";
				#endif
				newBoards.clear();
					
			}
			if(currCheck[a]->children.size()==0 || !currCheck[a]->isToBeExpanded){
				#ifdef PRINT
				cout<<"["<<__LINE__<<"]Node : "<<currCheck[a]->id<<" has no children so i need to evaluate him\n";
				#endif
				//~ if(currCheck[a]->isToBeExpanded)
					g->evaluateMove(currCheck[a]);
				reverseTraversing(currCheck[a],startID);
				currCheck[a]->isToBeExpanded=false;
				
				#ifdef GRAPHS
				t->createGraph("tree_node_"+numToString(currCheck[a]->id)+"_no_childs.png");
				#endif
			}
			
			#ifdef PRINT
			cout<<"["<<__LINE__<<"]CurrDepth : "<<currDepth<<"\n";
			cout<<"["<<__LINE__<<"]Depth is : "<<depth<<"\n";
			#endif
			for(unsigned int i=0;i<currCheck[a]->children.size();i++){
				#ifdef PRINT
				cout<<"["<<__LINE__<<"]Checking child : "<<currCheck[a]->children[i]->id<<" of parent node : "<<currCheck[a]->id<<"\n";
				cout<<"["<<__LINE__<<"]Child is visited : "<<currCheck[a]->children[i]->isVisited<<"\n";
				cout<<"["<<__LINE__<<"]Child is to be expanded : "<<currCheck[a]->children[i]->isToBeExpanded<<"\n";
				cout<<"["<<__LINE__<<"]Child has depth : "<<currCheck[a]->level<<"\n";
				#endif
				if(!(currCheck[a]->children[i]->isVisited) && (currCheck[a]->children[i]->level<currDepth+depth) && (currCheck[a]->children[i]->isToBeExpanded)){
					#ifdef PRINT
					cout<<"["<<__LINE__<<"]Setting child  : "<<currCheck[a]->children[i]->id<<" in NextCheck\n";
					#endif
					nextCheck.push_back(currCheck[a]->children[i]);
					
				}
				if(!(currCheck[a]->children[i]->level<currDepth+depth) && !(currCheck[a]->children[i]->isVisited)){
					#ifdef PRINT
					cout<<"["<<__LINE__<<"]Child : "<<currCheck[a]->children[i]->id<<" cannot be expanded so i will evaluate it\n";
					#endif
					if(currCheck[a]->children[i]->isToBeExpanded)
						g->evaluateMove(currCheck[a]->children[i]);
					reverseTraversing(currCheck[a]->children[i],startID);
					
					#ifdef GRAPHS
					t->createGraph("tree_node_"+numToString(currCheck[a]->id)+"_"+numToString(currCheck[a]->children[i]->id)+"_depth_eval.png");
					#endif
				}
			}
			
		}
		#ifdef PRINT
		cout<<"CurrCheck size is : "<<currCheck.size()<<"\n";
		#endif
		currCheck.swap(nextCheck);
		nextCheck.clear();
		
	}
	
	int it=0;
	int sub=currCheck.size()/numberOfThreads;
	#ifdef PRINT
	cout<<"Initial Children are = "<<currCheck.size()<<"\n";
	#endif
	
	threadInput ** sendNodes;
	sendNodes = new threadInput * [numberOfThreads];
	for(unsigned int i=0;i<numberOfThreads;i++){
		sendNodes[i] = new threadInput;
		sendNodes[i]->ng=g;
		sendNodes[i]->nt=t;
		sendNodes[i]->ndepth=depth;
		sendNodes[i]->nodes.clear();
		if(i==numberOfThreads-1){
			sub=currCheck.size()-it;  
		}
		for(unsigned int j=0;j<sub;j++){
			sendNodes[i]->nodes.push_back(currCheck[it]);
			it++;
		}
		
		sendNodes[i]->threadID=i;
		#ifdef PRINT
		cout<<"Creating thread "<<sendNodes[i]->threadID<<" that has : "<<sendNodes[i]->nodes.size()<<" elements\n";
		#endif
		pthread_create(&pthreads[i],NULL,playThread,(void *)sendNodes[i]);
		
	}
	
	#ifdef PRINT
	cout<<"Waiting for all threads to finish...\n";
	#endif
	for(unsigned int i=0;i<numberOfThreads;i++)
		pthread_join(pthreads[i],NULL);  
	#ifdef PRINT
	cout<<"Threads have finished processing!\n";
	#endif
	
	#ifdef GRAPHS
	t->createGraph("tree_threads_evaluating.png");
	#endif
	//---evaluate rest of the tree until you reach the root
	#ifdef PRINT
	cout<<"--StartID is : "<<startID<<"\n";
	#endif
	for(unsigned int i=0;i<numberOfThreads;i++){
		for(unsigned int j=0;j<sendNodes[i]->nodes.size();j++){
			#ifdef PRINT
			cout<<"Doing reverse traversing for node : "<<sendNodes[i]->nodes[j]->id<<" \n";
			#endif
			reverseTraversing(sendNodes[i]->nodes[j],startID);
		}
	}
	#ifdef GRAPHS
	t->createGraph("tree_total_evaluating.png");
	#endif
	for(unsigned int i=0;i<numberOfThreads;i++)
		delete sendNodes[i];
		
	delete [] sendNodes;
}

/**
	@brief main function of the program
**/

int main(int argc,char **argv){
	
	int choice;
	int depth;
	int size;
	int numofThreads=0;
	
	float meanTime=0;
	int moves=0;
	long meanNodes=0;
	
	std::vector<unsigned char> board;
	
	Game *g;
	Tree *t;
	
	struct timeval msTime;
	
	cout<<"Please choose the game that you wish to play... \n[1 : Nim]\n[2 : 4 in a row]\nGame : ";
	cin>>choice;
	
	/***********GAME OF NIM***********/
	if(choice==1){
		unsigned char startValue;
		int sv;
		cout<<"\nYou chose to play Nim\n";
		cout<<"\nSet start value to play ... ";
		cin>>sv;
		startValue=sv;
		cout<<"\nStart Value is : "<<(int)startValue<<"\n";
		
		t = new Tree(startValue);
		g = new Nim(startValue);
	}
	/***********FOUR IN A ROW***********/
	else if(choice==2){
		int mode;
		cout<<"\nYou chose to play Four in a row\n";
		cout<<"\nSet size of board (AxA) : A=";
		cin>>size;
		cout<<"\nWrite 0 for a serial process or 1 for using threads [0:serial, 1:threads] : ";
		cin>>mode;
		if(mode){
			cout<<"\nInsert the number of Threads you wish to run... Number of threads : ";
			cin>>numofThreads;
		}
		else
			cout<<"\nPlaying serial game..\n";
		
		initializeBoard(board,size);
		t =new Tree(board);
		g=new FourInRow(size);
		
	}
	/***********FOUR IN A ROW***********/
	
	cout<<"\nSelect computer's depth of thinking ... Depth : ";
	cin>>depth;
	cout<<"\n";
	
	treeNode * qStart = t->root;  
	
	cout<<"Initial board : \n";
	g->showBoard(qStart->board);
	
	
	//--------------Play-----------------//
	treeNode * runner=qStart;
	std::vector<int> move(3,0);
	std::vector<unsigned char> tempBoard;
	int counter=0;
	while(runner->isToBeExpanded){
		counter++;
		//~ Construct tree
		
		/**------PLAY--------**/
		gettimeofday(&msTime, NULL);
		double ms1=(double)msTime.tv_sec * 1000 + (double)msTime.tv_usec / 1000 ;
		
		if(numofThreads>0)
			playParallel(g,runner,2*depth,t,numofThreads);
		else
			play(g,runner,2*depth,t);
		
		gettimeofday(&msTime, NULL);
		double ms2=(double)msTime.tv_sec * 1000 + (double)msTime.tv_usec / 1000 ;
		#ifdef EXP
		cout<<"Time : "<<ms2-ms1<<"\n";
		cout<<"Nodes : "<<t->sumAllNodesInTree()<<" \n";
		#endif
		meanTime+=(ms2-ms1);
		meanNodes+=t->sumAllNodesInTree();
		moves++;
		
		/**------PLAY--------**/
		
		if(runner==NULL){
			cout<<"Not Good\n";
			exit(0);
		}
		else{
			if (counter!=1){
				#ifdef PRINT
				cout<<"\nMy minimum profit till now for ["<<runner->id<<"] is "<<runner->weight<<"\n children's weights:";
				for (unsigned k=0;k<runner->parent->children.size();k++)
					cout<<"[id="<<runner->parent->children[k]->id<<" w="<<runner->parent->children[k]->weight<<"] ";
				cout<<"\n";
				#endif
			}
		}
			
		//------------------------------------------------------//
		
		
		int nid=11222237; 
		
		//-------------------------------------------------------//

		//--Computer plays
		runner=runner->getBestMove();
		cout<<"\nComputer has played :\n";
		g->showBoard(runner->board);

		//--Player plays

		if(runner->isToBeExpanded==false){
				cout<<"Game finished! Computer Wins!\n";
				break;
		}
		if(choice==1){
			cout<<"Human, select move [p n1 n2] (p->[0,1,..]): ";
			cin>>move[0]>>move[1]>>move[2];
			cout<<"You played "<<move[0]<<" "<<move[1]<<" "<<move[2]<<"\n";
		}
		else if(choice==2){
			cout<<"Select move [x] : ";
			cin>>move[0];
		}
		
		tempBoard=g->createBoard(move,runner->board);
		
		while(runner->getNextBoard(tempBoard)==NULL){
				cout<<"Wrong move! Try again .. ";
				if(choice==1){
					cout<<"Human, select move [p n1 n2] : ";
					cin>>move[0]>>move[1]>>move[2];
				}
				else if(choice==2){
					cout<<"Select move [x] : ";
					cin>>move[0];
				}
				tempBoard=g->createBoard(move,runner->board);
		}
		runner=runner->getNextBoard(tempBoard);
		cout<<"You have played this ["<<runner->id<<"]:\n";
		g->showBoard(runner->board);
		if(runner->isToBeExpanded==false)
			cout<<"Game finished!You win!\n";
		
	}

	float resTime = (meanTime/moves);
	#ifdef EXP
	cout<<"Total time of Game is : "<<resTime<<" msec\n";
	cout<<"Mean Nodes constructed in Tree of Game are : "<<(meanNodes/moves)<<" \n";
	#endif
	#ifdef GRAPHS
	t->createGraph("final_tree.png");
	#endif
}
