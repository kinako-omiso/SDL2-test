#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 80

int main(int argc, char* argv[])
{
   SDL_Window* window = NULL;
   SDL_Renderer* renderer = NULL;
   SDL_Texture* playerTexture = NULL;
   SDL_Texture* obstacleTexture = NULL;
   SDL_Rect playerRect = {SCREEN_WIDTH/2 - PLAYER_WIDTH/2, SCREEN_HEIGHT/2 - PLAYER_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT};
   SDL_Rect obstacleRect = {SCREEN_WIDTH, SCREEN_HEIGHT - 100, 50, 50};
   SDL_Point player_point;
   int obstacleSpeed = 5;
   int Gravity = 1;
   bool isJump = false;
   bool isAir = false;
   bool isGameOver = false;
   int jumpSpeed = 20;
   int jumpHeight = 200;
   int jumpCounter = 0;
   bool isCollision = false;
   const Uint8 *pKeyStatus;

   SDL_Init(SDL_INIT_VIDEO);

   window = SDL_CreateWindow("Simple Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
   renderer = SDL_CreateRenderer(window, -1, 0);

   SDL_Surface* surface = SDL_LoadBMP("seiyo_1.bmp");
   playerTexture = SDL_CreateTextureFromSurface(renderer, surface);
   SDL_FreeSurface(surface);

   surface = SDL_LoadBMP("dopa_dark.bmp");
   obstacleTexture = SDL_CreateTextureFromSurface(renderer, surface);
   SDL_FreeSurface(surface);

   while (1)
   {
       SDL_Event event;
       while (SDL_PollEvent(&event))
        {
           if (event.type == SDL_QUIT)
               return 0;
        }
        
        pKeyStatus = SDL_GetKeyboardState(NULL);
        if (pKeyStatus[SDL_SCANCODE_SPACE])
        {    
            printf("input SPACE");
            if (!isJump && !isAir){
                isJump = true;
            }
        }

       //ジャンプ処理
       if (isJump)
       {
           jumpCounter += jumpSpeed;
           playerRect.y -= jumpSpeed;
           if (jumpCounter >= jumpHeight )
           {
                isJump = false;
                jumpCounter = 0;
           }
       }

       //重力処理
        if(playerRect.y < SCREEN_HEIGHT - PLAYER_HEIGHT){
            isAir = true;
            playerRect.y += Gravity;
        }else{
          isAir = false;
        }

        //衝突判定(書きかけ)
        player_point.x = playerRect.x;
        player_point.y = playerRect.y; 
        isCollision = SDL_PointInRect(&player_point, &obstacleRect);
        //SDL2_rectでサーフェイスを囲み、その領域との被ったときに衝突フラグをonにすればよさそう
        if(isCollision == true){
           isGameOver = true;
           printf("あたった！");
           isCollision = false;
        }


       printf("Player Y Position: %d\n", playerRect.y);

       obstacleRect.x -= obstacleSpeed;
       if (obstacleRect.x < -obstacleRect.w)
       {
           obstacleRect.x = SCREEN_WIDTH;
       }

       SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
       SDL_RenderClear(renderer);

       // プレイヤーの移動描画
       SDL_RenderCopy(renderer, playerTexture, NULL, &playerRect);
       // オブジェクトの移動の描画
       SDL_RenderCopy(renderer, obstacleTexture, NULL, &obstacleRect);

       SDL_RenderPresent(renderer);
       SDL_Delay(10);
   }

   SDL_DestroyTexture(playerTexture);
   SDL_DestroyTexture(obstacleTexture);
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();

   return 0;
}
