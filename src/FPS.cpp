#include"FPS.h"

using crustgames::FPS;

void FPS::Show() {
    frame_++;
}

int FPS::Get() {
    if (frame_ < 60) {
        return fps_;
    }
    fps_ = (double)frame_ / (clock_.getElapsedTime().asMilliseconds() / 1000.);
    clock_.restart();
    frame_ = 0;
    return fps_;
}