using System;
using System.Collections.Generic;
using System.Text;

namespace Bishop
{
    class Bishop : Piece.Piece
    {
        public Bishop(int iniID, int iniColor) : base(iniID, iniColor)
        {

        }
        public override List<(int, int)> AskForMoves(int yPos, int xPos)
        {
            List<(int, int)> moves = new List<(int, int)>();
            int[,] possibleMoves =
            {
                { 1, 1 }, { -1, 1 }, { 1, -1 }, { -1, -1 }
            };
            for (int i = 0; i < 4; i++)
            {
                int newY = yPos + possibleMoves[i, 0];
                int newX = xPos + possibleMoves[i, 1];

                while (newY >= 0 && newY < 8 && newX >= 0 && newX < 8)
                {
                    moves.Add((newY, newX));
                    newY += possibleMoves[i, 0];
                    newX += possibleMoves[i, 1];
                }
            }
            return moves;
        }
    }
}
