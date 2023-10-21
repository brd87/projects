using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using System.Collections.Generic;

namespace MGChess
{
    public class Piece
    {
        int ID;
        int Color; //1 - white, -1 - black
        bool IfMoved = false;
        int Row;
        int Col;
        int LRow;
        int LCol;

        public Piece(int iniID, int iniColor, int row, int col)
        {
            ID = iniID;
            Color = iniColor;
            Row = row;
            Col = col;

        }

        public virtual List<(int, int)> AskForMoves(int xPos, int yPos, int[,] board)
        {
            List<(int, int)> moves = new List<(int, int)>();
            moves.Add((-1,-1));
            return moves;
        }

        public void Draw(Texture2D texture, SpriteBatch spriteBatch, Vector2 location)
        {
            Texture2D Texture = texture;
            Rectangle sourceRectangle = new Rectangle(32*Col, 32*Row, 32,32);
            Rectangle target = new Rectangle((int)location.X, (int)location.Y, 32, 32);
            spriteBatch.Draw(Texture, target, sourceRectangle, Microsoft.Xna.Framework.Color.White);
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

        public void ModifyLoc((int col, int row) loc)
        {
            LCol = loc.col;
            LRow = loc.row;
        }

        public (int col, int row) ReturnLoc()
        {
            return (LCol, LRow);
        }
        
        
    }
}
