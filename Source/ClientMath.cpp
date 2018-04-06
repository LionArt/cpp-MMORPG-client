#include "ClientMath.hpp"

namespace clientMath
{
    void calcDimResolutionMod (int &mod, int &lightMod)
    {
        if(std::min(VideoSettings::CurrentVideoMode.width,VideoSettings::CurrentVideoMode.height)<=272)
        mod=1;
        else if(std::min(VideoSettings::CurrentVideoMode.width,VideoSettings::CurrentVideoMode.height)<=320)
        mod=2;
        else
        mod=3;
        if(mod==1)
        lightMod=0;
        else
        lightMod=1;
    }

    sf::Vector2f scaleWithResolution(sf::Vector2f percentagePosition,int modX, int modY)
    {
       return sf::Vector2f(round((float(VideoSettings::CurrentVideoMode.width)/100)*(percentagePosition.x))+modX,round((float(VideoSettings::CurrentVideoMode.height)/100)*(percentagePosition.y))+modY);
    }

    int scaleFontSize (int height,float p)
    {
        int a=round(float(height)/100*p);
        return a;
    }

    sf::Color calcColorChange(sf::Color color, int r,int g,int b,int a)
    {
        sf::Color result=sf::Color();
        if((color.r+r)>255)
        result.r=255;
        else if((color.r+r)<0)
        result.r=0;
        else
        result.r=color.r+r;

        if((color.g+g)>255)
        result.g=255;
        else if((color.g+g)<0)
        result.g=0;
        else
        result.g=color.g+g;

        if((color.b+b)>255)
        result.b=255;
        else if((color.b+b)<0)
        result.b=0;
        else
        result.b=color.b+b;

        if((color.a+a)>255)
        result.a=255;
        else if((color.a+a)<0)
        result.a=0;
        else
        result.a=color.a+a;

        return result;
    }
}
