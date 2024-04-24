#ifndef MAIN_H
#define MAIN_H

#include <iostream>

class State; // Forward declaration

class MDAEFSM {
    State *s;
    State *LS[8];
  public:
    void Activate();
    void Start();
    void PayType(int t);
    void Reject();
    void Cancel();
    void Approved();
    void StartPump();
    void Pump();
    void StopPump();
    void SelectGas(int g);
    void Receipt();
    void NoReceipt();
    void Continue();
    void ChangeState(int x);
};

class State {
    MDAEFSM *p;
  public:
    virtual void Activate();
    virtual void Start();
    virtual void PayType(int t);
    virtual void Reject();
    virtual void Cancel();
    virtual void Approved();
    virtual void StartPump();
    virtual void Pump();
    virtual void StopPump();
    virtual void SelectGas(int g);
    virtual void Receipt();
    virtual void NoReceipt();
    virtual void Continue();
};

class Start : public State {
  public:
    void Activate() override;
};

class S0 : public State {
  public:
    void Start() override;
};

class S1 : public State {
  public:
    void PayType(int t) override;
};

class S2 : public State {
  public:
    void Reject() override;
    void Approved() override;
};

class S3 : public State {
  public:
    void Cancel() override;
    void Continue() override;
    void SelectGas(int g) override;
};

class S4 : public State {
  public:
    void StartPump() override;
};

class S5 : public State {
  public:
    void Pump() override;
    void StopPump() override;
};

class S6 : public State {
  public:
    void NoReceipt() override;
    void Receipt() override;
};

class DataStore {
  public:
};

class DataStore1 : public DataStore {
  public:
    int temp_a;
    int price;
    int L;
    int total;
    int temp_cash;
    int w;
    int cash;
};

class DataStore2 : public DataStore {
  public:
    float temp_a;
    float temp_b;
    float temp_c;
    int temp_cash;
    float Dprice;
    float Rprice;
    float Pprice;
    int cash;
    int total;
    int G;
    float price;
};

class GP1 {
    MDAEFSM *m;
    DataStore *d;
  public:
    GP1(DataStore1 *ds);
    void Activate(int a);
    void Start();
    void PayCredit();
    void Reject();
    void Cancel();
    void Approved();
    void PayCash(int c);
    void StartPump();
    void Pump();
    void StopPump();
};

class GP2 {
    MDAEFSM *m;
    DataStore *d;
  public:
    GP2(DataStore2 *ds);
    void Activate(float a, float b, float c);
    void Start();
    void PayCash(int c);
    void Cancel();
    void Premium();
    void Regular();
    void Diesel();
    void StartPump();
    void PumpGallon();
    void Stop();
    void Receipt();
    void NoReceipt();
};

#endif /* MAIN_H */
