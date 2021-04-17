#ifndef C_CONTROL_HPP
#define C_CONTROL_HPP

/** 
 * Controller class to handle all the control problems.
 * Including keyboard, mouse, change state of the system
*/
class CControl{
public:
    
    static void UpdateState();
    static void keyboard(unsigned char key, int x, int y);
    static void motion(int x, int y);
    static void mouse(int button, int state, int x, int y);
    static void init();
    static void initSolar();
    static void SetSolarManually();
    static void AddNewPlanet();
    static void AddRandomPlanet();
    static void Terminate();
    
private:
    
    static bool ShowRecord;
    static bool play;
    static int prev_mouse_x, prev_mouse_y;
    static double E_init;
    
    friend void init();
    friend class CDisplay;

};

#endif