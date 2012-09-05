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



#include "abstract_game.h"


class Nim : public Game{
	public:
		unsigned char root;
		std::vector<std::vector<int> >moves;
	
		Nim(unsigned char  a);
		virtual void findMoves(std::vector<unsigned char> &board,std::vector<std::vector<int> > &posBoards,int turn=0);
		//virtual void chooseNextMove(std::vector<int> board,treeNode * qStart,int depth);
		virtual void evaluateMove(treeNode * node);
		virtual void reconstructBoard(std::vector<int> &curMoves,std::vector<unsigned char> &board,std::vector<unsigned char> &posBoard);
		virtual void showBoard(std::vector<unsigned char> b);
		virtual bool quickEvaluate(std::vector<unsigned char> &board,std::vector<int> move,treeNode * node); 
		virtual std::vector<unsigned char> createBoard(std::vector<int> move,std::vector<unsigned char> board);
		virtual std::string getBoard(std::vector<unsigned char> b);
};
