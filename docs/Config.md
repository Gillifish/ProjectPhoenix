# Config Structure

Textures

- Format: TextureType	TextureName		TexturePath
- ex. TEXTURE	sprite_1	assets/sprite1.png

Animations

- Format: AnimationType	AnimationTag TextureName FrameCount	Speed Rows Columns StartRow
- ex. Animation IDLE_DOWN player_anims 4 10 4 4 0

Tilemaps

- Format: Tag TextureXCoord TextureYCoord RenderLocationX RenderLocationY CollisionBool
- ex. TILEMAP 2 0 1 2 1

Game

- Format: GameWindow WindowWidth WindowHeight WindowName Framerate
- ex. GameWindow 1200 768 PhoenixEngine 60
- Note: Game config has not been implemented yet.