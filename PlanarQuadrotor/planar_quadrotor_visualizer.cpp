#include "planar_quadrotor_visualizer.h"

PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * done 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * done 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * done 3. Animate proppelers (extra points)
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer, Uint64 sprite, float target_x, float target_y) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;

    /* x, y, theta coordinates */
    q_x = state[0]+640;
    q_y = state[1]+360;
    q_theta = state[2];

    std::string file;

    file = "textures/quadrotor.bmp";


    SDL_Surface* surf = SDL_LoadBMP(file.c_str());
    SDL_Texture* text = SDL_CreateTextureFromSurface(gRenderer.get(), surf);
    SDL_FreeSurface(surf);

    SDL_Rect srcrect = { sprite*54, 0, 54, 34 };
    SDL_Rect dstrect = { q_x - 27, q_y - 17, 54, 34 };
    SDL_Rect target = { target_x - 3, target_y - 3, 6, 6 };

    SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer.get(), &target);

    SDL_RenderCopyEx(gRenderer.get(), text, &srcrect, &dstrect, -q_theta*180/M_PI, NULL, SDL_FLIP_NONE);
    SDL_RenderPresent(gRenderer.get());

}