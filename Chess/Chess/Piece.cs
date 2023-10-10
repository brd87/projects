using System;
using System.Collections.Generic;
using System.Text;

namespace Chess
{
    public class Piece
    {
        int ID;
        int Color; //1 - white, -1 - black
        bool IfMoved = false;

        public Piece(int iniID, int iniColor)
        {
            ID = iniID;
            Color = iniColor;
        }

        public virtual List<(int, int)> AskForMoves(int xPos, int yPos, int[,] board)
        {
            List<(int, int)> moves = new List<(int, int)>();
            moves.Add((-1,-1));
            return moves;
        }

        public void ModifyID(int newID)
        {
            ID = newID;
        }

        public int ReturnID()
        {
            return ID;
        }

        public void ModifyColor(int newColor)
        {
            Color = newColor;
        }

        public int ReturnColor()
        {
            return Color;
        }

        public void ModifyIfMoved(bool newIfMoved)
        {
            IfMoved = newIfMoved;
        }

        public bool ReturnIfMoved()
        {
            return IfMoved;
        }

    }
}
