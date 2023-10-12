using System;
using System.Collections.Generic;
using System.Text;

namespace MGChess.Pieces
{
    public class Pawn : Piece
    {
        public Pawn(int iniID, int iniColor, int row, int col) : base(iniID, iniColor, row, col)
        {

        }
        public override List<(int, int)> AskForMoves(int yPos, int xPos, int[,] board)
        {
            List<(int, int)> moves = new List<(int, int)>();
            int direction = ReturnColor();
            int[,] possibleMoves =
            {
                {direction*2, 0}, {direction, 0}, {direction, 1}, {direction, -1}
            };
            for (int i = 0; i < 4; i++)
            {
                if (i == 0)
                {
                    if (ReturnIfMoved())
                    {
                        continue;
                    }
                }
                int newY = yPos + possibleMoves[i, 0];
                int newX = xPos + possibleMoves[i, 1];
                if (newY >= 0 && newY < 8 && newX >= 0 && newX < 8)
                {
                    if (i == 0 || i == 1)
                    {
                        if (board[newY, newX] == 0)
                        {
                            moves.Add((newY, newX));
                        }
                    }
                    else
                    {
                        if (ReturnColor() == 1 && board[newY, newX] > 20000 || ReturnColor() == -1 && board[newY, newX] < 20000 && board[newY, newX] != 0)
                        {
                            moves.Add((newY, newX));
                        }
                    }
                }
            }
            return moves;
        }
    }
}
