using System;
using System.Collections.Generic;
using System.Text;

namespace Chessboard
{
    class Chessboard
    {
        int[,] Board = new int[8,8]; //[y,x]
        List<List<Piece.Piece>> Pieces = new List<List<Piece.Piece>>();
        int White = 16;
        int Black = 16;

        public Chessboard()
        {
            int p = 0;
            int gr = 10000;
            int figuresRow = 0;
            int pawnRow = 1;
            int color = 1;
            int q = 3;
            int k = 4;
            Random random = new Random();
            int randomID;
            for (int faction = 0; faction < 2; faction++)
            {
                List<Piece.Piece> group = new List<Piece.Piece>();
                for (int i=0; i < 8; i++)
                {
                    randomID = random.Next(1, 1000) + gr;
                    Board[pawnRow, i] = randomID;
                    group.Add(new Pawn.Pawn(randomID, color));
                }

                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, 0] = randomID;
                group.Add(new Rook.Rook(randomID, color));
                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, 7] = randomID;
                group.Add(new Rook.Rook(randomID, color));

                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, 1] = randomID;
                group.Add(new Knight.Knight(randomID, color));
                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, 6] = randomID;
                group.Add(new Knight.Knight(randomID, color));

                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, 2] = randomID;
                group.Add(new Bishop.Bishop(randomID, color));
                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, 5] = randomID;
                group.Add(new Bishop.Bishop(randomID, color));
                
                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, q] = randomID;
                group.Add(new Queen.Queen(randomID, color));
                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, k] = randomID;
                group.Add(new King.King(randomID, color));

                Pieces.Add(group);
                gr = 20000;
                figuresRow = 7;
                pawnRow = 6;
                color = -1;
                q = 4;
                k = 3;
            }
        }

        int[] GetLocation(int id)
        {
            int[] location = new int[2];
            for (int side = 0; side < 2; side++)
            {
                for (int p = 0; p < Pieces[side].Count; p++)
                {
                    if (Pieces[side][p].ReturnID() == id)
                    {
                        location[0] = side;
                        location[1] = p;
                        return location;
                    }
                }
            }
            location[0] = -1;
            location[1] = -1;
            return location;
        }

        List<(int, int)> GetMoves(int y, int x)
        {
            int id = Board[y, x];
            int[] l = GetLocation(id);
            return Pieces[l[0]][l[1]].AskForMoves(y, x, Board);
        }

        void ConsoleDisplay()
        {
            Console.WriteLine(Board);
            Console.WriteLine("Hello Chess!");
            Console.WriteLine($"White Pieces: {White} | Black Pieces: {Black}\n");
            for (int row = 0; row < 8; row++)
            {
                for (int cell = 0; cell < 8; cell++)
                {
                    Console.Write($"{Board[row, cell]}\t");
                }
                Console.WriteLine("\n");
            }
        }

        static void Main(string[] args)
        {
            Chessboard chessboard = new Chessboard();
            //test
            //////////////////////////////////////////////////////////////////////////////////////
            chessboard.ConsoleDisplay();
            int py = 6;
            int px = 3;
            List<(int, int)> askMoveTest = chessboard.GetMoves(py, px);
            Console.WriteLine($"For {chessboard.Board[py, px]}");
            if (askMoveTest.Count == 0)
            {
                Console.WriteLine("No moves aveliable\n");
            }
            else
            {
                Console.WriteLine($"{askMoveTest.Count} moves aveliable");
                foreach ((int y, int x) in askMoveTest)
                {
                    Console.Write($"({y}:{x} is:{chessboard.Board[y, x]}), ");
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////
        }
    }
}
