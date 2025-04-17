#ifndef POSSIBLE_EVENTS_H
#define POSSIBLE_EVENTS_H

#include <utility>

class PossibleEvents{

    int convincentPitch;
    int productsBugs;
    int userTrack;
    int angryInvestor;
    int pitchFakeNews;

    public:

        PossibleEvents();
        ~PossibleEvents();

        void setConvincentPitch();
        void setProductsBugs(); 
        void setUserTrack();
        void setAngryInvestor();
        void setPitchFakeNews();

        void cleanBools();
        
        int getConvincentPitch(); 
        int getProductsBugs(); 
        int getUserTrack();
        int getAngryInvestor();
        int getPitchFakeNews();

};

#endif