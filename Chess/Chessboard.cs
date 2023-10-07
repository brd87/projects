using System;
using System.Collections.Generic;
using System.Text;

namespace Chess
{
    class Chessboard
    {
        int[,] board = new int[8,8]; //[y,x]
        List<Piece> whitePieces = new List<Piece>();
        List<Piece> blackPieces = new List<Piece>();
        int White = 16;
        int Black = 16;

        public Chessboard()
        {
            int figuresRow = 0;
            int pawnRow = 1;
            int color = 1;
            int q = 3;
            int k = 4;
            Random random = new Random();
            int randomID;
            for (int faction = 0; faction < 2; faction++)
            {
                for (int i=0; i < 8; i++)
                {
                    randomID = random.Next(1, 1000);
                    board[pawnRow, i] = randomID;
                    whitePieces.Add(new Pawn(randomID, color));
                }

                randomID = random.Next(1, 1000);
                board[figuresRow, 0] = randomID;
                whitePieces.Add(new Rook(randomID, color));
                randomID = random.Next(1, 1000);
                Board[figuresRow, 7] = randomID;
                whitePieces.Add(new Rook(randomID, color));

                randomID = random.Next(1, 1000);
                board[figuresRow, 1] = randomID;
                whitePieces.Add(new Knight(randomID, color));
                randomID = random.Next(1, 1000);
                board[figuresRow, 6] = randomID;
                whitePieces.Add(new Knight(randomID, color));

                randomID = random.Next(1, 1000);
                board[figuresRow, 2] = randomID;
                whitePieces.Add(new Bishop(randomID, color));
                randomID = random.Next(1, 1000);
                board[figuresRow, 5] = randomID;
                whitePieces.Add(new Bishop(randomID, color));

                randomID = random.Next(1, 1000);
                board[figuresRow, q] = randomID;
                whitePieces.Add(new Queen(randomID, color));
                randomID = random.Next(1, 1000);
                board[figuresRow, k] = randomID;
                whitePieces.Add(new King(randomID, color));

                figuresRow = 7;
                pawnRow = 6;
                color = -1;
                q = 4;
                k = 3;
            }
            
        }

        static void Main(string[] args)
        {
            Chessboard chessboard = new Chessboard();
            Console.WriteLine("Hello World!");
        }
    }
}
