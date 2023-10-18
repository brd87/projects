using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net.NetworkInformation;
using System.Text;
using System.Threading.Tasks;

namespace MGChess
{
    public class Chessboard
    {
        //public int[,] Board { get => new int[8, 8]; }
        public int[,] Board = new int[8, 8]; //[y,x]
        //public List<List<Piece>> Pieces { get; set; } = new List<List<Piece>>();
        public List<List<Piece>> Pieces = new List<List<Piece>>();
        int turn = 1;
        int White = 16;
        int Black = 16;
        int[] Kings = new int[2]; //0-white, 1-black
        bool[] KingsDanger = new bool[2];
        /*
        int[,] Board = new int[8,8]; //[y,x]
        List<List<Piece>> Pieces = new List<List<Piece>>();
        
        */
        public Chessboard()
        {
            int row = 0;
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
                List<Piece> group = new List<Piece>();
                for (int i = 0; i < 8; i++)
                {
                    randomID = random.Next(1, 1000) + gr;
                    Board[pawnRow, i] = randomID;
                    group.Add(new MGChess.Pieces.Pawn(randomID, color, row, 0));
                }

                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, 0] = randomID;
                group.Add(new MGChess.Pieces.Rook(randomID, color, row, 1));
                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, 7] = randomID;
                group.Add(new MGChess.Pieces.Rook(randomID, color, row, 1));

                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, 1] = randomID;
                group.Add(new MGChess.Pieces.Knight(randomID, color, row, 2));
                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, 6] = randomID;
                group.Add(new MGChess.Pieces.Knight(randomID, color, row, 2));

                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, 2] = randomID;
                group.Add(new MGChess.Pieces.Bishop(randomID, color, row, 3));
                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, 5] = randomID;
                group.Add(new MGChess.Pieces.Bishop(randomID, color, row, 3));

                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, q] = randomID;
                group.Add(new MGChess.Pieces.Queen(randomID, color, row, 4));
                randomID = random.Next(1, 1000) + gr;
                Board[figuresRow, k] = randomID;
                group.Add(new MGChess.Pieces.King(randomID, color, row, 5));

                Kings[row] = randomID;
                KingsDanger[row] = false;

                Pieces.Add(group);
                row = 1;
                gr = 20000;
                figuresRow = 7;
                pawnRow = 6;
                color = -1;
                q = 4;
                k = 3;
            }
        }
        
        public void ChcekKings(int color)
        {
            List<(int, int)> moves = new List<(int, int)>();
            for (int side=0; side < 2; side++)
            {
                foreach(Piece piece in Pieces[side])
                {
                    (int col, int row) l = piece.ReturnLoc();
                    moves = GetMoves(l.col, l.row);
                    if(ChcekMoves(moves) == true)
                    {

                        break;
                    }
                }
            }
        }
        
        bool ChcekMoves(List<(int, int)> moves)
        {
            foreach ((int col, int row) in moves)
            {
                if ((Board[col, row] == Kings[0] && turn == -1) || (Board[col, row] == Kings[1] && turn == 1))
                {
                    if (Board[col, row] == Kings[0])
                    {
                        KingsDanger[0] = true;
                        return true;
                    }
                    else
                    {
                        KingsDanger[1] = true;
                        return true;
                    }
                }
            }
            return false;
        }
        

        public List<(int, int)> GetMoves(int y, int x)
        {
            int id = Board[y, x];
            int[] l = GetLocation(id);
            List<(int, int)> moves = new List<(int, int)>();
            if (Pieces[l[0]][l[1]].ReturnColor() == turn)
            {
                moves = Pieces[l[0]][l[1]].AskForMoves(y, x, Board);
            }
            else
            {
                moves.Add((-1, -1));
            }
            return moves;
        }

        public void DoMove((int col, int row) ogLocation, (int col, int row) target)
        {
            int pieceId = Board[ogLocation.col, ogLocation.row];
            int targetId = Board[target.col, target.row];
            if (targetId != 0)
            {
                int[] l = GetLocation(targetId);
                Pieces[l[0]].RemoveAt(l[1]);
            }
            if (pieceId != targetId && pieceId != 0)
            {
                Board[ogLocation.col, ogLocation.row] = 0;
                Board[target.col, target.row] = pieceId;
            }
            int[] sl = GetLocation(pieceId);
            Pieces[sl[0]][sl[1]].ModifyLoc(target);

            turn *= -1;
        }

        public void drawPieces(Texture2D texture, SpriteBatch spriteBatch)
        {
            for (int row = 0; row < 8; row++)
            { 
                for (int col = 0; col < 8; col++)
                {
                    int id = Board[row, col];
                    if (id == 0)
                    {  continue; }
                    Vector2 location = new Vector2(col * 32, row * 32);
                    int[] l = GetLocation(id);
                    Pieces[l[0]][l[1]].Draw(texture, spriteBatch, location);
                }
            }
        }

        public void DebugDisplay()
        {
            Debug.WriteLine(Board);
            Debug.WriteLine("Hello Chess!");
            Debug.WriteLine($"White Pieces: {White} | Black Pieces: {Black}\n");
            for (int row = 0; row < 8; row++)
            {
                for (int cell = 0; cell < 8; cell++)
                {
                    Debug.Write($"{Board[row, cell]}\t");
                }
                Debug.WriteLine("\n");
            }
        }

        private int[] GetLocation(int id)
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
    }
}
