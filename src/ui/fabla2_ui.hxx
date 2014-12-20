
#ifndef OPENAV_AVTK_TEST_UI_HXX
#define OPENAV_AVTK_TEST_UI_HXX

#include "avtk.hxx"

#include "../shared.hxx"
#include "pad.hxx"

// for write_function and controller
#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"

namespace Avtk
{
  class Widget;
};

#define UI_ATOM_BUF_SIZE 128

class TestUI : public Avtk::UI
{
  public:
    /// Set a NativeWindow for embedding: ignore for standalone 
    TestUI(PuglNativeWindow parent = 0);
    
    /// init function, called by LV2 UI wrapper after setting map, forge etc
    void init()
    {
      setBank( 0 );
      requestSampleState( 0, 0, 0 );
    }
    
    /// widget value callback
    void widgetValueCB( Avtk::Widget* widget);
    
    
    // always visible widgets
    // L
    Avtk::Widget* bankBtns[4];
    Avtk::Widget* recordOverPad;
    
    Avtk::Button* followPadBtn;
    
    Avtk::Dial* masterPitch;
    
    // R
    Avtk::Widget* masterVolume;
    
    
    // sample edit view
    Avtk::Number* muteGroup;
    Avtk::List* layers;
    Avtk::Widget* adsr;
    Avtk::Widget* filt1;
    Avtk::Widget* filt2;
    Avtk::Widget* bitcrusDist;
    Avtk::Widget* eq;
    Avtk::Widget* comp;
    Avtk::Widget* gainPitch;
    Avtk::Dial* sampleGain;
    Avtk::Dial* samplePan;
    Avtk::Dial* samplePitch;
    Avtk::Dial* sampleStartPoint;
    
    Avtk::Widget* padSends;
    Avtk::Widget* padMaster;
    
    // Preset loading screen
    /*
    Avtk::List* list;
    Avtk::List* list2;
    */
    
    // shared between views!
    Avtk::Waveform* waveform;
    
    Avtk::Widget* loadSampleBtn;
    
    void padEvent( int bank, int pad, int layer, bool noteOn, int velocity );
    
    Avtk::Pad* pads[16];
    
    // LV2 ports
    LV2UI_Controller controller;
    LV2UI_Write_Function write_function;
    
    // LV2 Atom
    URIs uris;
    LV2_URID_Map* map;
    LV2_Atom_Forge forge;
  
  private:
    /// followPad allows the UI to update to the last played PAD.
    bool followPad;
    
    int currentBank;
    int currentPad;
    int currentLayer;
    /// updates the UI to a specifc bank
    void setBank( int bank );
    /// writes event/value identified by eventURI using currentBank / currentPad
    void writeAtom( int eventURI, float value );
    /// request the state of a sample from the DSP, to show in the UI
    void requestSampleState( int bank, int pad, int layer );
};


#endif // OPENAV_AVTK_TEST_UI_HXX
