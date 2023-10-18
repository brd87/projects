﻿using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using System.Collections.Generic;
using System.Diagnostics;

namespace MGChess
{
    public class Chess : Game
    {
        Chessboard chessboard;
        Texture2D background;
        Texture2D pieceSprites;
        GraphicsDeviceManager _graphics;
        SpriteBatch _spriteBatch;
        List<(int, int)> moves;
        (int col, int row) source;
        public Chess()
        {
            _graphics = new GraphicsDeviceManager(this);
            Content.RootDirectory = "Content";
            IsMouseVisible = true;
        }

        protected override void Initialize()
        {
            // TODO: Add your initialization logic here
            chessboard = new Chessboard();
            _graphics.IsFullScreen = false;
            _graphics.PreferredBackBufferWidth = 256;
            _graphics.PreferredBackBufferHeight = 256;
            _graphics.ApplyChanges();

            moves = new List<(int, int)>
            {
                (-1, -1)
            };
            source = (-1, -1);
            base.Initialize();

        }

        protected override void LoadContent()
        {
            _spriteBatch = new SpriteBatch(GraphicsDevice);

            // TODO: use this.Content to load your game content here
            background = Content.Load<Texture2D>("board");
            pieceSprites = Content.Load<Texture2D>("pieces");
        }

        protected override void Update(GameTime gameTime)
        {
            if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
                Exit();

            // TODO: Add your update logic here
            MouseState state = Mouse.GetState();
            if (state.RightButton == ButtonState.Pressed)
            {
                int col = state.Y / 32;
                int row = state.X / 32;
                if (chessboard.Board[col, row] != 0)
                {
                    //do something with a king if in danger
                    moves = chessboard.GetMoves(col, row);
                    if (moves.Count != 0)
                    {
                        if (moves[0] != (-1,-1))
                        {
                            source.col = col;
                            source.row = row;
                        }
                    }
                }
            }

            if (state.LeftButton == ButtonState.Pressed)
            {
                int col = state.Y / 32;
                int row = state.X / 32;
                foreach ((int mCol, int mRow) in moves)
                {
                    if(mCol == col && mRow == row && source != (-1,-1))
                    {
                        //do something with a king if in danger
                        chessboard.ChcekKings(1);
                        chessboard.ChcekKings(-1);
                        chessboard.DoMove(source, (mCol, mRow));
                        source = (-1,-1);
                        moves.Clear();
                        break;
                    }
                }
            }


            base.Update(gameTime);
        }

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            // TODO: Add your drawing code here
            _spriteBatch.Begin();
            _spriteBatch.Draw(background, new Rectangle(0, 0, 256, 256), Color.White);
            chessboard.drawPieces(pieceSprites, _spriteBatch);
            _spriteBatch.End();
            base.Draw(gameTime);
        }
    }
}