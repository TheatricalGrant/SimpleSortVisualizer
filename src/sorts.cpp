#include <vector>
#include <iostream>
#include "program.h"
#include "rectangle.h"
#include "sorts.h"

// Sorts begin

// Bubble sort
void sorts::bubbleSort(SDL_Renderer* renderer, std::vector<rectangle> &rects, int sortTime)
{
    // through every iteration of the i for loop,
    // the biggest number will makes it's way to the back
    // just like how bubbles float to the top

    // this is done by checking j and j+1
    // naturally the biggest number will slowly make it's way
    // as with each check it'll be bigger then go right

    // the swapped bool is there to check if a swapped happen
    // if it didn't happen the loop will break
    // this is because if no swap happens after checking every one side by side
    // its already sorted!

    bool finished = false;
    for (uint16_t i = 0; i < rects.size(); i++)
    {
        bool swapped = false;

        for (uint16_t j = 0; j < rects.size() - 1; j++)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    finished = true;
                    break;
                }
            }

            if (finished) break;

            if (rects[j].getValue() > rects[j + 1].getValue())
            {
                sorts::swap(renderer, rects, j, j+1, sortTime);
                swapped = true;
            }
        }

        if (!swapped)
            break;

        SDL_RenderPresent(renderer);
        SDL_PumpEvents();
    }
}

void sorts::selectionSort(SDL_Renderer* renderer, std::vector<rectangle> &rects, int sortTime) 
{
    // selection sort looks for the lowest number in the array
    // Once it does that it places it at the front of the array
    // then keeps swapping with the one next to it until its sorted

    int pos;
    bool finished = false;
    for (uint16_t i = 0; i < rects.size() - 1; i++)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                finished = true;
                break;
            }
        }

        if (finished) break;

        pos = i;
        for (uint16_t j = i + 1; j < rects.size(); j++)
        {
            if (rects[j].getValue() < rects[pos].getValue())
            {
                pos = j;
            }
        }
        sorts::swap(renderer, rects, pos, i, sortTime);
    }

    SDL_RenderPresent(renderer);
    SDL_PumpEvents();
}

void sorts::insertionSort(SDL_Renderer* renderer, std::vector<rectangle> &rects, int sortTime)
{
    // insertion sort starts at the beginning of the array
    // it compares from left to right, right next to each other
    // once it finds one smaller it goes back and inserts it where it needs to be

    bool finished = false;
    for (uint16_t i = 0; i < rects.size(); i++)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                finished = true;
                break;
            }
        }

        if (finished) break;

        uint16_t j = i;
        while (j > 0 && rects[j-1].getValue() > rects[j].getValue())
        {
            sorts::swap(renderer, rects, j, j-1, sortTime);
            j--;
        }
    }

    SDL_RenderPresent(renderer);
    SDL_PumpEvents();
}

// Sorts end

void sorts::swap(SDL_Renderer* renderer, std::vector<rectangle> &rects, int first, int second, int sortTime)
{
    //change the color to red
    rects[first].setColor(Color(255, 0, 0, 255));
    rects[second].setColor(Color(255, 0, 0, 255));
    sorts::sortingDraw(renderer, rects);

    // change the position in the array
    rectangle tempRect = rects[first];
    rects[first] = rects[second];
    rects[second] = tempRect;

    // update the actual position variable
    // along with where it is on the screen
    rects[first].setPosition(first);
    rects[second].setPosition(second);

    // Get the current milliseconds since the program started
    uint32_t time = SDL_GetTicks();
    // start time to compare with the time later
    uint32_t startTime = time;

    while (time < startTime + sortTime)
    {
        time = SDL_GetTicks();
    }

    rects[first].setColor(Color(255, 255, 255, 255));
    rects[second].setColor(Color(255, 255, 255, 255));
    sorts::sortingDraw(renderer, rects);
}

void sorts::sortingDraw(SDL_Renderer* renderer, std::vector<rectangle> rects)
{
    // Change the background color to black, then put on back buffer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // redraw all the rectangles in their fixed order while sorting
    for (uint8_t i = 0; i < rects.size(); i++)
    {
        // for every iteration of the loop draw each rectangle
        rects[i].draw(renderer);
    }

    SDL_RenderPresent(renderer);
}

int sorts::addSortSpeed(int curSpeed)
{
    // add to the sorting speed unless the curSpeed is already equal/greater than 100
    if (curSpeed >= 50)
        return curSpeed;

    std::cout << curSpeed + 5 << std::endl;
    return curSpeed += 5;
}

int sorts::removeSortSpeed(int curSpeed)
{
    // remove 5 from the sorting unless curSpeed <= 5
    if (curSpeed <= 5)
        return curSpeed;

    std::cout << curSpeed - 5 << std::endl;
    return curSpeed -= 5;
}

