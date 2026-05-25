#include <lua.h>
#include <lauxlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

static const Uint8 *keys;

static SDL_Texture *texture = NULL;
static TTF_Font *font = NULL;

static int l_window(lua_State *L) {
    const char *title = luaL_checkstring(L, 1);
    int width = luaL_checkinteger(L, 2);
    int height = luaL_checkinteger(L, 3);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Window Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(
    window,
    -1,
    SDL_RENDERER_SOFTWARE
);
    if (!renderer) {
        printf("Renderer Error: %s\n", SDL_GetError());
        return 0;
    }

    return 0;
}

static int l_clear(lua_State *L) {
    int r = luaL_checkinteger(L, 1);
    int g = luaL_checkinteger(L, 2);
    int b = luaL_checkinteger(L, 3);

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderClear(renderer);

    return 0;
}

static int l_rect(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int w = luaL_checkinteger(L, 3);
    int h = luaL_checkinteger(L, 4);

    int r = luaL_checkinteger(L, 5);
    int g = luaL_checkinteger(L, 6);
    int b = luaL_checkinteger(L, 7);

    SDL_Rect rect = {x, y, w, h};

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);

    return 0;
}

static int l_image(lua_State *L) {
    const char *path = luaL_checkstring(L, 1);

    SDL_Surface *surface = IMG_Load(path);

    if (!surface) {
        printf("Erro IMG_Load: %s\n", IMG_GetError());
        return 0;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return 0;
}

static int l_draw(lua_State *L) {
    int x = luaL_checkinteger(L, 1);
    int y = luaL_checkinteger(L, 2);
    int w = luaL_checkinteger(L, 3);
    int h = luaL_checkinteger(L, 4);

    SDL_Rect rect = {x, y, w, h};

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    return 0;
}

static int l_text(lua_State *L) {
    const char *msg = luaL_checkstring(L, 1);

    int x = luaL_checkinteger(L, 2);
    int y = luaL_checkinteger(L, 3);

    SDL_Color color = {255, 255, 255};

    font = TTF_OpenFont("arial.ttf", 24);

    if (!font) {
        printf("Erro fonte: %s\n", TTF_GetError());
        return 0;
    }

    SDL_Surface *surface =
        TTF_RenderText_Solid(font, msg, color);

    if (!surface) {
        printf("Erro texto\n");
        return 0;
    }

    SDL_Texture *text =
        SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect rect = {
        x,
        y,
        surface->w,
        surface->h
    };

    SDL_RenderCopy(renderer, text, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(text);

    TTF_CloseFont(font);

    return 0;
}

static int l_running(lua_State *L) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            lua_pushboolean(L, 0);
            return 1;
        }
    }

    keys = SDL_GetKeyboardState(NULL);

    SDL_RenderPresent(renderer);

    lua_pushboolean(L, 1);

    SDL_Delay(16);

    return 1;
}

static int l_key(lua_State *L) {
    const char *key = luaL_checkstring(L, 1);

    SDL_Scancode code = SDL_GetScancodeFromName(key);

    lua_pushboolean(L, keys[code]);

    return 1;
}

int luaopen_game(lua_State *L) {
    lua_register(L, "window", l_window);
    lua_register(L, "clear", l_clear);
    lua_register(L, "rect", l_rect);

    lua_register(L, "image", l_image);
    lua_register(L, "draw", l_draw);

    lua_register(L, "text", l_text);

    lua_register(L, "running", l_running);
    lua_register(L, "key", l_key);

    return 0;
}
