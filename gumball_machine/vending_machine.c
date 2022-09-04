#include "vending_machine.h"

void initialize_machine(vending_machine *machine){
    machine->balance = 0;
    machine->penny_count = 0;
    machine->nickel_count = 0;
    machine->dime_count = 0;
    machine->quarter_count = 0;
}

void insert_coin(char coin_type, vending_machine *machine){
    switch (coin_type)
    {
    /* Valid Currency */
    case 'N':
        machine->balance += NICKEL;
        break;
    case 'D':
        machine->balance += DIME;
        break;
    case 'Q':
        machine->balance += QUARTER;
        break;
    /* Invalid Currency */
    case 'P': 
        machine->penny_count++;
        break;
    default:
        break;
    }
}

uint8_t dispense_item(char color, vending_machine *machine){
    uint8_t result = FALSE;
    switch (color)
    {
    case 'R':
        if(machine->balance >= 5){
            machine->balance -= NICKEL;
            // printf("\nRed gumball dispensed.\n");
            result = TRUE;
        }
        break;
    case 'Y':
        if(machine->balance >= 10){
            machine->balance -= DIME;
            // printf("\nYellow gumball dispensed.\n");
            result = TRUE;
        }
    default:
        break;
    }
    #if NOT_TESTING
    printf("\n%c gumball dispensed.\n", color);
    #endif
    return result;
}

uint8_t return_change(vending_machine *machine){
    uint8_t change = machine->balance;
    #if NOT_TESTING
    printf("\nChange Returned: %u cents", change); // Does invalid currency count as change?
    // if(change >= 25){
    //     machine->quarter_count = change / QUARTER;
    //     change = change - (machine->quarter_count * QUARTER);
    // }
    // if(change >= 10){
    //     machine->dime_count = change / DIME;
    //     change = change - (machine->dime_count * DIME);
    // }
    // if(change >= 5){
    //     machine->nickel_count = change / NICKEL;
    // }
    printf("\nQuarters: %u \nDimes: %u \nNickels: %u", machine->quarter_count, machine->dime_count, machine->nickel_count);
    printf("\n\nInvalid currency returned:\nPennies: %u\n\n", machine->penny_count);
    #endif
    machine->balance = 0;
    machine->penny_count = 0;
    return change;
}

uint8_t return_invalid_currency(vending_machine *machine){
    return machine->penny_count;
}


uint8_t quarter_count_change( vending_machine *machine){
    if(machine->balance >= 25){
    machine->quarter_count = machine->balance / QUARTER;
    machine->balance = machine->balance - (machine->quarter_count * QUARTER);
    return machine->quarter_count;
    }
    return 0;
}
uint8_t dime_count_change( vending_machine *machine){
    if(machine->balance >= 10){
    machine->dime_count = machine->balance / DIME;
    machine->balance = machine->balance - (machine->dime_count * DIME);
    return machine->dime_count;
    }
    return 0;
}
uint8_t nickel_count_change( vending_machine *machine){
    if(machine->balance >= 5){
    machine->nickel_count = machine->balance / NICKEL;
    machine->balance = machine->balance - (machine->nickel_count * NICKEL);
    return machine->nickel_count;
    }
    return 0;
}

void return_change2(vending_machine *machine){
    printf("\nQuarters: %u \nDimes: %u \nNickels: %u", quarter_count_change(machine), dime_count_change(machine), nickel_count_change(machine));
    printf("\n\nInvalid currency returned:\nPennies: %u\n\n", machine->penny_count);
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

void set_gumball_penny(uint8_t input, vending_machine *machine){
    machine->penny_count = input;
}