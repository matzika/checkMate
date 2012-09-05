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
 * abstract_game : includes class Game that defines the abstract game in
 *                 the program and struct threadInput that includes all
 *                 data needed to transfer to thread function.
 * 
 * */



#ifndef GAME_ABS
#define GAME_ABS

#include "tree.h"


class Game{
	
	public:
		virtual void findMoves(std::vector<unsigned char> &board,std::vector<std::vector<int> > &posBoards,int turn=0)=0;
		//virtual void chooseNextMove(std::vector<int>board,treeNode * qStart,int depth)=0;
		virtual void evaluateMove(treeNode * node)=0;
		virtual void reconstructBoard(std::vector<int> &curMoves,std::vector<unsigned char> &board,std::vector<unsigned char> &posBoard)=0;
		virtual void showBoard(std::vector<unsigned char> b)=0;
		virtual bool quickEvaluate(std::vector<unsigned char> &board,std::vector<int> move,treeNode * node)=0; 
		virtual std::vector<unsigned char> createBoard(std::vector<int> move,std::vector<unsigned char> board)=0;
		virtual std::string getBoard(std::vector<unsigned char> b)=0;
};


struct threadInput{
	
	int threadID;
	int ndepth;
	Game * ng;
	Tree  * nt;
	std::vector<treeNode *>nodes;
	
	threadInput(){};
};


#endif
