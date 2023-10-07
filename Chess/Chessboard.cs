using System;
using System.Collections.Generic;
using System.Text;

namespace Chess
{
    class Chessboard
    {
        int[,] Board = new int[8,8]; //[y,x]
        List<Piece> WhitePieces = new List<Piece>();
        List<Piece> BlackPieces = new List<Piece>();
        int White = 16;
        int Black = 16;

        Chessboard()
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
                    Board[pawnRow, i] = randomID;
                    WhitePieces.Add(new Pawn(randomID, color));
                }

                randomID = random.Next(1, 1000);
                Board[figuresRow, 0] = randomID;
                WhitePieces.Add(new Rook(randomID, color));
                randomID = random.Next(1, 1000);
                Board[figuresRow, 7] = randomID;
                WhitePieces.Add(new Rook(randomID, color));

                randomID = random.Next(1, 1000);
                Board[figuresRow, 1] = randomID;
                WhitePieces.Add(new Knight(randomID, color));
                randomID = random.Next(1, 1000);
                Board[figuresRow, 6] = randomID;
                WhitePieces.Add(new Knight(randomID, color));

                randomID = random.Next(1, 1000);
                Board[figuresRow, 2] = randomID;
                WhitePieces.Add(new Bishop(randomID, color));
                randomID = random.Next(1, 1000);
                Board[figuresRow, 5] = randomID;
                WhitePieces.Add(new Bishop(randomID, color));

                randomID = random.Next(1, 1000);
                Board[figuresRow, q] = randomID;
                WhitePieces.Add(new Queen(randomID, color));
                randomID = random.Next(1, 1000);
                Board[figuresRow, k] = randomID;
                WhitePieces.Add(new King(randomID, color));

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
