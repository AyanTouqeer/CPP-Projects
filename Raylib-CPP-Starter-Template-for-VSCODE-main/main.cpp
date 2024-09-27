#include <iostream>
#include <raylib.h>

using namespace std;

//Initializing game colors.
Color green = Color{38, 185, 154, 255};
Color darkGreen = Color{20, 160, 133, 255};
Color lightGreen = Color{129, 204, 184, 255};
Color yellow = Color{243, 213, 91, 255};

//Draw variables to store score of CPU and Player individually.
int playerScore = 0; //Global variable.
int cpuScore = 0; //Global variable.

//Create a ball class.
class Ball{
public:
    //Attributes of ball.
    int xPos, yPos, radius;
    int xSpeed, ySpeed;

    //Methods.

    void DrawBall() //To draw the ball.
    {
        DrawCircle(xPos, yPos, radius, yellow);
    }

    void UpdateBallPosition() //To update the position of the ball.
    {
        xPos += xSpeed;
        yPos += ySpeed;

        //If ball collides with top or bottom of the screen.
        if (yPos + radius >= GetScreenHeight() || yPos - radius <= 0)
        {
            ySpeed *= -1; //Then change its direction.
        }

        //If ball hits right side (Player paddle side) of the screen.
        if (xPos + radius >= GetScreenWidth())
        {
            cpuScore++; //Then increment the CPU Score.

            //Reset ball position when player scores.
            ResetBallPosition();
        }

        //If ball hits left side (CPU paddle side) of the screen.
        if ( xPos - radius <= 0)
        {
            playerScore++; //Then increment the Player score.

            //Reset ball position when cpu scores.
            ResetBallPosition();
        }
    }

    //We need to reset ball to center of the screen.
    void ResetBallPosition()
    {
        //Give the xPos and yPos the center coordinate values.
        xPos = GetScreenWidth() / 2;
        yPos = GetScreenHeight() / 2;

        //Give ball a random direction.
        int speedChoices[2] = {-1, 1};

        //Choose random values from speedChoices by using built-in GetRandomValue() function.
        xSpeed *= speedChoices[GetRandomValue(0, 1)];
        ySpeed *= speedChoices[GetRandomValue(0, 1)];
    }

};

//Create a paddle class.
class Paddles{
protected:
    //Movement Restriction Method for Right Paddle.
    void RestrictMovementRightPaddle()
    {
        //Restricting the paddle position within the window.
        if (yPosRight <= 0) //Upper position.
        {
            yPosRight = 0;
        }

        if ( yPosRight + height >= GetScreenHeight()) //Lower position.
        {
            yPosRight = GetScreenHeight() - height;
        }
    }

    //Movement Restriction Method for left Paddle.
    void RestrictMovementLeftPaddle()
    {
        //Restricting the paddle position within the window.
        if (yPosLeft <= 0) //Upper position.
        {
            yPosLeft = 0;
        }

        if ( yPosLeft + height >= GetScreenHeight()) //Lower position.
        {
            yPosLeft = GetScreenHeight() - height;
        }
    }

public:
    //Attributes.
    int xPosRight, xPosLeft, yPosRight, yPosLeft, width, height, ySpeedRight, ySpeedLeft;

    //Methods.
    void DrawRightPaddle()
    {
        DrawRectangleRounded(Rectangle{xPosRight, yPosRight, width, height}, 0.8, 0, WHITE);
    }

    void DrawLeftPaddle()
    {
        DrawRectangleRounded(Rectangle{xPosLeft, yPosLeft, width, height}, 0.8, 0, WHITE);
    }

    void UpdateRightPaddlePosition(){
        //Move the right paddle with key events.
        if (IsKeyDown(KEY_UP))
        {
            yPosRight -= ySpeedRight; //Vertically Up Position.
        }

        if (IsKeyDown(KEY_DOWN))
        {
            yPosRight += ySpeedRight; //Vertically Down Position.
        }

        //Call Restriction Method.
        RestrictMovementRightPaddle();
    }

    void UpdateLeftPaddlePosition(int ballYPos)
    {
        if (yPosLeft + height / 2 > ballYPos)
        {
            yPosLeft -= ySpeedLeft;
        }

        if (yPosLeft + height / 2 < ballYPos)
        {
            yPosLeft += ySpeedLeft;
        }

        //Call Restriction Method.
        RestrictMovementLeftPaddle();
    }

};


//Create a screen class.
class Screen{
public:
    //Attributes.

    //For rectangle.
    int recXPos, recYPos, recWidth, recHeight;

    //For circle.
    int cirXPos, cirYPos, cirRadius;


    //Methods.
    void DrawBackground() //Draws background shapes with colors.
    {
        DrawRectangle(recXPos, recYPos, recWidth, recHeight, green);
        DrawCircle(cirXPos, cirYPos, cirRadius, lightGreen);
    }
};






int main(){
    cout << "Starting the game." << endl;

    //Screen size variables.
    const int screenWidth = 800;
    const int screenHeight = 600;

    //Initialize the window of game.
    InitWindow(screenWidth, screenHeight, "Pong Game");

    //Declare the frame rate.
    SetTargetFPS(60);

    //Create ball object.
    Ball ball;

    //Initialize values.
    ball.xPos = screenWidth / 2;
    ball.yPos = screenHeight / 2;
    ball.radius = 10;
    ball.xSpeed = 7;
    ball.ySpeed = 7;

    //Create paddle object.
    Paddles paddle;

    //Initialize values.
    paddle.xPosRight = screenWidth - 30;
    paddle.xPosLeft = 10;
    paddle.yPosRight = screenHeight / 2 - 60;
    paddle.yPosLeft = screenHeight / 2 - 60;
    paddle.width = 20;
    paddle.height = 120;
    paddle.ySpeedRight = 7;
    paddle.ySpeedLeft = 7;

    //Create screen object.
    Screen screen;

    //initializing values.
    //Rectangle.
    screen.recXPos = screenWidth / 2;
    screen.recYPos = 0;
    screen.recWidth = screenWidth / 2;
    screen.recHeight = screenHeight;

    //Circle.
    screen.cirXPos = screenWidth / 2;
    screen.cirYPos = screenHeight / 2;
    screen.cirRadius = 120;

    //Starting the game loop.
    while(!WindowShouldClose())
    {

        BeginDrawing();

        //Clear background for ball.
        ClearBackground(darkGreen);

        //Call DrawBackground() function.
        screen.DrawBackground();

        //Check for collision of ball with right paddle.
        if (CheckCollisionCircleRec(Vector2 {ball.xPos, ball.yPos}, ball.radius, Rectangle {paddle.xPosRight, paddle.yPosRight, paddle.width, paddle.height}))
        {
            ball.xSpeed *= -1;
        }

        //Check for collision of ball with left paddle.
        if (CheckCollisionCircleRec(Vector2{ball.xPos, ball.yPos}, ball.radius, Rectangle{paddle.xPosLeft, paddle.yPosLeft, paddle.width, paddle.height}))
        {
            ball.xSpeed *= -1;
        }

        //Draw the ball.
        ball.DrawBall();

        //Move the ball.
        ball.UpdateBallPosition();


        //Draw left paddle.
        paddle.DrawLeftPaddle();

        //Draw right paddle.
        paddle.DrawRightPaddle();

        //Move right paddle on users command.
        paddle.UpdateRightPaddlePosition();

        //Move left paddle on A.I command.
        paddle.UpdateLeftPaddlePosition(ball.yPos);


        //Draw line in the middle.
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);


        //Draw score by using built-in raylib function.
        //To convert numbers into text we use raylib TextFormat() function.
        DrawText(TextFormat("%d", cpuScore), screenWidth / 4 - 20, 20, 80, WHITE); //CPU Score.

        DrawText(TextFormat("%d", playerScore), 3*screenWidth / 4 - 20, 20, 80, WHITE); //Player Score.

        EndDrawing();
    }

    CloseWindow();

    return 0;
}




