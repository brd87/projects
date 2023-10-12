using System.Collections.Generic;
using System;
using System.Diagnostics;
using var game = new MGChess.Chess();
game.Run();
namespace MGChess
{
    public class Program
    {
        static void Main(string[] args)
        {
            Chessboard chessboard = new Chessboard();
            //test
            //////////////////////////////////////////////////////////////////////////////////////
            chessboard.DebugDisplay();
            int py = 1;
            int px = 0;
            List<(int, int)> askMoveTest = chessboard.GetMoves(py, px);
            Debug.WriteLine($"For {chessboard.Board[py, px]}");
            if (askMoveTest.Count == 0)
            {
                Debug.WriteLine("No moves aveliable\n");
            }
            else
            {
                Debug.WriteLine($"{askMoveTest.Count} moves aveliable");
                foreach ((int y, int x) in askMoveTest)
                {
                    Debug.Write($"({y}:{x} is:{chessboard.Board[y, x]}), ");
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////
            
        }
    }
}