using System;
using System.Collections.Generic;
using System.Text;

namespace Chess
{
    class Pawn : Piece
    {   
        public Pawn(int iniID, int iniColor) : base(iniID, iniColor)
        {

        }
        public List<(int, int)> AskForMoves(int yPos, int xPos)
        {
            List<(int, int)> moves = new List<(int, int)>();
            int direction = ReturnColor();
            int[,] possibleMoves =
            {
                {direction*2, 0}, {direction, 0}, {direction, 1}, {direction, -1}
            };
            bool first = true;
            for(int i = 0; i < 4; i++)
            {
                if (first)
                {
                    first = false;
                    if (ReturnIfMoved())
                    {
                        continue;
                    }
                }
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
