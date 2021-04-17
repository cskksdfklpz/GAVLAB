#ifndef CINTEGRATOR_HPP
#define CINTEGRATOR_HPP

class CSolar;

/** 
 * Integrator class to calculate the trajectory
 * of the object. This is a base class. Each
 * implementation should be a derived class.
*/
class CIntegrator {
   protected:
    double DT;

   public:
    virtual void Update(CSolar &S) = 0;
    void SetDT(double dt) { DT = dt; }
    double GetDT() const { return DT; }
};

/** 
 * SI2, see README.md for detail
*/
class CSI2 : public CIntegrator {
   public:
    virtual void Update(CSolar &S);
};

/** 
 * SI4, see README.md for detail
*/
class CSI4 : public CIntegrator {
   public:
    virtual void Update(CSolar &S);
};

/** 
 * SI6, see README.md for detail
*/
class CSI6 : public CIntegrator {
   public:
    virtual void Update(CSolar &S);
};

#endif