namespace Chess
{
    public class Program
    {
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