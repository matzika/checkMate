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

#ifndef TREE_H
#define TREE_H

#include "graph.h"

std::string getRandomColor(void);


struct treeNode{
	static int ID;
	int id;
	int level;
	int threadID;
	
	float weight;
	float tempWeight;
	
	bool isVisited;
	bool isChecked;
	bool isToBeExpanded;
	
	std::vector<treeNode *> children;
	std::vector<unsigned char> board;
	
	treeNode *parent;
	
	treeNode(){};
	treeNode(int level);
	
	std::string getStringElements(void);
	
	void fixGraphConnections(Graph &g,int d);
	void alphaBetaPrunning(void);
	void reinitializeWeights(void);
	void deleteChildren(void);
	bool checkIfAllVisited(void);
	bool checkIfAllHaveWeights(void);
	treeNode * findInChildren();
	treeNode * getBestMove(void);
	treeNode * getNextBoard(std::vector<unsigned char> board);
	//void eliminateNodes();  --->TO BE DONE
	treeNode * findNextLeftChild(void);
	treeNode * findLeftmostEmpty(void);
	
	treeNode * returnNodeWithId(int id);
	
	void destroyChildrenExcept(treeNode * ex);
};


struct Tree{
	public:
		treeNode *root;
		
	Tree(){};
	Tree(unsigned char number);
	Tree(std::vector<unsigned char> board);
	void fixGraph(Graph &g);
	void printTree();
	
	void createGraph(std::string name);
	void createGraph(treeNode *start,std::string name,int d);
	
	treeNode * returnNodeWithId(int id);
	
	void freeTree(treeNode *bias);
	
	long sumAllNodesInTree(void);
};

#endif
