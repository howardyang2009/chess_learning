#include "raylib-cpp.hpp"
#include <vector>
#include "iostream"

const int screenWidth = 1300;
const int screenHeight = 1000;
const int tileSize = 80;
const int pawnSize = 40;
double prevTime = 0.0; // Variable to store the previous time value
int m=0;
int count = 1;

bool work=false;

int currmove=0;

int loccount=0;

float hoveredTileX = -1.0;
float hoveredTileY = -1.0;

int placecount=0;
int newcount=0;

bool isMouseButtonHeld=false;
bool allow=0;

bool moved=false;

raylib::Vector2 chessBoardOffset{500, 50};

const int lpo=10;
const int bpo=10;

int GetFrameCount(double videoDuration, int framesPerSecond)
{
    return static_cast<int>(videoDuration * framesPerSecond);
}

raylib::Color GetImagePixelColor(raylib::Image& image, int x, int y)
{
    raylib::Color* imageData = static_cast<raylib::Color*>(image.GetData());

    int pixelIndex = (y * image.width) + x;
    raylib::Color pixelColor = imageData[pixelIndex];

    return pixelColor;
}


raylib::Image image = LoadImage("chesspulltab.png");

bool CheckHoverOverImg(raylib::Image& image, raylib::Vector2 position, raylib::Vector2 mousePosition)
{
    // Calculate the image boundaries
    float imageRight = position.x + image.width;
    float imageBottom = position.y + image.height;

    // Check if the mouse position is within the image boundaries
    if (mousePosition.x >= position.x && mousePosition.x < imageRight &&
        mousePosition.y >= position.y && mousePosition.y < imageBottom)
    {
        // Get the pixel color at the mouse position
        raylib::Color pixelColor = GetImagePixelColor(image, static_cast<int>(mousePosition.x - position.x), static_cast<int>(mousePosition.y - position.y));

        // Check if the pixel color's alpha component is greater than 0
        if (pixelColor.a > 0)
        {
            return true; // Mouse is hovering over a non-transparent pixel
        }
    }

    return false; // Mouse is not hovering over the image
}
//12,25,27,34,47,1.29,1.45,2.18,2.50,2.57,3.19, end 3.46

int main()
{ 

    

    raylib::AudioDevice audioDevice;
    static raylib::Sound sound("/Users/stavanmukherjee./Downloads/raylib-master 2/build/raylib-cpp/projects/VSCode/raylib-cpp-starter/src/sprites/16x32 pieces/Movie on 14.06.23 at 13.16 2-1.wav");

    sound.Play();

    double audioDuration = 0.0; // Assuming you have the audio duration in seconds
    int framesPerSecond = 60;
    int frameCount = GetFrameCount(audioDuration, framesPerSecond);

        int currentFrame = 0;

    const int pawn = 0;
    const int knight = 1;
    const int bishop = 2;
    const int rook = 3;
    const int queen = 4;
    const int king = 5;

       const int numMoves = 18;
    Vector3 whiteMovesFrom[numMoves/2];
    Vector3 whiteMovesTo[numMoves/2];
    Vector3 blackMovesFrom[numMoves/2];
    Vector3 blackMovesTo[numMoves/2];

// Set the mirrored moves for the chess game
whiteMovesFrom[0] = {4, 6, 0};  // From: (4, 6), Piece: Pawn
whiteMovesTo[0] = {4, 4, 0};    // To: (4, 4)
blackMovesFrom[0] = {4, 1, 0};  // From: (4, 1), Piece: Pawn
blackMovesTo[0] = {4, 3, 0};    // To: (4, 3)
whiteMovesFrom[1] = {3, 7, 1};  // From: (3, 7), Piece: Knight
whiteMovesTo[1] = {4, 5, 1};    // To: (4, 5)
blackMovesFrom[1] = {3, 0, 1};  // From: (3, 0), Piece: Knight
blackMovesTo[1] = {4, 2, 1};    // To: (4, 2)
whiteMovesFrom[2] = {4, 0, 2};  // From: (4, 0), Piece: Bishop
whiteMovesTo[2] = {2, 2, 2};    // To: (2, 2)
blackMovesFrom[2] = {4, 5, 2};  // From: (4, 5), Piece: Bishop
blackMovesTo[2] = {0, 7, 2};    // To: (0, 7)
whiteMovesFrom[3] = {6, 4, 3};  // From: (6, 4), Piece: Rook
whiteMovesTo[3] = {6, 0, 3};    // To: (6, 0)
blackMovesFrom[3] = {3, 3, 4};  // From: (3, 3), Piece: Queen
blackMovesTo[3] = {3, 5, 4};    // To: (3, 5)
whiteMovesFrom[4] = {3, 5, 5};  // From: (3, 5), Piece: King
whiteMovesTo[4] = {3, 7, 5};    // To: (3, 7)
blackMovesFrom[4] = {2, 3, 2};  // From: (2, 3), Piece: Bishop
blackMovesTo[4] = {5, 6, 2};    // To: (5, 6)
whiteMovesFrom[5] = {5, 4, 2};  // From: (5, 4), Piece: Bishop
whiteMovesTo[5] = {3, 2, 2};    // To: (3, 2)
blackMovesFrom[5] = {5, 3, 3};  // From: (5, 3), Piece: Rook
blackMovesTo[5] = {5, 1, 3};    // To: (5, 1)
whiteMovesFrom[6] = {5, 6, 4};  // From: (5, 6), Piece: Queen
whiteMovesTo[6] = {2, 3, 4};    // To: (2, 3)
blackMovesFrom[6] = {1, 4, 5};  // From: (1, 4), Piece: King
blackMovesTo[6] = {1, 2, 5};    // To: (1, 2)
whiteMovesFrom[7] = {1, 3, 2};  // From: (1, 3), Piece: Bishop
whiteMovesTo[7] = {5, 7, 2};    // To: (5, 7)
blackMovesFrom[7] = {1, 2, 2};  // From: (1, 2), Piece: Bishop
blackMovesTo[7] = {3, 0, 2};    // To: (3, 0)


    std::vector<raylib::Vector2> blackPawns;
    std::vector<raylib::Vector2> whitePawns;
    std::vector<raylib::Vector2> blackKnights;
    std::vector<raylib::Vector2> whiteKnights;
    std::vector<raylib::Vector2> blackRooks;
    std::vector<raylib::Vector2> whiteRooks;
    std::vector<raylib::Vector2> whiteBishops;
    std::vector<raylib::Vector2> blackBishops;
    std::vector<raylib::Vector2> whiteQueen;
    std::vector<raylib::Vector2> blackQueen;

        int prevMouseX = GetMouseX();
        int prevMouseY = GetMouseY();


    // Set up initial positions
    for (int i = 0; i < 8; ++i)
    {
        blackPawns.push_back({static_cast<float>(i), 1});
        whitePawns.push_back({static_cast<float>(i), 6});
    }

    blackRooks.push_back({0, 0});
    blackRooks.push_back({7, 0});
    whiteRooks.push_back({0, 7});
    whiteRooks.push_back({7, 7});

    blackKnights.push_back({1, 0});
    blackKnights.push_back({6, 0});
    whiteKnights.push_back({1, 7});
    whiteKnights.push_back({6, 7});

    whiteBishops.push_back({2, 7});
    whiteBishops.push_back({5, 7});
    blackBishops.push_back({2, 0});
    blackBishops.push_back({5, 0});

    whiteQueen.push_back({3,7});
    blackQueen.push_back({3,0});

    raylib::Vector2 kingW{4, 7};
    raylib::Vector2 kingB{4, 0};

    int currentMouseX = GetMouseX();
    int currentMouseY = GetMouseY();

    int mouseDeltaX = currentMouseX - prevMouseX;
    int mouseDeltaY = currentMouseY - prevMouseY;

    SetTargetFPS(60);

    raylib::Window window(screenWidth, screenHeight, "chess learning");

    raylib::Texture2D chessPullTab = LoadTexture("src/sprites/16x32 pieces/chesspulltab.png");
    raylib::Texture2D Wpawn("src/sprites/16x32 pieces/W_Pawn.png");
    raylib::Texture2D Bpawn("src/sprites/16x32 pieces/B_Pawn.png");
    raylib::Texture2D Wking("src/sprites/16x32 pieces/W_King.png");
    raylib::Texture2D Bking("src/sprites/16x32 pieces/B_King.png");
    raylib::Texture2D Wrook("src/sprites/16x32 pieces/W_Rook.png");
    raylib::Texture2D Brook("src/sprites/16x32 pieces/B_Rook.png");
    raylib::Texture2D Wknight("src/sprites/16x32 pieces/W_Knight.png");
    raylib::Texture2D Bknight("src/sprites/16x32 pieces/B_Knight.png");
    raylib::Texture2D Wbishop("src/sprites/16x32 pieces/W_Bishop.png");
    raylib::Texture2D Bbishop("src/sprites/16x32 pieces/B_Bishop.png");
    raylib::Texture2D SquareB("src/sprites/16x32 pieces/background2.png");
    raylib::Texture2D Bqueen("src/sprites/16x32 pieces/B_Queen.png");
    raylib::Texture2D Wqueen("src/sprites/16x32 pieces/W_Queen.png");

    raylib::Image image = LoadImageFromTexture(chessPullTab);


    Color lightgreen = (Color){118, 150, 86, 255};
    Color green = (Color){186, 202, 68, 255};

    double startTime = GetTime();
    double pauseTime = 0.0; // Variable to store the paused time
    bool isPaused = false;  // Flag to indicate if the sound is paused

    while (! WindowShouldClose())
    {



                currentMouseX = GetMouseX();
    currentMouseY = GetMouseY();

    mouseDeltaX = currentMouseX - prevMouseX;
    mouseDeltaY = currentMouseY - prevMouseY;

                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isMouseButtonHeld = true;
        }
        else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isMouseButtonHeld = false;
        }


        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTextureEx(SquareB, {chessBoardOffset.x*1.3f,chessBoardOffset.y*1.15f}, 0, 0.94f, WHITE);

        DrawTextureEx(chessPullTab,{chessBoardOffset.x,chessBoardOffset.y-30},0,0.10f,WHITE);


        for (int Y = 0; Y < 8; Y++)
        {
            for (int X = 0; X < 8; X++)
            {
                Rectangle tileRect = { (X * tileSize) + chessBoardOffset.x, (Y * tileSize) + chessBoardOffset.y, tileSize, tileSize };

                // Check if mouse cursor is hovering over the current tile
                if (CheckCollisionPointRec(GetMousePosition(), tileRect))
                {
                    hoveredTileX = X;
                    hoveredTileY = Y;
                }
                
                
                    if (count % 2 == 0)
                    {
                        DrawRectangleRec(tileRect, lightgreen);
                    }
                    else
                    {
                        DrawRectangleRec(tileRect, green);
                    }
                
                count++;
            }
            count++;
        }

        // Print the hovered tile coordinates
        if (hoveredTileX != -1 && hoveredTileY != -1)
        {
            DrawText(TextFormat("Hovered Tile: (%d, %d)", hoveredTileX, hoveredTileY), 10, 10, 20, BLACK);
        }

        while(loccount<=16 && isMouseButtonHeld && !allow){
            
if (isMouseButtonHeld) {
    // Check for a match in blackRooks
    if (blackRooks[0].x == hoveredTileX && blackRooks[0].y == hoveredTileY) {
        if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
            work = true;
        }
    }

    if (blackRooks[0].x == hoveredTileX && blackRooks[0].y == hoveredTileY && work) {
        if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
            blackRooks[0].x = hoveredTileX;
            blackRooks[0].y = hoveredTileY;
            work = false;
            currmove=+1;
        }
    }

    if (blackRooks[1].x == hoveredTileX && blackRooks[1].y == hoveredTileY) {
        if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
            work = true;
        }
    }

    if (blackRooks[1].x == hoveredTileX && blackRooks[1].y == hoveredTileY && work) {
        if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
            blackRooks[1].x = hoveredTileX;
            blackRooks[1].y = hoveredTileY;
            work = false;
            currmove=+1;
        }
    }

    // Check for a match in whiteRooks
    if (whiteRooks[0].x == hoveredTileX && whiteRooks[0].y == hoveredTileY) {
        if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
            work = true;
        }
    }

    if (whiteRooks[0].x == hoveredTileX && whiteRooks[0].y == hoveredTileY && work) {
        if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
            whiteRooks[0].x = hoveredTileX;
            whiteRooks[0].y = hoveredTileY;
            work = false;            currmove=+1;
        }
    }

    if (whiteRooks[1].x == hoveredTileX && whiteRooks[1].y == hoveredTileY) {
        if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
            work = true;
        }
    }

    if (whiteRooks[1].x == hoveredTileX && whiteRooks[1].y == hoveredTileY && work) {
        if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
            whiteRooks[1].x = hoveredTileX;
            whiteRooks[1].y = hoveredTileY;
            work = false;            currmove=+1;
            }}



// Check for a match in blackKnights
if (blackKnights[0].x == hoveredTileX && blackKnights[0].y == hoveredTileY) {
    if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
        work = true;
    }
}

if (blackKnights[0].x == hoveredTileX && blackKnights[0].y == hoveredTileY && work) {
    if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
        blackKnights[0].x = hoveredTileX;
        blackKnights[0].y = hoveredTileY;
        work = false;            currmove=+1;
    }
}

if (blackKnights[1].x == hoveredTileX && blackKnights[1].y == hoveredTileY) {
    if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
        work = true;
    }
}

if (blackKnights[1].x == hoveredTileX && blackKnights[1].y == hoveredTileY && work) {
    if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
        blackKnights[1].x = hoveredTileX;
        blackKnights[1].y = hoveredTileY;
        work = false;            currmove=+1;
    }
}

// Check for a match in whiteKnights
if (whiteKnights[0].x == hoveredTileX && whiteKnights[0].y == hoveredTileY) {
    if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
        work = true;
    }
}

if (whiteKnights[0].x == hoveredTileX && whiteKnights[0].y == hoveredTileY && work) {
    if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
        whiteKnights[0].x = hoveredTileX;
        whiteKnights[0].y = hoveredTileY;
        work = false;            currmove=+1;
    }
}

if (whiteKnights[1].x == hoveredTileX && whiteKnights[1].y == hoveredTileY) {
    if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
        work = true;
    }
}

if (whiteKnights[1].x == hoveredTileX && whiteKnights[1].y == hoveredTileY && work) {
    if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
        whiteKnights[1].x = hoveredTileX;
        whiteKnights[1].y = hoveredTileY;
        work = false;            currmove=+1;
    }
}

// Check for a match in whiteBishops
if (whiteBishops[0].x == hoveredTileX && whiteBishops[0].y == hoveredTileY) {
    if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
        work = true;
    }
}

if (whiteBishops[0].x == hoveredTileX && whiteBishops[0].y == hoveredTileY && work) {
    if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
        whiteBishops[0].x = hoveredTileX;
        whiteBishops[0].y = hoveredTileY;
        work = false;            currmove=+1;
    }
}

if (whiteBishops[1].x == hoveredTileX && whiteBishops[1].y == hoveredTileY) {
    if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
        work = true;
    }
}

if (whiteBishops[1].x == hoveredTileX && whiteBishops[1].y == hoveredTileY && work) {
    if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
        whiteBishops[1].x = hoveredTileX;
        whiteBishops[1].y = hoveredTileY;
        work = false;            currmove=+1;
    }
}

// Check for a match in blackBishops
if (blackBishops[0].x == hoveredTileX && blackBishops[0].y == hoveredTileY) {
    if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
        work = true;
    }
}

if (blackBishops[0].x == hoveredTileX && blackBishops[0].y == hoveredTileY && work) {
    if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
        blackBishops[0].x = hoveredTileX;
        blackBishops[0].y = hoveredTileY;
        work = false;            currmove=+1;
    }
}

if (blackBishops[1].x == hoveredTileX && blackBishops[1].y == hoveredTileY) {
    if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
        work = true;
    }
}

if (blackBishops[1].x == hoveredTileX && blackBishops[1].y == hoveredTileY && work) {
    if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
        blackBishops[1].x = hoveredTileX;
        blackBishops[1].y = hoveredTileY;
        work = false;            currmove=+1;
    }
}

// Check for a match in whiteQueen
if (whiteQueen[0].x == hoveredTileX && whiteQueen[0].y == hoveredTileY) {
    if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
        work = true;
    }
}

if (whiteQueen[0].x == hoveredTileX && whiteQueen[0].y == hoveredTileY && work) {
    if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
        whiteQueen[0].x = hoveredTileX;
        whiteQueen[0].y = hoveredTileY;
        work = false;            currmove=+1;
    }
}

// Check for a match in blackQueen
if (blackQueen[0].x == hoveredTileX && blackQueen[0].y == hoveredTileY) {
    if (hoveredTileY == whiteMovesFrom[currmove].x && hoveredTileY == whiteMovesFrom[currmove].y) {
        work = true;
    }
}

if (blackQueen[0].x == hoveredTileX && blackQueen[0].y == hoveredTileY && work) {
    if (hoveredTileX == whiteMovesTo[currmove].x && hoveredTileY == whiteMovesTo[currmove].y) {
        blackQueen[0].x = hoveredTileX;
        blackQueen[0].y = hoveredTileY;
        work = false;            currmove=+1;
    }
}
}
// Repeat the pattern for the other arrays...

        }


if (!moved) {
    DrawRectangle(whiteMovesFrom[placecount].x * tileSize + chessBoardOffset.x, whiteMovesFrom[placecount].y * tileSize + chessBoardOffset.y, tileSize, tileSize, RED);
}

if (!moved) {
    DrawRectangle(whiteMovesTo[placecount].x * tileSize + chessBoardOffset.x, whiteMovesTo[placecount].y * tileSize + chessBoardOffset.y, tileSize, tileSize, RED);
}






if (placecount >= 9) {
    placecount = 0;
}

if(placecount==9){placecount=0;}






        // Draw black pawns
        for (const auto &pawn : blackPawns)
        {
            DrawTextureEx(Bpawn, {(pawn.x * tileSize) + chessBoardOffset.x + lpo, (pawn.y * tileSize) + chessBoardOffset.y - lpo}, 0.0f, static_cast<float>(pawnSize) / static_cast<float>(Bpawn.width), WHITE);
        }

        // Draw white pawns
        for (const auto &pawn : whitePawns)
        {
            DrawTextureEx(Wpawn, {(pawn.x * tileSize) + chessBoardOffset.x + lpo, (pawn.y * tileSize) + chessBoardOffset.y - lpo}, 0.0f, static_cast<float>(pawnSize) / static_cast<float>(Wpawn.width), WHITE);
        }

        // Draw kings
        DrawTextureEx(Wking, {(kingW.x * tileSize) + chessBoardOffset.x+bpo+lpo-5, (kingW.y * tileSize) + chessBoardOffset.y-20}, 0, (pawnSize-1) / 13, WHITE);
        DrawTextureEx(Bking, {(kingB.x * tileSize) + chessBoardOffset.x+lpo+bpo-5, (kingB.y * tileSize) + chessBoardOffset.y-20}, 0, (pawnSize-1) / 13, WHITE);

        // Draw rooks
        for (const auto &rook : whiteRooks)
        {
            DrawTextureEx(Wrook, {(rook.x * tileSize+10) + chessBoardOffset.x, (rook.y * tileSize-20) + chessBoardOffset.y}, 0, pawnSize / 13, WHITE);
        }
        for (const auto &rook : blackRooks)
        {
            DrawTextureEx(Brook, {(rook.x * tileSize+10) + chessBoardOffset.x, (rook.y * tileSize-20) + chessBoardOffset.y}, 0, pawnSize / 13, WHITE);
        }

        // Draw knights
        for (const auto &knight : whiteKnights)
        {
            DrawTextureEx(Wknight, {(knight.x * tileSize+20) + chessBoardOffset.x, (knight.y * tileSize) + chessBoardOffset.y}, 0.0f, static_cast<float>(pawnSize) / static_cast<float>(Wpawn.width), WHITE);
        }
        for (const auto &knight : blackKnights)
        {
            DrawTextureEx(Bknight, {(knight.x * tileSize+20) + chessBoardOffset.x, (knight.y * tileSize) + chessBoardOffset.y}, 0.0f, static_cast<float>(pawnSize) / static_cast<float>(Wpawn.width), WHITE);
        }

        // Draw bishops
        for (const auto &bishop : whiteBishops)
        {
            DrawTextureEx(Wbishop, {(bishop.x * tileSize+20) + chessBoardOffset.x, (bishop.y * tileSize) + chessBoardOffset.y}, 0.0f, static_cast<float>(pawnSize) / static_cast<float>(Wpawn.width), WHITE);
        }
        for (const auto &bishop : blackBishops)
        {
            DrawTextureEx(Bbishop, {(bishop.x * tileSize+20) + chessBoardOffset.x, (bishop.y * tileSize) + chessBoardOffset.y}, 0.0f, static_cast<float>(pawnSize) / static_cast<float>(Wpawn.width), WHITE);
        }

       for (const auto &queen : whiteQueen)
        {
            DrawTextureEx(Wqueen, {(queen.x * tileSize) + chessBoardOffset.x+lpo+bpo, (queen.y * tileSize) + chessBoardOffset.y-lpo+5}, 0.0f, static_cast<float>(pawnSize) / static_cast<float>(Wpawn.width), WHITE);
        }
        for (const auto &queen : blackQueen)
        {
            DrawTextureEx(Bqueen, {(queen.x * tileSize) + chessBoardOffset.x+bpo+lpo, (queen.y * tileSize) + chessBoardOffset.y-lpo+5}, 0.0f, static_cast<float>(pawnSize) / static_cast<float>(Wpawn.width), WHITE);
        }



                if (IsKeyPressed(KEY_F4))
        {
            ToggleFullscreen();
        }





if (CheckHoverOverImg(image, {chessBoardOffset.x - 200, chessBoardOffset.y - 30}, {static_cast<float>(GetMouseX()), static_cast<float>(GetMouseY())}) && isMouseButtonHeld) {
    allow = true;

    std::cout<< "f";

}


if (isMouseButtonHeld && allow) {

    std::cout << "e";

    chessBoardOffset.x += mouseDeltaX;
    chessBoardOffset.y += mouseDeltaY;
} else {
    allow = false;
}


EndDrawing();

prevMouseX = currentMouseX;
prevMouseY = currentMouseY;

    }
    CloseWindow();

    PollInputEvents();

    return 0;
}
