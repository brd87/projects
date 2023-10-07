﻿using System;
using System.Collections.Generic;
using System.Text;

namespace King
{
    class King : Piece.Piece
    {
        public King(int iniID, int iniColor) : base(iniID, iniColor)
        {

        }
        public override List<(int, int)> AskForMoves(int yPos, int xPos)
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
                    moves.Add((newY, newX));
                }
            }
            return moves;
        }
    }
}