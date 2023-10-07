using System;
using System.Collections.Generic;
using System.Text;

namespace Chessboard
{
    class Chessboard
    {
        int[,] Board = new int[8,8]; //[y,x]
        List<Piece.Piece> whitePieces = new List<Piece.Piece>();
        List<Piece.Piece> blackPieces = new List<Piece.Piece>();
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
                    Board[pawnRow, i] = randomID;
                    whitePieces.Add(new Pawn.Pawn(randomID, color));
                }

                randomID = random.Next(1, 1000);
                Board[figuresRow, 0] = randomID;
                whitePieces.Add(new Rook.Rook(randomID, color));
                randomID = random.Next(1, 1000);
                Board[figuresRow, 7] = randomID;
                whitePieces.Add(new Rook.Rook(randomID, color));

                randomID = random.Next(1, 1000);
                Board[figuresRow, 1] = randomID;
                whitePieces.Add(new Knight.Knight(randomID, color));
                randomID = random.Next(1, 1000);
                Board[figuresRow, 6] = randomID;
                whitePieces.Add(new Knight.Knight(randomID, color));

                randomID = random.Next(1, 1000);
                Board[figuresRow, 2] = randomID;
                whitePieces.Add(new Bishop.Bishop(randomID, color));
                randomID = random.Next(1, 1000);
                Board[figuresRow, 5] = randomID;
                whitePieces.Add(new Bishop.Bishop(randomID, color));
                
                randomID = random.Next(1, 1000);
                Board[figuresRow, q] = randomID;
                whitePieces.Add(new Queen.Queen(randomID, color));
                randomID = random.Next(1, 1000);
                Board[figuresRow, k] = randomID;
                whitePieces.Add(new King.King(randomID, color));

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
