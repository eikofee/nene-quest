#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED

#include <string>
#include <vector>

// Something that happens once the camera has scrolled `distance` pixels.
//   - "scroll": the camera now moves at `value` pixels/second (0 stops it)
//   - anything else is spawned just past the right edge of the screen, so
//     the camera scrolls onto it, with `value` as its y position:
//     "boar", "dragon", "chest", "barrel", "onigiri", "axe", "sword",
//     "greatsword" and "bow" (the last four are weapons to pick up)
struct LevelEvent {
    float distance;  // Pixels
    std::string what;
    float value;
};

class Level {
   public:
    Level(std::vector<LevelEvent> events);
    // Fires every event the camera has reached since the last call
    void update();

   private:
    std::vector<LevelEvent> events;  // Sorted by distance
    std::size_t next = 0;            // The first event not fired yet

    void fire(const LevelEvent &event);
};

extern const std::vector<LevelEvent> level0;

#endif
