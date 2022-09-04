#include "vending_machine.h"

void initialize_machine(vending_machine *machine){
    machine->balance = 0;
    machine->penny_count = 0;
    machine->nickel_count = 0;
    machine->dime_count = 0;
    machine->quarter_count = 0;
}

void reset_machine(vending_machine *machine){
    machine->balance = 0;
    machine->penny_count = 0;
    machine->nickel_count = 0;
    machine->dime_count = 0;
    machine->quarter_count = 0;
}

uint8_t insert_coin(char coin_type, vending_machine *machine){
    uint8_t result = FALSE;
    switch (coin_type)
    {
    /* Valid Currency */
    case 'N':
        if( machine->nickel_count < 255){
            machine->nickel_count++;
            machine->balance += NICKEL;
            result = TRUE;
        }
        break;
    case 'D':
        if(machine->dime_count < 255){
            machine->dime_count++;
            machine->balance += DIME;
            result = TRUE;
        }
        break;
    case 'Q':
        if(machine->quarter_count < 255){
            machine->quarter_count++;
            machine->balance += QUARTER;
            result = TRUE;
        }
        break;
    /* Invalid Currency */
    case 'P': 
        if(machine->penny_count < 255){        
            machine->penny_count++;
            result = TRUE;
        }
        break;
    default:
        break;
    }
    return result;
}

uint8_t dispense_item(char color, vending_machine *machine){
    uint8_t result = FALSE;
    switch (color)
    {
    case 'R':
        /* Dispense Red gumball only if there's enough credit */
        if(machine->balance >= 5){
            machine->balance -= NICKEL;
            result = TRUE;
        }
        break;
    case 'Y':
        /* Dispense Yellow gumball only if there's enough credit */
        if(machine->balance >= 10){
            machine->balance -= DIME;
            result = TRUE;
        }
    default:
        break;
    }
    return result;
}

uint8_t return_change(vending_machine *machine){
    uint8_t change = machine->balance;
    if(machine->balance >= 25){
        machine->quarter_count = machine->balance / QUARTER;
        machine->balance = machine->balance - (machine->quarter_count * QUARTER);
    }
    if(machine->balance >= 10){
        machine->dime_count = machine->balance / DIME;
        machine->balance = machine->balance - (machine->dime_count * DIME);
    }
    if(machine->balance >= 5){
        machine->nickel_count = machine->balance / NICKEL;
        machine->balance = machine->balance - (machine->nickel_count * NICKEL);
    }
    machine->balance = 0;
    return change;
}

uint8_t return_invalid_currency(vending_machine *machine){
    uint8_t pennies = machine->penny_count;
    machine->penny_count = 0;
    return pennies;
}

void print_interface(vending_machine *machine){
    printf("\n**************************************");
    printf("\nGumball Machine v1.0");
    printf("\nCurrent Balance: %u cents", machine->balance);
    printf("\n\n-Enter R for Red gumball. Price: 5 cents\n-Enter Y for Yellow gumball. Price: 10 cents");
    printf("\n\nEnter coins( N, D, Q) for credit. Pennies (P) are invalid currency");
    printf("\nTo dispense change and exit enter X");
    printf("\n**************************************\n\n");
}

void set_gumball_balance(uint8_t input, vending_machine *machine){
    machine->balance = input;
}

uint8_t get_nickel_count(vending_machine *machine){
    return machine->nickel_count;
}

uint8_t get_dime_count(vending_machine *machine){
    return machine->dime_count;
}

uint8_t get_quarter_count(vending_machine *machine){
    return machine->quarter_count;
}

void set_gumball_nickel( uint8_t count, vending_machine *machine){
    machine->nickel_count = count;
}

void set_gumball_dime( uint8_t count, vending_machine *machine){
    machine->dime_count = count;
}

void set_gumball_quarter( uint8_t count, vending_machine *machine){
    machine->quarter_count = count;
}