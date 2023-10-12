using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace MGChess
{
    public class Chess : Game
    {
        Chessboard chessboard;
        Texture2D background;
        Texture2D pieceSprites;
        GraphicsDeviceManager _graphics;
        SpriteBatch _spriteBatch;

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

            base.Update(gameTime);
        }

        protected override void Draw(GameTime gameTime)
        {
            GraphicsDevice.Clear(Color.CornflowerBlue);

            // TODO: Add your drawing code here
            _spriteBatch.Begin();

            _spriteBatch.Draw(background, new Rectangle(0, 0, 256, 256), Color.White);
            //chessboard.Pieces[0][1].Draw(pieceSprites, _spriteBatch, new Vector2(0,0));
            chessboard.drawPieces(pieceSprites, _spriteBatch);
            _spriteBatch.End();
            base.Draw(gameTime);
        }
    }
}