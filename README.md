# 2024 Spring CS586 Project

# Gas Pump System

## Project Overview

This project comprises several classes and functions implementing various design patterns, including the State Pattern, Strategy Pattern, and Abstract Factory Pattern.

### Classes and Functions about State Pattern

Please refer to lines 6 to 270 in main.cpp and lines 44 to 159 in main.h. These sections include the following classes related to the State Pattern:

1. Manages state transitions and operations of the gas pump: MDAEFSM.

2. Abstract base class defining the interface for gas pump states: State.

3. Concrete states representing various states of the gas pump: Start, S0, S1, S2, S3, S4, S5, S6.

### Classes and Functions about Strategy Pattern

Please refer to lines 172 to 605 in main.cpp and lines 161 to 446 in main.h. These sections include the following classes related to the Strategy Pattern:

1. Abstract base class defining interfaces for various strategies related to gas pump operations: StorePrices, PayMsg, StoreCash, DisplayMenu, RejectMsg, SetPrice, SetInitValues, PumpGasUnit, GasPumpedMsg, PrintReceipt, CancelMsg, ReturnCash, SetPayType, EjectCard.

2. Classes defining interfaces and concrete implementations for various strategies related to gas pump operations: StorePrices1, PayMsg1, StoreCash1, DisplayMenu1, RejectMsg1, SetPrice1, SetInitValues1, PumpGasUnit1, GasPumpedMsg1, PrintReceipt1, CancelMsg1, ReturnCash1, SetPayType1, EjectCard1.

3. Classes defining interfaces and concrete implementations for various strategies related to gas pump operations: StorePrices2, PayMsg2, StoreCash2, DisplayMenu2, RejectMsg2, SetPrice2, SetInitValues2, PumpGasUnit2, GasPumpedMsg2, PrintReceipt2, CancelMsg2, ReturnCash2, SetPayType2, EjectCard2.

### Classes and Functions about Abstract Factory Pattern

Please refer to lines 607 to 1035 in main.cpp and lines 448 to 515 in main.h. These sections include the following classes related to the Abstract Factory Pattern:

1. Abstract base class defining the interface for creating families of related objects: AbstractFactory.

2. Concrete implementations of the abstract factory for different types of gas pumps: ConcreteFactory1, ConcreteFactory2.

## Start the program

### step 1

```
clang++ -std=c++11 -o my_program main.cpp
```

### step 2

```
\./my_program
```
