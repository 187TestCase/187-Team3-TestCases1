#pragma once 

#include "stdio.h"
#include "stdint.h"

#define TRUE        (1u)
#define FALSE       (0u)

#define NICKEL      (5u)
#define DIME        (10u)
#define QUARTER     (25u)

typedef struct {
    /* Balance is in cents */
    uint16_t balance;

    /* Valid Currency */
    uint8_t nickel_count;
    uint8_t dime_count;
    uint8_t quarter_count;

    /* Ivalid Currency */
    uint8_t penny_count;

} vending_machine;

void initialize_machine(vending_machine *machine);
void reset_machine(vending_machine *machine);

uint8_t insert_coin(char coin_type, vending_machine *machine);

uint8_t dispense_item(char color, vending_machine *machine);

uint8_t return_change(vending_machine *machine);

uint8_t return_invalid_currency(vending_machine *machine);

void print_interface(vending_machine *machine);

void set_gumball_balance(uint8_t input, vending_machine *machine);

uint8_t get_nickel_count(vending_machine *machine);

uint8_t get_dime_count(vending_machine *machine);

uint8_t get_quarter_count(vending_machine *machine);

void set_gumball_nickel( uint8_t count, vending_machine *machine);

void set_gumball_dime( uint8_t count, vending_machine *machine);

void set_gumball_quarter( uint8_t count, vending_machine *machine);