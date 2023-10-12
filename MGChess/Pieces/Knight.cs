using System;
using System.Collections.Generic;
using System.Text;

namespace MGChess.Pieces
{
    public class Knight : Piece
    {
        public Knight(int iniID, int iniColor, int row, int col) : base(iniID, iniColor, row, col)
        {

        }
        public override List<(int, int)> AskForMoves(int yPos, int xPos, int[,] board)
        {
            List<(int, int)> moves = new List<(int, int)>();
            int[,] possibleMoves =
            {
                { 2, 1 }, { 2, -1 }, { -2, 1 }, { -2, -1 }, { 1, 2 }, { 1, -2 }, { -1, 2 }, { -1, -2 }
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
