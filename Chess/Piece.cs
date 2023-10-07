using System;
using System.Collections.Generic;
using System.Text;

namespace Chess
{
    class Piece
    {
        int ID;
        int Color; //1 - white, -1 - black
        bool IfMoved = false;

        public Piece(int iniID, int iniColor)
        {
            ID = iniID;
            Color = iniColor;
        }

        public List<(int, int)> AskForMoves(int xPos, int yPos)
        {
            List<(int, int)> moves = new List<(int, int)>();
            moves.Add((-1,-1));
            return moves;
        }

        protected void ModifyID(int newID)
        {
            ID = newID;
        }

        protected int ReturnID()
        {
            return ID;
        }

        protected void ModifyColor(int newColor)
        {
            Color = newColor;
        }

        protected int ReturnColor()
        {
            return Color;
        }

        protected void ModifyIfMoved(bool newIfMoved)
        {
            IfMoved = newIfMoved;
        }

        protected bool ReturnIfMoved()
        {
            return IfMoved;
        }

    }
}
