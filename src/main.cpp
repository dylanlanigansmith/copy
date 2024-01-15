#include <SDL3/SDL.h>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <thread>
#include <chrono>
// copy
/*
i want to pipe commands into my clipboard

so i can go like:

cat /proc/status | copy


ls ~ | copy

etc..

and now i can

but the code is so so so so so so so
so so so bad

*/
#define SDL_FAIL() std::cout << "copy: sdlerror: " << SDL_GetError() << std::endl
#define CLIP_FAIL()                        \
    std::cout << "clip fail" << std::endl; \
    return 1
#define DBG(fmt, ...) printf(fmt, __VA_ARGS__)
#define DEBUG(str) std::cout << "debug: " << str << std::endl
int main(int argc, char **argv)
{
    if(argc > 1){
        std::cout << "copy only accepts pipes! \n usage: echo example | copy" << std::endl; return 0;
    }

    constexpr size_t buf_size = 4096;
    char* buf = new char[buf_size];
    std::cin.read(buf, buf_size);

    size_t idx = 0;
    while(buf[idx] > 0x4 && idx < buf_size )
        idx++;
    
    buf[idx] = 0;//0 0xa;
   // std::cout << "buf: \n" << buf << std::endl;
   
   
  
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_FAIL();
        CLIP_FAIL();
    }

    auto sdl_win = SDL_CreateWindow(std::to_string(rand()).append("copy").c_str(), 64, 64, SDL_WINDOW_HIDDEN);
    if (sdl_win == NULL)
    {
        SDL_FAIL();
        CLIP_FAIL();
    }

  
//ifdk man but it works 
    std::thread([](const char* pipe) 
                {
        while(true) //idk
        {

            
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if(event.type == SDL_EVENT_QUIT){
                    break;
                }
            }
            static bool didClip = false;
            if(!didClip){
                auto err = SDL_SetClipboardText(pipe);
                if (err != 0)
                {
                    SDL_FAIL();
                    DEBUG("clip: sdlsetfailed");
                    didClip = true;
                    break;
                }
                else if (err == 0)
                {
                    didClip = true;
                   // DEBUG("copy: set clip");
                   //break;
                }
            }
           
           std::this_thread::sleep_for(std::chrono::milliseconds(50)); //idk
           SDL_assert(pipe && strlen(pipe));
        }

        
        
        
        }, buf)
        .detach();


  


    
       std::this_thread::sleep_for(std::chrono::milliseconds(500)); //idfk im sorry
    if (false) //for debug
    {
        char *maybe_clip = SDL_GetClipboardText();

        if (!maybe_clip)
        {
            DEBUG("nullclip!");
            SDL_FAIL();
            CLIP_FAIL();
        }
        if (!strlen(maybe_clip))
        {

            SDL_FAIL();
            DEBUG("clip empty");
        }
        else
        {
            DBG("clipget: %s \n", maybe_clip); // broken
            //  std::cout << maybe_clip << std::endl;
        }
        SDL_free(maybe_clip);
    }

    //babdbdbabdbabdbbadbadbabdbadbadbadbad
  //   SDL_Quit(); 
  // SDL_DestroyWindow(sdl_win);
    return 0;
}