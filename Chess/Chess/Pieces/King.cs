﻿using System;
using System.Collections.Generic;
using System.Text;

namespace Chess.Pieces
{
    public class King : Piece
    {
        public King(int iniID, int iniColor) : base(iniID, iniColor)
        {

        }
        public override List<(int, int)> AskForMoves(int yPos, int xPos, int[,] board)
        {
            List<(int, int)> moves = new List<(int, int)>();
            int[,] possibleMoves =
            {
                { 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 }, { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }
            };
            for (int i = 0; i < 8; i++)
            {
                int newY = yPos + possibleMoves[i, 0];
                int newX = xPos + possibleMoves[i, 1];

                if (newY >= 0 && newY < 8 && newX >= 0 && newX < 8)
                {
                    if (ReturnColor() == 1 && board[newY, newX] > 20000 || ReturnColor() == -1 && board[newY, newX] < 20000 && board[newY, newX] != 0 || board[newY, newX] == 0)
                    {
                        moves.Add((newY, newX));
                    }
                }
            }
            return moves;
        }
    }
}
