#ifndef POSSIBLE_EVENTS_H
#define POSSIBLE_EVENTS_H

#define CONVINCENT_PITCH 6
#define PRODUCTS_BUGS    (-4)
#define USER_TRACK       3
#define ANGRY_INVESTOR   (-6)
#define PITCH_FAKE_NEWS  (-8)

#include <iostream>
#include <utility>

class PossibleEvents{

    std::pair<bool, int> convincentPitch;
    std::pair<bool, int> productsBugs;
    std::pair<bool, int> userTrack;
    std::pair<bool, int> angryInvestor;
    std::pair<bool, int> pitchFakeNews;

    public:

        PossibleEvents();
        ~PossibleEvents();

        void setConvincentPitch();
        void setProductsBugs(); 
        void setUserTrack();
        void setAngryInvestor();
        void setPitchFakeNews();

        void cleanBools();
        int valueEvents();
        
        std::pair<bool, int> getConvincentPitch(); 
        std::pair<bool, int> getProductsBugs(); 
        std::pair<bool, int> getUserTrack();
        std::pair<bool, int> getAngryInvestor();
        std::pair<bool, int> getPitchFakeNews();

};

#endif