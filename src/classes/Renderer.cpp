#include "Renderer.h"

Renderer::Renderer(SDL_Window* window)
{
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("Accelerated renderer could not be created! SDL_Error: %s\nSwitching to software renderer", SDL_GetError());
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    }

    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    } else {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) && imgFlags)) {
            printf("SDL_Image could not initialize! SDL_Error: %s\n", SDL_GetError());
        }
    }
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
}

void Renderer::Reset()
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
}

void Renderer::Draw(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Rect drawing = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderFillRect(renderer, &drawing);
}

void Renderer::Draw(Player* player)
{
    SDL_Rect drawing = {player->x, player->y, player->width, player->height};
    SDL_SetRenderDrawColor(renderer, player->r, player->g, player->b, player->a);
    SDL_RenderFillRect(renderer, &drawing);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderDrawRect(renderer, &drawing);
}

void Renderer::Draw(Wall* walls[4])
{
    for (int x {}; x < 4; ++x) {
        SDL_Rect drawing = {walls[x]->x, walls[x]->y, walls[x]->width, walls[x]->height};
        SDL_SetRenderDrawColor(renderer, walls[x]->r, walls[x]->g, walls[x]->b, walls[x]->a);
        SDL_RenderFillRect(renderer, &drawing);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderDrawRect(renderer, &drawing);
    }
}

void Renderer::Draw(Enemy* enemies[2])
{
    for (int x {}; x < 2; ++x) {
        SDL_Rect drawing = {enemies[x]->x, enemies[x]->y, enemies[x]->width, enemies[x]->height};
        SDL_SetRenderDrawColor(renderer, enemies[x]->r, enemies[x]->g, enemies[x]->b, enemies[x]->a);
        SDL_RenderFillRect(renderer, &drawing);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderDrawRect(renderer, &drawing);
    }
}

void Renderer::Draw(UI* ui)
{
}

void Renderer::ManageBullets(Enemy* enemies[2], Player& player)
{
    for (int x {}; x < 2; ++x) {
        if (enemies[x]->bullet != nullptr) {
            if (enemies[x]->bullet->y >= -20 && enemies[x]->bullet->x >= -100 && enemies[x]->bullet->x <= 1500 && !player.CheckBulletCollisions(enemies[x]->bullet)) {
                enemies[x]->bullet->Move();
                SDL_Rect drawing = {enemies[x]->bullet->x, enemies[x]->bullet->y, enemies[x]->bullet->width, enemies[x]->bullet->height};
                SDL_SetRenderDrawColor(renderer, enemies[x]->bullet->r, enemies[x]->bullet->g, enemies[x]->bullet->b, enemies[x]->bullet->a);
                SDL_RenderFillRect(renderer, &drawing);
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderDrawRect(renderer, &drawing);
            } else {
                enemies[x]->DeleteBullet();
            }
        }
    }
}