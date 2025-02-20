#include "../include/lib.h"
#include "../include/main.h"
#include "../include/window.h"
#include "../include/player.h"
#include "../include/map.h"
#include "../include/camera.h"


int init_systeme ();
void terminate_system (SDL_Renderer * renderer, SDL_Window * window, Mix_Music * music, int audio, Player_t * player, Map_t * map, int ttf, int mixer, int img, int sdl, Camera_t * camera);
void handle_input (const uint8_t * keys, Player_t * player);

SDL_Window * window ; 
SDL_Renderer * renderer ; 
GameStatus_t gameStatus ; 

int main(int argc, char* argv[]) {

    if (init_systeme()) {
        return 1;
    }


    // charge music 
    Mix_Music * music = Mix_LoadMUS("music/ah_shit_here_we_go_again.ogg");
    if (music == NULL) {
        printf("Erreur de chargement music \"%s\": %s\n", "music/ah_shit_here_we_go_again.mp3", SDL_GetError());
        terminate_system(renderer, window, NULL, TRUE, NULL, NULL, TRUE, TRUE, TRUE, TRUE, NULL);
        return 1;
    }


    // creer personnage 
    Player_t * player = player_constructor();
    if (player == NULL) {
        terminate_system(renderer, window, music, TRUE, NULL, NULL, TRUE, TRUE, TRUE, TRUE, NULL);
        return 1;
    }

    Map_t * map = map_constructor();
    if (map == NULL) {
        terminate_system(renderer, window, music, TRUE, player, NULL, TRUE, TRUE, TRUE, TRUE, NULL);
        return 1;
    }

    Camera_t * camera = camera_constructor (player);
    if (camera == NULL) {
        terminate_system(renderer, window, music, TRUE, player, map, TRUE, TRUE, TRUE, TRUE, NULL);
        return 1;
    }
    
    // variable pour l'affichage du nombre de FPS 
    uint32_t previousTime = SDL_GetTicks(); // to print fps every second 
    int nbFrame = 0; 
    int updateCount = 0;
    
    // Variable to keep track of the time elapsed during the actual frame rendering 
    uint32_t timerStart; 
    uint32_t timerDelay; 

    int signal = 0;
    
    // Boucle principale
    SDL_Event event;
    while (gameStatus.running) {

        timerStart = SDL_GetTicks();
        nbFrame++;
        updateCount++;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                gameStatus.running = FALSE;
            }
        }

        const uint8_t * keys = SDL_GetKeyboardState(NULL);
        handle_input(keys, player);

        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear (renderer); 

        update_player(player, &map->ground);
        update_camera(camera, player);
        draw_map(map, camera);
        draw_player(player, camera);

        // Mettre à jour l'écran
        SDL_RenderPresent (renderer);

        
        if (updateCount == 5) {
            updateCount = 0;
            update_player_anim_state (player);
        }        


        // print fps 
        // uint32_t time = SDL_GetTicks();
        // if (time - previousTime > 1000) {
        //     previousTime = time;
        //     printf("FPS : %d\n", nbFrame);
        //     nbFrame = 0;
        // }


        // block program at 60fps 
        timerDelay = SDL_GetTicks() - timerStart;
        if (timerDelay < FRAME_DELAY) {
            SDL_Delay(FRAME_DELAY - timerDelay);
        }

    }

    // Nettoyage
    terminate_system(renderer, window, music, TRUE, player, map, TRUE, TRUE, TRUE, TRUE, camera);

    return 0;
}


// initialise les variables globales du systeme et les differentes librairies 
int init_systeme () {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        return 1;
    }


    // Initialisation de SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("Erreur d'initialisation de SDL_image: %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }


    // initialisation de SDL_ttf 
    if (TTF_Init() == -1) {
        printf("Erreur d'initialisation de SDL_ttf : %s\n", TTF_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }


    // Initialisation de SDL_mixer et configuration audio 
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        printf("Erreur d'initialisation de SDL_mixer : %s\n", Mix_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur d'initialisation de Mix_OpenAudio : %s\n", Mix_GetError());
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }


    // Création de la fenêtre
    window = SDL_CreateWindow("Intro Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur de création de la fenêtre: %s\n", SDL_GetError());
        Mix_CloseAudio();
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_SetWindowResizable(window, SDL_FALSE);


    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur de création du renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        Mix_CloseAudio();
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    
    gameStatus.running = TRUE;
    gameStatus.level = 0;

    return 0;
}


void terminate_system (SDL_Renderer * renderer, SDL_Window * window, Mix_Music * music, int audio, Player_t * player, Map_t * map, int ttf, int mixer, int img, int sdl, Camera_t * camera) {
    
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    if (music) {
        Mix_FreeMusic(music);
    }
    if (audio) {
        Mix_CloseAudio();
    }
    if (player) {
        player_destructor(&player);
    }
    if (map) {
        map_destructor(&map);
    }
    if (ttf) {
        TTF_Quit();
    }
    if (mixer) {
        Mix_Quit();
    }
    if (img) {
        IMG_Quit();
    }
    if (sdl) {
        SDL_Quit();
    }
    if (camera) {
        camera_destructor(&camera);
    }
}