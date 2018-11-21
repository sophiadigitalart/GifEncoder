//
//  ofxGifEncoder.h
//  ofxGifEncoder
//
//  Created by Jesus Gollonet on 3/20/11.
// http://github.com/jesusgollonet/ofxGifEncoder
// adapted threaded saving, events, error checking and frame managing from Nick Hardeman.
// http://github.com/NickHardeman/ofxGifEncoder/tree/threaded
// Thanks!
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include "cinder/Json.h"

#include "FreeImage.h"
#include "GifDitherTypes.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

class GifEncoder {
    public:
    
        typedef struct {
            unsigned char * pixels;
            int width;
            int height;
            float duration;  // seconds
            int bitsPerPixel;
        } GifFrame;
        
        GifEncoder();
    
        void setup(int _w, int _h, float _frameDuration = 0.1f, int _nColors = 256 );
        void setNumColors(int _nColors = 256);
        void setDitherMode(int _ditherMode = GIF_DITHER_FS);
        void setFrameDuration(float _duration); // for all gifs;
        
        //static ofEvent<string>	GIF_SAVE_FINISHED;

        // thread saving
        // blocking, verbose
        //void start() {startThread(true);}
        //void stop() {stopThread();}
        void exit();
		void reset();
        
        // if no duration is specified, we'll use default (from setup())
        void addFrame(ci::gl::Texture2dRef image, float duration = 0.f);
		void addFrame(unsigned char * px, int _w, int _h, int _bitsPerPixel = 24, float duration = 0.f);
		//void addFramePx(ofPixels * px, int _w, int _h, int _bitsPerPixel = 24, float duration = 0.f);

        static GifFrame * createGifFrame(unsigned char * px, int _w, int _h, int _bitsPerPixel = 24, float duration = 0.1f);
        void save(string _fileName = "test.gif" );
    private:
        void calculatePalette(FIBITMAP * bmp);
        int getClosestToGreenScreenPaletteColorIndex();
        Color greenScreenColor;
        vector <Color> palette;
        GifFrame * convertTo24BitsWithGreenScreen(GifFrame * frame);
        void processFrame(GifFrame * frame, FIMULTIBITMAP * multi);
        void swapRgb(GifFrame * pix);
        //void threadedFunction();
        void doSave();
        bool bSaving;

        vector <GifFrame *> frames;
        string  fileName;
        int     nColors;
        float   frameDuration;
        int w;
        int h;
        int bitsPerPixel;
        int nChannels;
        int ditherMode;
    
    
};

