#ifndef Module_H
#define Module_H

class Module
{
  public:
    virtual void setup();
    virtual void loop();
    int getNextModule();
    void setNextModule(int module);
    boolean isInit();
    void setInit(int rinit);
  private:
    boolean init;
    int nextModule;
};

#endif

